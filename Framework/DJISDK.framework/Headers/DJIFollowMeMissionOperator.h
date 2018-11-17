//
//  DJIFollowMeMissionOperator.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import "DJISDKFoundation.h"
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIFollowMeMission;
@class DJIFollowMeMissionOperator;


/**
 *  All the possible state of `DJIFollowMeMissionOperator`.
 */
typedef NS_ENUM(NSInteger, DJIFollowMeMissionState) {
    

    /**
     *  The state of the operator is unknown. It is the initial state when the  operator
     *  is just created.
     */
    DJIFollowMeMissionStateUnknown = -1,


    /**
     *  The connection between the mobile device and aircraft is lost.
     */
    DJIFollowMeMissionStateDisconnected,


    /**
     *  The connection between the mobile device and aircraft is built-up. The operator
     *  is synchronizing the state from the aircraft.
     */
    DJIFollowMeMissionStateRecovering,


    /**
     *  The connected product does not support Follow Me mission.
     */
    DJIFollowMeMissionStateNotSupported,


    /**
     *  The operator is ready to start a Follow Me mission.
     */
    DJIFollowMeMissionStateReadyToStart,

    /**
     *  The mission execution is started successfully.
     */
    DJIFollowMeMissionStateExecuting
};


/**
 *  This class encapsulates all the state change of the Follow Me mission operator.
 */
@interface DJIFollowMeMissionEvent : NSObject


/**
 *  The previous follow me mission state, check the `DJIFollowMeMissionState` enum
 *  value.
 */
@property (nonatomic, readonly) DJIFollowMeMissionState previousState;


/**
 *  The current follow me mission state, check the `DJIFollowMeMissionState` enum
 *  value.
 */
@property (nonatomic, readonly) DJIFollowMeMissionState currentState;


/**
 *  The distance in meters between the aircraft and the Follow Me coordinate.  When
 *  there is no executing mission, it is 0.0.
 */
@property (nonatomic, readonly) float distanceToFollowMeCoordinate;


/**
 *  The encountered error if there is any. Otherwise, it is `nil`.
 */
@property (nonatomic, readonly, nullable) NSError *error;

@end

/*********************************************************************************/
#pragma mark Listener
/*********************************************************************************/


/**
 *  The follow me mission operator is the only object that controls, runs and
 *  monitors FollowMe Missions. It can be accessed from `DJIMissionControl`.
 */
@interface DJIFollowMeMissionOperator : NSObject


/**
 *  The current state of the executing Follow Me mission.
 */
@property (readonly, nonatomic) DJIFollowMeMissionState currentState;


/**
 *  Block to receive the Follow Me operator event.
 *  
 *  @param event The Follow Me operator event with the state change.
 */
typedef void (^DJIFollowMeMissionOperatorEventBlock)(DJIFollowMeMissionEvent *event);


/**
 *  Adds a listener object to the listener pool that will listen to all events.
 *  
 *  @param listener A listener object.
 *  @param queue The dispatch queue that `block` will be called on.
 *  @param block A `DJIFollowMeMissionOperatorEventBlock` block.
 */
- (void)addListenerToEvents:(id)listener
                  withQueue:(nullable dispatch_queue_t)queue
                   andBlock:(DJIFollowMeMissionOperatorEventBlock)block;


/**
 *  An simple event block for follow me mission.
 */
typedef void (^DJIFollowMeMissionOperatorSimpleEventBlock)();


/**
 *  Adds listener to receive the notification when a Follow Me mission is started.
 *  
 *  @param listener Listener that will listen for mission start.
 *  @param queue The dispatch queue that `block` will be called on.
 *  @param block Block to be called when mission starts.
 */
- (void)addListenerToStarted:(id)listener
                   withQueue:(nullable dispatch_queue_t)queue
                    andBlock:(DJIFollowMeMissionOperatorSimpleEventBlock)block;


/**
 *  Adds listener to receive the notification when a Follow Me mission has finished.
 *  
 *  @param listener Listener that will listen for mission end.
 *  @param queue The dispatch queue that `block` will be called on.
 *  @param block Block to be called when mission ends. If the mission is  interrupted with an error, the error will be passed to the block.
 */
- (void)addListenerToFinished:(id)listener
                    withQueue:(nullable dispatch_queue_t)queue
                     andBlock:(DJICompletionBlock)block;



/**
 *  Removes listener. If the listener is listening to more than one event, it  will
 *  be removed from listening for all events.
 *  
 *  @param listener Listener to be removed.
 */
- (void)removeListener:(id)listener;


/**
 *  Removes listener from listener pool for specific event.
 *  
 *  @param listener Listener to be removed.
 */
- (void)removeListenerOfEvents:(id)listener;


/**
 *  Removes listener from listener pool for specific start mission events.
 *  
 *  @param listener Listener to be removed.
 */
- (void)removeListenerOfStarted:(id)listener;


/**
 *  Removes listener from listener pool for specific finish mission events.
 *  
 *  @param listener Listener to be removed.
 */
- (void)removeListenerOfFinished:(id)listener;



/**
 *  Remove all listeners.
 */
- (void)removeAllListeners;


/**
 *  Starts to execute a Follow Me mission. It can only be called when the
 *  `currentState` is  `DJIFollowMeMissionStateReadyToStart`. After a mission is
 *  started  successfully, the `currentState` will become
 *  `DJIFollowMeMissionStateExecuting`.
 *  
 *  @param mission An object of `DJIFollowMeMission`.
 *  @param completion Completion block that will be called when the operator succeeds or fails to  start the execution. If it fails, an error will be returned.
 */
- (void)startMission:(DJIFollowMeMission *)mission withCompletion:(DJICompletionBlock)completion;


/**
 *  Stops the executing mission. It can only be called when the  `currentState` is
 *  `DJIFollowMeMissionStateExecuting`. After a mission is stopped successfully,
 *  `currentState` will become  `DJIFollowMeMissionStateReadyToStart`.
 *  
 *  @param completion The completion block of `DJICompletionBlock`.
 */
- (void)stopMissionWithCompletion:(DJICompletionBlock)completion;


/**
 *  Update the Follow Me mission's target location to follow.
 *  
 *  @param coordinate A CLLocationCoordinate2D struct of the following target.
 *  
 *  @return The possible error if the functionality fails.
 */
-(nullable NSError *)updateFollowMeCoordinate:(CLLocationCoordinate2D)coordinate;


/**
 *  The latest Follow Me coordinate. The operator will send the updated  Follow Me
 *  coordinate to the aircraft at a fixed frequency in order to maintain  the
 *  mission heart-beat.  The value is only valid when the `currentState`  is
 *  `DJIFollowMeMissionStateExecuting`.
 *  
 *  @return The latest Follow Me mission target location.
 */
-(CLLocationCoordinate2D)followMeCoordinate;

@end

NS_ASSUME_NONNULL_END

