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
