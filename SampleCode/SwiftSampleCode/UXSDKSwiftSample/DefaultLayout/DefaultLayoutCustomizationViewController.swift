//
//  DefaultLayoutCustomizationViewController.swift
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
