//
//  DUXStatusBarViewController.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <DJIUXSDK/DUXWidgetCollectionViewController.h>

@class DUXStatusBarView;
@class DUXDJILogoWidget;
@class DUXPreFlightStatusWidget;
@class DUXPreflightChecklistController;
@class DUXConnectionWidget;
@class DUXBatteryWidget;
@class DUXVideoSignalWidget;
@class DUXGPSSignalWidget;
@class DUXVisionWidget;
@class DUXFlightModeWidget;
@class DUXRemainingFlightTimeWidget;
@class DUXRTKStatusViewController;
@class DUXAccessLockerWidget;


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


/**
 *  The instance of DUXDJILogoWidget which is actually shown in the
 *    `DUXDefaultLayoutView`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXDJILogoWidget *djiLogoWidget;


/**
 *  The instance of DUXPreFlightStatusWidget which is actually shown in the
 *    `DUXDefaultLayoutView`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXPreFlightStatusWidget *preflightWidget;


/**
 *  The instance of DUXPreflightChecklistController which is actually shown in the
 *    `DUXDefaultLayoutView`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXPreflightChecklistController *preflightChecklistController;


/**
 *  The instance of DUXConnectionWidget which is actually shown in the
 *    `DUXDefaultLayoutView`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXConnectionWidget *connectionWidget;


/**
 *  The instance of DUXBatteryWidget which is actually shown in the
 *    `DUXDefaultLayoutView`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXBatteryWidget *batteryWidget;


/**
 *  The instance of DUXVideoSignalWidget which is actually shown in the
 *    `DUXDefaultLayoutView`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXVideoSignalWidget *videoSignalWidget;


/**
 *  The instance of DUXGPSSignalWidget which is actually shown in the
 *    `DUXDefaultLayoutView`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXGPSSignalWidget *gpsWidget;


/**
 *  The instance of DUXVisionWidget which is actually shown in the
 *    `DUXDefaultLayoutView`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXVisionWidget *visionWidget;


/**
 *  The instance of DUXFlightModeWidget which is actually shown in the
 *    `DUXDefaultLayoutView`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXFlightModeWidget *flightModeWidget;


/**
 *  The instance of DUXRemainingFlightTimeWidget which is actually shown in the
 *    `DUXDefaultLayoutView`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXRemainingFlightTimeWidget *remainingFlightTimeWidget;


/**
 *  The instance of DUXRTKStatusViewController which is actually shown in the
 *    `DUXDefaultLayoutView`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXRTKStatusViewController *rtkSettingsViewController;


/**
 *  The instance of DUXAccessLockerWidget which is actually shown in the
 *    `DUXDefaultLayoutView`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXAccessLockerWidget *accessLockerWidget;

@end
