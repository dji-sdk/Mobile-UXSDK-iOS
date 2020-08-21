//
//  MyBatteryWidget.swift
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

class MyBatteryWidget: DUXBatteryWidget {

    let percentageLabel = UILabel()
    
    override func prepare() { // This is - (void)prepareWidget in Objective-C
        // We do not call super, because we are overriding the whole design aspect
        
        percentageLabel.textColor = UIColor.green
        percentageLabel.adjustsFontSizeToFitWidth = true
        percentageLabel.font = UIFont.systemFont(ofSize: 100)
        percentageLabel.minimumScaleFactor = 0.1
        percentageLabel.numberOfLines = 0
        percentageLabel.textAlignment = .center
        percentageLabel.translatesAutoresizingMaskIntoConstraints = false
        self.addSubview(percentageLabel)
        percentageLabel.topAnchor.constraint(equalTo: self.topAnchor).isActive = true
        percentageLabel.bottomAnchor.constraint(equalTo: self.bottomAnchor).isActive = true
        percentageLabel.leadingAnchor.constraint(equalTo: self.leadingAnchor).isActive = true
        percentageLabel.trailingAnchor.constraint(equalTo: self.trailingAnchor).isActive = true
        
        self.update()
    }
    
    // Subclass (override) this method if you want to change how the data is processed.
    // in our case, we won't need it.
    /*
    override func transform(_ value: DUXSDKModelValue, for key: DJIKey) {
        
    }
     */
    
    override func update() {
        if self.battery1Percentage < 10 {
            self.percentageLabel.textColor = UIColor.red
        } else {
            self.percentageLabel.textColor = UIColor.green
        }
        
        let uiString = String(format: "%.0f", self.battery1Percentage)
        self.percentageLabel.text = "\(uiString)%"
    }
    
}
