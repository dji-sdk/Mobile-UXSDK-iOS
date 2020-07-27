//
//  CustomMapViewController.swift
//  DJIUXSDKTest
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
import iOS_Color_Picker

class CustomMapViewController: UIViewController, UIPickerViewDelegate, UIPickerViewDataSource, FCColorPickerViewControllerDelegate {
    
    var mapViewController:DUXMapViewController?
    
    @IBOutlet weak var widthSlider:UISlider?
    @IBOutlet weak var alphaSlider:UISlider?
    @IBOutlet weak var widthLabel:UILabel?
    @IBOutlet weak var alphaLabel:UILabel?
    
    @IBOutlet weak var lockAircraftCameraSwitch:UISwitch?
    @IBOutlet weak var lockHomeCameraSwitch:UISwitch?
    
    @IBOutlet weak var flyZoneDisplaySwitch:UISwitch?
    
    @IBOutlet weak var colorSelectionPickerView:UIPickerView?
    @IBOutlet weak var widthSelectionPickerView:UIPickerView?
    @IBOutlet weak var alphaSelectionPickerView:UIPickerView?
    @IBOutlet weak var visibleFlyZoneSelectionPickerView:UIPickerView?
    
    var colorPickerCurrentlySelectedRow: Int = 0
    var widthPickerCurrentlySelectedRow: Int = 0
    var alphaPickerCurrentlySelectedRow: Int = 0
    var visibleFlyZonesPickerCurrentlySelectedRow: Int = 0
    
    @IBOutlet weak var replaceIconSegmentedView: UISegmentedControl!
    @IBOutlet weak var replaceIconBlurView: UIVisualEffectView!
    @IBOutlet weak var replaceIconImageView: UIImageView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.widthSlider?.minimumValue = 0.5
        self.widthSlider?.maximumValue = 10.0
        
        self.mapViewController?.mapWidget.showDirectionToHome = true
        self.replaceIconBlurView.layer.cornerRadius           = 7.0
        self.replaceIconBlurView.layer.masksToBounds          = true
        self.mapViewController?.mapWidget.visibleFlyZones     = []
        
        if let selectedColorSelectionPickerViewRow = self.colorSelectionPickerView?.selectedRow(inComponent: 0) {
            self.colorPickerCurrentlySelectedRow = selectedColorSelectionPickerViewRow
        }
        
        if let selectedAlphaSelectionPickerViewRow = self.alphaSelectionPickerView?.selectedRow(inComponent: 0) {
            self.alphaPickerCurrentlySelectedRow = selectedAlphaSelectionPickerViewRow
        }
        
        if let selectedWidthSelectionPickerViewRow = self.widthSelectionPickerView?.selectedRow(inComponent: 0) {
            self.widthPickerCurrentlySelectedRow = selectedWidthSelectionPickerViewRow
        }
        
        if let selectedVisibleFlyZonesSelectionPickerViewRow = self.visibleFlyZoneSelectionPickerView?.selectedRow(inComponent: 0) {
            self.visibleFlyZonesPickerCurrentlySelectedRow = selectedVisibleFlyZonesSelectionPickerViewRow
        }
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        self.updateAlpha()
        self.updateWidth()
        self.updateFlyZones()
    }
    
    func updateAlpha() {
        if self.alphaPickerCurrentlySelectedRow == 0 {
            self.alphaSlider?.setValue(Float(self.mapViewController!.mapWidget.flyZoneOverlayAlpha(for: .restricted)), animated: false)
            self.alphaLabel?.text = "\(self.mapViewController!.mapWidget.flyZoneOverlayAlpha(for: .restricted))"
        } else if self.alphaPickerCurrentlySelectedRow == 1 {
            self.alphaSlider?.setValue(Float(self.mapViewController!.mapWidget.flyZoneOverlayAlpha(for: .authorization)), animated: false)
            self.alphaLabel?.text = "\(self.mapViewController!.mapWidget.flyZoneOverlayAlpha(for: .authorization))"
        } else if self.alphaPickerCurrentlySelectedRow == 2 {
            self.alphaSlider?.setValue(Float(self.mapViewController!.mapWidget.flyZoneOverlayAlpha(for: .enhancedWarning)), animated: false)
            self.alphaLabel?.text = "\(self.mapViewController!.mapWidget.flyZoneOverlayAlpha(for: .enhancedWarning))"
        } else if self.alphaPickerCurrentlySelectedRow == 3 {
            self.alphaSlider?.setValue(Float(self.mapViewController!.mapWidget.flyZoneOverlayAlpha(for: .warning)), animated: false)
            self.alphaLabel?.text = "\(self.mapViewController!.mapWidget.flyZoneOverlayAlpha(for: .warning))"
        } else if self.alphaPickerCurrentlySelectedRow == 4 {
            self.alphaSlider?.setValue(Float(self.mapViewController!.mapWidget.unlockedFlyZoneOverlayAlpha), animated: false)
            self.alphaLabel?.text = "\(self.mapViewController!.mapWidget.unlockedFlyZoneOverlayAlpha)"
        } else if self.alphaPickerCurrentlySelectedRow == 5 {
            self.alphaSlider?.setValue(Float(self.mapViewController!.mapWidget.maximumHeightFlyZoneOverlayAlpha), animated: false)
            self.alphaLabel?.text = "\(self.mapViewController!.mapWidget.maximumHeightFlyZoneOverlayAlpha)"
        } else if self.alphaPickerCurrentlySelectedRow == 6 {
            self.alphaSlider?.setValue(Float(self.mapViewController!.mapWidget.customUnlockFlyZoneOverlayAlpha), animated: false)
            self.alphaLabel?.text = "\(self.mapViewController!.mapWidget.customUnlockFlyZoneOverlayAlpha)"
        } else if self.alphaPickerCurrentlySelectedRow == 7 {
            self.alphaSlider?.setValue(Float(self.mapViewController!.mapWidget.customUnlockFlyZoneSentToAircraftOverlayAlpha), animated: false)
            self.alphaLabel?.text = "\(self.mapViewController!.mapWidget.customUnlockFlyZoneSentToAircraftOverlayAlpha)"
        } else if self.alphaPickerCurrentlySelectedRow == 8 {
            self.alphaSlider?.setValue(Float(self.mapViewController!.mapWidget.customUnlockFlyZoneEnabledOverlayAlpha), animated: false)
            self.alphaLabel?.text = "\(self.mapViewController!.mapWidget.customUnlockFlyZoneEnabledOverlayAlpha)"
        }
    }
    
    func updateFlyZones() {
        var visibleFlyZones:DUXMapVisibleFlyZones = []
        
        if self.visibleFlyZonesPickerCurrentlySelectedRow == 0 {
            visibleFlyZones.insert(DUXMapVisibleFlyZones.restricted)
        } else if self.visibleFlyZonesPickerCurrentlySelectedRow == 1 {
            visibleFlyZones.insert(DUXMapVisibleFlyZones.authorization)
        } else if self.visibleFlyZonesPickerCurrentlySelectedRow == 2 {
            visibleFlyZones.insert(DUXMapVisibleFlyZones.enhancedWarning)
        } else if self.visibleFlyZonesPickerCurrentlySelectedRow == 3 {
            visibleFlyZones.insert(DUXMapVisibleFlyZones.warning)
        }
        
        self.flyZoneDisplaySwitch?.setOn((self.mapViewController?.mapWidget.visibleFlyZones.contains(visibleFlyZones))!, animated: true)
    }
    
    func updateWidth() {
        if self.widthPickerCurrentlySelectedRow == 0 {
            self.widthSlider?.setValue(Float(self.mapViewController!.mapWidget.flyZoneOverlayBorderWidth), animated: false)
            self.widthLabel?.text = "\(self.mapViewController!.mapWidget.flyZoneOverlayBorderWidth)"
        } else if self.widthPickerCurrentlySelectedRow == 1 {
            self.widthSlider?.setValue(Float(self.mapViewController!.mapWidget.flightPathStrokeWidth), animated: false)
            self.widthLabel?.text = "\(self.mapViewController!.mapWidget.flightPathStrokeWidth)"
        } else if self.widthPickerCurrentlySelectedRow == 2 {
            self.widthSlider?.setValue(Float(self.mapViewController!.mapWidget.directionToHomeStrokeWidth), animated: false)
            self.widthLabel?.text = "\(self.mapViewController!.mapWidget.directionToHomeStrokeWidth)"
        }
    }
    
    @IBAction func widthSliderControlChanged(sender: UISlider) {
        let sliderValue = CGFloat(sender.value)
        self.widthLabel?.text = "\(sliderValue)"
        
        if self.widthPickerCurrentlySelectedRow == 0 {
            self.mapViewController?.mapWidget.flyZoneOverlayBorderWidth = sliderValue
        } else if self.widthPickerCurrentlySelectedRow == 1 {
            self.mapViewController?.mapWidget.flightPathStrokeWidth = sliderValue
        } else if self.widthPickerCurrentlySelectedRow == 2 {
            self.mapViewController?.mapWidget.directionToHomeStrokeWidth = sliderValue
        }
    }
    
    @IBAction func alphaSliderControlChanged(sender: UISlider) {
        let sliderValue = CGFloat(sender.value)
        self.alphaLabel?.text = "\(sliderValue)"
        
        if self.alphaPickerCurrentlySelectedRow == 0 {
            self.mapViewController?.mapWidget.setFlyZoneOverlayAlpha(sliderValue, for: .restricted)
        } else if self.alphaPickerCurrentlySelectedRow == 1 {
            self.mapViewController?.mapWidget.setFlyZoneOverlayAlpha(sliderValue, for: .authorization)
        } else if self.alphaPickerCurrentlySelectedRow == 2 {
            self.mapViewController?.mapWidget.setFlyZoneOverlayAlpha(sliderValue, for: .enhancedWarning)
        } else if self.alphaPickerCurrentlySelectedRow == 3 {
            self.mapViewController?.mapWidget.setFlyZoneOverlayAlpha(sliderValue, for: .warning)
        } else if self.alphaPickerCurrentlySelectedRow == 4 {
            self.mapViewController?.mapWidget.unlockedFlyZoneOverlayAlpha = sliderValue
        } else if self.alphaPickerCurrentlySelectedRow == 5 {
            self.mapViewController?.mapWidget.maximumHeightFlyZoneOverlayAlpha = sliderValue
        } else if self.alphaPickerCurrentlySelectedRow == 6 {
            self.mapViewController?.mapWidget.customUnlockFlyZoneOverlayAlpha = sliderValue
        } else if self.alphaPickerCurrentlySelectedRow == 7 {
            self.mapViewController?.mapWidget.customUnlockFlyZoneSentToAircraftOverlayAlpha = sliderValue
        } else if self.alphaPickerCurrentlySelectedRow == 8 {
            self.mapViewController?.mapWidget.customUnlockFlyZoneEnabledOverlayAlpha = sliderValue
        }
    }
    
    @IBAction func flyZoneDisplaySwitchValueChanged(sender: UISwitch) {
        let isOn = sender.isOn
        var visibleFlyZones:DUXMapVisibleFlyZones = []
        
        if self.visibleFlyZonesPickerCurrentlySelectedRow == 0 {
            visibleFlyZones.insert(DUXMapVisibleFlyZones.restricted)
        } else if self.visibleFlyZonesPickerCurrentlySelectedRow == 1 {
            visibleFlyZones.insert(DUXMapVisibleFlyZones.authorization)
        } else if self.visibleFlyZonesPickerCurrentlySelectedRow == 2 {
            visibleFlyZones.insert(DUXMapVisibleFlyZones.enhancedWarning)
        } else if self.visibleFlyZonesPickerCurrentlySelectedRow == 3 {
            visibleFlyZones.insert(DUXMapVisibleFlyZones.warning)
        }
        
        if isOn {
            self.mapViewController?.mapWidget.visibleFlyZones.insert(visibleFlyZones)
        } else {
            self.mapViewController?.mapWidget.visibleFlyZones.remove(visibleFlyZones)
        }
        
        self.updateFlyZones()
    }
    
    func updateMapWith(color:UIColor) {
        if colorPickerCurrentlySelectedRow == 0 {
            self.mapViewController?.mapWidget.setFlyZoneOverlayColor(color, for: .restricted)
        } else if colorPickerCurrentlySelectedRow == 1 {
            self.mapViewController?.mapWidget.setFlyZoneOverlayColor(color, for: .authorization)
        } else if colorPickerCurrentlySelectedRow == 2 {
            self.mapViewController?.mapWidget.setFlyZoneOverlayColor(color, for: .enhancedWarning)
        } else if colorPickerCurrentlySelectedRow == 3 {
            self.mapViewController?.mapWidget.setFlyZoneOverlayColor(color, for: .warning)
        } else if colorPickerCurrentlySelectedRow == 4 {
            self.mapViewController?.mapWidget.unlockedFlyZoneOverlayColor = color
        } else if colorPickerCurrentlySelectedRow == 5 {
            self.mapViewController?.mapWidget.maximumHeightFlyZoneOverlayColor = color
        } else if colorPickerCurrentlySelectedRow == 6 {
            self.mapViewController?.mapWidget.flightPathStrokeColor = color
        } else if colorPickerCurrentlySelectedRow == 7 {
            self.mapViewController?.mapWidget.directionToHomeStrokeColor = color
        } else if colorPickerCurrentlySelectedRow == 8 {
            self.mapViewController?.mapWidget.customUnlockFlyZoneOverlayColor = color
        } else if self.colorPickerCurrentlySelectedRow == 9 {
            self.mapViewController?.mapWidget.customUnlockFlyZoneSentToAircraftOverlayColor = color
        } else if self.colorPickerCurrentlySelectedRow == 10 {
            self.mapViewController?.mapWidget.customUnlockFlyZoneEnabledOverlayColor = color
        }
    }
    
    @IBAction func close(_ sender: UIButton) {
        self.willMove(toParent: nil)
        self.view.removeFromSuperview()
        self.removeFromParent()
    }
    
    //MARK - FCColorPickerViewControllerDelegate
    
    func colorPickerViewController(_ colorPicker: FCColorPickerViewController, didSelect color: UIColor) {
        self.updateMapWith(color: color)
        self.presentedViewController?.dismiss(animated: true, completion: nil)
    }
    
    func colorPickerViewControllerDidCancel(_ colorPicker: FCColorPickerViewController) {
        self.presentedViewController?.dismiss(animated: true, completion: nil)
    }
    
    func currentlySelectedColorFor(row:Int) -> UIColor? {
        if colorPickerCurrentlySelectedRow == 0 {
            return self.mapViewController?.mapWidget.flyZoneOverlayColor(for: .restricted)
        } else if colorPickerCurrentlySelectedRow == 1 {
            return self.mapViewController?.mapWidget.flyZoneOverlayColor(for: .authorization)
        } else if colorPickerCurrentlySelectedRow == 2 {
            return self.mapViewController?.mapWidget.flyZoneOverlayColor(for: .enhancedWarning)
        } else if colorPickerCurrentlySelectedRow == 3 {
            return self.mapViewController?.mapWidget.flyZoneOverlayColor(for: .warning)
        } else if colorPickerCurrentlySelectedRow == 4 {
            return self.mapViewController?.mapWidget.unlockedFlyZoneOverlayColor
        } else if colorPickerCurrentlySelectedRow == 5 {
            return self.mapViewController?.mapWidget.maximumHeightFlyZoneOverlayColor
        } else if colorPickerCurrentlySelectedRow == 6 {
            return self.mapViewController?.mapWidget.flightPathStrokeColor
        } else if colorPickerCurrentlySelectedRow == 7 {
            return self.mapViewController?.mapWidget.directionToHomeStrokeColor
        } else if colorPickerCurrentlySelectedRow == 8 {
            return self.mapViewController?.mapWidget.customUnlockFlyZoneOverlayColor
        } else if self.colorPickerCurrentlySelectedRow == 9 {
            return self.mapViewController?.mapWidget.customUnlockFlyZoneSentToAircraftOverlayColor
        } else if self.colorPickerCurrentlySelectedRow == 10 {
            return self.mapViewController?.mapWidget.customUnlockFlyZoneEnabledOverlayColor
        } else {
            return nil
        }
    }
    
    @IBAction func toggleColor() {
        if let currentlySelectedColorForPickerTarget = self.currentlySelectedColorFor(row:self.colorPickerCurrentlySelectedRow) {
            let colorPicker = FCColorPickerViewController.colorPicker(with: currentlySelectedColorForPickerTarget, delegate: self)
            self.present(colorPicker, animated: true, completion: nil)
        } else {
            self.updateMapWith(color: UIColor.cyan)
        }
    }
    
    @IBAction func directionToHomeValueChanged(_ sender: UISwitch) {
        self.mapViewController?.mapWidget.showDirectionToHome = sender.isOn
    }
    
    @IBAction func lockAircraftCameraValueChanged(_ sender: UISwitch) {
        self.mapViewController?.mapWidget.isMapCameraLockedOnAircraft = sender.isOn
        if (sender.isOn) {
            self.lockHomeCameraSwitch?.setOn(false, animated: true)
        }
    }
    
    @IBAction func lockHomePointCameraValueChanged(_ sender: UISwitch) {
        self.mapViewController?.mapWidget.isMapCameraLockedOnHomePoint = sender.isOn
        if (sender.isOn) {
            self.lockAircraftCameraSwitch?.setOn(false, animated: true)
        }
    }
    
    @IBAction func showFlightPathValueChanged(_ sender: UISwitch) {
        self.mapViewController?.mapWidget.showFlightPath = sender.isOn
    }
    
    @IBAction func showHomePointValueChanged(_ sender: UISwitch) {
        self.mapViewController?.mapWidget.showHomeAnnotation = sender.isOn
    }
    
    @IBAction func tapToUnlockEnabledValueChanged(_ sender: UISwitch) {
        self.mapViewController?.mapWidget.tapToUnlockEnabled = sender.isOn
    }
    
    @IBAction func showLegendValueChanged(_ sender: UISwitch) {
        self.mapViewController?.showFlyZoneLegend = sender.isOn
    }
    
    @IBAction func showCustomUnlockZonesValueChanged(_ sender: UISwitch) {
        self.mapViewController?.mapWidget!.showCustomUnlockZones = sender.isOn
    }
    
    @IBAction func showDJIAccountLoginIndicator(_ sender: UISwitch) {
        self.mapViewController?.mapWidget!.showDJIAccountLoginIndicator = sender.isOn
    }
    
    @IBAction func replaceIconButtonPressed(_ sender: UIButton) {
        if self.replaceIconSegmentedView.selectedSegmentIndex == 0 {
            self.mapViewController?.mapWidget.changeAnnotation(of: .aircraft, toCustomImage: self.replaceIconImageView.image!, withCenterOffset: CGPoint(x: -8.75, y: -27.3));
        } else if self.replaceIconSegmentedView.selectedSegmentIndex == 1 {
            self.mapViewController?.mapWidget.changeAnnotation(of: .home, toCustomImage: self.replaceIconImageView.image!, withCenterOffset: CGPoint(x: -8, y: -15));
        } else if self.replaceIconSegmentedView.selectedSegmentIndex == 2 {
            self.mapViewController?.mapWidget.changeAnnotation(of: .eligibleFlyZones, toCustomImage: self.replaceIconImageView.image!, withCenterOffset: CGPoint(x: 8, y: -15));
        } else if self.replaceIconSegmentedView.selectedSegmentIndex == 3 {
            self.mapViewController?.mapWidget.changeAnnotation(of: .unlockedFlyZones, toCustomImage: self.replaceIconImageView.image!, withCenterOffset: CGPoint(x: 8, y: -15));
        } else if self.replaceIconSegmentedView.selectedSegmentIndex == 4 {
            self.mapViewController?.mapWidget.changeAnnotation(of: .customUnlockedFlyZones, toCustomImage: self.replaceIconImageView.image!, withCenterOffset: CGPoint(x: 8, y: -15));
        }
    }
    
    @IBAction func replaceIconValueChanged(_ sender: UISegmentedControl) {
        if sender.selectedSegmentIndex == 0 {
            self.replaceIconImageView.image = UIImage(named: "Aircraft")
        } else if sender.selectedSegmentIndex == 2 {
            self.replaceIconImageView.image = UIImage(named: "Lock")
        } else {
            self.replaceIconImageView.image = UIImage(named: "HomePoint")
        }
    }
    
    //MARK: - UIPickerViewDataSource
    
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        if pickerView == self.colorSelectionPickerView {
            return 11
        } else if pickerView == self.widthSelectionPickerView {
            return 3
        } else if pickerView == self.alphaSelectionPickerView {
            return 9
        } else if pickerView == self.visibleFlyZoneSelectionPickerView {
            return 4
        } else {
            return 0
        }
    }
    
    //MARK: - UIPickerViewDelegate
    
    public func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        if pickerView == self.colorSelectionPickerView {
            return self.colorSelectionTitleForRow(row: row, forComponent: component)
        } else if pickerView == self.widthSelectionPickerView {
            return self.widthSelectionTitleForRow(row: row, forComponent: component)
        } else if pickerView == self.alphaSelectionPickerView {
            return self.alphaSelectionTitleForRow(row: row, forComponent: component)
        } else if pickerView == self.visibleFlyZoneSelectionPickerView {
            return self.visibleFlyZoneSelectionTitleForRow(row: row, forComponent: component)
        } else {
            return nil
        }
    }
    
    func colorSelectionTitleForRow(row: Int, forComponent component:Int) -> String? {
        if row == 0 {
            return "Restricted Overlay Color"
        } else if row == 1 {
            return "Authorization Overlay Color"
        } else if row == 2 {
            return "Enhanced Warning Overlay Color"
        } else if row == 3 {
            return "Warning Overlay Color"
        } else if row == 4 {
            return "Self Unlocked Overlay Color"
        } else if row == 5 {
            return "Max Height Overlay Color"
        } else if row == 6 {
            return "Flight Path Color"
        } else if row == 7 {
            return "Direction to Home Color"
        } else if row == 8 {
            return "Custom Unlock Not Sent Not Enabled Color"
        } else if row == 9 {
            return "Custom Unlock Sent Not Enabled Color"
        } else if row == 10 {
            return "Custom Unlock Sent Enabled Color"
        } else {
            return ""
        }
    }
    
    func widthSelectionTitleForRow(row: Int, forComponent component:Int) -> String? {
        if row == 0 {
            return "Overlay Border Width"
        } else if row == 1 {
            return "Flight Path Stroke Width"
        } else if row == 2 {
            return "Direction to Home Stroke Width"
        } else {
            return ""
        }
    }
    
    func alphaSelectionTitleForRow(row: Int, forComponent component:Int) -> String? {
        if row == 0 {
            return "Restricted Overlay Alpha"
        } else if row == 1 {
            return "Authorization Overlay Alpha"
        } else if row == 2 {
            return "Enhanced Warning Overlay Alpha"
        } else if row == 3 {
            return "Warning Overlay Alpha"
        } else if row == 4 {
            return "Self Unlocked Overlay Alpha"
        } else if row == 5 {
            return "Max Height Overlay Alpha"
        } else if row == 6 {
            return "Custom Unlock Not Sent Not Enabled Alpha"
        } else if row == 7 {
            return "Custom Unlock Sent Not Enabled Alpha"
        } else if row == 8 {
            return "Custom Unlock Sent Enabled Alpha"
        } else {
            return ""
        }
    }
    
    func visibleFlyZoneSelectionTitleForRow(row: Int, forComponent component:Int) -> String? {
        if row == 0 {
            return "Restricted"
        } else if row == 1 {
            return "Authorization"
        } else if row == 2 {
            return "Enhanced Warning"
        } else if row == 3 {
            return "Warning"
        } else {
            return ""
        }
    }
    
    public func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        if pickerView == self.colorSelectionPickerView {
            self.didSelectColor(row: row, inComponent: component)
        } else if pickerView == self.widthSelectionPickerView {
            self.didSelectAlpha(row: row, inComponent: component)
        } else if pickerView == self.alphaSelectionPickerView {
            self.didSelectWidth(row: row, inComponent: component)
        } else if pickerView == self.visibleFlyZoneSelectionPickerView {
            self.didSelectVisibleFlyZone(row: row, inComponent: component)
        }
    }
    
    func didSelectColor(row: Int, inComponent component: Int) {
        self.colorPickerCurrentlySelectedRow = row
    }
    
    func didSelectWidth(row: Int, inComponent component: Int) {
        self.widthPickerCurrentlySelectedRow = row
        self.updateWidth()
    }
    
    func didSelectAlpha(row: Int, inComponent component: Int) {
        self.alphaPickerCurrentlySelectedRow = row
        self.updateAlpha()
    }
    
    func didSelectVisibleFlyZone(row: Int, inComponent component: Int) {
        self.visibleFlyZonesPickerCurrentlySelectedRow = row
        self.updateFlyZones()
    }
}

