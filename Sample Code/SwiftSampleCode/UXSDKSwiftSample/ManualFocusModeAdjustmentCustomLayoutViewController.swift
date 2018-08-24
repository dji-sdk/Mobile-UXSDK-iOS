//
//  ManualFocusModeAdjustmentCustomLayoutViewController.swift
//  UXSDK Sample
//
//  Copyright © 2018 DJI. All rights reserved.
//

import UIKit
import DJIUXSDK
import DJISDK

class ManualFocusModeAdjustmentCustomLayoutViewController: DUXDefaultLayoutViewController, DUXObjectProtocol {
    @IBOutlet weak var manualFocusAdjustmentControl: DUXManualFocusAdjustmentWidget!
    var currentFocusMode = DJICameraFocusMode.unknown
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        DUXSDKModel.default()?.registerDependentKeys(self.dependentKeys(), forObject: self)
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        DUXSDKModel.default()?.unregisterDependentKeys(forObject: self)
        super.viewWillDisappear(animated)
    }
    
    @IBAction func close () {
        self.dismiss(animated: true) {
            
        }
    }
    
    // MARK: - DUXObjectProtocol
    func dependentKeys() -> [DJIKey] {
        return [
            DJICameraKey(param: DJICameraParamFocusMode)!
        ]
    }
    
    func transform(_ value: DUXSDKModelValue, for key: DJIKey) {
        if (key.param == DJICameraParamFocusMode) {
            self.currentFocusMode = DJICameraFocusMode(rawValue: value.unsignedIntegerValue)!
        }
    }
    
    func update() {
        self.manualFocusAdjustmentControl.isHidden = !(self.currentFocusMode == DJICameraFocusMode.manual)
    }
}
