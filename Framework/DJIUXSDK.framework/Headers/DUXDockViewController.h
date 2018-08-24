//
//  DUXDockViewController.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <DJIUXSDK/DUXWidgetCollectionViewController.h>

@class DUXDockView;


/**
 *  DUXDockViewController manages the logic for pre-populating the DUXDockView  with
 *  widgets similar to DJI Go.
 */
@interface DUXDockViewController : DUXWidgetCollectionViewController


/**
 *  The instance of DUXDockView which is actually shown in the
 *    `DUXDefaultLayoutView`.
 */
@property (readonly, nullable, nonatomic) __kindof DUXDockView *dockView;

@end
