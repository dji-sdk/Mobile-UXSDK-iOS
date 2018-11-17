//
//  DJILandingGear.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIBaseComponent.h>
#import <DJISDK/DJILandingGearStructs.h>

NS_ASSUME_NONNULL_BEGIN



/**
 *  This class controls and gives state of the landing gear.
 */
@interface DJILandingGear : NSObject



/**
 *  The current state/position of the landing gear.
 */
@property(nonatomic, readonly) DJILandingGearState state;


/**
 *  The current mode of the landing gear.
 */
@property(nonatomic, readonly) DJILandingGearMode mode;


/**
 *  Turns on/off self-adaptive landing gear. When turned on, landing gear will
 *  automatically lower  when aircraft is 0.5m above the ground. After take-off,
 *  landing gear will automatically rise when  aircraft reaches 0.5m above the
 *  ground. If self-adaptive landing gear is turned off, aircraft  will not
 *  automatically raise or lower its landing gear.
 *  
 *  @param enabled YES if automatic movement is enabled.
 *  @param completion Asynchronous execution result.
 */
- (void)setAutomaticMovementEnabled:(BOOL)enabled
                     withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets self-adaptive landing gear state (on/off). When turned on, landing gear
 *  will automatically lower  when aircraft is 0.5m above the ground. After take-
 *  off, landing gear will automatically rise when  aircraft reaches 0.5m above the
 *  ground. If self-adaptive landing gear is turned off, aircraft  will not
 *  automatically raise or lower its landing gear.
 *  
 *  @param enabled YES if automatic movement is enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getAutomaticMovementEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Enters transport mode, moving the landing gear to its optimal position for
 *  transportation. Note that if the gimbal is not removed, or the ground is not
 *  flat, entering transport mode will fail.
 *  
 *  @param completion Completion block that receives the execution result.
 */
- (void)enterTransportModeWithCompletion:(DJICompletionBlock)completion;


/**
 *  Exits transport mode. Note that if the ground is not flat, exit transport mode
 *  will fail.
 *  
 *  @param completion Completion block that receives the execution result.
 */
- (void)exitTransportModeWithCompletion:(DJICompletionBlock)completion;


/**
 *  Retracts the landing gear. Should only be used when `mode`  is
 *  `DJILandingGearModeManual`. For Matrice 600 and Matrice 600 Pro, landing gear
 *  cannot be controlled through the SDK, only automatically by the aircraft or
 *  manually by the remote controller.
 *  
 *  @param completion Completion block that receives the execution result.
 */
- (void)retractWithCompletion:(DJICompletionBlock)completion;


/**
 *  Deploys landing gear. Should only be used when `mode`  is
 *  `DJILandingGearModeManual`. For Matrice 600 and Matrice 600 Pro, the landing
 *  gear cannot  be controlled through the SDK, only automatically by the aircraft
 *  or manually by the remote controller.
 *  
 *  @param completion Completion block that receives the execution result.
 */
- (void)deployWithCompletion:(DJICompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END
