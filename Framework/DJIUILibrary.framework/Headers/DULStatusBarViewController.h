//
//  DULStatusBarViewController.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DULWidgetCollectionViewController.h"

@class DULStatusBarView;

// TDL

/**
 *  This view controller manages the collection equivalent to the top bar present in
 *  DJI Go.
 */
@interface DULStatusBarViewController : DULWidgetCollectionViewController


/**
 *  The actual instance of `DULStatusBarView`.
 */
@property (readonly, nonatomic, nullable) __kindof DULStatusBarView *statusBarView;

@end
