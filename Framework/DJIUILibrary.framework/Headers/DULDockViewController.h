//
//  DULDockViewController.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <DJIUILibrary/DULWidgetCollectionViewController.h>

@class DULDockView;


/**
 *  DULDockViewController manages the logic for pre-populating the DULDockView  with
 *  widgets similar to DJI Go.
 */
@interface DULDockViewController : DULWidgetCollectionViewController


/**
 *  The instance of DULDockView which is actually shown in the
 *    DULDefaultLayoutView.
 */
@property (readonly, nullable, nonatomic) __kindof DULDockView *dockView;

@end
