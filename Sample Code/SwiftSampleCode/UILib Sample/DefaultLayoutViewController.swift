//
//  DefaultLayoutViewController.swift
//  DJIUILibrary
//
//  Created by Arnaud Thiercelin on 12/12/16.
//  Copyright © 2016 DJI. All rights reserved.
//

import UIKit
import DJIUILibrary

// We subclass the DULRootViewController to inherit all its behavior and add
// a couple of widgets in the storyboard.
class DefaultLayoutViewController: DULDefaultLayoutViewController {

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
