//
//  DUXFPVInteractionEventContext.h
//  DJIUXSDK
//
//  Created by Andrew Lauer Barinov on 7/19/18.
//  Copyright © 2018 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Bitmask options indicating whether various potential interactions are enabled
 *  for the FPV view.
 */
typedef NS_OPTIONS(NSUInteger, DUXFPVInteractionOptions) {

/**
 *  No interactive options are enabled.
 */
    DUXFPVInteractionOptionsNone = 0,

/**
 *  Camera focusing options are enabled for manual exposure mode only.
 */
    DUXFPVInteractionOptionsActivateCameraFocusing = 1 << 0,

/**
 *  Center metering enabled.
 */
    DUXFPVInteractionOptionsActivateExposureCenterMetering = 1 << 1,

/**
 *  Spot metering via touch enabled when camera supports it.
 */
    DUXFPVInteractionOptionsActivateExposureSpotMetering  = 1 << 2,

/**
 *  Gimbal control via long press gesture enabled.
 */
    DUXFPVInteractionOptionsActivateGimbalControl = 1 << 3,
};


/**
 *  Exposes greater granularity of enabling/disabling the various interactive
 *  features of `DUXFPVViewController`. By default all supported features are
 *  enabled.
 */
@interface DUXFPVInteractionController : NSObject

// This doesn't need to be a public API, the user will always get the appropriate instance of DUXFPVInteractionController from DUXFPVViewController
// Use DUXFPVInteractionController_fpvViewController to distinguish between multiple interaction controllers
// I've put it in the public header just for reference purposes
+ (nonnull instancetype)controllerWithFPVViewController:(nonnull DUXFPVViewController *)fpvViewController;


/**
 *  The instance of `DUXFPVViewController` whose interactivity this class controls.
 */
@property (nonatomic, weak, readonly) DUXFPVViewController *fpvViewController;


/**
 *  Interaction options supported by the currently connected product, and the only
 *  ones that may be enabled. Returns `DUXFPVInteractionOptionsNone`  if no options
 *  are supported or product is connected.
 */
@property (nonatomic, assign, readonly) DUXFPVInteractionOptions supportedInteractionOptions;


/**
 *  Interaction options currently enabled by the FPV.
 */
@property (nonatomic, assign) DUXFPVInteractionOptions activeInteractionOptions;

@end
