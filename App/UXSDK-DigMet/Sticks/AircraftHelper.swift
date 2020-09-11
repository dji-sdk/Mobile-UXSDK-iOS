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
    
    var ref_x: Float = 0.0
    var ref_y: Float = 0.0
    var ref_z: Float = 0.0
    var ref_yaw: Float = 0.0
    var ref_yawRate: Float = 0.0
    
    var xyVelLimit: Float = 120 // cm/s horizontal speed
    var zVelLimit: Float = 50 // cm/s vertical speed
    var yawRateLimit:Float = 10 // deg/s, defensive.

    var timer: Timer?
    let sampleTime: Double = 50     // Sample time in ms
    let controlPeriod: Double = 1500 // Number of millliseconds to send command
    var loopCnt: Int = 0
    var loopTarget: Int = 0
    
    // Init
    //init(controlPeriod: Double, sampleTime: Double){
    init(){
    // Calc number of loops for dutt cycle
        loopTarget = Int(controlPeriod / sampleTime)
    }

    //************************
    // Set up reference frames
    func initFlightController(){
        // Default the coordinate system to body and reference yaw to heading
        self.flightController?.setFlightOrientationMode(DJIFlightOrientationMode.aircraftHeading, withCompletion: { (error: Error?) in
            print("Error when setting OrientationMode")})

        // Set properties of VirtualSticks
        self.flightController?.rollPitchCoordinateSystem = DJIVirtualStickFlightCoordinateSystem.body
        self.flightController?.yawControlMode = DJIVirtualStickYawControlMode.angularVelocity
        self.flightController?.rollPitchControlMode = DJIVirtualStickRollPitchControlMode.velocity
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

    //*******************************************************************
    // Stop ongoing stick command. TODO: handle all modes, stop is stop..
    func stop(){
        timer?.invalidate()
        loopCnt = 0
        sendControlData(x: 0, y: 0, z: 0, yaw: 0)
    }
    
    //********************************
    // Disable the virtual sticks mode
    func stickDisable(){
        stop()
        self.flightController?.setVirtualStickModeEnabled(false, withCompletion: { (error: Error?) in
            guard error == nil else { return }
                print("Virtual stick mode change did not go through")
        })
    }

    //**************************************************************
    // Enable the virtual sticks mode and reset reference velocities
    func stickEnable(){
        // Reset any speed set, think about YAW -> Todo!
        ref_x = 0
        ref_y = 0
        ref_z = 0
        //let temp: Double = self.flightController?.compass?.heading   returns optionalDouble, i want Float..
        ref_yaw = 0

        // Set flight controller mode
        self.flightController?.setVirtualStickModeEnabled(true, withCompletion: { (error: Error?) in
         guard error == nil else { return }
             print("Virtual stick mode change did not go through")
        })
    }
    
    func dutt(x: Float, y: Float, z: Float, yaw: Float){
        // limit to max
        self.ref_x = limitToMax(value: x, limit: xyVelLimit/100)
        self.ref_y = limitToMax(value: y, limit: xyVelLimit/100)
        self.ref_z = limitToMax(value: z, limit: zVelLimit/100)
        self.ref_yaw = limitToMax(value: yaw, limit: yawRateLimit)
        
        // Schedule the timer at 20Hz while the default specified for DJI is between 5 and 25Hz. Timer will execute control commands for a period of time
        timer?.invalidate()
        loopCnt = 0
        timer = Timer.scheduledTimer(timeInterval: sampleTime/1000, target: self, selector: #selector(fireTimer), userInfo: nil, repeats: true)
       }
    
    //***************************************************************************************************************
    // Send controller data (joystick). Called from fireTimer that send commands every x ms. Stop timer to stop commands.
    func sendControlData(x: Float, y: Float, z: Float, yaw: Float) {
        print("Sending x: \(x), y: \(y), z: \(z), yaw: \(yaw)")
       
        // Construct the flight control data object
        var controlData = DJIVirtualStickFlightControlData()
        controlData.verticalThrottle = z // in m/s
        controlData.roll = x
        controlData.pitch = y
        controlData.yaw = yaw
       
        // Send the control data to the FC
        self.flightController?.send(controlData, withCompletion: { (error: Error?) in
           
           // There's an error so let's stop (What happens with last sent command..?
           if error != nil {
               
               print("Error sending data")
               
               // Disable the timer
            self.timer?.invalidate()
            self.loopCnt = 0
           }
           
       })
   }
}

extension Copter{
    //************************************************************************************************************
    // Timer function that loops every x ms until timer is invalidated. Each loop control data (joystick) is sent.
   
    @objc func fireTimer() {
        loopCnt += 1
        if loopCnt >= loopTarget {
            sendControlData(x: 0, y: 0, z: 0, yaw: 0)
            timer?.invalidate()
            loopCnt = 0
        }
        else {
            sendControlData(x: self.ref_x, y: self.ref_y, z: self.ref_z, yaw: self.ref_yawRate)
        }
    }
}
