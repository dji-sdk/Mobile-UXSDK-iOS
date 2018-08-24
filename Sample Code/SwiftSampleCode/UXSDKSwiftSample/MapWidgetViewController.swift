//
//  MapWidgetViewController.swift
//  UXSDK Sample
//
//  Copyright © 2017 DJI. All rights reserved.
//

import UIKit
import DJIUXSDK

class MapWidgetViewController: UIViewController {
    @IBOutlet weak var mapWidget: DUXMapWidget!
    @IBOutlet weak var replaceIconSegmentedView: UISegmentedControl!
    @IBOutlet weak var replaceIconBlurView: UIVisualEffectView!
    @IBOutlet weak var testAPIMethodsBlurView: UIVisualEffectView!
    @IBOutlet weak var replaceIconImageView: UIImageView!
    @IBOutlet weak var closeButton: UIButton!
    @IBOutlet weak var clearFlightPathButton: UIButton!
    @IBOutlet weak var mapDisplaySwitch: UISegmentedControl!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.setupMapWidget()
    }
    
    // MARK: - Setup
    func setupMapWidget() {
        self.mapWidget.showDirectionToHome              = true
        self.testAPIMethodsBlurView.layer.cornerRadius  = 7.0;
        self.testAPIMethodsBlurView.layer.masksToBounds = true
        self.replaceIconBlurView.layer.cornerRadius     = 7.0
        self.replaceIconBlurView.layer.masksToBounds    = true
        
        self.view.bringSubview(toFront: self.testAPIMethodsBlurView)
        self.view.bringSubview(toFront: self.replaceIconBlurView)
        self.view.bringSubview(toFront: self.closeButton)
        self.view.bringSubview(toFront: self.mapDisplaySwitch)
        self.view.bringSubview(toFront: self.clearFlightPathButton)
    }
    
    // MARK: - Actions
    @IBAction func close(_ sender: UIButton) {
        self.dismiss(animated: true, completion: nil)
    }
    
    @IBAction func showFlyZonesValueChanged(_ sender: UISwitch) {
        self.mapWidget.visibleFlyZones = sender.isOn ? [.restricted, .authorization, .enhancedWarning, .warning] : []
    }
    
    @IBAction func directionToHomeValueChanged(_ sender: UISwitch) {
        self.mapWidget.showDirectionToHome = sender.isOn
    }

    @IBAction func lockAircraftCameraValueChanged(_ sender: UISwitch) {
        self.mapWidget.isMapCameraLockedOnAircraft = sender.isOn
    }
    
    @IBAction func showFlightPathValueChanged(_ sender: UISwitch) {
        self.mapWidget.showFlightPath = sender.isOn
    }
    
    @IBAction func mapTypeValueChanged(_ sender: UISegmentedControl) {
        if sender.selectedSegmentIndex == 0 {
            self.mapWidget.mapView.mapType = .standard
        } else if sender.selectedSegmentIndex == 1 {
            self.mapWidget.mapView.mapType = .satellite
        } else if sender.selectedSegmentIndex == 2 {
            self.mapWidget.mapView.mapType = .hybrid
        }
    }

    @IBAction func clearFlightPathButtonPressed(_ sender: UIButton) {
        self.mapWidget.clearCurrentFlightPath()
    }
    
    @IBAction func showHomePointValueChanged(_ sender: UISwitch) {
        self.mapWidget.showHomeAnnotation = sender.isOn
    }
    
    @IBAction func replaceIconButtonPressed(_ sender: UIButton) {
        if self.replaceIconSegmentedView.selectedSegmentIndex == 0 {
            self.mapWidget.change(.aircraft, with: self.replaceIconImageView.image!)
        } else if self.replaceIconSegmentedView.selectedSegmentIndex == 1 {
            self.mapWidget.change(.home, with: self.replaceIconImageView.image!)
        }
    }
    
    @IBAction func replaceIconValueChanged(_ sender: UISegmentedControl) {
        if sender.selectedSegmentIndex == 0 {
            self.replaceIconImageView.image = #imageLiteral(resourceName: "Aircraft")
        } else if sender.selectedSegmentIndex == 1 {
            self.replaceIconImageView.image = #imageLiteral(resourceName: "HomePoint")
        }
    }
}
