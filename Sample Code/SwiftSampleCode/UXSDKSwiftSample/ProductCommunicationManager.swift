//
//  ProductCommunicationManager.swift
//  UXSDK Sample
//
//  Copyright © 2016 DJI. All rights reserved.
//

import UIKit
import DJISDK

let ProductCommunicationManagerStateDidChange = "ProductCommunicationManagerStateDidChange"

class ProductCommunicationManager: NSObject, DJISDKManagerDelegate {
    open weak var appDelegate = UIApplication.shared.delegate as? AppDelegate
    open var connectedProduct: DJIBaseProduct!
    
    var registered = false
    var connected = false
    
    open func connectToProduct() {
        if useBridge {
            NSLog("Connecting to Product using debug IP address: \(debugIP)...")
            DJISDKManager.enableBridgeMode(withBridgeAppIP: debugIP)
        } else {
            NSLog("Connecting to product...")
            let startedResult = DJISDKManager.startConnectionToProduct()
            
            if startedResult {
                NSLog("Connecting to product started successfully!")
            } else {
                NSLog("Connecting to product failed to start!")
            }
        }
    }
    
    func registerWithProduct() {
        guard
            let path = Bundle.main.path(forResource: "Info", ofType: "plist"),
            let dict = NSDictionary(contentsOfFile: path) as? Dictionary<String, AnyObject>,
            let appKey = dict["DJISDKAppKey"] as? String,
            appKey != "PASTE_YOUR_DJI_APP_KEY_HERE"
        else {
                print("\n<<<ERROR: Please add DJI App Key in Info.plist after registering as developer>>>\n")
                return
        }
        DispatchQueue.main.asyncAfter(deadline: .now() + 1) {
            NSLog("Registering Product with registration ID: \(appKey)")
            DJISDKManager.registerApp(with: self)
        }
    }
    
    //MARK: - DJISDKManagerDelegate
    func appRegisteredWithError(_ error: Error?) {
        if useBridge {
            if error == nil {
                self.registered = true
                NotificationCenter.default.post(Notification(name: Notification.Name(rawValue: ProductCommunicationManagerStateDidChange)))
            }
            self.connectToProduct()
        } else {
            if error != nil {
                NSLog("Error Registrating App: \(String(describing: error))")
            } else {
                self.registered = true
                NotificationCenter.default.post(Notification(name: Notification.Name(rawValue: ProductCommunicationManagerStateDidChange)))
                NSLog("Registration Succeeded")
                self.connectToProduct()
            }
        }
    }
    
    func productConnected(_ product: DJIBaseProduct?) {
        if product != nil {
            self.connected = true
            NotificationCenter.default.post(Notification(name: Notification.Name(rawValue: ProductCommunicationManagerStateDidChange)))
            NSLog("Connection to new product succeeded!")
            self.connectedProduct = product
        }
    }
    
    func productDisconnected() {
        self.connected = false
        NotificationCenter.default.post(Notification(name: Notification.Name(rawValue: ProductCommunicationManagerStateDidChange)))
        NSLog("Disconnected from product!");
    }
}
