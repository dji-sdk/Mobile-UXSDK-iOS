//
//  UIButtonExtension.swift
//  UXSDKSwiftSample
//
//  Created by Andreas Gising on 2020-08-20.
//  Copyright © 2020 DJI. All rights reserved.
//

import Foundation
import UIKit

extension UIButton{
    func pulsate() {
        let pulse = CASpringAnimation(keyPath: "transform.scale")
        pulse.duration = 0.8
        pulse.fromValue = 1.0
        pulse.toValue = 1.02
        pulse.autoreverses = true
        pulse.repeatCount = .infinity
        pulse.initialVelocity = 0.5
        pulse.damping = 1.0
        
        layer.add(pulse, forKey: nil)
    }
    
    func flash(duration: CFTimeInterval) {
           
        let flash = CABasicAnimation(keyPath: "opacity")
        flash.duration = duration
        flash.fromValue = 1
        flash.toValue = 0.1
        flash.timingFunction = CAMediaTimingFunction(name: CAMediaTimingFunctionName.easeInEaseOut)
        flash.autoreverses = true
        flash.repeatCount = .infinity
           
           layer.add(flash, forKey: nil)
    }
       
     
    func shake() {
       
        let shake = CABasicAnimation(keyPath: "position")
        shake.duration = 0.1
        shake.repeatCount = 2
        shake.autoreverses = true
       
        let fromPoint = CGPoint(x: center.x - 5, y: center.y)
        let fromValue = NSValue(cgPoint: fromPoint)
       
        let toPoint = CGPoint(x: center.x + 5, y: center.y)
        let toValue = NSValue(cgPoint: toPoint)
       
        shake.fromValue = fromValue
        shake.toValue = toValue
       
        layer.add(shake, forKey: "position")
   }
}
