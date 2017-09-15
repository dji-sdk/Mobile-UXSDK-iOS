//
//  DULSideBarViewController.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <DJIUILibrary/DULWidgetCollectionViewController.h>

@class DULSideBarView;


/**
 *  This base class is used by `DULLeadingBarViewController` and
 *  `DULTrailingBarViewController`.
 */
@interface DULSideBarViewController : DULWidgetCollectionViewController


/**
 *  The actual instance of `DULSideBarView` containing all the widgets.
 */
@property (readonly, nullable, nonatomic) __kindof DULSideBarView *sideBarView;

@end
