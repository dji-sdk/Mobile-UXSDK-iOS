//
//  SticksViewControllerHelper.swift
//  UXSDK-DigMet
//
//  Created by Andreas Gising on 2020-08-31.
//  Copyright © 2020 DJI. All rights reserved.
//

import Photos
import UIKit


//
// Class to use for allocation of resources, like camera, gimbal, etc.
class Allocator: NSObject{
    private var allocated = false
    private var owner = ""
    private var name = ""
    private var dateAllocated = Date()
    private var maxTime = Double(0)
    
    init(name: String){
        self.name = name
    }
    
    func allocate(_ owner: String, maxTime: Double)->Bool{
        // Check if it is rightfully allocated
        if self.allocated{
            if self.maxTime > self.timeAllocated(){
                // Resource is rightfully allocated
                let tempStr = self.name + "-Allocator : Resource occupied by " + self.owner + ", " + owner + "tried to occupy"
                print(tempStr)
                return false
            }
            print(self.name + "-Allocator : Forcing allocation from " + self.owner)
        }
        // Resource is not rightfully allocated -> Allocate it!
        self.allocated = true
        self.owner = owner
        self.dateAllocated = Date()
        self.maxTime = maxTime
        return true
    }
    
    
    func deallocate(){
        print("Resource was busy for " + String(self.timeAllocated()) + "by: " + self.owner)
        self.allocated = false
        self.owner = ""
    }

    func timeAllocated()->Double{
        if self.allocated{
            // timeIntervalSinceNow returns a negative time in seconds. This function returns positive value.
            return -dateAllocated.timeIntervalSinceNow
        }
        else{
            return Double(0)
        }
    }
}


// https://www.hackingwithswift.com/books/ios-swiftui/how-to-save-images-to-the-users-photo-library
class imageSaver: NSObject {
    func writeToPhotoAlbum(image: UIImage) {
        UIImageWriteToSavedPhotosAlbum(image, self, #selector(saveError), nil)
        
    }
    @objc func saveError(_ image: UIImage, didFinishSavingWithError error: Error?, contextInfo: UnsafeRawPointer) {
        print("Save Finished")
    }
}


class serverClass: NSObject{
    var key_value = ""
    
    // Http lookup of .json struct.
    func getServerData(key: String, completionHandler: @escaping (Bool) -> Void) {
//        // In sticksViewcontroller, call this code to get the data. http read only server in /Users/gising/Documents/Projects/test_folder. Start with http-server
//        self.getServerData(key: "id", completionHandler: {(succsess: Bool) in
//            _ = 1
//        })
//        DispatchQueue.main.asyncAfter(deadline: .now() + 0.5, execute: {
//            self.printSL(self.server.key_value)
//        })
        

        let session = URLSession.shared
        let serviceUrl = URL(string: "http://25.17.84.213:8080/API.json")
        let task = session.dataTask(with:serviceUrl!) { (serviceData, serviceResponse, error) in
            if error == nil{
                let httpResponse = serviceResponse as! HTTPURLResponse
                if(httpResponse.statusCode == 200){
                    // data parse
                    let jsonData = try? JSONSerialization.jsonObject(with: serviceData!, options: .mutableContainers)
                    let result = jsonData as! Dictionary<String, Any>
                    if let value = result[key]{
                        print("id = \(result["id"]!)")
                        self.key_value = String(describing: value)
                        completionHandler(true)
                    }
                }
            }
            else{
                print("Error fetching key" + key)
                completionHandler(false)
                }
        }
       task.resume()
    }
    
    func putServerData(){
        // Read only server..
    }
}





// Possible to work using DLSFTPClient
//https://stackoverflow.com/questions/46968011/local-file-not-readable-when-trying-to-upload-in-swift

// Not fully working..
//https://stackoverflow.com/questions/51617805/sending-csv-file-with-sftp-in-swift
//class sftpClass: NSObject{
    
//    let session = NMSSHSession.init(host: serverHost, port: xx, andUsername: serverUsername)
//       session.connect()
//       if session.isConnected{
//           session.authenticate(byPassword: serverPasswordString)
//           if session.isAuthorized == true {
//               let sftpsession = NMSFTP(session: session)
//               sftpsession.connect()
//               if sftpsession.isConnected {
//                   sftpsession.writeFile(atPath: csvFileURL.path, toFileAtPath: folderLocation)
//               }
//           }
//       }
//}





//Check system logs for sshd, https://stackoverflow.com/questions/43382825/where-to-find-sshd-logs-on-macos-sierra
//Apple, as usual, decided to re-invent the wheel.
//
//In super-user window
//
//# log config --mode "level:debug" --subsystem com.openssh.sshd
//# log  stream --level debug  2>&1 | tee /tmp/logs.out
//In another window
//
//$ ssh localhost
//$ exit
//Back in Super-user window
//
//^C (interrupt)
//# grep sshd /tmp/logs.out
//2019-01-11 08:53:38.991639-0500 0x17faa85  Debug       0x0                  37284  sshd: (libsystem_network.dylib) sa_dst_compare_internal <private>@0 < <private>@0
//2019-01-11 08:53:38.992451-0500 0xb47b5b   Debug       0x0                  57066  socketfilterfw: (Security) [com.apple.securityd:unixio] open(/usr/sbin/sshd,0x0,0x1b6) = 12
//...
//...
//In super-user window, restore default sshd logging
//
//# log config --mode "level:default" --subsystem com.openssh.sshd


  
    
    
    
    
    
//    //************************************
//    // Tested ok, but not in use anymore..
//    // ***********************************
//
//    // Store an UIImage to filename (.png will be added). Full path is returned (and written to self.lastImageURL
//    func saveUIImageToAppPNG(image: UIImage, filename: String) -> String {
//        //// Code gives an ur to the unsaved image.
//        // https://stackoverflow.com/questions/29009621/url-of-image-after-uiimagewritetosavedphotosalbum-in-swift
//        let png = NSData(data: image.pngData()!)
//        let paths = NSSearchPathForDirectoriesInDomains(FileManager.SearchPathDirectory.documentDirectory, FileManager.SearchPathDomainMask.userDomainMask, true)
//        let docs: String = paths[0]
//        let fullPath = docs + filename + ".png"
//        self.lastImageURL = fullPath
//        self.printSL(fullPath)
//        png.write(toFile: fullPath, atomically: true)
//        return fullPath
//    }
//
//    // Store an UIImage to filename (.png will be added). Full path is returned (and written to self.lastImageURL
//    func saveUIImageToAppJPG(image: UIImage, filename: String) -> String {
//        //// Code gives an ur to the unsaved image.
//        // https://stackoverflow.com/questions/29009621/url-of-image-after-uiimagewritetosavedphotosalbum-in-swift
//        let png = NSData(data: image.jpegData(compressionQuality: 0.3)!)
//
//        let paths = NSSearchPathForDirectoriesInDomains(FileManager.SearchPathDirectory.documentDirectory, FileManager.SearchPathDomainMask.userDomainMask, true)
//        let docs: String = paths[0]
//        let fullPath = docs + filename + ".JPG"
//        self.lastImageURL = fullPath
//        self.printSL(fullPath)
//        png.write(toFile: fullPath, atomically: true)
//        return fullPath
//    }
//
//  //Called in savePhotoButton
//    self.lastImageURL = self.saveUIImageToAppPNG(image: self.lastImage, filename: "/1")
//    self.lastImageURL = self.saveUIImageToAppJPG(image: self.lastImage, filename: "/3")
//    //**************************************
    
    
    
    
    
    
    
    // API calls in hhindi.. https://www.youtube.com/watch?v=-7EyKipJltc&list=PLb5R4QC2DtFuXr4177KQ2lIXOkqwq97a4
    // https://www.youtube.com/watch?v=-7EyKipJltc
    // Upload image https://www.youtube.com/watch?v=qhoL1lp4kiY
    
    // https://github.com/http-party/http-server
    
    
    
    
    
    
    
//
//    func old_cameraSetMode(_ newCameraMode: DJICameraMode, completionHandler: @escaping (Bool) -> Void) {
//        // Update the cameraModeReferemce, then set mode and confirm that is is correctly set.
//        self.cameraModeReference = newCameraMode
//        self.camera?.setMode(newCameraMode, withCompletion: {(error) in
//            if error != nil {
//                self.statusLabel.text = "Error setting CameraMode"
//            }
//            else {
//                self.camera?.getModeWithCompletion( {(mode: DJICameraMode, error: Error?) in
//                    if error != nil{
//                        self.statusLabel.text = "Error getting Cameramode"
//                    }
//                    else {
//                        self.cameraModeAcitve = mode
//                        if self.cameraModeAcitve != self.cameraModeReference{
//                            self.statusLabel.text = "Camermode setting failed. Calling cameraSetMode again.."
//                            completionHandler(false)
//                        }
//                        else {
//                            self.statusLabel.text = "CameraMode has been changed"
//                            completionHandler(true)
//                        }
//                    }
//                })
//
//            }
//        })
//    }
//
//
//
//    // Only set camera mode if it is not in shootPhoto, then capture an image
//    func old_captureImage() {
//        // Make sure camera is set up: Mode and Shoot mode, if not set it up
//        self.camera?.getModeWithCompletion( {(mode, error) in
//            if mode != DJICameraMode.shootPhoto {
//                self.old_setUpSinglePhoto()
//                // Need a dispatch here?
//            }
//        })
//        // Take a single photo (single since the camera now is set up that way)
//        self.camera?.startShootPhoto(completion: { (error) in
//            if let _ = error {
//                NSLog("Shoot Photo Error: " + String(describing: error))
//            }
//        })
//    }
//
//    // Set camera Mode to shootPhoto and set camera shootPhotoMode to single
//    func old_setUpSinglePhoto(){
//        // Set shootMode to shootPhoto
//        self.camera?.setMode(DJICameraMode.shootPhoto, withCompletion: {(error) in
//            // Wait a bit and then set shootFotoMode to single. Needed? TODO
//            DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + 1){
//                self.camera?.setShootPhotoMode(DJICameraShootPhotoMode.single, withCompletion: {(error) in
//                    if let _ = error {
//                        NSLog("Shoot Photo Error: " + String(describing: error))
//                    }
//                })
//            }
//        })
//    }
    
    
    
    
    
    
    

    
    
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





// Works but is not general. Replaced by setMode

//    func setUpDownload(){
//        // Set mode to download
//
//        if self.cameraModeReference != DJICameraMode.mediaDownload{
//            self.cameraModeReference = DJICameraMode.mediaDownload
//            self.camera?.setMode(DJICameraMode.mediaDownload, withCompletion: {(error) in
//                if error != nil {
//                    self.statusLabel.text = "Error setting CameraMode to mediaDownload"
//                }
//                else {
//                    self.camera?.getModeWithCompletion( {(mode: DJICameraMode, error: Error?) in
//                        if error != nil{
//                            self.statusLabel.text = "Error getting mode"
//                        }
//                        else {
//                            self.cameraModeAcitve = mode
//                            if self.cameraModeAcitve != self.cameraModeReference{
//                                self.statusLabel.text = "Calling setUpDownload again.." // + String(describing: self.cameraModeAcitve.rawValue)
//                                self.setUpDownload()
//                            }
//                            else {
//                                self.statusLabel.text = "Works like a sharm!"
//                            }
//                        }
//                    })
//
//                }
//            })
//        }
//    }









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









































// Delete below comments. this is only for safety during clean up

    /**
//     * This function downloads the N latest images from the drone and passes them to the completionhandler once all images have completed downloading
//     */
//    func downloadImages(files: [DJIMediaFile], howMany: Int, maxErrors: Int, completion: @escaping ([UIImage]) -> Void){
//
//        print("Queueing.. ")
//
//        func downloadNextImage( files: [DJIMediaFile], fileCount: Int, index: Int = 0, downloadedFiles: [UIImage] = [], errorCount: Int = 0) {
//            // stop when we reach the end of the list
//            if index == fileCount {
//                completion(downloadedFiles)
//                statusLabel.text = "Finished downloading images"
//                return
//            }
//            else {
//                var imageData: Data?
//                let file = files[index]
//
//                file.fetchData(withOffset: 0, update: DispatchQueue.main, update: {(_ data: Data?, _ isComplete: Bool, _ error: Error?) -> Void in
//
//                    if let error = error {
//                        print("Error: " + String(describing: error))
//                        if errorCount < maxErrors {
//                            DispatchQueue.main.asyncAfter(deadline: .now() + 1) {
//                                print("Attempting to download: ") //\(file.fileName) again")
//                                self.statusLabel.text = "Attemting to download" + String(describing: index) + " but receiving error, trying again"
//                                downloadNextImage(files: files, fileCount: fileCount, index: index, downloadedFiles: downloadedFiles, errorCount: errorCount + 1)
//                            }
//                        }
//                        else {
//                            print("Too many errors downloading the images, try downloading again")
//                            self.statusLabel.text = "Too many errors downloading. Abort"
//                        }
//                    }
//                    else {
//                        // if image is done downloading
//                        if isComplete {
//                            // get full image data
//                            if let imageData = imageData, let image = UIImage(data: imageData) {
//                                print("Downloaded: " + String(describing: file.fileName))
//                                self.statusLabel.text = "Downloaded: " + String(describing: fileCount)
//
//                                // Preview the downloaded image
//                                self.previewImageView.image = image
//
//                                // now that the image is done downloading, move onto the next image
//                                downloadNextImage(files: files, fileCount: fileCount, index: (index + 1), downloadedFiles: downloadedFiles + [image], errorCount: 0)
//                            }
//                        }
//                            // else, download the file
//                        else {
//                            // If image exists, append the data
//                            if let _ = imageData, let data = data {
//                                imageData?.append(data)
//                            }
//                                // initialize the image data
//                            else {
//                                imageData = data
//                            }
//                        }
//                    }
//
//
//                }) // end of filedata fetch
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
//        // start the recursive function
//        downloadNextImage(files: filesToDownload, fileCount: filesToDownload.count)
//    }
//
////    func setUpDownload(){
////        // Set shootMode to ownload
////        self.camera?.stopShootPhoto(completion: {(error) in
////            self.statusLabel.text = "Stopping shoot photo"
////            DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + 1){
////                print("Stopped shoot photo")
////                self.statusLabel.text = "Shoot photo stopped..?"
////
////                self.camera?.setMode(DJICameraMode.mediaDownload, withCompletion: {(error) in
////                    DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + 4){
////                        if error != nil {
////                            print("Is dispatch needed? TODO")
////                            self.statusLabel.text = "Error setting CameraMode to mediaDownload"
////                        }
////                        else {
////                            self.camera?.getModeWithCompletion( {(mode: DJICameraMode, error: Error?) in
////                                if mode == DJICameraMode.mediaDownload{
////                                    self.statusLabel.text = "Camera mode is mediaDownload"
////                                }
////                                else if mode == DJICameraMode.shootPhoto{
////                                    self.statusLabel.text = "Camera mode is still shootPhoto. Abort download"
////                                    return
////                                }
////                                else {
////                                    self.statusLabel.text = "Camera mode is not mediaDownload. Abort download"
////                                    return
////                                }
////                                })
////                        }
////                    }
////                })
////            }
////
////        })
////        // TODO update manager to self.camera.mediamanager
////        // get the media manager from the drone to gain access to the files
////        statusLabel.text = "Early finish..?"
////        let manager = self.camera?.mediaManager!
////        manager?.refreshFileList(of: DJICameraStorageLocation.sdCard, withCompletion:  {(error) in
////            if error != nil {
////                print("State: " + (String(describing: manager?.sdCardFileListState.rawValue)))
////                print("Error refreshing list: " + String(describing: error!.localizedDescription))
////            }
////            else {
////                print("Refreshed file list")
////                print("State: " + String(describing: manager?.sdCardFileListState.rawValue))
////
////                // get list of files
////                guard let files = manager?.sdCardFileListSnapshot() else {
////                    print("No files to download")
////                    return
////                }
////
////                print("There are files to download.. Beginning Download")
////
////                self.camera?.getModeWithCompletion( {(mode: DJICameraMode, error: Error?) in
////                    if mode == DJICameraMode.mediaDownload {
////                        self.downloadImages(files: files, howMany: 3, maxErrors: 4, completion: { images in
////                            print("Finished downloading: " + String(describing:images.count))
////                            // do something with the images here
////                        })
////                    }
////                else{
////                    self.statusLabel.text = "Can't continue due to camera mode, abort"
////                    return
////                    }
////                })
////            }
////
////        }) // end of file-refresh block
////
////    }



// remove the newline and speces
//               let lines = response.components(separatedBy: "\n")



//    let response: String = session.channel.execute(commandString, error: &error)
//    DispatchQueue.main.asyncAfter(deadline: .now() + 3, execute: {
//        let lines = response.components(separatedBy: "\n")
//        print(lines[0])
//        self.printSL(lines[0])
//        self.printSL(error.debugDescription)
//    })


//      Counter did not work as intended.
//    if true { // NMSSH: Could not open file at path apa.png (Error 0: )
//        session.sftp.writeFile(atPath: self.lastImageURL, toFileAtPath: "app.png", progress: {(progress: UInt) -> Bool in
//            self.printSL(String(describing: progress))
//            if progress == 100 {
//                self.printSL("Pregress seem to be 100%")
//                return true
//            }
//            else {
//                return false
//            }
//        })
//    }


// SFTP working code
//    if true { // Works but image from duttLeft is very low resolution.. Serrver must be silent!
//                          session.sftp.connect()
//                          let filelist = session.sftp.contentsOfDirectory(atPath: "/")
//                          printSL(String(describing: (filelist?[0])!))
//                          session.sftp.writeFile(atPath: self.lastImageURL, toFileAtPath: "/Users/gising/apa.png")
//                      }


