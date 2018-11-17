//
//  DJITapFlyMissionOperator.h
//  DJISDK
//
//  Created by Tim Lee on 2017/3/7.
//  Copyright © 2017年 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DJISDKFoundation.h"
#import "DJITapFlyMission.h"

NS_ASSUME_NONNULL_BEGIN

@class DJITapFlyMissionOperator;


/**
 *  All the possible states of `DJITapFlyMissionOperator`.
 */
typedef NS_ENUM(NSInteger, DJITapFlyMissionState) {


    /**
     *  The state of the operator is unknown. This is the initial state when the
     *  operator is  first created.
     */
    DJITapFlyMissionStateUnknown = -1,


    /**
     *  The connection between the mobile device and aircraft is broken.
     */
    DJITapFlyMissionStateDisconnected,


    /**
     *  The connection between the mobile device and aircraft is recovering.  In this
     *  state, the operator is synchronizing the state from the aircraft.
     */
    DJITapFlyMissionStateRecovering,


    /**
     *  The connected product does not support TapFly mission.
     */
    DJITapFlyMissionStateNotSupported,


    /**
     *  There is an existing error stopping the TapFly mission to start.  Resolve
     *  `persistentError`  of `DJITapFlyMissionOperator` to start a mission.
     */
    DJITapFlyMissionStateCannotStart,


    /**
     *  The operator is ready to start a TapFly mission.
     */
    DJITapFlyMissionStateReadyToStart,


    /**
     *  The operator is executing a TapFly mission.
     */
    DJITapFlyMissionStateExecuting,


    /**
     *  The execution of the TapFly mission is paused. User can pause or resume a
     *  TapFly mission by pressing the pause button on the physical remote controller.
     */
    DJITapFlyMissionStateExecutionPaused,


    /**
     *  The TapFly mission cannot continue the execution. The execution is being stopped
     *  automatically.
     */
    DJITapFlyMissionStateExecutionResetting,
};


/**
 *  This class encapsulates all the state changes of the TapFly mission operator.
 */
@interface DJITapFlyMissionEvent : NSObject


/**
 *  The previous state of the operator.
 */
@property (nonatomic, readonly) DJITapFlyMissionState previousState;


/**
 *  The current state of the operator.
 */
@property (nonatomic, readonly) DJITapFlyMissionState currentState;


/**
 *  The detailed state of the executing TapFly mission. It is only valid  when
 *  `currentState` is one of the following:
 *   - `DJITapFlyMissionStateExecuting`
 *   - `DJITapFlyMissionStateExecutionPaused`
 *   For the other states, it is `nil`.
 */
@property (nonatomic, readonly, nullable) DJITapFlyExecutionState *executionState;


/**
 *  The encountered error if any. Otherwise, it is `nil`.
 */
@property (nonatomic, readonly, nullable) NSError *error;

@end


/**
 *  The operator for TapFly mission. It is used to execute a TapFly mission.
 */
@interface DJITapFlyMissionOperator : NSObject


/**
 *  The current state of the operator.
 */
@property (nonatomic, readonly) DJITapFlyMissionState currentState;


/**
 *  The current tracking mode of the aircraft. It is valid when  the `currentState`
 *  is one of the following:
 *   - `DJITapFlyMissionStateExecuting`
 *   - `DJITapFlyMissionStateExecutionPaused`
 *    - `DJITapFlyMissionStateExecutionResetting`
 *   For the other states, the value is `DJITapFlyModeUnknown`.
 */
@property (nonatomic, readonly) DJITapFlyMode mode;


/**
 *  Existing error that prevents a TapFly mission to start.  If it is not `nil`,
 *  `currentState` will be   `DJITapFlyMissionStateCannotStart`.
 */
@property (nonatomic, readonly, nullable) NSError *persistentError;


/**
 *  Block to receive the Tap Fly operator event.
 *  
 *  @param event The Tap Fly operator event with the state change.
 */
typedef void (^DJITapFlyMissionOperatorEventBlock)(DJITapFlyMissionEvent *event);


/**
 *  Adds listener to receive all the events of the TapFly mission operator.
 *  
 *  @param listener Listener that is interested in the TapFly mission operator.
 *  @param queue The dispatch queue that `block` will be called on.
 *  @param block Block will be called when there is event updated.
 */
-(void)addListenerToEvents:(id)listener
                 withQueue:(dispatch_queue_t)queue
                  andBlock:(DJITapFlyMissionOperatorEventBlock)block;


/**
 *  Removes listener. The listener will not receive any updates after calling this
 *  method.
 *  
 *  @param listener Listener to be removed.
 */
-(void)removeListener:(id)listener;


/**
 *  Remove all listeners.
 */
-(void)removeAllListeners;


/**
 *  Starts to execute a TapFly mission. It can only be called when  the
 *  `currentState`   is `DJITapFlyMissionStateReadyToStart`. If the mission is
 *  started successfully,  the `currentState` will  become
 *  `DJITapFlyMissionStateExecuting`.
 *  
 *  @param mission An object of `DJITapFlyMission`.
 *  @param completion Completion block that will be called when the operator succeeds or fails to start  the execution. If it fails, an error will be returned.
 */
-(void)startMission:(DJITapFlyMission *)mission withCompletion:(DJICompletionBlock)completion;


/**
 *  Stops the executing mission. It can only be called when  the `currentState` is
 *  one of the following:
 *   - `DJITapFlyMissionStateExecuting`
 *   - `DJITapFlyMissionStateExecutionPaused`
 *   - `DJITapFlyMissionStateExecutionResetting`
 *   After a mission is stopped  successfully, `currentState` will  become
 *  `DJITapFlyMissionStateReadyToStart`.
 *  
 *  @param completion Completion block that will be called when the operator succeeds or fails to start  the execution. If it fails, an error will be returned.
 */
-(void)stopMissionWtihCompletion:(DJICompletionBlock)completion;


/**
 *  Resets aircraft heading to the flight direction. It can only be used  when
 *  `mode` is `DJITapFlyModeFree`.
 *  
 *  @param completion Completion block that receives the execution result.
 */
-(void)resetHeadingWithCompletion:(DJICompletionBlock)completion;



/**
 *  Sets auto flight speed for TapFly mission. It can be changed before or during
 *  the  execution of a TapFly mission.
 *  
 *  @param speed Auto flight speed.
 *  @param completion Completion block that receives the execution result.
 */
-(void)setAutoFlightSpeed:(float)speed withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the auto flight speed for TapFly mission in m/s.
 *  
 *  @param completion Completion block that receives the execution result.
 */
-(void)getAutoFlightSpeedWithCompletion:(DJIFloatCompletionBlock)completion;


/**
 *  `YES` allows the aircraft to bypass or move around an obstacle by going to  the
 *  left or right of the obstacle. If `NO`, the aircraft will only  go over an
 *  obstacle to avoid it. It can be changed before or during the execution  of a
 *  TapFly mission.
 *  
 *  @param enabled `YES` allows aircraft to bypass or move around an obstacle by going to the left or right.
 *  @param completion Completion block that receives the execution result.
 */
-(void)setHorizontalObstacleBypassEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  `YES` allows the aircraft to bypass or move around an obstacle by going to  the
 *  left or right of the obstacle. If `NO`, the aircraft will only  go over an
 *  obstacle to avoid it. It can be changed before or during the execution  of a
 *  TapFly mission.
 *  
 *  @param completion Completion block that receives the execution result.
 */
-(void)getHorizontalObstacleBypassEnabledWithCompletion:(DJIBooleanCompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END

