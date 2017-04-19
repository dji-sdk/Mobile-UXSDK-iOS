//
//  DULDockViewController.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DULWidgetCollectionViewController.h"

@class DULDockView;

//TDL 

/**
 *  This view controller manages the collection equivalent to the bottom bar present
 *  in DJI Go.
 */
@interface DULDockViewController : DULWidgetCollectionViewController


/**
 *  The actual instance of `DULDockView`.
 */
@property (readonly, nullable, nonatomic) __kindof DULDockView *dockView;

@end
