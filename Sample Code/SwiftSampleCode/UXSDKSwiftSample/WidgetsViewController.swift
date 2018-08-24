//
//  WidgetsViewController.swift
//  UXSDK Sample
//
//  Copyright © 2016 DJI. All rights reserved.
//

import UIKit
import DJIUXSDK

class WidgetsViewController: UIViewController {
    
    var widgets = [AnyObject]()
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

    
    @IBAction func close () {
        self.dismiss(animated: true) {
            
        }
    }
    
}
