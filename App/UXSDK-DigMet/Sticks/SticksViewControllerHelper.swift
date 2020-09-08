//
//  SticksViewControllerHelper.swift
//  UXSDK-DigMet
//
//  Created by Andreas Gising on 2020-08-31.
//  Copyright © 2020 DJI. All rights reserved.
//

import Photos
import UIKit

// https://www.hackingwithswift.com/books/ios-swiftui/how-to-save-images-to-the-users-photo-library
class imageSaver: NSObject {
    func writeToPhotoAlbum(image: UIImage) {
        UIImageWriteToSavedPhotosAlbum(image, self, #selector(saveError), nil)
        
    }
    @objc func saveError(_ image: UIImage, didFinishSavingWithError error: Error?, contextInfo: UnsafeRawPointer) {
        print("Save Finished")
    }
}

class my_Helper: NSObject {
    func my_test(number: Int) -> Int{
        return -number
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


// Save UIImage, post "Xcode Version 10.2 (10E125), Swift 5" https://stackoverflow.com/questions/37344822/saving-image-and-then-loading-it-in-swift-ios
extension UIImage {

    func save(at directory: FileManager.SearchPathDirectory,
              pathAndImageName: String,
              createSubdirectoriesIfNeed: Bool = true,
              compressionQuality: CGFloat = 1.0)  -> URL? {
            print("ett")
            do {
                let documentsDirectory = try FileManager.default.url(for: directory, in: .userDomainMask, appropriateFor: nil, create: false)
                print(documentsDirectory.absoluteString)
                print("tva")
                return save(at: documentsDirectory.appendingPathComponent(pathAndImageName),
                    createSubdirectoriesIfNeed: createSubdirectoriesIfNeed,
                    compressionQuality: compressionQuality)
            }
            catch {
                print("-- Error: \(error)")
                return nil
        }
    }

    func save(at url: URL,
              createSubdirectoriesIfNeed: Bool = true,
              compressionQuality: CGFloat = 1.0)  -> URL? {
        do {
            print("one")
            if createSubdirectoriesIfNeed {
                try FileManager.default.createDirectory(at: url.deletingLastPathComponent(),
                                                        withIntermediateDirectories: true,
                                                        attributes: nil)
            }
            print("two")
            guard let data = jpegData(compressionQuality: compressionQuality) else { return nil }
            
            print("three")
            print(url)
            try data.write(to: url)
            return url
        } catch {
            print("-- Error: \(error)")
            return nil
        }
    }
}

// load UIImage from path, post "Xcode Version 10.2 (10E125), Swift 5" https://stackoverflow.com/questions/37344822/saving-image-and-then-loading-it-in-swift-ios
extension UIImage {
    convenience init?(fileURLWithPath url: URL, scale: CGFloat = 1.0) {
        do {
            let data = try Data(contentsOf: url)
            self.init(data: data, scale: scale)
        } catch {
            print("-- Error: \(error)")
            return nil
        }
    }
}


// Extension to convert PHAsset to UIImage, https://stackoverflow.com/questions/30812057/phasset-to-uiimage
extension PHAsset {

    var image : UIImage {
        var thumbnail = UIImage()
        let imageManager = PHCachingImageManager()
        imageManager.requestImage(for: self, targetSize: CGSize(width: 100, height: 100), contentMode: .aspectFit, options: nil, resultHandler: { image, _ in
            thumbnail = image!
        })
        return thumbnail
    }
}

// Extension to write data objects to a temp directory
extension Data {

    func myWrite(withName name: String) -> URL {

        let url = URL(fileURLWithPath: NSTemporaryDirectory()).appendingPathComponent(name)

        try! write(to: url, options: .atomicWrite)

        return url
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
