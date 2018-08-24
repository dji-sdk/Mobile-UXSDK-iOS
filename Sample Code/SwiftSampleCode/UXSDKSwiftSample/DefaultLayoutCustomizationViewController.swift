//
//  DefaultLayoutCustomizationViewController.swift
//  UXSDK Sample
//
//  Copyright © 2016 DJI. All rights reserved.
//


import UIKit
import DJIUXSDK

// We subclass the DUXRootViewController to inherit all its behavior.
class DefaultLayoutCustomizationViewController: DUXDefaultLayoutViewController {
    
    var isContentViewSwitched = false
    
    var oldContentViewController: DUXFPVViewController?
    
    override var preferredStatusBarStyle: UIStatusBarStyle {
        return .lightContent;
    }
    
    @IBAction func close () {
        self.dismiss(animated: true) {
            
        }
    }
    
    // Toggle for the content view for our button.  This will swap between our red view controller and the fpv view controller.
    @IBAction func switchContent(_ sender: UIButton) {
        if (isContentViewSwitched) {
            isContentViewSwitched = false
            self.contentViewController = self.oldContentViewController
        } else {
            isContentViewSwitched = true
            let newContentViewController = UIViewController()
            newContentViewController.view.backgroundColor = UIColor.red
            self.oldContentViewController = self.contentViewController as? DUXFPVViewController
            self.contentViewController = newContentViewController
        }
        
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }
}
