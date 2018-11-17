//
//  DJIActiveTrackMissionOperator.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <DJISDK/DJISDKFoundation.h>
#import "DJIActiveTrackMission.h"

NS_ASSUME_NONNULL_BEGIN

@class DJIActiveTrackMissionOperator;
@class DJIActiveTrackTrackingState; 


/**
 *  All the possible states of `DJIActiveTrackMissionOperator`.
 */
typedef NS_ENUM(NSInteger, DJIActiveTrackMissionState) {


    /**
     *  The state of the operator is unknown. It is the initial state when the  operator
     *  is just created.
     */
    DJIActiveTrackMissionStateUnknown = -1,
    

    /**
     *  The connection between the mobile device and aircraft is broken.
     */
    DJIActiveTrackMissionStateDisconnected,


    /**
     *  The connection between the mobile device and aircraft is recovering.  In this
     *  state, the operator is synchronizing the state from the aircraft.
     */
    DJIActiveTrackMissionStateRecovering,


    /**
     *  The connected product does not support ActiveTrack mission.
     */
    DJIActiveTrackMissionStateNotSupported,


    /**
     *  There is existing error stopping any ActiveTrack mission to start.  Resolve
     *  `persistentError`  of `DJIActiveTrackMissionOperator` to start a mission.
     */
    DJIActiveTrackMissionStateCannotStart,


    /**
     *  The operator is ready to start an ActiveTrack mission.
     */
    DJIActiveTrackMissionStateReadyToStart,
    

    /**
     *  Auto sensing is enabled and the aircraft is looking for humans automatically  in
     *  the live view. Sensed subjects are pushed  through `autoSensedSubjects` of
     *  `DJIActiveTrackTrackingState`.
     */
    DJIActiveTrackMissionStateAutoSensing,
    

    /**
     *  Auto sensing for QuickShot is enabled and the aircraft is looking for humans
     *  automatically  in the live view. Sensed subjects are pushed through
     *  `autoSensedSubjects`  of `DJIActiveTrackTrackingState`.
     */
    DJIActiveTrackMissionStateAutoSensingForQuickShot,


    /**
     *  Gesture mode is enabled and the aircraft is looking for a target automatically.
     *  If a target is found, the operator will go to state
     *  `DJIActiveTrackMissionStateWaitingForConfirmation`  or
     *  `DJIActiveTrackMissionStateCannotConfirm`.
     */
    DJIActiveTrackMissionStateDetectingHuman,


    /**
     *  Target is found. Camera is already tracking the target. In order to make the
     *  aircraft follow the target, the confirmation from user is required. Once the
     *  target is confirmed, the state will become
     *  `DJIActiveTrackMissionStateAircraftFollowing`.
     */
    DJIActiveTrackMissionStateWaitingForConfirmation,


    /**
     *  Target is found. Camera is already tracking the target but there is an error
     *  stopping the aircraft to follow the target. Use `cannotConfirmReason`  in
     *  `DJIActiveTrackTrackingState` to check the reason.
     */
    DJIActiveTrackMissionStateCannotConfirm,


    /**
     *  Target is found. Camera is already tracking the target and the aircraft is
     *  following the target.
     */
    DJIActiveTrackMissionStateAircraftFollowing,


    /**
     *  The operator is executing an ActiveTrack mission in Splotlight mode or
     *  Spotlight Pro mode. The target is found and camera is following the target.
     */
    DJIActiveTrackMissionStateOnlyCameraFollowing,


    /**
     *  ActiveTrack is started but the target is lost. The vision system is detecting
     *  the previously found target.
     */
    DJIActiveTrackMissionStateFindingTrackedTarget,

	/**
	 *  The operator is executing a QuickShot ActiveTrack mission.
	 */
	DJIActiveTrackMissionStatePerformingQuickShot,
};


/**
 *  This class encapsulates all the state changes of the ActiveTrack mission
 *  operator.
 */
@interface DJIActiveTrackMissionEvent : NSObject


/**
 *  The previous state of the operator.
 */
@property (nonatomic, readonly) DJIActiveTrackMissionState previousState;


/**
 *  The current state of the operator.
 */
@property (nonatomic, readonly) DJIActiveTrackMissionState currentState;


/**
 *  The tracking state of the executing ActiveTrack mission. It is only valid  when
 *  `currentState` is one of the following:
 *   - `DJIActiveTrackMissionStateWaitingForConfirmation`
 *   - `DJIActiveTrackMissionStateCannotConfirm`
 *   - `DJIActiveTrackMissionStateAircraftFollowing`
 *   - `DJIActiveTrackMissionStateOnlyCameraFollowing`
 *   For the other states, it is `nil`.
 */
@property (nonatomic, readonly, nullable) DJIActiveTrackTrackingState *trackingState;


/**
 *  The encountered error if there is any. Otherwise, it is `nil`.
 */
@property (nonatomic, readonly, nullable) NSError *error;

@end


/**
 *  The active track mission operator is the only object that controls, runs and
 *  monitors ActiveTrack Missions. It can be accessed from `DJIMissionControl`.
 *   An ActiveTrack Mission allows an aircraft to track a moving subject using the
 *  vision system and without a GPS tracker on the subject. To use an ActiveTrack
 *  mission:
 *   - Prepare a mission with the rectangle that best represents the target to track
 *   - Start the mission to initiate tracking of the object and begin the state
 *  updates (DJIMissionProgressStatus)
 *   - At this point, the aircraft will track the target while hovering in place.
 *   - Give confirmation that the tracked target is correct with
 *  `acceptConfirmationWithCompletion` and the aircraft will begin flying relative
 *  to the target.
 *   - If the tracking algorithm looses sufficient confidence in tracking the
 *  target, then the aircraft will stop flying relative to the object and either
 *  notify the user (through execution state) that the target is lost or it needs
 *  another confirmation that the target is correct.
 *   - If the mission is paused, the aircraft will hover in place, but continue
 *  tracking the target by adjusting gimbal pitch and aircraft yaw.
 *   - If mission is resumed, confirmation of tracking rectangle will need to be
 *  sent through to start flying relative to target.
 *   - The mission can be canceled with `stopMissionWithCompletion` at any time. -
 *  `stopMissionWithCompletion` should also be used to reject tracking confirmation
 *  if the camera is tracking the wrong target. After stopping the mission, the
 *  mission needs to be recreated with a new rectangle and loaded into the operator.
 *   - The main camera is used to track the target, so gimbal cannot be adjusted
 *  during an ActiveTrack mission.
 *   - During the mission the aircraft can be manually flown with pitch, roll and
 *  throttle. Yaw and gimbal are automatically controlled to continue tracking the
 *  target.
 *   - If the mission is executing, and after confirmation of the tracking rectangle
 *  has been sent, the aircraft can be manually controlled horizontally similar to a
 *  `DJIFlightOrientationModeHomeLock` where the home is the tracked target. If
 *  aircraft is manually controlled upward, the aircraft will lift and retreat, and
 *  if it is controlled downward, it will go down and get closer to the target.
 */
@interface DJIActiveTrackMissionOperator : NSObject


/**
 *  The current state of the operator.
 */
@property (nonatomic, readonly) DJIActiveTrackMissionState currentState;


/**
 *  `YES` if gesture mode is enabled. Value is undefined if  the `currentState` is
 *  one of the following:
 *   - `DJIActiveTrackMissionStateNotSupported`
 *   - `DJIActiveTrackMissionStateDisconnected`
 *    - `DJIActiveTrackMissionStateRecovering`
 */
@property (nonatomic, readonly) BOOL isGestureModeEnabled;


/**
 *  `YES` if auto sensing is enabled. Value is undefined if  the `currentState` is
 *  one of the following:
 *   - `DJIActiveTrackMissionStateNotSupported`
 *   - `DJIActiveTrackMissionStateDisconnected`
 *    - `DJIActiveTrackMissionStateRecovering`
 */
@property (nonatomic, readonly) BOOL isAutoSensingEnabled;


/**
 *  `YES` if auto sensing for QuickShot is enabled. Value is undefined if  the
 *  `currentState` is one of the following:
 *   - `DJIActiveTrackMissionStateNotSupported`
 *   - `DJIActiveTrackMissionStateDisconnected`
 *    - `DJIActiveTrackMissionStateRecovering`
 */
@property (nonatomic, readonly) BOOL isAutoSensingForQuickShotEnabled;


/**
 *  The current tracking mode of the aircraft. It is valid when  the `currentState`
 *  is one of the following:
 *   - `DJIActiveTrackMissionStateWaitingForConfirmation`
 *   - `DJIActiveTrackMissionStateCannotConfirm`
 *   - `DJIActiveTrackMissionStateAircraftFollowing`
 *   - `DJIActiveTrackMissionStateOnlyCameraFollowing`
 *   - `DJIActiveTrackMissionStateFindingTrackedTarget`
 *   For the other states,  the value is `DJIActiveTrackModeUnknown`.
 */
@property (nonatomic, readonly) DJIActiveTrackMode trackingMode;


/**
 *  Existing error that stops any ActiveTrack missions to start. If it is not `nil`,
 *  `currentState` will be  `DJIActiveTrackMissionStateCannotStart`.
 */
@property (nonatomic, readonly, nullable) NSError *persistentError;


/**
 *  Block to receive the ActiveTrack operator event.
 *  
 *  @param event The ActiveTrack operator event with the state change.
 */
typedef void (^DJIActiveTrackMissionOperatorEventBlock)(DJIActiveTrackMissionEvent *event);


/**
 *  Adds listener to receive all the events of the ActiveTrack mission operator.
 *  
 *  @param listener Listener that is interested in the ActiveTrack mission operator events.
 *  @param queue The dispatch queue that `block` will be called on.
 *  @param block Block will be called when there is event updated.
 */
-(void)addListenerToEvents:(id)listener
                 withQueue:(dispatch_queue_t)queue
                  andBlock:(DJIActiveTrackMissionOperatorEventBlock)block;


/**
 *  Removes listener. The listener will not receive any update after  calling this
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
 *  Checks if the connected product supports gesture mode.
 *  
 *  @return `YES` if the product supports gesture mode.
 */
-(BOOL)isGestureModeSupported;


/**
 *  Enables/disables gesture mode.
 *   - A human subject can be automatically  detected if they are moving a little
 *  (instead of requiring a defining rectangle)
 *   - The human subject can accept the confirmation to track them by waving their
 *  arms.
 *   - The tracked human can make the camera shoot a photo by showing a rectangle
 *  with their thumbs and index fingers to the aircraft.
 *   Gesture mode can only be enabled  when the aircraft is flying but not tracking
 *  a target. The `currentState` should be one of the following:
 *   - `DJIActiveTrackMissionStateReadyToStart`
 *   - `DJIActiveTrackMissionStateCannotStart`
 *  After the gesture mode is enabled, `currentState` will become
 *  `DJIActiveTrackMissionStateDetectingHuman`.
 *   Gesture mode can be disabled when `currentState`  is not any of the following:
 *   - `DJIActiveTrackMissionStateUnknown`
 *   - `DJIActiveTrackMissionStateDisconnected`
 *   - `DJIActiveTrackMissionStateRecovering`
 *   - ``DJIActiveTrackMissionState_NotSupported`
 *   If the aircraft is already tracking a target, disabling gesture mode will  stop
 *  the ActiveTrack mission.
 *  
 *  @param enabled `YES` to enable gesture mode.
 *  @param completion Completion block that receives the execution result.
 */
-(void)setGestureModeEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Checks if the connected product supports auto sensing. When the product
 *  supports auto sensing, enabling auto sensing is the pre-condition of starting
 *  active track.
 *  
 *  @return `YES` if the product supports auto sensing.
 */
- (BOOL)isAutoSensingSupported;


/**
 *  Starts auto sensing. After auto sensing starts, the aircraft will sense  humans
 *  captured by the camera and return the detected subjects by `autoSensedSubjects`
 *  in the updated event. QuickShot requires a special auto sensing mode, therefore,
 *  use `enableAutoSensingForQuickShotWithCompletion`  if a QuickShot mission will
 *  be performed. It is only supported when `isAutoSensingSupported`  returns `YES`.
 *  When the product supports auto sensing, enabling auto sensing is the pre-
 *  condition of starting active track.
 *  
 *  @param completion Completion block that receives the execution result.
 */
- (void)enableAutoSensingWithCompletion:(DJICompletionBlock)completion;


/**
 *  Starts auto sensing specifically for QuickShot. After auto sensing starts, the
 *  aircraft will sense humans captured by the camera and return the  detected
 *  subjects by `autoSensedSubjects` in the updated event. This interface is
 *  specific for QuickShot, therefore,  use `enableAutoSensingWithCompletion` for
 *  missions other than QuickShot. It is only supported  when
 *  `isAutoSensingSupported` returns `YES`. When the product supports auto sensing,
 *  enabling auto sensing  is the pre-condition of starting active track.
 *  
 *  @param completion Completion block that receives the execution result.
 */
- (void)enableAutoSensingForQuickShotWithCompletion:(DJICompletionBlock)completion;


/**
 *  Stops auto sensing (either for QuickShot or the other active track modes). It is
 *  only supported  when `isAutoSensingSupported` returns `YES`.
 *  
 *  @param completion Completion block that receives the execution result.
 */
- (void)disableAutoSensingWithCompletion:(DJICompletionBlock)completion;


/**
 *  Checks if the operator can start the mission.
 *  
 *  @param mission An ActiveTrack mission.
 *  
 *  @return The possible error if the operator tries to start the mission.
 */
-(nullable NSError *)canStartMission:(DJIActiveTrackMission *)mission;


/**
 *  Starts to execute an ActiveTrack mission. It can only be called when the
 *  `currentState` is  `DJIActiveTrackMissionStateReadyToStart`. If a mission with
 *  `DJIActiveTrackModeTrace` or  `DJIActiveTrackModeProfile` is started
 *  successfully, the `currentState`  will become one of the following:
 *   - `DJIActiveTrackMissionStateWaitingForConfirmation`
 *   - `DJIActiveTrackMissionStateCannotConfirm`
 *   If a mission with  `DJIActiveTrackModeSpotlight` or
 *  `DJIActiveTrackModeSpotlightPro` is started  successfully, the `currentState`
 *  will  become `DJIActiveTrackMissionStateOnlyCameraFollowing`.
 *  
 *  @param mission The ActiveTrack mission to check.
 *  @param completion Completion block that receives the execution result.
 */
-(void)startMission:(DJIActiveTrackMission *)mission withCompletion:(DJICompletionBlock)completion;


/**
 *  Starts to execute an ActiveTrack mission after auto sensing (either for
 *  QuickShot or the other active track modes) is  started. The aircraft will start
 *  to track the subject defined by `subjectIndex`.  If auto sensing for active
 *  track modes other than QuickShot is enabled, the active track mode to start is
 *  defined  by `DJIActiveTrackMission`'s `mode`. `quickShotMode` of
 *  `DJIActiveTrackMission`  will be ignored. If auto sensing specifically for
 *  QuickShot is enabled, The QuickShot mode to start is defined  by
 *  `DJIActiveTrackMission`'s `quickShotMode`. `quickShotMode` of
 *  `DJIActiveTrackMission`  will be ignored.
 *  It can only be called when the `currentState` is one of the following:
 *  - `DJIActiveTrackMissionStateAutoSensing`
 *  - `DJIActiveTrackMissionStateAutoSensingForQuickShot`
 *  If the aircraft has high  confidence about the auto-sensed subject, confirmation
 *  is not required and the state will change to
 *  `DJIActiveTrackMissionStateAircraftFollowing`  or
 *  `DJIActiveTrackMissionStateOnlyCameraFollowing` (determined by the active track
 *  mode). Otherwise, the state will change  to
 *  `DJIActiveTrackMissionStateWaitingForConfirmation` and user need to perform
 *  `acceptConfirmationWithCompletion`.
 *  
 *  @param mission The ActiveTrack mission to check.
 *  @param completion Completion block that receives the execution result.
 */
-(void)startAutoSensingMission:(DJIActiveTrackMission *)mission withCompletion:(DJICompletionBlock)completion;


/**
 *  Stops the executing mission. It can only be called when the  `currentState` is
 *  one of the following:
 *   - `DJIActiveTrackMissionStateWaitingForConfirmation`
 *   - `DJIActiveTrackMissionStateCannotConfirm`
 *   - `DJIActiveTrackMissionStateAircraftFollowing`
 *   - `DJIActiveTrackMissionStateOnlyCameraFollowing`
 *   - `DJIActiveTrackMissionStateFindingTrackedTarget`
 *   After a mission is  stopped successfully, `currentState` will become
 *  `DJIActiveTrackMissionStateReadyToStart` or
 *  `DJIActiveTrackMissionStateDetectingHuman` if gesture mode is enabled.
 *  
 *  @param completion Completion block that will be called when the operator succeeds or fails to  stop the mission. If it fails, an error will be returned.
 */
-(void)stopMissionWithCompletion:(DJICompletionBlock)completion;


/**
 *  When the vision system is not sure the tracking rectangle is around the user's
 *  desired target, it will need confirmation before starting to fly relative to the
 *  target. The vision system will need confirmation when  `currentState` is
 *  `DJIActiveTrackMissionStateReadyToStart`.  `targetRect` of
 *  `DJIActiveTrackTrackingState` can  be used to show the user the rectangle the
 *  vision system is using. If the user  agrees the rectangle represents the target
 *  they want to track, this method can be  called to start flying relative to the
 *  target.
 *  
 *  @param completion Completion block that will be called when the operator succeeds or fails to  accept the target. If it fails, an error will be returned.
 */
-(void)acceptConfirmationWithCompletion:(DJICompletionBlock)completion;


/**
 *  Stops the aircraft from following the target and ask for user confirmation
 *  again.  It can only be called when the `currentState` is
 *  `DJIActiveTrackMissionStateAircraftFollowing`. After it is called successfully,
 *  `currentState` will become  `DJIActiveTrackMissionStateWaitingForConfirmation`.
 *  
 *  @param completion Completion block that will be called when the operator succeeds or fails to  accept the target. If it fails, an error will be returned.
 */
-(void)stopAircraftFollowingWithCompletion:(DJICompletionBlock)completion; 


/**
 *  Setting a non-zero speed starts the aircraft circling the target. Speed can be
 *  set within the range [-5, 5] m/s where a positive speed is a counter-clockwise
 *  movement (when viewing from the top). Reverting the speed to 0 m/s ends the
 *  circling movement. It can only be called when the `currentState`  is
 *  `DJIActiveTrackMissionStateAircraftFollowing` and `trackingMode`  is
 *  `DJIActiveTrackModeTrace`.
 *  
 *  @param speed Circular speed to set in m/s.
 *  @param completion Completion block that will be called when the operation succeeds or fails.  If it fails, an error will be returned.
 */
-(void)setCircularSpeed:(float)speed withCompletion:(DJICompletionBlock)completion;


/**
 *  In an ActiveTrack mission, the aircraft can be set to circle the target while
 *  following it. This method returns the circular speed of the aircraft in m/s.
 *  
 *  @param completion Completion block that will be called when the operation succeeds or fails.  If it fails, an error will be returned.
 */
-(void)getCircularSpeedWithCompletion:(DJIFloatCompletionBlock)completion;


/**
 *  Changes the ActiveTrack mode on the currently executing mission. It can only  be
 *  called when the `currentState` is one of the  following:
 *   - `DJIActiveTrackMissionStateWaitingForConfirmation`
 *   - `DJIActiveTrackMissionStateCannotConfirm`
 *   - `DJIActiveTrackMissionStateOnlyCameraFollowing`
 *   - `DJIActiveTrackMissionStateFindingTrackedTarget`
 *   If the current state  is `DJIActiveTrackMissionStateAircraftFollowing`,
 *  `stopAircraftFollowingWithCompletion` should be called before  switching the
 *  mode. Also, The ActiveTrack mode can only be changed when gesture  mode is
 *  disabled.
 *  
 *  @param mode Active track mode to change.
 *  @param completion Completion block that receives the execution result.
 */
-(void)switchMode:(DJIActiveTrackMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Sets the recommended camera and gimbal configuration that optimizes performance
 *  for the ActiveTrack Mission in most environments.
 *  
 *  @param completion Completion block that receives the execution result.
 */
-(void)setRecommendedConfigurationWithCompletion:(DJICompletionBlock)completion;


/**
 *  Enables/disable if the aircraft can retreat (fly backwards) when the target
 *  comes toward it. When it is disabled, the aircraft will not retreat and instead
 *  rotate the gimbal pitch down to track the target as it goes underneath. If the
 *  target goes beyond the gimbal's pitch stop, the target will be lost and the
 *  mission  will stop.
 *  
 *  @param enabled `YES` to enable retreat during ActiveTrack mission.
 *  @param completion Completion block that receives the execution result.
 */
-(void)setRetreatEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether retreat is enabled in ActiveTrack mission.
 *  
 *  @param completion Completion block that receives the execution result.
 */
-(void)getRetreatEnabledWithCompletion:(DJIBooleanCompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END

