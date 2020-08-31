//
//  stickViewController.swift
//  UXSDKSwiftSample
//
//  Created by Andreas Gising on 2020-08-20.
//  Copyright © 2020 DJI. All rights reserved.
//

import UIKit
import DJIUXSDK
import DJIWidget

public class SticksViewController: DUXDefaultLayoutViewController {
    //**********************
    // Variable declarations
    var aircraft: DJIAircraft?
    var flightController: DJIFlightController?
    var camera: DJICamera?
    var gimbal: DJIGimbal?
    //manager?


    var pitchRangeExtension_set: Bool = false
    var nextGimbalPitch: Int = 0
    
    var gimbalcapability: [AnyHashable: Any]? = [:]
    var cameraModeReference: DJICameraMode = DJICameraMode.playback
    var cameraModeAcitve: DJICameraMode = DJICameraMode.shootPhoto
    
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
    
    var image: UIImage = UIImage.init()
    var image_index: UInt?
    //*********************
    // IBOutlet declaration: Labels
    @IBOutlet weak var controlPeriodLabel: UILabel!
    @IBOutlet weak var horizontalSpeedLabel: UILabel!
    
    // IBOutlet declaration: ImageView
    @IBOutlet weak var previewImageView: UIImageView!
    
    // Steppers
    @IBOutlet weak var controlPeriodStepperButton: UIStepper!
    @IBOutlet weak var horizontalSpeedStepperButton: UIStepper!
    
    // Buttons
    @IBOutlet weak var DeactivateSticksButton: UIButton!
    @IBOutlet weak var ActivateSticksButton: UIButton!
    @IBOutlet weak var statusLabel: UILabel!
    @IBOutlet weak var DuttLeftButton: UIButton!
    @IBOutlet weak var DuttRightButton: UIButton!
    
    @IBOutlet weak var savePhotoButton: UIButton!
    
    // Just to test an init function
    required init?(coder aDecoder: NSCoder) {
        self.image_index = 0
        super.init(coder: aDecoder)
    }
    
    //**********************
    // Fucntion declarations
    
    // Disable button and change colormode
    func disableButton(_ button: UIButton!){
        button.isEnabled = false
        button.backgroundColor = UIColor.lightGray
    }
    // Enable button and change colormode
    func enableButton(_ button: UIButton!){
        button.isEnabled = true
        button.backgroundColor = UIColor.systemBlue
    }

    // Deactivate the sticks and disable dutt buttons
    func deactivateSticks(){
        DeactivateSticksButton.backgroundColor = UIColor.lightGray
        ActivateSticksButton.backgroundColor = UIColor.systemBlue
        disableButton(DuttLeftButton)
        disableButton(DuttRightButton)
        // Stop any current movement and reset loop counter
        self.timer?.invalidate()
        loopCnt = 0
        // Set flight controller mode
        self.flightController?.setVirtualStickModeEnabled(false, withCompletion: { (error: Error?) in
            // If there's an error let's stop
            guard error == nil else { return }
                print("Virtual stick mode change did not go through")
        })
    }
      
    // Activate sticks and dutt buttons, reset any velocity references
    func activateSticks(){
        ActivateSticksButton.backgroundColor = UIColor.lightGray
        DeactivateSticksButton.backgroundColor = UIColor.systemRed
        enableButton(DuttLeftButton)
        enableButton(DuttRightButton)
        // Reset any speed set, think about YAW -> Todo!
        x = 0
        y = 0
        z = 0
        //let temp: Double = self.flightController?.compass?.heading   returns optionalDouble, i want Float..
        yaw = 0
        
        // Set flight controller mode
        self.flightController?.setVirtualStickModeEnabled(true, withCompletion: { (error: Error?) in
            // If there's an error let's stop
            guard error == nil else { return }
                print("Virtual stick mode change did not go through")
       })
    }

    // Support function to step through gimbal pitch values
    func updateGnextGimbalPitch(){
        self.nextGimbalPitch -= 20
        if self.nextGimbalPitch < -40 {
            self.nextGimbalPitch = 20
        }
    }
    
    // Set the gimbal pitch value
    func setGimbalPitch(pitch: Int){
        // Check if rangeExtension for gimbal has been set sucessfully
        if self.pitchRangeExtension_set != true{
            statusLabel.text = "Gimbal pitch does not seem to have been updated"
        }
        // Create a DJIGimbalRotaion object
        let gimbal_rotation = DJIGimbalRotation(pitchValue: pitch as NSNumber, rollValue: 0, yawValue: 0, time: 1, mode: DJIGimbalRotationMode.absoluteAngle, ignore: true)
        // Feed rotate object to Gimbal method rotate
        self.gimbal?.rotate(with: gimbal_rotation, completion: { (error: Error?) in
            if error != nil {
                self.statusLabel.text = "Gimbal rotation" + String(describing: error)
            }
        })
    }
        
        
    // Only set camera mode if it is not in shootPhoto, then capture an image
    func captureImage() {
        // Make sure camera is set up: Mode and Shoot mode, if not set it up
        self.camera?.getModeWithCompletion( {(mode, error) in
            if mode != DJICameraMode.shootPhoto {
                self.setUpSinglePhoto()
                // Need a dispatch here?
            }
        })
        // Take a single photo (single since the camera now is set up that way)
        self.camera?.startShootPhoto(completion: { (error) in
            if let _ = error {
                NSLog("Shoot Photo Error: " + String(describing: error))
            }
        })
    }

    // Set camera Mode to shootPhoto and set camera shootPhotoMode to single
    func setUpSinglePhoto(){
        // Set shootMode to shootPhoto
        self.camera?.setMode(DJICameraMode.shootPhoto, withCompletion: {(error) in
            // Wait a bit and then set shootFotoMode to single. Needed? TODO
            DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + 1){
                self.camera?.setShootPhotoMode(DJICameraShootPhotoMode.single, withCompletion: {(error) in
                    if let _ = error {
                        NSLog("Shoot Photo Error: " + String(describing: error))
                    }
                })
            }
        })
    }
    
    // AG building from scratch
    func getLastImage() {
        /***** Get Last Picture *****/

        // check if we can download images with the product
        if !self.camera!.isMediaDownloadModeSupported() {
            print("Product does not support media download mode")
            return
        }

        print("before set mode...")
        let retry = RetryManager() // Run the same block multiple times if the command has an error
        // switch camera mode to allow for media downloads
        retry.runBlock(withRetries: 5) {
            self.camera?.setMode( .mediaDownload, withCompletion: {(error) in

                print("in set mode...")

                if error != nil {

                    print(("\(error!.localizedDescription)"))

                }
                else {
                    retry.stop()
                    // get the media manager from the drone to gain access to the files
                    let manager = self.camera?.mediaManager!

                    manager?.refreshFileList(of: DJICameraStorageLocation.sdCard, withCompletion:  { (error) in

                        print("in refresh file list...")

                        if error != nil {

                            ///////TIMES OUT HERE/////////

                            print("Refresh error State: \(manager?.sdCardFileListState.rawValue)")
                            print("Error refreshing list: \(error!.localizedDescription)")

                        }else {
                            self.statusLabel.text = "Refreshed file list"
                            print("Refreshed file list")
                            print("No error State: \(manager?.sdCardFileListState.rawValue)")

                            // get list of files
                            guard let files = manager?.sdCardFileListSnapshot() else {
                                print("No files to download")
                                return
                            }
                            self.statusLabel.text = "There are files to download"
                            print("There are files to download.. Beginning Download")
                            print(("files \(files.count)"))
                        }
                    }) // end of file-refresh block
                } // end of if else
                retry.proceed()
            })// end of camera setMode block
        }

    }
    
    func my_cameraSetMode(_ newCameraMode: DJICameraMode, completionHandler: @escaping (Bool) -> Void) {
        // Update the cameraModeReferemce, then set mode and confirm that is is correctly set.
        self.cameraModeReference = newCameraMode
        self.camera?.setMode(newCameraMode, withCompletion: {(error) in
            if error != nil {
                self.statusLabel.text = "Error setting CameraMode"
            }
            else {
                self.camera?.getModeWithCompletion( {(mode: DJICameraMode, error: Error?) in
                    if error != nil{
                        self.statusLabel.text = "Error getting Cameramode"
                    }
                    else {
                        self.cameraModeAcitve = mode
                        if self.cameraModeAcitve != self.cameraModeReference{
                            self.statusLabel.text = "Camermode setting failed. Calling my_cameraSetMode again.."
                            completionHandler(false)
                        }
                        else {
                            self.statusLabel.text = "CameraMode has been changed"
                            completionHandler(true)
                        }
                    }
                })
                    
            }
        })
    }
    
    func printSL(_ str: String){
        self.statusLabel.text = str
    }


    func my_getImage(completionHandler: @escaping (Bool) -> Void){
        let manager = self.camera?.mediaManager
        manager?.refreshFileList(of: DJICameraStorageLocation.sdCard, withCompletion: {(error: Error?) in
            self.printSL("Refreshing file list...")
            if error != nil {
                completionHandler(false)
                self.printSL("Refreshing file list failed.")
            }
            else{
                guard let files = manager?.sdCardFileListSnapshot() else {
                    self.printSL("No images on sdCard")
                    completionHandler(true)
                    return
                }
                self.printSL("Files on sdCard: " + String(describing: files.count))
                let index = files.count - 1

                var imageData: Data?
                //var imageSaver: NSObject
                
                files[index].fetchData(withOffset: 0, update: DispatchQueue.main, update: {(_ data: Data?, _ isComplete: Bool, error: Error?) -> Void in
                    if error != nil{
                        // THis happens if download is triggered to close to taking a picture.
                        self.printSL("Er" + String(error!.localizedDescription))
                    }
                    else if isComplete {
                            self.printSL("it isComplete")
                        if let imageData = imageData{
                                let image = UIImage(data: imageData)
                                    self.printSL("Image complete, showing image")
                                    self.previewImageView.image = image
                                    let imageSaverHelper = imageSaver()
                                    imageSaverHelper.writeToPhotoAlbum(image: image!)
                                    //UIImageWriteToSavedPhotosAlbum(image!, nil, nil, nil) https://www.hackingwithswift.com/books/ios-swiftui/how-to-save-images-to-the-users-photo-library
                                }
                            else{
                                    self.printSL("If let NOK")
                            }
                    }
                    else {
                        // If image exists, append the data
                        if let _ = imageData, let data = data {
                            imageData?.append(data)
                            self.printSL("Appending data to image")
                        }
                            // initialize the image data
                        else {
                            imageData = data
                            self.printSL("Initiating a new image")
                        }
                    }
                })
            }
        })
    }
                // Download a preview
                //files[index].fetchPreview(completion: {(error: Error?) in
                //    self.previewImageView.image = files[index].preview
                //    completionHandler(true)
                //})
            
            
                
//                files[index].fetchData(withOffset: 0, update: DispatchQueue.main, update: {(_ data: Data?, _ isComplete: Bool, _ error: Error?) -> Void in
//                        if let error = error {
//                            print("Error: " + String(describing: error))
//                            self.printSL("Downloading image failed, timeout?")
//                        }
//                        else{
//                            if let data = data, let downloadedImage = UIImage(data: data) {
//                                print("Downloaded: " + String(describing: files[index].fileName))
//
//                                // Preview the downloaded image
//                                self.printSL("Trying to preview the image")
//                                self.previewImageView.image = downloadedImage
//
//                                // now that the image is done downloading, move onto the next image
//                                //downloadNextImage(files: files, fileCount: fileCount, index: (index + 1), downloadedFiles: downloadedFiles + [image], errorCount: 0)
//                            }// Download was successful..
//
//                            completionHandler(true)
//                    }
//
//                })
     
    
    
    func my_setUpDownload(){
        // Set mode to download

        if self.cameraModeReference != DJICameraMode.mediaDownload{
            self.cameraModeReference = DJICameraMode.mediaDownload
            self.camera?.setMode(DJICameraMode.mediaDownload, withCompletion: {(error) in
                if error != nil {
                    self.statusLabel.text = "Error setting CameraMode to mediaDownload"
                }
                else {
                    self.camera?.getModeWithCompletion( {(mode: DJICameraMode, error: Error?) in
                        if error != nil{
                            self.statusLabel.text = "Error getting mode"
                        }
                        else {
                            self.cameraModeAcitve = mode
                            if self.cameraModeAcitve != self.cameraModeReference{
                                self.statusLabel.text = "Calling my_setUpDownload again.." // + String(describing: self.cameraModeAcitve.rawValue)
                                self.my_setUpDownload()
                            }
                            else {
                                self.statusLabel.text = "Works like a sharm!"
                            }
                        }
                    })
                        
                }
            })
        }
    }
    

    
    /**
     * This function downloads the N latest images from the drone and passes them to the completionhandler once all images have completed downloading
     */
    func downloadImages(files: [DJIMediaFile], howMany: Int, maxErrors: Int, completion: @escaping ([UIImage]) -> Void){

        print("Queueing.. ")
        
        func downloadNextImage( files: [DJIMediaFile], fileCount: Int, index: Int = 0, downloadedFiles: [UIImage] = [], errorCount: Int = 0) {
            // stop when we reach the end of the list
            if index == fileCount {
                completion(downloadedFiles)
                statusLabel.text = "Finished downloading images"
                return
            }
            else {
                var imageData: Data?
                let file = files[index]
                
                file.fetchData(withOffset: 0, update: DispatchQueue.main, update: {(_ data: Data?, _ isComplete: Bool, _ error: Error?) -> Void in

                    if let error = error {
                        print("Error: " + String(describing: error))
                        if errorCount < maxErrors {
                            DispatchQueue.main.asyncAfter(deadline: .now() + 1) {
                                print("Attempting to download: ") //\(file.fileName) again")
                                self.statusLabel.text = "Attemting to download" + String(describing: index) + " but receiving error, trying again"
                                downloadNextImage(files: files, fileCount: fileCount, index: index, downloadedFiles: downloadedFiles, errorCount: errorCount + 1)
                            }
                        }
                        else {
                            print("Too many errors downloading the images, try downloading again")
                            self.statusLabel.text = "Too many errors downloading. Abort"
                        }
                    }
                    else {
                        // if image is done downloading
                        if isComplete {
                            // get full image data
                            if let imageData = imageData, let image = UIImage(data: imageData) {
                                print("Downloaded: " + String(describing: file.fileName))
                                self.statusLabel.text = "Downloaded: " + String(describing: fileCount)
                                
                                // Preview the downloaded image
                                self.previewImageView.image = image

                                // now that the image is done downloading, move onto the next image
                                downloadNextImage(files: files, fileCount: fileCount, index: (index + 1), downloadedFiles: downloadedFiles + [image], errorCount: 0)
                            }
                        }
                            // else, download the file
                        else {
                            // If image exists, append the data
                            if let _ = imageData, let data = data {
                                imageData?.append(data)
                            }
                                // initialize the image data
                            else {
                                imageData = data
                            }
                        }
                    }


                }) // end of filedata fetch
            }   // end of else statement
        }

        // bounds checking
        let available = files.count
        let n = howMany > available ? available : howMany

        // grab the N latest images taken by the drone
        let filesToDownload : [DJIMediaFile] = Array ( files.suffix(n) )

        // start the recursive function
        downloadNextImage(files: filesToDownload, fileCount: filesToDownload.count)
    }
    
    func setUpDownload(){
        // Set shootMode to ownload
        self.camera?.stopShootPhoto(completion: {(error) in
            self.statusLabel.text = "Stopping shoot photo"
            DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + 1){
                print("Stopped shoot photo")
                self.statusLabel.text = "Shoot photo stopped..?"

                self.camera?.setMode(DJICameraMode.mediaDownload, withCompletion: {(error) in
                    DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + 4){
                        if error != nil {
                            print("Is dispatch needed? TODO")
                            self.statusLabel.text = "Error setting CameraMode to mediaDownload"
                        }
                        else {
                            self.camera?.getModeWithCompletion( {(mode: DJICameraMode, error: Error?) in
                                if mode == DJICameraMode.mediaDownload{
                                    self.statusLabel.text = "Camera mode is mediaDownload"
                                }
                                else if mode == DJICameraMode.shootPhoto{
                                    self.statusLabel.text = "Camera mode is still shootPhoto. Abort download"
                                    return
                                }
                                else {
                                    self.statusLabel.text = "Camera mode is not mediaDownload. Abort download"
                                    return
                                }
                                })
                        }
                    }
                })
            }
            
        })
        // TODO update manager to self.camera.mediamanager
        // get the media manager from the drone to gain access to the files
        statusLabel.text = "Early finish..?"
        let manager = self.camera?.mediaManager!
        manager?.refreshFileList(of: DJICameraStorageLocation.sdCard, withCompletion:  {(error) in
            if error != nil {
                print("State: " + (String(describing: manager?.sdCardFileListState.rawValue)))
                print("Error refreshing list: " + String(describing: error!.localizedDescription))
            }
            else {
                print("Refreshed file list")
                print("State: " + String(describing: manager?.sdCardFileListState.rawValue))

                // get list of files
                guard let files = manager?.sdCardFileListSnapshot() else {
                    print("No files to download")
                    return
                }

                print("There are files to download.. Beginning Download")
                
                self.camera?.getModeWithCompletion( {(mode: DJICameraMode, error: Error?) in
                    if mode == DJICameraMode.mediaDownload {
                        self.downloadImages(files: files, howMany: 3, maxErrors: 4, completion: { images in
                            print("Finished downloading: " + String(describing:images.count))
                            // do something with the images here
                        })
                    }
                else{
                    self.statusLabel.text = "Can't continue due to camera mode, abort"
                    return
                    }
                })
            }
            
        }) // end of file-refresh block

    }
            

    // retreive the gimbal pitch. DOES CRASH THE APP! TODO
    func getGimbalAttitude(){
        // Get the key
        guard let gimbalAttitudeInDegreesKey = DJIGimbalKey(param: DJIGimbalParamAttitudeInDegrees) else {
            print("Could not create DJIGimbalParamAttitudeInDegrees key")
            return
        }
        // Get the keyManager
        guard let keyManager = DJISDKManager.keyManager() else {
            print("Could not get the key manager, manke sure you are registered")
            return
        }
        // Use key to retreive info
        let gimbalAttitudeInDegreesValue = keyManager.getValueFor(gimbalAttitudeInDegreesKey)
        let gimbalAttitudeInDegrees = gimbalAttitudeInDegreesValue?.value as! DJIGimbalState
        _ = gimbalAttitudeInDegrees.attitudeInDegrees.pitch

        // I want to use gimbalAttitude.attitudeInDegrees.pitch.description
        var temp_str:String = ""
        temp_str += "Roll" + gimbalAttitudeInDegrees.attitudeInDegrees.roll.description
        temp_str += "Pitch" + gimbalAttitudeInDegrees.attitudeInDegrees.pitch.description
        temp_str += "Yaw" + gimbalAttitudeInDegrees.attitudeInDegrees.yaw.description
        self.statusLabel.text = temp_str
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
    
    
    // **************
    // Button actions
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
        deactivateSticks()
        self.timer?.invalidate()
        self.dismiss(animated: true, completion: nil)
        //if let camera = fetchCamera(), let delegate = camera.delegate, delegate.isEqual(self) {
        //    camera.delegate = nil
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
        // Set the control command

        y = self.horizontalSpeed/100
        // Schedule the timer at 20Hz while the default specified for DJI is between 5 and 25Hz. Timer will execute control commands for a period of time
        self.timer?.invalidate()
        loopCnt = 0
        timer = Timer.scheduledTimer(timeInterval: sampleTime/1000, target: self, selector: #selector(fireTimer), userInfo: nil, repeats: true)
    }

    @IBAction func DuttLeftPressed(_ sender: UIButton) {
        // Set the control command
        previewImageView.image = nil
        y = -self.horizontalSpeed/100
        // Schedule the timer at 20Hz while the default specified for DJI is between 5 and 25Hz. Timer will execute control commands for a period of time
        self.timer?.invalidate()
        loopCnt = 0
        timer = Timer.scheduledTimer(timeInterval: sampleTime/1000, target: self, selector: #selector(fireTimer), userInfo: nil, repeats: true)
    }


    
    @IBAction func takePhotoButton(_ sender: Any) {
       statusLabel.text = "Capture image button pressed"
       
       setGimbalPitch(pitch: self.nextGimbalPitch)
       updateGnextGimbalPitch()
       
       // Dispatch, then capture an image
       DispatchQueue.main.asyncAfter(deadline: .now() + 1.2, execute: {
           self.captureImage()
       })
    }
    
    @IBAction func savePhotoButton(_ sender: Any) {
        my_cameraSetMode(DJICameraMode.mediaDownload, completionHandler: {(succsess: Bool) in
            if succsess {
                self.my_getImage(completionHandler: {(success: Bool) in
                    if succsess{
                        _ = 1
                    }
                })
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
    
    // **************
    // viewDidLoad
    override public func viewDidLoad() {
        super.viewDidLoad()
        // Init variables
        // Calc number of loops for dutt cycle
        loopTarget = Int(controlPeriod / sampleTime)
        // Init steppers
        controlPeriodStepperButton.value = controlPeriod
        controlPeriodLabel.text = String(controlPeriod/1000)
        horizontalSpeedStepperButton.value = Double(horizontalSpeed)
        horizontalSpeedLabel.text = String(horizontalSpeed/100)
        
        // Set up layout
        let radius: CGFloat = 5
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
        if let product = DJISDKManager.product() as? DJIAircraft {
            self.aircraft = product
            // Store flight controller reference
            if let fc = product.flightController {
                // Store the flightController reference
                self.flightController = fc
                // Default the coordinate system to body and reference yaw to heading
                self.flightController?.setFlightOrientationMode(DJIFlightOrientationMode.aircraftHeading, withCompletion: { (error: Error?) in
                    print("Error when setting OrientationMode")})
                // Set properties of VirtualSticks
                self.flightController?.rollPitchCoordinateSystem = DJIVirtualStickFlightCoordinateSystem.body
                self.flightController?.yawControlMode = DJIVirtualStickYawControlMode.angle
                self.flightController?.rollPitchControlMode = DJIVirtualStickRollPitchControlMode.velocity
            }
            
            // Store the camera refence
            if let cam = product.camera {
                self.camera = cam
                image_index = self.camera?.index
                // Should try to implement callback listener to progress image index.
            }
            // Store the gimbla reference
            if let gimb = product.gimbal{
                self.gimbal = gimb
                self.gimbal?.setPitchRangeExtensionEnabled(true, withCompletion: nil)
                self.gimbal?.getPitchRangeExtensionEnabled(completion: {(sucsess: Bool, error_msg: Error?) in
                    self.pitchRangeExtension_set = sucsess})
                // Have to dispatch in order for change to fall through before checking it
                DispatchQueue.main.asyncAfter(deadline: .now() + 1, execute: {
                    if self.pitchRangeExtension_set {
                        self.statusLabel.text = "Range extension set"}
                    else {
                        self.statusLabel.text = "Range extension not set"}
                })
            }
        }
    }
    
    
   
    

    
    
   // https://stackoverflow.com/questions/45872030/retrieve-images-from-a-dji-drone-with-exif-data
    
//    /**
//     * This function downloads the N latest images from the drone and passes them to the completionhandler once all images have completed downloading
//     */
//    func downloadImages( files: [DJIMediaFile], howMany: Int, maxErrors: Int, completion: @escaping ([UIImage]) -> Void){
//
//        Logger.logH1("Queueing \(howMany) image(s) to be downloaded")
//
//        func downloadNextImage( files: [DJIMediaFile], fileCount: Int, index: Int = 0, downloadedFiles: [UIImage] = [], errorCount: Int = 0) {
//
//            // stop when we reach the end of the list
//            if index == fileCount {
//                completion(downloadedFiles)
//                return
//            }
//            else {
//                var imageData: Data?
//                let file = files[index]
//
//                file.fetchData(withOffset: 0, update: DispatchQueue.main, update: {(_ data: Data?, _ isComplete: Bool, _ error: Error?) -> Void in
//
//                    if let error = error {
//                        Logger.logError("\(error)")
//
//                        if errorCount < maxErrors {
//                            DispatchQueue.main.asyncAfter(deadline: .now() + 1) {
//                                Logger.logH1("Attempting to download: \(file.fileName) again")
//                                downloadNextImage(files: files, fileCount: fileCount, index: index, downloadedFiles: downloadedFiles, errorCount: errorCount + 1)
//                            }
//
//                        }
//                        else {
//                            Logger.logError("Too many errors downloading the images, try downloading again")
//                        }
//
//
//                    }
//                    else {
//                        // if image is done downloading
//                        if isComplete {
//
//                            // get full image data
//                            if let imageData = imageData, let image = UIImage(data: imageData) {
//                                Logger.logH1("Downloaded: \(file.fileName)")
//
//                                // now that the image is done downloading, move onto the next image
//                                downloadNextImage(files: files, fileCount: fileCount, index: (index + 1), downloadedFiles: downloadedFiles + [image], errorCount: 0)
//                            }
//                        }
//                            // else, download the file
//                        else {
//
//                            // If image exists, append the data
//                            if let _ = imageData, let data = data {
//                                imageData?.append(data)
//                            }
//                                // initialize the image data
//                            else {
//                                imageData = data
//                            }
//
//                        }
//                    }
//
//
//                }) // end of filedata fetch
//
//
//            }   // end of else statement
//        }
//
//        // bounds checking
//        let available = files.count
//        let n = howMany > available ? available : howMany
//
//        // grab the N latest images taken by the drone
//        let filesToDownload : [DJIMediaFile] = Array ( files.suffix(n) )
//
//
//        // start the recursive function
//        downloadNextImage(files: filesToDownload, fileCount: filesToDownload.count)
//    }
//
//    // get current product
//    guard; let drone = DJISDKManager.product()
//        else {
//        Logger.logError("Product is connected but DJISDKManager.product is nil when attempting to download media")
//        return
//    }
//
//
//    // Get camera on drone
//    guard  let camera: DJICamera = drone.camera else {
//        Logger.logError("Unable to detect Camera in initDownload()")
//        return
//    }
//
//    Logger.logH1("Successfully detected the camera")
//
//    // check if we can download images with the product
//    if !camera.isMediaDownloadModeSupported() {
//        Logger.logError("Product does not support media download mode")
//        return
//    }
//
//    // switch camera mode to allow for media downloads
//    camera.setMode( .mediaDownload, withCompletion: {(error) in
//        if error != nil {
//            print("\(error!.localizedDescription)")
//        }
//        else {
//
//            // get the media manager from the drone to gain access to the files
//            let manager = camera.mediaManager!
//            manager.refreshFileList(completion: { (error) in
//
//                if error != nil {
//                    print("State: \(manager.fileListState.rawValue)")
//                    print("Error refreshing list: \(error!.localizedDescription)")
//                }
//                else {
//                    Logger.logH1("Refreshed file list")
//                    print("State: \(manager.fileListState.rawValue)")
//
//                    // get list of files
//                    guard let files = manager.fileListSnapshot() else {
//                        Logger.logError("No files to download")
//                        return
//                    }
//
//                    Logger.logH1("There are files to download.. Beginning Download")
//                    self.downloadImages(files: files, howMany: waypoints, maxErrors: 4, completion: { images in
//                        Logger.logH1("Finished downloading: \(images.count) image(s)")
//                        // do something with the images here
//                    })
//
//
//
//                }
//            }) // end of file-refresh block
//
//        }
//
//    })// end of camera setMode block
    
    
    
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


//https://developer.dji.com/iframe/mobile-sdk-doc/ios/Classes/DJIGimbal.html


// Capabilities..
//            if let gimbalcapability = self.gimbal?.capabilities {
//                statusLabel.text = String(describing: gimbalcapability[DJIGimbalParamPitchUpEndpoint])
//                for (keys, values) in gimbalcapability {
//                    statusLabel.text = String(describing: keys) + String(describing: values)
//                    print(keys, values)
//                }


// Iterative loop
//    func increasLabel(){
//        DispatchQueue.main.asyncAfter(deadline: .now() + 2) {
//            if gameActive {
//                score += 1
//                self.scoreLabel.text = "\(score)"
//                increaseLabel()
//            }
//        }
//
//    }


// Extend gimbal movement
//self.gimbal?.setPitchRangeExtensionEnabled(true, withCompletion: {DJICompletionBlock in
//    print("setPitchRangeExtensionEnabled completed with unknown result")
//    })


// Animations
//ActivateSticksButton.flash(duration: 1.5)
//ActivateSticksButton.layer.removeAllAnimations()
//ActivateSticksButton.setTitle("Activate Sticks", for: .normal)



//    Use keys to conform with SDK, the keys are written in the SDK
//    // get location via Key
//    guard let locationKey = DJIFlightControllerKey(param: DJIFlightControllerParamAircraftLocation) else {
//        NSLog("Couldn't create the key")
//        return
//    }
//    guard let keyManager = DJISDKManager.keyManager() else {
//        print("Couldn't get the keyManager")
//        // This will happen if not registered
//        return
//    }
//    if let locationValue = keyManager.getValueFor(locationKey) {
//        let location = locationValue.value as! CLLocation
//        // do something
//        print(location.coordinate)
//        print(location.altitude)
//    }


//    // Get gimbal capabilities via keyManager
//    func getGimbalCapabilites() -> Int {
//        guard let gimbalCapabilitiesKey = DJIGimbalKey(param: DJIGimbalParamCapabilities) else {
//            print("Cold not creat DJIGimbalParamCapabilities key")
//            return 0
//        }
//        guard let keyManager = DJISDKManager.keyManager() else {
//            print("Could not get the keyManager, make sure you are registered")
//            return 0
//        }
//        if let capabilityValue = keyManager.getValueFor(gimbalCapabilitiesKey) {
//            //let capability = capabilityValue.value as! DJIParamCapabilityMinMax
//            let capability = capabilityValue.value as! NSDictionary
//            let check_first = capability.object(forKey: DJIGimbalParamPitchUpEndpoint) as! DJIParamCapability
//            statusLabel.text = String(check_first.isSupported)
//            // Unfortunately, DJIGimbalParamPitchUpEndpoint is not supported..
//            // If it was we should be able to get the min max like this:
//            if check_first.isSupported{
//                let minmaxCapability = capability.object(forKey: DJIGimbalParamPitchUpEndpoint) as! DJIParamCapabilityMinMax
//                let my_value = minmaxCapability.min
//                statusLabel.text = my_value?.stringValue
//                return my_value as! Int
//            }
//            //statusLabel.text = String(describing: keys) + String(describing: values)
//        }
//        return 0
//    }



//             if let gimbalcapability = self.gimbal?.capabilities {
//                statusLabel.text = String(describing: gimbalcapability[DJIGimbalParamPitchUpEndpoint])
//                for (keys, values) in gimbalcapability {
//                    statusLabel.text = String(describing: keys) + String(describing: values)
//                    print(keys, values)
//                }









// Airmap https://developers.airmap.com/docs/ios-app-with-dji-sdk-and-airmap-sdk#dji-sdk
///// Sets up a listener for when the aircraft takes off / lands
//  fileprivate func setupFlyingListeners() {
//
//      let manager = DJISDKManager.keyManager()
//
//      // Flying
//      if let isFlyingKey = DJIFlightControllerKey(param: DJIFlightControllerParamIsFlying) {
//
//          manager?.startListeningForChanges(on: isFlyingKey, withListener: self, andUpdate: { oldKeyedValue, newKeyedValue in
//
//              guard let takeOff = newKeyedValue?.boolValue else {
//                  return
//              }
//
//              if takeOff {
//                  self.createAirMapFlight()
//              } else {
//                  self.endAirMapFlight()
//              }
//
//          })
//      }
//
//  }
//
//  /// Sets up a Telemetry Listener
//  fileprivate func setupTelemetryListeners() {
//
//      let manager = DJISDKManager.keyManager()
//
//      // Position & Altitude
//      if let positionKey = DJIFlightControllerKey(param: DJIFlightControllerParamAircraftLocation) {
//
//          manager?.startListeningForChanges(on: positionKey, withListener: self, andUpdate: { oldKeyedValue, newKeyedValue in
//
//              guard let location = newKeyedValue?.value as? CLLocation, let flightId = self.airmapFlight?.id else {
//                  return
//              }
//
//              guard let altitudeKey = DJIFlightControllerKey(param: DJIFlightControllerParamAltitudeInMeters), let altitude = manager?.getValueFor(altitudeKey)?.floatValue  else {
//                  return
//              }
//
//              do { try AirMap.sendTelemetryData(flightId, coordinate: location.coordinate, altitudeAgl: altitude, altitudeMsl: nil) }
//              catch let error { AirMap.logger.error(error) }
//
//              // update flight
//              self.airmapFlight?.coordinate = location.coordinate
//          })
//      }
//
//      // Velocity
//      if let velocityKey = DJIFlightControllerKey(param: DJIFlightControllerParamVelocity) {
//
//          manager?.startListeningForChanges(on: velocityKey, withListener: self, andUpdate: { oldKeyedValue, newKeyedValue in
//
//              guard let velocity = newKeyedValue?.value as? DJISDKVector3D, let flightId = self.airmapFlight?.id else {
//                  return
//              }
//
//              do { try AirMap.sendTelemetryData(flightId, velocity: (x: Float(velocity.x), y: Float(velocity.y), z: Float(velocity.z))) }
//              catch let error { AirMap.logger.error(error) }
//          })
//      }
//
//      // Attitude
//      if let attitudeKey = DJIFlightControllerKey(param: DJIFlightControllerParamAttitude) {
//
//          manager?.startListeningForChanges(on: attitudeKey, withListener: self, andUpdate: { oldKeyedValue, newKeyedValue in
//              guard let attitude = newKeyedValue?.value as? DJISDKVector3D, let flightId = self.airmapFlight?.id else {
//                  return
//              }
//              do { try AirMap.sendTelemetryData(flightId, yaw: Float(attitude.z), pitch: Float(attitude.y), roll: Float(attitude.x)) }
//              catch let error { AirMap.logger.error(error) }
//          })
//      }
//  }











// Throw under the bus
        // Use key to retreive info
        
       //

    //  -> returns TRUE!
        
        //let apa = keyManager.getValueFor(gimbalAttitudeKeyxx)
        //apa?.floatValue
        
  // gimbalAttitudeInDegreeesValue is a DJIKEYEDVALUE
//        search for dji keyed value

//        ALL REPORTS 0.0
 //       var apa = DJIGimbalState()
    //    statusLabel.text = apa.attitudeInDegrees.pitch.description + apa.isCalibrating.description + String(apa.attitudeInDegrees.roll) + apa.attitudeInDegrees.yaw.debugDescription
        
    //    All reports 0.0
    //    var apa = DJIGimbalAttitude()
    //    statusLabel.text = apa.pitch.description + apa.roll.description + String(apa.yaw)
//        All reports 0.0
//        var apa = DJIAttitude()
 //       apa.pitch = 3
 //       statusLabel.text = apa.pitch.description + apa.roll.description + String(apa.yaw)
//        if let gimbalAttitudeInDegreesValue = keyManager.getValueFor(gimbalAttitudeKeyxx){
            //let gimbalAttitudeInDegrees = gimbalAttitudeInDegreesValue.value.debugDescription as! DJIGimbalAttitude
            
//            statusLabel.text = gimbalAttitudeInDegreesValue.value.debugDescription
            //statusLabel.text = kul.description
            //let check = kul.value(forKey: DJIGimbalParamAttitudeInDegrees) as! DJIParamCapabilityMinMax
            
            //self.statusLabel.text = check.max.description
            
            // crash let testa = gimbalAttitudeInDegreesValue.value as! DJIAttitude
            // crash let testaa = gimbalAttitudeInDegreesValue.value as! DJIGimbalAttitude
            //_ = testa.pitch
            //_ = testaa.pitch
            //self.statusLabel.text = my_attitude.pitch.description
        
    //}
    
    
    //     let my_gimbalAttitude = gimbalAttitudeInDegreesValue.value as! DJIAttitude
            //_ = my_gimbalAttitude.pitch
//            var temp_str:String = ""
//            temp_str += "Roll: " + String(my_gimbalAttitude.roll)
//            temp_str += "Pitch" + String(self.gimbalAttitude.pitch)
//            temp_str += "Yaw" + String(self.gimbalAttitude.yaw)
//            self.statusLabel.text = temp_str
        //}
    
    //    if let capabilityValue = keyManager.getValueFor(gimbalCapabilitiesKey) {
    //            //let capability = capabilityValue.value as! DJIParamCapabilityMinMax
    //            let capability = capabilityValue.value as! NSDictionary
    //            let check_first = capability.object(forKey: DJIGimbalParamPitchUpEndpoint) as! DJIParamCapability
    //            statusLabel.text = String(check_first.isSupported)
    //            // Unfortunately, DJIGimbalParamPitchUpEndpoint is not supported..
    //            // If it was we should be able to get the min max like this:
    //            if check_first.isSupported{
    //                let minmaxCapability = capability.object(forKey: DJIGimbalParamPitchUpEndpoint) as! DJIParamCapabilityMinMax
    //                let my_value = minmaxCapability.min
    //                statusLabel.text = my_value?.stringValue
    //                return my_value as! Int
    //            }
    //            //statusLabel.text = String(describing: keys) + String(describing: values)
    //        }
    
    
    // Actions
//    func fetchCamera() -> DJICamera? {
//           guard let product = DJISDKManager.product() else {
//               return nil
//           }
//           if product is DJIAircraft {
//               return (product as! DJIAircraft).camera
//           }
//           if product is DJIHandheld {
//               return (product as! DJIHandheld).camera
//           }
//           return nil
//       }
   






//    // Activate virtual stick via keys
//    func startVirtualStick(enabled: Bool = true) {
//        guard let virtualStickKey = DJIFlightControllerKey(param: DJIFlightControllerParamVirtualStickControlModeEnabled) else {
//            return;
//        }
//
//        DJISDKManager.keyManager()?.setValue(NSNumber(value: enabled), for: virtualStickKey, withCompletion: { (error: Error?) in
//            if error != nil {
//                print("Error start virtual stick")
//            }
//            print("Start virtual stick \(enabled)")
//        })
//    }
//
//    func startAdvancedVirtualStick(enabled: Bool = true) {
//        guard let virtualStickKey = DJIFlightControllerKey(param: DJIFlightControllerParamVirtualStickAdvancedControlModeEnabled) else {
//            return;
//        }
//
//        DJISDKManager.keyManager()?.setValue(NSNumber(value: enabled), for: virtualStickKey, withCompletion: { (error: Error?) in
//            if error != nil {
//                print("Error start advanced virtual stick")
//            }
//            print("Start advanced virtual stick \(enabled)")
//        })
//    }



//        // Set camera mode to shootPhoto and then startShootPhoto as camera mode is completed.
//        func captureImage() {
//            self.camera?.setMode(DJICameraMode.shootPhoto, withCompletion: {(error) in
//                DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + 1){
//                self.camera?.startShootPhoto(completion: { (error) in
//                    if let _ = error {
//                        NSLog("Shoot Photo Error: " + String(describing: error))
//                         }
//                    })
//                }
//            })
//        }



//
//    typealias CompletionHandler = (success:Bool) -> Void
//
//    func downloadFileFromURL(url: NSURL,completionHandler: CompletionHandler) {
//
//        // download code.
//
//        let flag = true // true if download succeed,false otherwise
//
//        completionHandler(success: flag)
//    }
//
//    // How to use it.
//
//    downloadFileFromURL(NSURL(string: "url_str")!, { (success) -> Void in
//
//        // When download completes,control flow goes here.
//        if success {
//            // download success
//        } else {
//            // download fail
//        }
//    })
