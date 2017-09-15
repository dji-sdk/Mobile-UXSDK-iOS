//
//  MyBatteryWidget.swift
//  UILib Sample
//
//  Created by Arnaud Thiercelin on 12/14/16.
//  Copyright © 2016 DJI. All rights reserved.
//

import UIKit
import DJIUILibrary

class MyBatteryWidget: DULBatteryWidget {

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
    override func transform(_ value: DULSDKModelValue, for key: DJIKey) {
        
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
