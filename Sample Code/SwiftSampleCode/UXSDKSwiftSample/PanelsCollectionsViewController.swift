//
//  PanelsCollectionsViewController.swift
//  UXSDK
//
//  Created by Arnaud Thiercelin on 12/12/16.
//  Copyright © 2016 DJI. All rights reserved.
//

import UIKit
import DJIUXSDK

class PanelsCollectionsViewController: UIViewController {

    @IBOutlet var statusBarContainingView: UIView!
    var statusBarVC = DUXStatusBarViewController()
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Adding our DUXStatusBarViewController to our container in code.
        // This could be done in the storyboard
        self.addChildViewController(self.statusBarVC)
        self.statusBarContainingView.addSubview(self.statusBarVC.view);
        self.statusBarVC.view.translatesAutoresizingMaskIntoConstraints = false;
        self.statusBarVC.view.topAnchor.constraint(equalTo: self.statusBarContainingView.topAnchor).isActive = true
        self.statusBarVC.view.bottomAnchor.constraint(equalTo: self.statusBarContainingView.bottomAnchor).isActive = true
        self.statusBarVC.view.leadingAnchor.constraint(equalTo: self.statusBarContainingView.leadingAnchor).isActive = true
        self.statusBarVC.view.trailingAnchor.constraint(equalTo: self.statusBarContainingView.trailingAnchor).isActive = true
        self.statusBarVC.didMove(toParentViewController: self)
        
        /*
         *  Customizing a predefined widget view collection
         */
        
        // Removing a pre-defined widget you don't want.
        guard let preflightChecklistWidget = self.statusBarVC.widget(at: 1) else {
            return;
        }
        self.statusBarVC.removeWidget(preflightChecklistWidget)
        
        
        // Changing the edgeInset of a placed widget.
        guard let djiWidgetItem = self.statusBarVC.widgetItem(at: 0) else {
            return;
        }
        djiWidgetItem.edgeInset.top = 10
        djiWidgetItem.edgeInset.bottom = 10
        
        
        // Switch stack for widgets in stack collections
        guard let batteryWidget = self.statusBarVC.widget(with: DUXBatteryWidget.self) else {
            return;
        }
        self.statusBarVC.statusBarView?.moveWidget(batteryWidget, to: .first)
        
        
        // We need to call reloadData to adjust the rendering, but we call it at the end to avoid redundant calls
        self.statusBarVC.statusBarView?.reloadData()
    }
    
    var widgetMovingTimer: Timer!
    var lastStack = DUXWidgetCollectionViewStack.first
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        
        // You can also change the UI dynamically.
        self.widgetMovingTimer = Timer.scheduledTimer(timeInterval: 2.0, target: self, selector: #selector(moveWidget), userInfo: nil, repeats: true)
    }
    
    func moveWidget() {
        // Switch stack for widgets in stack collections
        guard let batteryWidget = self.statusBarVC.widget(with: DUXBatteryWidget.self) else {
            return;
        }
        self.lastStack = self.lastStack == .first ? .last : .first
        self.statusBarVC.statusBarView?.moveWidget(batteryWidget, to: self.lastStack)
        DispatchQueue.main.async { [unowned self] in
            self.statusBarVC.statusBarView?.reloadData()
        }
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        self.widgetMovingTimer.invalidate()
        self.widgetMovingTimer = nil
    }
    
    @IBAction func close () {
        self.dismiss(animated: true) {}
    }
}
