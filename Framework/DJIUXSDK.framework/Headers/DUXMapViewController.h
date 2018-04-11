//
//  DUXMapViewController.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <DJIUXSDK/DUXContentViewController.h>
@class DUXMapWidget;


/**
 *  Subclass of DUXContentViewController which manages the logic for showing  the
 *  map view.
 */
@interface DUXMapViewController : DUXContentViewController


/**
 *  Instance of the map widget which is shown.
 */
@property (readonly, nonatomic) DUXMapWidget *mapWidget;

@end
