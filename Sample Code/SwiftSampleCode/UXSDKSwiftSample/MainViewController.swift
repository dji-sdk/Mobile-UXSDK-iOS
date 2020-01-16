//
//  MainViewController.swift
//  UXSDK Sample
//
//  Copyright © 2016 DJI. All rights reserved.
//


import UIKit
import DJISDK

class MainViewController: UITableViewController {

    var appDelegate = UIApplication.shared.delegate as! AppDelegate
    
    @IBOutlet weak var version: UILabel!
    @IBOutlet weak var registered: UILabel!
    @IBOutlet weak var register: UIButton!
    @IBOutlet weak var connected: UILabel!
    @IBOutlet weak var connect: UIButton!
    
    @IBOutlet weak var userAccountStatusHeader: UILabel!
    @IBOutlet weak var currentUserAccountStatus: UILabel!
    @IBOutlet weak var loginOrLogout: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        NotificationCenter.default.addObserver(self, selector: #selector(productCommunicationDidChange), name: Notification.Name(rawValue: ProductCommunicationManagerStateDidChange), object: nil)
        
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        var version = DJISDKManager.sdkVersion()
        if version == "" {
            version = "N/A"
        }
        
        self.version.text = "Version \(version)"
    }

    @IBAction func registerAction() {
        self.appDelegate.productCommManager.registerWithProduct()
    }
    
    @IBAction func connectAction() {
        self.appDelegate.productCommManager.connectToProduct()
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
        
        if self.appDelegate.productCommManager.registered {
            self.registered.text = "YES"
            self.register.isHidden = true
        } else {
            self.registered.text = "NO"
            self.register.isHidden = false
        }
        
        if self.appDelegate.productCommManager.connected {
            self.connected.text = "YES"
            self.connect.isHidden = true
        } else {
            self.connected.text = "NO"
            self.connect.isHidden = false
        }
    }
}
