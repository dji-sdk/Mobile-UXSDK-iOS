//
//  DefaultLayoutViewController.swift
//  UXSDK Sample
//
//  Copyright © 2016 DJI. All rights reserved.
//

import UIKit
import DJIUXSDK

// We subclass the DUXRootViewController to inherit all its behavior and add
// a couple of widgets in the storyboard.
class DefaultLayoutViewController: DUXDefaultLayoutViewController {

    override var preferredStatusBarStyle: UIStatusBarStyle {
        return .lightContent;
    }
    
    @IBAction func close () {
        self.dismiss(animated: true) {
            
        }
    }
    
    // We are going to add focus adjustment to the default view.
    override func viewDidLoad() {
        super.viewDidLoad()
        
    }
}
