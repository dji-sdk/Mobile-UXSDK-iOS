//
//  stickViewController.swift
//  UXSDKSwiftSample
//
//  Created by Andreas Gising on 2020-08-20.
//  Copyright © 2020 DJI. All rights reserved.
//

import UIKit
import DJIUXSDK


public class SticksViewController: DUXDefaultLayoutViewController {
    
    var flightController: DJIFlightController?
    
    var x: Float = 0.0
    var y: Float = 0.0
    var z: Float = 0.0
    var yaw: Float = 0.0
    var yawSpeed: Float = 30.0
    
    var timer: Timer?
    let sampleTime: Double = 50     // Sample time in ms
    let controlPeriod: Double = 1000 // Number of millliseconds to send command
    var loopCnt: Int = 0
    var loopTarget: Int = 0
    
    var horizontalSpeed: Float = 50 // cm/s horizontal speed
    
    
    @IBOutlet weak var controlPeriodLabel: UILabel!
    @IBOutlet weak var horizontalSpeedLabel: UILabel!
        
    @IBOutlet weak var controlPeriodStepperButton: UIStepper!
    @IBOutlet weak var horizontalSpeedStepperButton: UIStepper!
    
    // IBOutlets
    @IBOutlet weak var DeactivateSticksButton: UIButton!
    @IBOutlet weak var ActivateSticksButton: UIButton!
    @IBOutlet weak var DuttLeftButton: UIButton!
    @IBOutlet weak var DuttRightButton: UIButton!
    
    
    
    
    // Functions
    // Disable button and change colormode
    func disableButton(_ button: UIButton!){
        button.isEnabled = false
        button.backgroundColor = UIColor.lightGray
    }
    
    //DuttRightImageView.backgroundColor = UIColor.lightGray
    
    // Enable button and change colormode
    func enableButton(_ button: UIButton!){
        button.isEnabled = true
        button.backgroundColor = UIColor.systemBlue
    }

  
    // Deactivate the sticks and disable dutt buttons
    func deactivateSticks(){
        print("This is the function for deactivating sticks")
        DeactivateSticksButton.backgroundColor = UIColor.lightGray
        //ActivateSticksButton.layer.removeAllAnimations()
        ActivateSticksButton.backgroundColor = UIColor.systemBlue
        //ActivateSticksButton.setTitle("Activate Sticks", for: .normal)
        DeactivateSticksButton.backgroundColor = UIColor.lightGray
        
        disableButton(DuttLeftButton)
        disableButton(DuttRightButton)
        
        self.timer?.invalidate()
        loopCnt = 0
      // Set flight controller mode
         self.flightController?.setVirtualStickModeEnabled(false, withCompletion: { (error: Error?) in
             // If there's an error let's stop
             guard error == nil else { return }
             print("Virtual stick mode change error (BAD). trying to set to false")
         })
    }
    
    func deactivateJoystickMode(){
    }
    
    func activateSticks(){
        print("This is the function for activationg sticks")
        //ActivateSticksButton.flash(duration: 1.5)
        //ActivateSticksButton.setTitle("Sticks Active!", for: .normal)
        ActivateSticksButton.backgroundColor = UIColor.lightGray
        DeactivateSticksButton.backgroundColor = UIColor.systemRed

        enableButton(DuttLeftButton)
        enableButton(DuttRightButton)
        
        x = 0
        y = 0
        z = 0
        yaw = 0
        
        // Set flight controller mode
       self.flightController?.setVirtualStickModeEnabled(true, withCompletion: { (error: Error?) in
           // If there's an error let's stop
           guard error == nil else { return }
           print("Virtual stick mode change error (BAD). trying to set to true")
       })
    }
    
   
    override public func viewDidLoad() {
        super.viewDidLoad()
    
        // Init variables
        loopTarget = Int(controlPeriod / sampleTime)
        
        controlPeriodStepperButton.value = controlPeriod
        controlPeriodLabel.text = String(controlPeriod/1000)
        horizontalSpeedStepperButton.value = Double(horizontalSpeed)
        horizontalSpeedLabel.text = String(horizontalSpeed/100)
        
        // Set up layout
        let radius: CGFloat = 5
        // Do any additional setup after loading the view.
        // Set corner radiuses to buttons
        DeactivateSticksButton.layer.cornerRadius = radius
        ActivateSticksButton.layer.cornerRadius = radius
        DuttLeftButton.layer.cornerRadius = radius
        DuttRightButton.layer.cornerRadius = radius
        
        // Indicate to user what not to push
        DeactivateSticksButton.backgroundColor = UIColor.lightGray
        disableButton(DuttLeftButton)
        disableButton(DuttRightButton)
        
        // Setup aircraft
        // Grab a reference to the aircraft
        if let aircraft = DJISDKManager.product() as? DJIAircraft {
            
            // Grab a reference to the flight controller
            if let fc = aircraft.flightController {
                
                // Store the flightController
                self.flightController = fc
                
                print("We have a reference to the FC")
                
                // Ref https://developer.dji.com/api-reference/ios-api/Components/FlightController/DJIFlightController.html#djiflightcontroller_djivirtualstickyawcontrolmode_inline
                // Default the coordinate system to body and reference yaw to heading
                self.flightController?.rollPitchCoordinateSystem = DJIVirtualStickFlightCoordinateSystem.body
                self.flightController?.setFlightOrientationMode(DJIFlightOrientationMode.aircraftHeading, withCompletion: { (error: Error?) in
                    print("Error when setting OrientationMode")
                })

                // Default roll/pitch control mode to velocity
                self.flightController?.rollPitchControlMode = DJIVirtualStickRollPitchControlMode.velocity
                                
                // Set control modes
                self.flightController?.yawControlMode = DJIVirtualStickYawControlMode.angularVelocity
                
            }
            
        }
    }
    
    
    // Actions
    
    
    
 
    
    
    @IBAction func controlPeriodStepper(_ sender: UIStepper) {
        controlPeriodLabel.text = String(sender.value/1000)
        loopTarget = Int(sender.value / sampleTime)
    }
    
    
    @IBAction func horizontalSpeedStepper(_ sender: UIStepper) {
        horizontalSpeedLabel.text = String(sender.value/100)
        horizontalSpeed = Float(sender.value)
    }
    
    // Exit view, but first deactivate Sticks
    @IBAction func xclose(_ sender: UIButton) {
        print("TODO Deactivate sticks")
        deactivateSticks()
        self.timer?.invalidate()
        self.dismiss(animated: true, completion: nil)
    }
    
    // DeactivateSticks: Touch down action, deactivate immidiately and reset ActivateSticks button color
    @IBAction func DeactivateSticksPressed(_ sender: UIButton) {
        deactivateSticks()
        sendControlData(x: 0, y: 0, z: 0, yaw: 0)
    }
    
    // ActivateSticks: Touch down up inside action, ativate when ready (release of button)
    @IBAction func ActivateSticksPressed(_ sender: UIButton) {
        activateSticks()
        
    }
    
    @IBAction func DuttRightPressed(_ sender: UIButton) {
        print("Right button pressed")
        // Set the control command
        y = self.horizontalSpeed/100
        // Schedule the timer at 20Hz while the default specified for DJI is between 5 and 25Hz. Timer will execute control commands for a period of time
        self.timer?.invalidate()
        loopCnt = 0
        timer = Timer.scheduledTimer(timeInterval: sampleTime/1000, target: self, selector: #selector(fireTimer), userInfo: nil, repeats: true)
    }
    
    @IBAction func DuttLeftPressed(_ sender: UIButton) {
        print("Left button pressed")
        // Set the control command
        y = -self.horizontalSpeed/100
        // Schedule the timer at 20Hz while the default specified for DJI is between 5 and 25Hz. Timer will execute control commands for a period of time
        self.timer?.invalidate()
        loopCnt = 0
        timer = Timer.scheduledTimer(timeInterval: sampleTime/1000, target: self, selector: #selector(fireTimer), userInfo: nil, repeats: true)
    }
    
    
    
    private func sendControlData(x: Float, y: Float, z: Float, yaw: Float) {
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
    
    @objc func fireTimer() {
        
        loopCnt += 1
        if loopCnt >= loopTarget {
            x = 0
            y = 0
            z = 0
            yaw = 0
            sendControlData(x: x, y: y, z: z, yaw: yaw)
            timer?.invalidate()
            loopCnt = 0
        }
        else {
            sendControlData(x: x, y: y, z: z, yaw: yaw)
        }
        
        
    }
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}


//
//import UIKit
//import DJIUXSDK
//
//public class SticksViewController: UIViewController {
//
//    weak var mapWidget: DUXMapWidget?
//    var mapWidgetController: DUXMapViewController?
//
//
//    override public func viewDidLoad() {
//        super.viewDidLoad()
//        self.setupMapWidget()
//    }
//
//    // MARK: - Setup
//    func setupMapWidget() {
//        self.mapWidgetController = DUXMapViewController()
//        self.mapWidget = self.mapWidgetController?.mapWidget!
//        self.mapWidget?.translatesAutoresizingMaskIntoConstraints = false
//        self.mapWidgetController?.willMove(toParent: self)
//        self.addChild(self.mapWidgetController!)
//        self.view.addSubview(self.mapWidgetController!.mapWidget)
//        self.mapWidgetController?.didMove(toParent: self)
//
//        if let image = UIImage(named: "Lock") {
//            self.mapWidget?.changeAnnotation(of: .eligibleFlyZones, toCustomImage: image, withCenterOffset: CGPoint(x: -8, y: -15));
//        }
//
//        self.mapWidget?.topAnchor.constraint(equalTo: self.view.topAnchor).isActive = true
//        self.mapWidget?.bottomAnchor.constraint(equalTo: self.view.bottomAnchor).isActive = true
//        self.mapWidget?.leadingAnchor.constraint(equalTo: self.view.leadingAnchor).isActive = true
//        self.mapWidget?.trailingAnchor.constraint(equalTo: self.view.trailingAnchor).isActive = true
//
//        self.mapWidget?.setNeedsDisplay()
//        self.view.sendSubviewToBack(self.mapWidget!)
//    }
//
//
//    // MARK: - Actions
//
//
//    @IBAction func myclose(_ sender: UIButton) {
//        self.dismiss(animated: true, completion: nil)
//    }
//
////    @IBAction func close(_ sender: UIButton) {
////        self.dismiss(animated: true, completion: nil)
////    }
//}
