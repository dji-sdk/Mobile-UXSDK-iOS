//
//  DJIHandheldControllerKey.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import "DJIKey.h"

NS_ASSUME_NONNULL_BEGIN

EXTERN_KEY NSString *const DJIHandheldControllerComponent;

EXTERN_KEY NSString *const DJIHandheldControllerParamControlLED;
EXTERN_KEY NSString *const DJIHandheldControllerParamPowerMode;
EXTERN_KEY NSString *const DJIHandheldControllerParamStickGimbalControlEnabled;


/**
 *  `DJIHandheldControllerKey` provides dedicated access to all handheld  controller
 *  attributes.
 */
@interface DJIHandheldControllerKey : DJIKey

@end

NS_ASSUME_NONNULL_END
