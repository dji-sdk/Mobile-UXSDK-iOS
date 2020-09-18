//
//  AircraftHelper.swift
//  UXSDK-DigMet
//
//  Created by Andreas Gising on 2020-09-11.
//  Copyright © 2020 DJI. All rights reserved.
//

import Foundation
import DJIUXSDK




class Copter {
    var flightController: DJIFlightController?
    var state: DJIFlightControllerState?
    var posX: Double = 0
    var posY: Double = 0
    var posZ: Double = 0
    
    
    var ref_posX: Double = 0
    var ref_posY: Double = 0
    var ref_posZ: Double = 0
    var ref_yaw: Float = 0.0
    
    var ref_velX: Float = 0.0
    var ref_velY: Float = 0.0
    var ref_velZ: Float = 0.0
    var ref_yawRate: Float = 0.0
    
    var xyVelLimit: Float = 250 // cm/s horizontal speed
    var zVelLimit: Float = 100 // cm/s vertical speed
    var yawRateLimit:Float = 10 // deg/s, defensive.

    var pos: CLLocation?
    var startHeading: Double?  // This caused an issue at takeoff. TODO heading must be set for xy control.
    var homeLocation: CLLocation?
    var dssHome: CLLocation?
    var dssHomeHeading: Double?

    
    var _operator: String = "USER"

    var timer: Timer?
    var posCtrlTimer: Timer?
    let sampleTime: Double = 50     // Sample time in ms
    let controlPeriod: Double = 1500 // Number of millliseconds to send command
    var loopCnt: Int = 0
    var loopTarget: Int = 0
    var posCtrlLoopCnt: Int = 0
    var posCtrlLoopTarget: Int = 50
    
    // Init
    //init(controlPeriod: Double, sampleTime: Double){
    init(){
    // Calc number of loops for dutt cycle
        loopTarget = Int(controlPeriod / sampleTime)
        self.state = DJIFlightControllerState()
    }

    //*************************************
    // Start listening for position updates
    func startListenToPos(){
    
        
        guard let locationKey = DJIFlightControllerKey(param: DJIFlightControllerParamAircraftLocation) else {
            NSLog("Couldn't create the key")
            return
        }

        guard let keyManager = DJISDKManager.keyManager() else {
            print("Couldn't get the keyManager, are you registered")
            return
        }
        
        keyManager.startListeningForChanges(on: locationKey, withListener: self, andUpdate: { (oldValue: DJIKeyedValue?, newValue: DJIKeyedValue?) in
            if let checkedNewValue = newValue{
                self.pos = (checkedNewValue.value as! CLLocation)
                guard let home = self.getHomeLocation() else {return}
                guard let checkedStartHeading = self.startHeading else {return}
                
                let lat_diff = self.pos!.coordinate.latitude - home.coordinate.latitude
                let lon_diff = self.pos!.coordinate.longitude - home.coordinate.longitude

                let posN = lat_diff * 1854 * 60
                let posE = lon_diff * 1854 * 60 * cos(home.coordinate.latitude/180*Double.pi)
                let alt = self.pos!.altitude
                
                let alpha = checkedStartHeading/180*Double.pi

                // Coordinate transformation, from (E,N) to (y,x)
                self.posX =  posN * cos(alpha) + posE * sin(alpha)
                self.posY = -posN * sin(alpha) + posE * cos(alpha)
                self.posZ = -alt
                
                NotificationCenter.default.post(name: .didPosUpdate, object: nil)
            }
        })
    }

    //************************************
    // Stop listening for position updates
    func stopListenToPos(){
        guard let locationKey = DJIFlightControllerKey(param: DJIFlightControllerParamAircraftLocation) else {
            NSLog("Couldn't create the key")
            return
        }

        guard let keyManager = DJISDKManager.keyManager() else {
            print("Couldn't get the keyManager, are you registered")
            return
        }
        
        keyManager.stopListening(on: locationKey, ofListener: self)
    
    }
    
    //**************************************
    // Start listen to home position updates
    func startListenToHomePosUpdated(){
        guard let homeKey = DJIFlightControllerKey(param: DJIFlightControllerParamHomeLocation) else {
            NSLog("Couldn't create the key")
            return
        }

        guard let keyManager = DJISDKManager.keyManager() else {
            print("Couldn't get the keyManager, are you registered")
            return
        }
        
        keyManager.startListeningForChanges(on: homeKey, withListener: self, andUpdate: { (oldValue: DJIKeyedValue?, newValue: DJIKeyedValue?) in
            if let checkedNewValue = newValue{
                self.startHeading = self.getHeading()
                self.homeLocation = (checkedNewValue.value as! CLLocation)
                self.startListenToPos()
                print("Home location has been updated, caught by listener")
            }
        })
    }
    
    func saveCurrentPosAsDSSHome(){
        self.dssHomeHeading = getHeading()
        self.dssHome = getCurrentLocation()
    }
    
    //*************************************
    // Get home location as location object
    func getHomeLocation()->CLLocation?{
        // Start listen to home location instead
        guard let locationKey = DJIFlightControllerKey(param: DJIFlightControllerParamHomeLocation) else {
            NSLog("Couldn't create the key")
            return nil
        }

        guard let keyManager = DJISDKManager.keyManager() else {
            print("Couldn't get the keyManager, are you registered")
            return nil
        }
                
        if let locationValue = keyManager.getValueFor(locationKey) {
            let homeLocation = locationValue.value as! CLLocation
            self.homeLocation = homeLocation
            return homeLocation
        }
     return nil
    }
    
    //*************************************
    // Get current location as location object
    func getCurrentLocation()->CLLocation?{
        guard let locationKey = DJIFlightControllerKey(param: DJIFlightControllerParamAircraftLocation) else {
            NSLog("Couldn't create the key")
            return nil
        }

        guard let keyManager = DJISDKManager.keyManager() else {
            print("Couldn't get the keyManager, are you registered")
            return nil
        }
                
        if let locationValue = keyManager.getValueFor(locationKey) {
            let location = locationValue.value as! CLLocation
            return location
        }
     return nil
    }
    
    func getHeading()->Double?{
        guard let headingKey = DJIFlightControllerKey(param: DJIFlightControllerParamCompassHeading) else {
            NSLog("Couldn't create the key")
            return nil
        }

        guard let keyManager = DJISDKManager.keyManager() else {
            print("Couldn't get the keyManager, are you registered")
            return nil
        }
                
        if let headingValue = keyManager.getValueFor(headingKey) {
            let heading = headingValue.value as! Double
            return heading
        }
        return nil
    }
    

    //****************************************
    // Get the isFlying parameter from the DJI
    func getIsFlying()->Bool?{
        guard let flyingKey = DJIFlightControllerKey(param: DJIFlightControllerParamIsFlying) else {
            NSLog("Couldn't create the key")
            return nil
        }

        guard let keyManager = DJISDKManager.keyManager() else {
            print("Couldn't get the keyManager, are you registered")
            return nil
        }
                
        if let flyingValue = keyManager.getValueFor(flyingKey) {
            let flying = flyingValue.value as! Bool
            return flying
        }
        return nil
    }
    
    //
    // Get gimbal pitch
    func getGimbalPitchAtt()->DJIGimbalAttitude?{
        guard let gimbalAttitudeKey = DJIGimbalKey(param: DJIGimbalParamAttitudeInDegrees) else {
            NSLog("Couldn't create the key")
            return nil
        }

        guard let keyManager = DJISDKManager.keyManager() else {
            print("Couldn't get the keyManager, are you registered")
            return nil
        }
                
        if let attitudeValue = keyManager.getValueFor(gimbalAttitudeKey) {
            let attitude = attitudeValue.value as! DJIGimbalAttitude
            return attitude
        }
     return nil
    }
    
    //
    // Get gimbal pitch2
    func getGimbalPitchRot()->DJIGimbalRotation?{
        guard let gimbalRotateKey = DJIGimbalKey(param: DJIGimbalParamRotate) else {
            NSLog("Couldn't create the key")
            return nil
        }

        guard let keyManager = DJISDKManager.keyManager() else {
            print("Couldn't get the keyManager, are you registered")
            return nil
        }
                
        if let rotationValue = keyManager.getValueFor(gimbalRotateKey) {
            let rotation = rotationValue.value as! DJIGimbalRotation
            return rotation
        }
     return nil
    }
    
    
    //****************
    // Tester function
    func stateTest(){
        if let gimbalAttitude = self.getGimbalPitchAtt(){
            print("Gimbal pitch: (ATT)" + String(describing: gimbalAttitude.pitch))
        }
        
        if let gimbalRotation = self.getGimbalPitchRot(){
            print("Gimbal pitch (ROT): " + String(describing: gimbalRotation.pitch))
        }
        
        if let home = self.getHomeLocation(){
            print("Home location lat: " + String(describing: home.coordinate.latitude))
        }

        if let currLocation = self.getCurrentLocation(){
            print("Current location lat: " + String(describing: currLocation.coordinate.latitude))
        }

    }
    
    func getPos(){
        guard let home = getHomeLocation() else {return}
        guard let curr = getCurrentLocation() else {return}
        guard let startHeading = self.startHeading else {return}
        _ = startHeading

        let lat_diff = curr.coordinate.latitude - home.coordinate.latitude
        let lon_diff = curr.coordinate.longitude - home.coordinate.longitude

        let posN = lat_diff * 1854 * 60
        let posE = lon_diff * 1854 * 60 * cos(home.coordinate.latitude)
        let posD = curr.altitude
        
        let distance = curr.distance(from: home).magnitude
        print("posN: " + String(posN) + ", posE: " + String(posE), ", posD: " + String(posD) + ", Distance: " + String(describing: distance))
    }
    
    
    //
    // Get current state
    func getState(){
        
        // The key way.. https://stackoverflow.com/questions/46299244/which-function-is-used-for-get-the-exact-location-of-gps-coordinates-of-dji-dron
        guard let locationKey = DJIFlightControllerKey(param: DJIFlightControllerParamAircraftLocation) else {
            NSLog("Couldn't create the key")
            return
        }
        guard let homeLocationKey = DJIFlightControllerKey(param: DJIFlightControllerParamHomeLocation) else {
            NSLog("Couldn't create the key")
            return
        }

        guard let keyManager = DJISDKManager.keyManager() else {
            print("Couldn't get the keyManager")
            // This will happen if not registered
            return
        }
        
        
        if let locationValue = keyManager.getValueFor(locationKey) {
            let pos_ = locationValue.value as! CLLocation
            // do something
            print(pos_.coordinate.latitude)
        }
        if let locationValue = keyManager.getValueFor(homeLocationKey) {
            let home_ = locationValue.value as! CLLocation
            // do something
            print(home_.coordinate.latitude)
        }
    }
    
    //************************
    // Set up reference frames
    func initFlightController(){
        // Default the coordinate system to body and reference yaw to heading
        self.flightController?.setFlightOrientationMode(DJIFlightOrientationMode.aircraftHeading, withCompletion: { (error: Error?) in
            if error == nil{
                print("Orientation mode set")
            }
            else{
                print("Orientation mode not set: " + error.debugDescription)
            }
        })

        // Set properties of VirtualSticks
        self.flightController?.rollPitchCoordinateSystem = DJIVirtualStickFlightCoordinateSystem.body
        self.flightController?.yawControlMode = DJIVirtualStickYawControlMode.angularVelocity
        self.flightController?.rollPitchControlMode = DJIVirtualStickRollPitchControlMode.velocity
        self.state = DJIFlightControllerState()
        //self.flightController?.delegate?.flightController?(self.flightController!, didUpdate: self.state!)
    }
        
    //***************************************************
    // Limit any stick control command copters limitation
    func limitToMax(value: Float, limit: Float)-> Float{
        // Limit desired velocities to limit
        if value > limit {
            return limit
        }
        else if value < -limit {
            return -limit
        }
        else {
            return value
        }
    }

    //**************************************************************************************************
    // Stop ongoing stick command, invalidate all related timers. TODO: handle all modes, stop is stop..
    func stop(){
        timer?.invalidate()
        posCtrlTimer?.invalidate()
        sendControlData(velX: 0, velY: 0, velZ: 0, yawRate: 0)
    }
    
    //********************************
    // Disable the virtual sticks mode
    func stickDisable(){
        stop()
        self.flightController?.setVirtualStickModeEnabled(false, withCompletion: { (error: Error?) in
            if error == nil{
                print("Sticks disabled")
            }
            else{
                print("StickDisable: Virtual stick mode change did not go through" + error.debugDescription)
            }
        })
    }

    //**************************************************************
    // Enable the virtual sticks mode and reset reference velocities
    func stickEnable(){
        // Reset any speed set, think about YAW -> Todo!
        ref_velX = 0
        ref_velY = 0
        ref_velZ = 0
        //let temp: Double = self.flightController?.compass?.heading   returns optionalDouble, i want Float..
        ref_yaw = 0

        // Set flight controller mode
        self.flightController?.setVirtualStickModeEnabled(true, withCompletion: { (error: Error?) in
            if error == nil{
                print("Sticks enabled")
            }
            else{
                print("StickEnable: Virtual stick mode change did not go through" + error.debugDescription)
            }
        })
    }
    
    func dutt(x: Float, y: Float, z: Float, yawRate: Float){
        // limit to max
        self.ref_velX = limitToMax(value: x, limit: xyVelLimit/100)
        self.ref_velY = limitToMax(value: y, limit: xyVelLimit/100)
        self.ref_velZ = limitToMax(value: z, limit: zVelLimit/100)
        self.ref_yawRate = limitToMax(value: yawRate, limit: yawRateLimit)
        
        // Schedule the timer at 20Hz while the default specified for DJI is between 5 and 25Hz. Timer will execute control commands for a period of time
        posCtrlTimer?.invalidate() // Cancel any posControl
        timer?.invalidate()
        loopCnt = 0
        timer = Timer.scheduledTimer(timeInterval: sampleTime/1000, target: self, selector: #selector(fireTimer), userInfo: nil, repeats: true)
       }
    
    //***************************************************************************************************************
    // Send controller data (joystick). Called from fireTimer that send commands every x ms. Stop timer to stop commands.
    func sendControlData(velX: Float, velY: Float, velZ: Float, yawRate: Float) {
        print("Sending x: \(velX), y: \(velY), z: \(velZ), yaw: \(yawRate)")
       
//        controlData.verticalThrottle = velZ // in m/s
//        controlData.roll = velX
//        controlData.pitch = velY
//        controlData.yaw = yawRate
      
        // Check horizontal spped and reduce both proportionally
        let horizontalVel = sqrt(velX*velX + velY*velY)
        let limitedHorizontalVel = limitToMax(value: horizontalVel, limit: xyVelLimit/100)
        var factor: Float = 1
        if limitedHorizontalVel < horizontalVel{
            factor = limitedHorizontalVel/horizontalVel
        }
        
        // Make sure velocity limits are not exceeded.
        let limitedVelX = factor * velX
        let limitedVelY = factor * velY
        let limitedVelZ = limitToMax(value: velZ, limit: zVelLimit/100)
        let limitedYawRate = limitToMax(value: velX, limit: xyVelLimit/100)
                
        // Construct the flight control data object. Roll axis is pointing forwards but we use velocities..
        print("limitedVelZ: " + String(describing: limitedVelZ) + "is sent to verticalThrottle with negative sign")
        var controlData = DJIVirtualStickFlightControlData()
        controlData.verticalThrottle = -limitedVelZ
        controlData.roll = limitedVelX
        controlData.pitch = limitedVelY
        controlData.yaw = limitedYawRate
        
        
        // Send the control data to the FC
        self.flightController?.send(controlData, withCompletion: { (error: Error?) in
           // There's an error so let's stop (What happens with last sent command..?
            if error != nil {
                print("Error sending control data from position controller")
                // Disable the timer
                self.timer?.invalidate()
                //self.loopCnt = 0
                self.posCtrlTimer?.invalidate()
                //self.posCtrlLoopCnt = 0
            }
           
        })
    }
    
    func takeOff(){
        self.flightController?.startTakeoff(completion: {(error: Error?) in
            if error != nil{
                print("Takeoff error: " + String(error.debugDescription))
            }
            else{
                _ = 1
            }
            
        })
    }
    
    func land(){
        self.flightController?.startLanding(completion: {(error: Error?) in
            if error != nil{
                print("Takeoff error: " + String(error.debugDescription))
            }
            else{
                _ = 1
            }
            
        })
    }
    
    //**********************************************************************************
    // Function that sets reference position and executes the position controller timer.
    func gotoXYZ(refPosX: Double, refPosY: Double, refPosZ: Double){
        // start in Y only
        // Check if horixzontal positions are within geofence  (should X be max 1m?)
        if refPosY > -10 && refPosY < 10{
            self.ref_posY = refPosY
        }
        else if refPosX > -10 && refPosX < 10{
            self.ref_posX = refPosX
        }
        else{
            print("XYZ position is out of allowed area!")
            return
        }
        
        self.ref_posZ = refPosZ
        if self.ref_posZ > -10{
            print("Too low altitude for postion control")
            return
        }
        
        // Schedule the timer at 20Hz while the default specified for DJI is between 5 and 25Hz. Timer will execute control commands for a period of time
        timer?.invalidate()
        //loopCnt = 0
        
        posCtrlTimer?.invalidate()
        posCtrlLoopCnt = 0
        // Make sure noone else is updating the self.refPosXYZ ! TODO
        // Set fix timeinterval
        posCtrlTimer = Timer.scheduledTimer(timeInterval: 0.11, target: self, selector: #selector(firePosCtrlTimer), userInfo: nil, repeats: true)
    }
    
}

extension Copter{
    //************************************************************************************************************
    // Timer function that loops every x ms until timer is invalidated. Each loop control data (joystick) is sent.
   
    @objc func fireTimer() {
        loopCnt += 1
        if loopCnt >= loopTarget {
            sendControlData(velX: 0, velY: 0, velZ: 0, yawRate: 0)
            timer?.invalidate()
            //loopCnt = 0 // More safe to remove..
        }
        else {
            sendControlData(velX: self.ref_velX, velY: self.ref_velY, velZ: self.ref_velZ, yawRate: self.ref_yawRate)
        }
    }
    
    @objc func firePosCtrlTimer() {
        posCtrlLoopCnt += 1
        // If we arrived
        let trackedLimit = 0.1
        if abs(self.ref_posX - self.posX) < trackedLimit && abs(self.ref_posY - self.posY) < trackedLimit && abs(self.ref_posZ - self.posZ) < trackedLimit{
            sendControlData(velX: 0, velY: 0, velZ: 0, yawRate: 0)
            posCtrlTimer?.invalidate()
        }
        // The controller
            
            
        else{
            // Implement P-controller, position error to ref vel. Rotate aka SimpleMode
            let x_diff: Float = Float(self.ref_posX - self.posX)
            let y_diff: Float = Float(self.ref_posY - self.posY)
            let z_diff: Float = Float(self.ref_posZ - self.posZ)
            
            guard let checkedHeading = self.getHeading() else {return}
            guard let checkedStartHeading = self.startHeading else {return}
            let alpha = Float((checkedHeading - checkedStartHeading)/180*Double.pi)
            
            self.ref_velX =  x_diff * cos(alpha) + y_diff * sin(alpha)
            self.ref_velY = -x_diff * sin(alpha) + y_diff * cos(alpha)
            self.ref_velZ = z_diff
            // If velocity get limited the copter will not fly in straight line! Handled in sendControlData
            

            sendControlData(velX: self.ref_velX, velY: self.ref_velY, velZ: self.ref_velZ, yawRate: 0)
        }
        
        // For safety during testing..
        if posCtrlLoopCnt >= posCtrlLoopTarget{
            sendControlData(velX: 0, velY: 0, velZ: 0, yawRate: 0)
            print("FATAL - Position controller had to be interrupted - FATAL")
            posCtrlTimer?.invalidate()
        }
    }
}
