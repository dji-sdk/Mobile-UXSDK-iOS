//
//  DJIBeacon.h
//  DJISDK
//
//  Copyright © 2018 DJI. All rights reserved.
//

#import <DJISDK/DJISDK.h>

NS_ASSUME_NONNULL_BEGIN


/**
 *  The class represents the beacon accessory mounted on the aircraft.
 */
@interface DJIBeacon : DJIBaseComponent


/**
 *  Determines if the beacon is enabled.
 *  
 *  @param enabled Check if Beacon is enabled.
 *  @param error Error to receive the result.
 *  @param completion Completion block to receive the result.
 */
- (void)getEnabledWithCompletion:(void (^)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Enables the beacon to turn it on. The beacon will start blink.
 *  
 *  @param enabled `YES` to turn on the beacon.
 *  @param completion Completion block to receive the result.
 */
- (void)setEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END
