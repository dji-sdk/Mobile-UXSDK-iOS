//
//  SimulationControlsViewController.swift
//  UXSDKSwiftSample
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
import DJISDK

public let UserDefaultsLatitudeKey: String = "Latitude"
public let UserDefaultsLongitudeKey: String = "Longitude"

public let UserDefaultsPriorSimulatorLocationKey = "PriorSimulatorLocation"

class SimulatorControlsViewController: UIViewController {
    var latitudeControlAction: ControlAction?
    var longitudeControlAction: ControlAction?
    var startSimulatorControlAction: ControlAction?
    var saveSimulatorLocationControlAction: ControlAction?
    
    var latitude:CLLocationDegrees?
    var longitude:CLLocationDegrees?
    
    var savedStatusLabel: UILabel?
    
    override func viewDidLoad() {
        self.view.backgroundColor = UIColor.black.withAlphaComponent(0.65)
        self.title = "Enter Lat / Long and Tap Start"
        
        let latitudeTextField = UITextField()
        latitudeTextField.translatesAutoresizingMaskIntoConstraints = false
        latitudeTextField.attributedPlaceholder = NSAttributedString(string: "Enter Latitude Here", attributes: [NSAttributedString.Key.foregroundColor : UIColor.lightText])
        latitudeTextField.textColor = UIColor.white
        latitudeTextField.textAlignment = .center
        latitudeTextField.font = UIFont.systemFont(ofSize: 32.0)
        self.view.addSubview(latitudeTextField)
        
        self.latitudeControlAction = ControlAction {
            if let lat = MainViewController.numberFormatter.number(from: latitudeTextField.text ?? "0") {
                self.latitude = lat.doubleValue
            }
        }
        
        latitudeTextField.connect(controlAction: self.latitudeControlAction!,
                                  for: [.editingDidEnd, .editingDidEndOnExit])
        
        let longitudeTextField = UITextField()
        longitudeTextField.translatesAutoresizingMaskIntoConstraints = false
        longitudeTextField.attributedPlaceholder = NSAttributedString(string: "Enter Longitude Here", attributes: [NSAttributedString.Key.foregroundColor : UIColor.lightText])
        longitudeTextField.textColor = UIColor.white
        longitudeTextField.textAlignment = .center
        longitudeTextField.font = UIFont.systemFont(ofSize: 32.0)
        self.view.addSubview(longitudeTextField)
        
        self.longitudeControlAction = ControlAction {
            if let long = MainViewController.numberFormatter.number(from: longitudeTextField.text ?? "0") {
                self.longitude = long.doubleValue
            }
        }
        
        longitudeTextField.connect(controlAction: self.longitudeControlAction!,
                                   for: [.editingDidEnd, .editingDidEndOnExit])
        
        // Fill in values from User Defaults if they exist
        if let priorSimulatorLocation = UserDefaults.standard.value(forKey: UserDefaultsPriorSimulatorLocationKey) as? [String:NSNumber] {
            if let latitudeDegrees = priorSimulatorLocation[UserDefaultsLatitudeKey] {
                self.latitude = latitudeDegrees.doubleValue
                latitudeTextField.text = MainViewController.numberFormatter.string(from:latitudeDegrees)
            }
            
            if let longitudeDegrees = priorSimulatorLocation[UserDefaultsLongitudeKey] {
                self.longitude = longitudeDegrees.doubleValue
                longitudeTextField.text = MainViewController.numberFormatter.string(from:longitudeDegrees)
            }
        }
        
        let startSimulatorButton = UIButton(type: .system)
        startSimulatorButton.translatesAutoresizingMaskIntoConstraints = false
        startSimulatorButton.setTitle("Start", for: .normal)
        startSimulatorButton.setTitle("Start", for: .disabled)
        startSimulatorButton.setTitle("Start", for: .selected)
        startSimulatorButton.setTitle("Start", for: .highlighted)
        startSimulatorButton.titleLabel?.font = UIFont.systemFont(ofSize: 32.0)
        self.view.addSubview(startSimulatorButton)
        
        self.startSimulatorControlAction = ControlAction {
            guard let latitude = self.latitude, let longitude = self.longitude else {
                return
            }
            
            let coordinate = CLLocationCoordinate2DMake(latitude, longitude)
            
            let didBeginStartingSimulator = ProductCommunicationService.shared.startSimulator(at: coordinate)
            
            self.dismiss(self)
            if !didBeginStartingSimulator {
                self.presentError("Could Not Start Starting Simulator, Aircraft or SDK not available.")
            }
        }
        
        startSimulatorButton.connect(controlAction: self.startSimulatorControlAction!,
                                     for: .touchUpInside)
        
        let saveSimulatorLocationButton = UIButton(type: .system)
        saveSimulatorLocationButton.translatesAutoresizingMaskIntoConstraints = false
        saveSimulatorLocationButton.setTitle("Save", for: .normal)
        saveSimulatorLocationButton.setTitle("Save", for: .disabled)
        saveSimulatorLocationButton.setTitle("Save", for: .selected)
        saveSimulatorLocationButton.setTitle("Save", for: .highlighted)
        saveSimulatorLocationButton.titleLabel?.font = UIFont.systemFont(ofSize: 32.0)
        self.view.addSubview(saveSimulatorLocationButton)
        
        self.saveSimulatorLocationControlAction = ControlAction {
            guard let latitude = self.latitude, let longitude = self.longitude else {
                return
            }
            
            let location = [
                UserDefaultsLatitudeKey : NSNumber(value: latitude),
                UserDefaultsLongitudeKey: NSNumber(value: longitude)
            ]
            
            UserDefaults.standard.set(location,
                                      forKey: UserDefaultsPriorSimulatorLocationKey)
            
            self.savedStatusLabel?.text = "✅ Saved for Next Time"
        }
        
        saveSimulatorLocationButton.connect(controlAction: self.saveSimulatorLocationControlAction!,
                                     for: .touchUpInside)
        
        let savedStatusLabel = UILabel()
        savedStatusLabel.translatesAutoresizingMaskIntoConstraints = false
        savedStatusLabel.text = ""
        savedStatusLabel.textColor = UIColor.white
        self.view.addSubview(savedStatusLabel)
        
        latitudeTextField.centerXAnchor.constraint(equalTo: self.view.centerXAnchor).isActive = true
        longitudeTextField.centerXAnchor.constraint(equalTo: self.view.centerXAnchor).isActive = true
        startSimulatorButton.centerXAnchor.constraint(equalTo: self.view.centerXAnchor).isActive = true
        saveSimulatorLocationButton.centerXAnchor.constraint(equalTo: self.view.centerXAnchor).isActive = true
        
        longitudeTextField.centerYAnchor.constraint(equalTo: self.view.centerYAnchor).isActive = true
        latitudeTextField.bottomAnchor.constraint(equalTo: longitudeTextField.topAnchor, constant: -20.0).isActive = true
        startSimulatorButton.topAnchor.constraint(equalTo: longitudeTextField.bottomAnchor, constant: 20.0).isActive = true
        saveSimulatorLocationButton.topAnchor.constraint(equalTo: startSimulatorButton.bottomAnchor, constant: 20.0).isActive = true
        
        savedStatusLabel.leadingAnchor.constraint(equalTo: saveSimulatorLocationButton.trailingAnchor, constant: 8.0).isActive = true
        savedStatusLabel.centerYAnchor.constraint(equalTo: saveSimulatorLocationButton.centerYAnchor).isActive = true
        
        self.savedStatusLabel = savedStatusLabel
    }
    
    @objc public func dismiss(_ sender: Any) {
        self.presentingViewController?.dismiss(animated: true,
                                            completion: nil)
    }
}
