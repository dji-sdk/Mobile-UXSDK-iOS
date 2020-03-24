//
//  MainViewController.swift
//  UXSDK Sample
//
//  Copyright © 2016 DJI. All rights reserved.
//


import UIKit
import DJISDK

func simulatorLocationNumberFormatter() -> NumberFormatter {
    let nf = NumberFormatter()
    
    nf.usesSignificantDigits = true
    nf.minimumSignificantDigits = 8
    nf.alwaysShowsDecimalSeparator = true
    
    return nf
}

class MainViewController: UITableViewController, UITextFieldDelegate {

    var appDelegate = UIApplication.shared.delegate as! AppDelegate
    
    @IBOutlet weak var version: UILabel!
    @IBOutlet weak var registered: UILabel!
    @IBOutlet weak var register: UIButton!
    @IBOutlet weak var connected: UILabel!
    @IBOutlet weak var connect: UIButton!
    
    // Bridge Mode Controls
    @IBOutlet weak var bridgeModeSwitch: UISwitch!
    @IBOutlet weak var bridgeModeIPField: UITextField!
    
    // Simulator Controls
    @IBOutlet weak var simulatorOnOrOff: UILabel!
    @IBOutlet weak var startOrStopSimulator: UIButton!
    
    static let numberFormatter:NumberFormatter = simulatorLocationNumberFormatter()
    
    @IBOutlet weak var userAccountStatusHeader: UILabel!
    @IBOutlet weak var currentUserAccountStatus: UILabel!
    @IBOutlet weak var loginOrLogout: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        NotificationCenter.default.addObserver(self, selector: #selector(productCommunicationDidChange), name: Notification.Name(rawValue: ProductCommunicationServiceStateDidChange), object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(handleFlightControllerSimulatorDidStart), name: Notification.Name(rawValue: FligntControllerSimulatorDidStart), object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(handleFlightControllerSimulatorDidStop), name: Notification.Name(rawValue: FligntControllerSimulatorDidStop), object: nil)
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        var version = DJISDKManager.sdkVersion()
        if version == "" {
            version = "N/A"
        }
        
        self.version.text = "Version \(version)"
        
        self.bridgeModeSwitch.setOn(ProductCommunicationService.shared.useBridge, animated: true)
        self.bridgeModeIPField.text = ProductCommunicationService.shared.bridgeAppIP
        
        self.updateSimulatorControls(isSimulatorActive: ProductCommunicationService.shared.isSimulatorActive)
    }

    @IBAction func registerAction() {
        ProductCommunicationService.shared.registerWithProduct()
    }
    
    @IBAction func connectAction() {
        ProductCommunicationService.shared.connectToProduct()
    }
    
    @IBAction func userAccountAction() {
        if (DJISDKManager.userAccountManager().userAccountState == .notLoggedIn ||
            DJISDKManager.userAccountManager().userAccountState == .tokenOutOfDate ||
            DJISDKManager.userAccountManager().userAccountState == .unknown) {
            DJISDKManager.userAccountManager().logIntoDJIUserAccount(withAuthorizationRequired: false) { (state, error) in
                if(error != nil){
                    NSLog("Login failed: %@" + String(describing: error))
                }
                self.updateUserAccountStatus()
            }
        } else {
            DJISDKManager.userAccountManager().logOutOfDJIUserAccount { (error:Error?) in
                if(error != nil){
                    NSLog("Logout failed: %@" + String(describing: error))
                }
                self.updateUserAccountStatus()
            }
        }
    }
    
    func updateUserAccountStatus() {
        if DJISDKManager.userAccountManager().userAccountState == .notLoggedIn {
            self.currentUserAccountStatus?.text = "Not Logged In"
        } else if DJISDKManager.userAccountManager().userAccountState == .tokenOutOfDate {
            self.currentUserAccountStatus?.text = "Token Out of Date"
        } else if DJISDKManager.userAccountManager().userAccountState == .notAuthorized {
            self.currentUserAccountStatus?.text = "Not Authorized"
        } else if DJISDKManager.userAccountManager().userAccountState == .authorized {
            self.currentUserAccountStatus?.text = "Authorized"
        } else if DJISDKManager.userAccountManager().userAccountState == .unknown {
            self.currentUserAccountStatus?.text = "Unknown"
        }
    }
    
    @objc func productCommunicationDidChange() {
        
        //If this demo is used in China, it's required to login to your DJI account to activate the application. Also you need to use DJI Go app to bind the aircraft to your DJI account. For more details, please check this demo's tutorial.
        self.updateUserAccountStatus()
        
        if ProductCommunicationService.shared.registered {
            self.registered.text = "YES"
            self.register.isHidden = true
        } else {
            self.registered.text = "NO"
            self.register.isHidden = false
        }
        
        if ProductCommunicationService.shared.connected {
            self.connected.text = "YES"
            self.connect.isHidden = true
        } else {
            self.connected.text = "NO"
            self.connect.isHidden = false
        }
    }
    
    // MARK: - Bridge Mode Controls
    
    @objc func handleBridgeModeSwitchValueChanged(_ sender:Any) {
        ProductCommunicationService.shared.useBridge = self.bridgeModeSwitch.isOn
    }
    
    // MARK: - UITextFieldDelegate
    
    func textFieldDidEndEditing(_ textField: UITextField) {
        if textField == self.bridgeModeIPField {
            ProductCommunicationService.shared.bridgeAppIP = textField.text!
        }
    }
    
    func textField(_ textField: UITextField, shouldChangeCharactersIn range: NSRange, replacementString string: String) -> Bool {
        return true
    }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true
    }
    
    // MARK: - Simulator Controls

    @objc func handleFlightControllerSimulatorDidStart() {
        self.dismiss(self)
        self.updateSimulatorControls(isSimulatorActive: true)
    }
    
    @objc func handleFlightControllerSimulatorDidStop() {
        self.updateSimulatorControls(isSimulatorActive: false)
    }
    
    @objc func updateSimulatorControls(isSimulatorActive:Bool) {
        self.simulatorOnOrOff.text = isSimulatorActive ? "ON" : "OFF"
        let simulatorControlTitle = isSimulatorActive ? "Stop" : "Start"
        self.startOrStopSimulator.setTitle(simulatorControlTitle, for: .normal)
        self.startOrStopSimulator.setTitle(simulatorControlTitle, for: .highlighted)
        self.startOrStopSimulator.setTitle(simulatorControlTitle, for: .disabled)
        self.startOrStopSimulator.setTitle(simulatorControlTitle, for: .selected)
    }
    
    
    @IBAction func handleStartOrStopSimulator() {
        if ProductCommunicationService.shared.isSimulatorActive == true {
            let didStartStoppingSimulator = ProductCommunicationService.shared.stopSimulator()
            self.dismiss(self)
            if !didStartStoppingSimulator {
                self.presentError("Could Not Begin Stopping Simulator")
            }
            
        } else {
            let viewController = SimulatorControlsViewController()
            
            let navigationController = UINavigationController(rootViewController: viewController)
        
            let dismissItem = UIBarButtonItem(barButtonSystemItem: .done,
                                              target: self,
                                              action: #selector(MainViewController.dismiss(_:)))
            viewController.navigationItem.rightBarButtonItem = dismissItem
            
            navigationController.modalPresentationStyle = .formSheet
            viewController.modalPresentationStyle = .formSheet
            
            self.present(navigationController,
                         animated: true,
                         completion: nil)
        }
    }
    
    @objc public func dismiss(_ sender: Any) {
        self.presentedViewController?.dismiss(animated: true,
                                            completion: nil)
    }
}

extension UIViewController {
    func presentError(_ errorDescription:String) {
        let alertController = UIAlertController(title: "Error",
                                              message: errorDescription,
                                              preferredStyle: .alert)
        let action = UIAlertAction(title: "Ok",
                                   style: .cancel,
                                 handler: nil)
        
        alertController.addAction(action)
        
        self.present(alertController,
                     animated: true,
                     completion: nil)
    }
}
