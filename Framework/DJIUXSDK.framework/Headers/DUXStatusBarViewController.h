//
//  DUXStatusBarViewController.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <DJIUXSDK/DUXWidgetCollectionViewController.h>

@class DUXStatusBarView;


/**
 *  DUXStatusBarViewController manages the logic for pre-populating
 *    the DUXStatusBarView with widgets similar to DJI Go.
 */
@interface DUXStatusBarViewController : DUXWidgetCollectionViewController


/**
 *  The instance of DUXStatusBarView which is actually shown in the
 *    `DUXDefaultLayoutView`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXStatusBarView *statusBarView;

@end
