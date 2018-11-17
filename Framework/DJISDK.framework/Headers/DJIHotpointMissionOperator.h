//
//  DJIHotpointMissionOperator.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import "DJISDKFoundation.h"

NS_ASSUME_NONNULL_BEGIN

@class DJIHotpointMissionOperator;
@class DJIHotpointMission;


/**
 *  States of `DJIHotpointMissionOperator`.
 */
typedef NS_ENUM(NSInteger, DJIHotpointMissionState) {

    /**
     *  The state of the operator is unknown. This is the initial state when the
     *  operator has just been created.
     */
    DJIHotpointMissionStateUnknown = -1,


    /**
     *  The connection between the mobile device and aircraft is broken.
     */
    DJIHotpointMissionStateDisconnected,


    /**
     *  The connection between the mobile device and aircraft is recovering. At this
     *  time, the operator is synchronizing the state from the aircraft.
     */
    DJIHotpointMissionStateRecovering,


    /**
     *  The connected product does not support Hotpoint mission.
     */
    DJIHotpointMissionStateNotSupported,


    /**
     *  The operator is ready to start a Hotpoint mission.
     */
    DJIHotpointMissionStateReadyToStart,


    /**
     *  The aircraft is moving towards the start point of the Hotpoint mission.
     */
    DJIHotpointMissionStateExecutingInitialPhase,


    /**
     *  The execution is started successfully.
     */
    DJIHotpointMissionStateExecuting,

    /**
     *  Hotpoint mission is paused successfully. User can call
     *  `resumeMissionWithCompletion` to continue the execution.
     */
    DJIHotpointMissionStateExecutionPaused,
};


/**
 *  This class encapsulates all the state changes of the Hotpoint mission operator.
 */
@interface DJIHotpointMissionEvent : NSObject


/**
 *  The previous state of the operator.
 */
@property (nonatomic, readonly) DJIHotpointMissionState previousState;


/**
 *  The current state of the operator.
 */
@property (nonatomic, readonly) DJIHotpointMissionState currentState;


/**
 *  The Hotpoint radius in meters of the mission. If there is no executing mission,
 *  it is 0.
 */
@property (nonatomic, readonly) float radius;


/**
 *  The Hotpoint max angular velocity from current radius.
 */
@property (nonatomic, readonly) float maxAngularVelocity;


/**
 *  The encountered error if there is any. Otherwise, it is `nil`.
 */
@property (nonatomic, readonly, nullable) NSError *error;

@end


/**
 *  The hotpoint mission operator is the only object that controls, runs and
 *  monitors Hotpoint Missions. It can be accessed from `DJIMissionControl`.
 */
@interface DJIHotpointMissionOperator : NSObject


/**
 *  The current state of the executing Hotpoint mission executing.
 */
@property (readonly, nonatomic) DJIHotpointMissionState currentState;


/**
 *  Block to receive the hotpoint operator event.
 *  
 *  @param event The hotpoint operator event with the state change.
 */
typedef void (^DJIHotpointMissionOperatorEventBlock)(DJIHotpointMissionEvent *event);


/**
 *  Adds listener to receive all of the Hotpoint mission operator events.
 *  
 *  @param listener Listener that is interested in the Hotpoint mission operator.
 *  @param queue The dispatch queue that `block` will be called on.
 *  @param block Block will be called when there is event updated.
 */
- (void)addListenerToEvents:(id)listener
                  withQueue:(nullable dispatch_queue_t)queue
                   andBlock:(DJIHotpointMissionOperatorEventBlock)block;


/**
 *  Block to receive the notification that a Hotpoint mission is started
 *  successfully.
 */
typedef void (^DJIHotpointMissionOperatorSimpleEventBlock)();


/**
 *  Adds listener to receive a notification when a Hotpoint mission is started.
 *  
 *  @param listener Listener that is interested in the start of the Hotpoint mission.
 *  @param queue The dispatch queue that `block` will be called on.
 *  @param block Block will be called when a Hotpoint mission is started.
 */
- (void)addListenerToStarted:(id)listener
                   withQueue:(nullable dispatch_queue_t)queue
                    andBlock:(DJIHotpointMissionOperatorSimpleEventBlock)block;


/**
 *  Adds listener to receive a notification when a Hotpoint mission is finished.
 *  
 *  @param listener Listener that is interested in the finish of the Hotpoint mission.
 *  @param queue The dispatch queue that `block` will be called on.
 *  @param block Block will be called when a Hotpoint mission is finished. If the mission is interrupted with an error, the error will be passed to the block.
 */
- (void)addListenerToFinished:(id)listener
                    withQueue:(nullable dispatch_queue_t)queue
                     andBlock:(DJICompletionBlock)block;




/**
 *  Removes listener. If the listener is listening to events and notifications, then
 *  it will stop listening to all if called with this method.
 *  
 *  @param listener Listener to be removed.
 */
- (void)removeListener:(id)listener;


/**
 *  Removes listener from listener pool of events.
 *  
 *  @param listener Listener to be removed.
 */
- (void)removeListenerOfEvents:(id)listener;


/**
 *  Removes listener from listener pool of start mission notifications.
 *  
 *  @param listener Listener to be removed.
 */
- (void)removeListenerOfStarted:(id)listener;


/**
 *  Removes listener from listener pool of stop mission notifications
 *  
 *  @param listener Listener to be removed.
 */
- (void)removeListenerOfFinished:(id)listener;



/**
 *  Remove all listeners from listener pool.
 */
- (void)removeAllListeners;




/**
 *  Starts to execute a Hotpoint mission. This only be called when the
 *  `currentState` is `DJIHotpointMissionStateReadyToStart`. After a mission is
 *  started successfully, the `currentState` will become
 *  `DJIHotpointMissionStateExecutingInitialPhase` or
 *  `DJIHotpointMissionStateExecuting`.
 *  
 *  @param mission An object of `DJIHotpointMission`.
 *  @param completion Completion block that will be called when the operator succeeds or fails to stop the mission. If it fails, an error will be returned.
 */
- (void)startMission:(DJIHotpointMission *)mission withCompletion:(DJICompletionBlock)completion;


/**
 *  Pauses the executing mission. It can only be called when the `currentState` is
 *  `DJIHotpointMissionStateExecutingInitialPhase` or
 *  `DJIHotpointMissionStateExecuting`.  If this method is called in the
 *  `DJIHotpointMissionStateExecutingInitialPhase` state, the aircraft will continue
 *  flying to the start point but it will not continue to circle around the
 *  hotpoint until the user resumes the mission. After a mission
 *  is paused successfully, the `currentState` will become
 *  `DJIHotpointMissionStateExecutionPaused`.
 *  
 *  @param completion Completion block that will be called when the operator succeeds or fails to stop the mission. If it fails, an error will be returned.
 */
- (void)pauseMissionWithCompletion:(DJICompletionBlock)completion;


/**
 *  Resumes the paused mission. It can only be called when the `currentState` is
 *  `DJIHotpointMissionStateExecutionPaused`. After a mission is resumed
 *  successfully, the `currentState` will become
 *  `DJIHotpointMissionStateExecutingInitialPhase` or
 *  `DJIHotpointMissionStateExecuting`.
 *  
 *  @param completion Completion block that will be called when the operator succeeds or fails to stop the mission. If it fails, an error will be returned.
 */
- (void)resumeMissionWithCompletion:(DJICompletionBlock)completion;


/**
 *  Stops the executing or paused mission. It can only be called when `currentState`
 *  is one of the following:
 *   - `DJIHotpointMissionStateExecutingInitialPhase`
 *   - `DJIHotpointMissionStateExecuting`
 *   - `DJIHotpointMissionStateExecutionPaused`
 *   After a mission is stopped successfully, `currentState` will become
 *  `DJIHotpointMissionStateReadyToStart`.
 *  
 *  @param completion Completion block that will be called when the operator succeeds or fails to stop the mission. If it fails, an error will be returned.
 */
- (void)stopMissionWithCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the executing mission from the aircraft. It can only be called when
 *  `currentState` is one of the following:
 *   - `DJIHotpointMissionStateExecutingInitialPhase`
 *   - `DJIHotpointMissionStateExecuting`
 *   - `DJIHotpointMissionStateExecutionPaused`
 *  
 *  @param mission Detailed information of the mission being executed. `altitude` and `radius` may be different from the initial settings when starting the mission. It is `nil` if there is an error encountered when trying to get the mission.
 *  @param error Error retrieving the value.
 *  @param completion Completion block that will be called when the operator succeeds or fails to stop the mission. If it fails, an error will be returned.
 */
-(void)getExecutingMissionWithCompletion:(void(^_Nonnull )(DJIHotpointMission *_Nullable mission,
                                                           NSError *_Nullable error))completion;


/**
 *  Sets angular velocity for the executing mission. It can only be called when
 *  `currentState` is one of the following:
 *   - `DJIHotpointMissionStateExecutingInitialPhase`
 *   - `DJIHotpointMissionStateExecuting`
 *   - `DJIHotpointMissionStateExecutionPaused`
 *  
 *  @param angularVelocity Angular velocity to set.
 *  @param completion Completion block that will be called when the operator succeeds or fails to stop the mission. If it fails, an error will be returned.
 */
- (void)setAngularVelocity:(float)angularVelocity withCompletion:(DJICompletionBlock)completion;


/**
 *  Sets radius for the executing mission. It can only be called when the
 *  `currentState` is one of the following:
 *   - `DJIHotpointMissionStateExecutingInitialPhase`
 *   - `DJIHotpointMissionStateExecuting`
 *   - `DJIHotpointMissionStateExecutionPaused`
 *  
 *  @param radius Radius to set.
 *  @param completion Completion block that will be called when the operator succeeds or fails to stop the mission. If it fails, an error will be returned.
 */
- (void)setRadius:(float)radius completion:(DJICompletionBlock)completion;


/**
 *  Resets aircraft's heading to the direction defined by `heading` of
 *  `DJIHotpointMission`. It can only be called when the `currentState` is one of
 *  the following:
 *   - `DJIHotpointMissionStateExecutingInitialPhase`
 *   - `DJIHotpointMissionStateExecuting`
 *   - `DJIHotpointMissionStateExecutionPaused`
 *  
 *  @param completion Completion block that will be called when the operator succeeds or fails to stop the mission. If it fails, an error will be returned.
 */
- (void)resetMissionHeadingWithCompletion:(DJICompletionBlock)completion;


/**
 *  Returns the maximum supported angular velocity, in degrees/s, for a given
 *  Hotpoint mission radius in meters. Returns 0 if an unsupported radius is
 *  specified.
 *  
 *  @param radius Hotpoint radius with a range of [5,500] meters. This is used to calculate the maximum angular velocity.
 *  @param angularVelocity Angular velocity in degrees/s.
 *  @param error Error if there is any.
 *  @param completion Completion block to receive the execution result.
 */
+ (void)getMaxAngularVelocityForRadius:(double)radius withCompletion:(void(^)(float angularVelocity, NSError *_Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
