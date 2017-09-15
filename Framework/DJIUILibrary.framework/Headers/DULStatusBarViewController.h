//
//  DULStatusBarViewController.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <DJIUILibrary/DULWidgetCollectionViewController.h>

@class DULStatusBarView;


/**
 *  DULStatusBarViewController manages the logic for pre-populating
 *    the DULStatusBarView with widgets similar to DJI Go.
 */
@interface DULStatusBarViewController : DULWidgetCollectionViewController


/**
 *  The instance of DULStatusBarView which is actually shown in the
 *    DULDefaultLayoutView.
 */
@property (readonly, nonatomic, nullable) __kindof DULStatusBarView *statusBarView;

@end
