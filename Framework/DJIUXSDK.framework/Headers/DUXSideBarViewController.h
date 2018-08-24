//
//  DUXSideBarViewController.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <DJIUXSDK/DUXWidgetCollectionViewController.h>

@class DUXSideBarView;


/**
 *  This base class is used by `DUXLeadingBarViewController` and
 *  `DUXTrailingBarViewController`.
 */
@interface DUXSideBarViewController : DUXWidgetCollectionViewController


/**
 *  The actual instance of `DUXSideBarView` containing all the widgets.
 */
@property (readonly, nullable, nonatomic) __kindof DUXSideBarView *sideBarView;

@end
