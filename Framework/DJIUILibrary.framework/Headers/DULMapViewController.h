//
//  DULMapViewController.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DULContentViewController.h"
#import "DULMapWidget.h"

/**
 *  Subclass of DULContentViewController which manages the logic for
 *  showing the map view.
 */
@interface DULMapViewController : DULContentViewController

/**
 *  Instance of the map widget which is shown.
 */
@property (readonly, nonatomic) DULMapWidget *mapWidget;

@end
