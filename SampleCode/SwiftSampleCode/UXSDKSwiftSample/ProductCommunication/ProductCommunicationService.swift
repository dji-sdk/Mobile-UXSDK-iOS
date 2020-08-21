//
//  ProductCommunicationService.swift
//  UXSDK Sample
//
//  MIT License
//
//  Copyright © 2018-2020 DJI
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:

//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.

//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//

import UIKit
import DJISDK

let ProductCommunicationServiceStateDidChange = "ProductCommunicationServiceStateDidChange"

// Automatically set default to bridge when on iOS simulator
func defaultUseBridgeSetting() -> Bool {
    #if arch(i386) || arch(x86_64)
        return true
    #else
        return false
    #endif
}

func postNotificationNamed(_ rawStringName:String,
                           dispatchOntoMainQueue:Bool = false,
                           notificationCenter:NotificationCenter = NotificationCenter.default) {
    let post = {
        notificationCenter.post(Notification(name: Notification.Name(rawValue: rawStringName)))
    }
    
    if dispatchOntoMainQueue {
        DispatchQueue.main.async {
            post()
        }
    } else {
        post()
    }
}

public let FligntControllerSimulatorDidStart = "FligntControllerSimulatorDidStart"
public let FligntControllerSimulatorDidStop = "FligntControllerSimulatorDidStop"

class SimulatorControl: NSObject {
    fileprivate var _isSimulatorActive: Bool = false
    public var isSimulatorActive: Bool {
        get {
            return _isSimulatorActive
        }
        set {
            _isSimulatorActive = newValue
            postNotificationNamed(newValue ? FligntControllerSimulatorDidStart : FligntControllerSimulatorDidStop, dispatchOntoMainQueue: true)
        }
    }
    
    func startListeningToProductState() {
        if let isSimulatorActiveKey = DJIFlightControllerKey(param: DJIFlightControllerParamIsSimulatorActive) {
            DJISDKManager.keyManager()?.startListeningForChanges(on: isSimulatorActiveKey, withListener: self, andUpdate: { (oldValue: DJIKeyedValue?, newValue: DJIKeyedValue?) in
                if let isSimulatorActive = newValue?.boolValue {
                    self.isSimulatorActive = isSimulatorActive
                }
            })
            
            DJISDKManager.keyManager()?.getValueFor(isSimulatorActiveKey, withCompletion: { (value: DJIKeyedValue?, error: Error?) in
                if let isSimulatorActive = value?.boolValue {
                    self.isSimulatorActive = isSimulatorActive
                }
            })
        }
    }
    
    func stopListeningOnProductState() {
        let isSimulatorActiveKey = DJIFlightControllerKey(param: DJIFlightControllerParamIsSimulatorActive)!
        
        DJISDKManager.keyManager()?.stopListening(on: isSimulatorActiveKey,
                                          ofListener: self)
    }
    
    deinit {
        self.stopListeningOnProductState()
    }
    
    // Returns false if no aircraft present, true if simulator command sent
    func startSimulator(at locationCoordinates:CLLocationCoordinate2D) -> Bool {
        guard let aircraft = DJISDKManager.product() as? DJIAircraft else {
            return false
        }
        
        guard let simulator = aircraft.flightController?.simulator else {
            return false
        }
        
        simulator.start(withLocation: locationCoordinates,
                     updateFrequency: 20,
                 gpsSatellitesNumber: 12) { (error:Error?) in
            if let e = error {
                print("Start Simulator Error: \(e)")
            } else {
                print("Start Simulator Command Acked")
            }
        }
        
        return true
    }
    
    func stopSimulator() -> Bool {
        guard let stopSimulatorKey = DJIFlightControllerKey(param: DJIFlightControllerParamStopSimulator) else {
            return false
        }
        
        guard let keyManager = DJISDKManager.keyManager() else {
            return false
        }
        
        keyManager.performAction(for: stopSimulatorKey,
                                 withArguments: nil,
                                 andCompletion: { (didSucceed:Bool, value:DJIKeyedValue?, error:Error?) in
            if let e = error {
                print("Stop Simulator Error: \(e)")
            } else {
                print("Stop Simulator Command Acked")
            }
        })
        
        return true
    }
}

// Returns "0.0.0.0" if no cached value present
func fetchCachedBridgeAppIP() -> String {
    if let ip = UserDefaults.standard.value(forKey: "bridgeAppIP") as? String {
        return ip
    } else {
        return "0.0.0.0"
    }
}

@dynamicMemberLookup
class ProductCommunicationService: NSObject, DJISDKManagerDelegate {
    // Static Instance
    static let shared = ProductCommunicationService()
    
    open weak var appDelegate = UIApplication.shared.delegate as? AppDelegate
    open var connectedProduct: DJIBaseProduct!
    
    var registered = false
    var connected = false
    
    var bridgeAppIP = fetchCachedBridgeAppIP() {
        didSet {
            UserDefaults.standard.set(bridgeAppIP, forKey: "bridgeAppIP")
        }
    }
    var useBridge = defaultUseBridgeSetting() {
        didSet {
            if useBridge == false {
                NSLog("Disabling bridge mode...")
                DJISDKManager.disableBridgeMode()
            } else {
                NSLog("Enabling bridge mode with IP \(self.bridgeAppIP)...")
                DJISDKManager.enableBridgeMode(withBridgeAppIP: self.bridgeAppIP)
            }
        }
    }
    
    //MARK: - Start Registration
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
    
    //MARK: - Start Connecting to Product
    open func connectToProduct() {
        if self.useBridge {
            NSLog("Connecting to Product using debug IP address: \(bridgeAppIP)...")
            DJISDKManager.enableBridgeMode(withBridgeAppIP: bridgeAppIP)
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
    
    public func disconnectProduct() {
        DJISDKManager.stopConnectionToProduct()
        
        // This is a little cheat because sdkmanager is not properly disconnecting the product.
        self.connected = false
        NotificationCenter.default.post(Notification(name: Notification.Name(rawValue: "ProductCommunicationManagerStateDidChange")))
    }
    
    //MARK: - DJISDKManagerDelegate
    func appRegisteredWithError(_ error: Error?) {
        if error == nil {
            self.registered = true
            postNotificationNamed(ProductCommunicationServiceStateDidChange, dispatchOntoMainQueue: true)
            self.simulatorControl.startListeningToProductState()
            self.connectToProduct()
        } else {
            NSLog("Error Registrating App: \(String(describing: error))")
        }
    }
    
    func didUpdateDatabaseDownloadProgress(_ progress: Progress) {
        print("Downloading Database Progress: \(progress.completedUnitCount) / \(progress.totalUnitCount)")
    }
    
    func productConnected(_ product: DJIBaseProduct?) {
        if product != nil {
            self.connected = true
            NotificationCenter.default.post(Notification(name: Notification.Name(rawValue: ProductCommunicationServiceStateDidChange)))
            NSLog("Connection to new product succeeded!")
            self.connectedProduct = product
            self.simulatorControl.startListeningToProductState()
        }
    }
    
    func productDisconnected() {
        self.connected = false
        NotificationCenter.default.post(Notification(name: Notification.Name(rawValue: ProductCommunicationServiceStateDidChange)))
        NSLog("Disconnected from product!");
    }
    
    //MARK: - Bridge Mode API
    
    //MARK: - Simulator Controls API
    let simulatorControl:SimulatorControl = SimulatorControl()
    
    // Leverages Swift language feature described in SE-0252
    subscript(dynamicMember keyPath: KeyPath<SimulatorControl, Bool>) -> Bool {
        return simulatorControl[keyPath: keyPath]
    }
    
    // Returns false if no aircraft present, true if simulator command sent
    func stopSimulator() -> Bool {
        return self.simulatorControl.stopSimulator()
    }
    
    // Returns false if no aircraft present, true if simulator command sent
    func startSimulator(at locationCoordinates:CLLocationCoordinate2D) -> Bool {
        return self.simulatorControl.startSimulator(at: locationCoordinates)
    }
}
