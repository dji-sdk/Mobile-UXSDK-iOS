//
//  DefaultLayoutCustomizationViewController.swift
//  UILib Sample
//
//  Copyright © 2016 DJI. All rights reserved.
//


import UIKit
import DJIUILibrary

// We subclass the DULRootViewController to inherit all its behavior.
class DefaultLayoutCustomizationViewController: DULDefaultLayoutViewController {
    
    var isContentViewSwitched = false
    
    var oldContentViewController: DULFPVViewController?
    
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
            self.oldContentViewController = self.contentViewController as? DULFPVViewController
            self.contentViewController = newContentViewController
        }
        
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }
}
