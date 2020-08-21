//
//  PanelsCollectionsViewController.swift
//  UXSDK
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

class PanelsCollectionsViewController: UIViewController {

    @IBOutlet var statusBarContainingView: UIView!
    var statusBarVC = DUXStatusBarViewController()
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Adding our DUXStatusBarViewController to our container in code.
        // This could be done in the storyboard
        self.addChild(self.statusBarVC)
        self.statusBarContainingView.addSubview(self.statusBarVC.view);
        self.statusBarVC.view.translatesAutoresizingMaskIntoConstraints = false;
        self.statusBarVC.view.topAnchor.constraint(equalTo: self.statusBarContainingView.topAnchor).isActive = true
        self.statusBarVC.view.bottomAnchor.constraint(equalTo: self.statusBarContainingView.bottomAnchor).isActive = true
        self.statusBarVC.view.leadingAnchor.constraint(equalTo: self.statusBarContainingView.leadingAnchor).isActive = true
        self.statusBarVC.view.trailingAnchor.constraint(equalTo: self.statusBarContainingView.trailingAnchor).isActive = true
        self.statusBarVC.didMove(toParent: self)
        
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
    
    @objc func moveWidget() {
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
