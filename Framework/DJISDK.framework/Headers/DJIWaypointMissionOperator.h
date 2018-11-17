//
//  DJIWaypointMissionOperator.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import "DJISDKFoundation.h"
#import "DJIWaypointMissionTypes.h"

NS_ASSUME_NONNULL_BEGIN


/**
 *  All the possible state of `DJIWaypointMissionOperator`.
 */
typedef NS_ENUM(NSInteger, DJIWaypointMissionState) {

    /**
     *  The state of the operator is unknown. It is the initial state when the operator
     *  is just created.
     */
    DJIWaypointMissionStateUnknown = -1,


    /**
     *  The connection between the mobile device, remote controller and aircraft is
     *  broken.
     */
    DJIWaypointMissionStateDisconnected,


    /**
     *  The connection between the mobile device, remote controller and aircraft is
     *  built-up. The operator is synchronizing the state from the aircraft.
     */
    DJIWaypointMissionStateRecovering,


    /**
     *  The connected product does not support waypoint mission.
     */
    DJIWaypointMissionStateNotSupported,


    /**
     *  The aircraft is ready to upload a mission.
     */
    DJIWaypointMissionStateReadyToUpload,


    /**
     *  The uploading is started successfully. Detail information for each waypoint is
     *  being uploaded one by one.
     */
    DJIWaypointMissionStateUploading,
    

    /**
     *  Waypoint mission is uploaded completely and the aircraft is ready to start the
     *  execution.
     */
    DJIWaypointMissionStateReadyToExecute,
    

    /**
     *  The execution is started successfully.
     */
    DJIWaypointMissionStateExecuting,
    

    /**
     *  Waypoint mission is paused successfully. User can call
     *  `resumeMissionWithCompletion` to continue the execution.
     */
    DJIWaypointMissionStateExecutionPaused,
};


@class DJIWaypointMission;
@class DJIWaypointMissionOperator;


/**
 *  The execution event of a waypoint mission.
 */
@interface DJIWaypointMissionExecutionEvent : NSObject


/**
 *  The previous state of the operator.
 */
@property (nonatomic, readonly) DJIWaypointMissionState previousState;


/**
 *  The current state of the operator.
 */
@property (nonatomic, readonly) DJIWaypointMissionState currentState;


/**
 *  The execution progress of the mission. It is `nil` if there is an error during
 *  the execution.
 */
@property (nonatomic, readonly, nullable) DJIWaypointExecutionProgress *progress;


/**
 *  The encountered error during the execution if there is any. Otherwise, it is
 *  `nil`.
 */
@property (nonatomic, readonly, nullable) NSError *error;

@end


/**
 *  The upload event of a waypoint mission.
 */
@interface DJIWaypointMissionUploadEvent : NSObject


/**
 *  The previous state of the operator.
 */
@property (nonatomic, readonly) DJIWaypointMissionState previousState;


/**
 *  The current state of the operator.
 */
@property (nonatomic, readonly) DJIWaypointMissionState currentState;


/**
 *  The upload progress of the mission. It is `nil` if there is an error during
 *  upload.
 */
@property (nonatomic, readonly, nullable) DJIWaypointUploadProgress *progress;


/**
 *  The encountered error during upload if there is any. Otherwise, it is `nil`.
 */
@property (nonatomic, readonly, nullable) NSError *error;

@end


/**
 *  The download event of a waypoint mission.
 */
@interface DJIWaypointMissionDownloadEvent : NSObject


/**
 *  The download progress of the mission. It is `nil` if there is an error during
 *  download.
 */
@property (nonatomic, readonly, nullable) DJIWaypointDownloadProgress *progress;


/**
 *  The encountered error during download if there is any. Otherwise, it is `nil`.
 */
@property (nonatomic, readonly, nullable) NSError *error;

@end



/**
 *  The waypoint operator is the only object that controls, runs and monitors
 *  Waypoint Missions. It can be accessed from `DJIMissionControl`.
 */
@interface DJIWaypointMissionOperator : NSObject


/**
 *  Gets the currently loaded mission of the operator. There are two ways to load a
 *  mission. 1. A mission can be loaded by user through `loadMission`. 2. If the
 *  aircraft is already executing a waypoint mission when SDK is re-connected, the
 *  operator will download part of the mission's information from the aircraft and
 *  load it automatically. In that case, the loaded mission will only contain the
 *  summary of the executing mission but information for each waypoint is absent.
 *  User can call `downloadMissionWithCompletion` to get all the information for the
 *  loaded mission. The `loadedMission` will be reset to `nil` when the execution of
 *  the loadedMission is stopped, finished or interrupted.
 */
@property (readonly, nonatomic, nullable) DJIWaypointMission *loadedMission;


/**
 *  Loads a waypoint mission into the operator. A mission can be loaded only when
 *  the `DJIWaypointMissionState` is one of the following:
 *   - `DJIWaypointMissionStateReadyToUpload`
 *   - `DJIWaypointMissionStateReadyToExecute`
 *   Calling `loadMission` when the current state is
 *  `DJIWaypointMissionStateReadyToExecute` will change the state to
 *  `DJIWaypointMissionStateReadyToUpload`. After calling `loadMission`,
 *  `latestExecutionProgress` will be reset to `nil`.
 *  
 *  @param mission Waypoint mission to load.
 *  
 *  @return Returns an error when mission data is invalid or the mission cannot be loaded in the current state.
 */
-(NSError * _Nullable)loadMission:(DJIWaypointMission *)mission;


/**
 *  The current state of the operator.
 */
@property (readonly, nonatomic) DJIWaypointMissionState currentState;


/**
 *  The latest execution progress cached by the operator. It will be reset to `nil`
 *  after `loadMission` is called.
 */
@property (readonly, nonatomic, nullable) DJIWaypointExecutionProgress *latestExecutionProgress;


/**
 *  The latest execution progress cached by the operator. It will be reset to `nil`
 *  after `loadMission` is called.
 */
@property (readonly, nonatomic, nullable) DJIWaypointUploadProgress *latestUploadProgress;

/*********************************************************************************/
#pragma mark Listener
/*********************************************************************************/


/**
 *  Block that receive the updated upload event.
 *  
 *  @param event The updated upload event.
 */
typedef void (^DJIWaypointMissionOperatorUploadEventBlock)(DJIWaypointMissionUploadEvent *event);


/**
 *  Adds listener to receive the event related to upload.
 *  
 *  @param listener Listener that is interested on upload event.
 *  @param queue The dispatch queue that `block` will be called on.
 *  @param block Block will be called when there is event updated related to upload.
 */
- (void)addListenerToUploadEvent:(id)listener
                       withQueue:(nullable dispatch_queue_t)queue
                       andBlock:(DJIWaypointMissionOperatorUploadEventBlock)block;


/**
 *  Block to receive the updated download event.
 *  
 *  @param event The updated download event.
 */
typedef void (^DJIWaypointMissionOperatorDownloadEventBlock)(DJIWaypointMissionDownloadEvent *event);


/**
 *  Adds listener to receive the event related to download.
 *  
 *  @param listener Listener that is interested on download event.
 *  @param queue The dispatch queue that `block` will be called on.
 *  @param block Block will be called when there is event updated related to download.
 */
- (void)addListenerToDownloadEvent:(id)listener
                         withQueue:(nullable dispatch_queue_t)queue
                          andBlock:(DJIWaypointMissionOperatorDownloadEventBlock)block;


/**
 *  Block to receive the updated execution event.
 *  
 *  @param event The updated execution event.
 */
typedef void (^DJIWaypointMissionOperatorExecutionEventBlock)(DJIWaypointMissionExecutionEvent *event);

/**
 *  Adds listener to receive the event related to execution.
 *  
 *  @param listener Listener that is interested on execution event.
 *  @param queue The dispatch queue that `block` will be called on.
 *  @param block Block will be called when there is event updated related to execution.
 */
- (void)addListenerToExecutionEvent:(id)listener
                          withQueue:(nullable dispatch_queue_t)queue
                           andBlock:(DJIWaypointMissionOperatorExecutionEventBlock)block;


/**
 *  Block to receive the notification that a waypoint mission is started
 *  successfully.
 */
typedef void (^DJIWaypointMissionOperatorSimpleEventBlock)();

/**
 *  Adds listener to receive the notification when a waypoint mission is started.
 *  
 *  @param listener Listener that is interested on the start of waypoint mission.
 *  @param queue The dispatch queue that `block` will be called on.
 *  @param block Block will be called when a waypoint mission is started.
 */
- (void)addListenerToStarted:(id)listener
                   withQueue:(nullable dispatch_queue_t)queue
                   andBlock:(DJIWaypointMissionOperatorSimpleEventBlock)block;


/**
 *  Adds listener to receive the notification when a waypoint mission is finished.
 *  
 *  @param listener Listener that is interested on the finish of waypoint mission.
 *  @param queue The dispatch queue that `block` will be called on.
 *  @param block Block will be called when a waypoint mission is finished. If the mission is interrupted with an error, the error will be passed to the block.
 */
- (void)addListenerToFinished:(id)listener
                    withQueue:(nullable dispatch_queue_t)queue
                     andBlock:(DJICompletionBlock)block;


/**
 *  Removes listener. If the same listener is listening to multiple events and
 *  notifications (e.g. upload event and download event), it will not receive any
 *  update of them.
 *  
 *  @param listener Listener to be removed.
 */
- (void)removeListener:(id)listener;


/**
 *  Removes listener to stop listening to upload events.
 *  
 *  @param listener Listener to be removed.
 */
- (void)removeListenerOfUploadEvents:(id)listener;


/**
 *  Removes listener to stop listening to download events.
 *  
 *  @param listener Listener to be removed.
 */
- (void)removeListenerOfDownloadEvents:(id)listener;


/**
 *  Removes listener to stop listening to execution events.
 *  
 *  @param listener Listener to be removed.
 */
- (void)removeListenerOfExecutionEvents:(id)listener;


/**
 *  Removes listener to stop listening to the notification that a mission is
 *  started.
 *  
 *  @param listener Listener to be removed.
 */
- (void)removeListenerOfStarted:(id)listener;


/**
 *  Removes listener to stop listening to the notification that a mission is
 *  finished.
 *  
 *  @param listener Listener to be removed.
 */
- (void)removeListenerOfFinished:(id)listener;


/**
 *  Remove all listeners.
 */
- (void)removeAllListeners;

/*********************************************************************************/
#pragma mark - Mission Operation
/*********************************************************************************/


/**
 *  Starts to upload the `loadedMission` to the aircraft. It can only be called when
 *  the `loadedMission` is complete and the `currentState` is
 *  `DJIWaypointMissionStateReadyToUpload`. If a timeout error occurs during the
 *  previous upload, the upload operation will resume from the previous break-point.
 *  After a mission is uploaded successfully, the `DJIWaypointMissionState` will
 *  become `DJIWaypointMissionStateReadyToExecute`.
 *  
 *  @param completion Completion block that will be called when the upload operation succeeds or fails to start. If it is started successfully, use `addListenerToUploadEvent:withQueue:andBlock` to receive the detailed progress.
 */
- (void)uploadMissionWithCompletion:(DJICompletionBlock)completion;


/**
 *  Downloads information of each waypoint from aircraft and save it to
 *  `loadedMission`. If a download operation is started, the operator will download
 *  the information of waypoints missing in `loadedMission` one-by-one in ascending
 *  order. If `loadedMission` is already complete (containing all the waypoints),
 *  this method will call `completion` immediately without error. It can only be
 *  called when the `currentState` is one of the following: -
 *  `DJIWaypointMissionStateExecuting` - `DJIWaypointMissionStateExecutionPaused`
 *  
 *  @param completion Completion block that will be called when the download operation succeeds or fails to start. If it is started successfully, use `addListenerToDownloadEvent:withQueue:andBlock` to receive the detailed progress.
 */
- (void)downloadMissionWithCompletion:(DJICompletionBlock)completion;


/**
 *  Starts the execution of the uploaded mission. It can only be called when the
 *  `currentState` is `DJIWaypointMissionStateReadyToExecute`. After a mission is
 *  started successfully, the `currentState` will become
 *  `DJIWaypointMissionStateExecuting`.
 *  
 *  @param completion Completion block that will be called when the operator succeeds or fails to start the execution. If it fails, an error will be returned.
 */
- (void)startMissionWithCompletion:(DJICompletionBlock)completion;


/**
 *  Pauses the executing mission. It can only be called when the
 *  `DJIWaypointMissionState` is `DJIWaypointMissionStateExecuting`. After a mission
 *  is paused successfully, the `currentState` will become
 *  `DJIWaypointMissionStateExecutionPaused`.
 *  
 *  @param completion Completion block that will be called when the operator succeeds or fails to pause the mission. If it fails, an error will be returned.
 */
- (void)pauseMissionWithCompletion:(DJICompletionBlock)completion;


/**
 *  Resumes the paused mission. It can only be called when the `currentState` is
 *  `DJIWaypointMissionStateExecutionPaused`. After a mission is resumed
 *  successfully, the `currentState` will become `DJIWaypointMissionStateExecuting`.
 *  
 *  @param completion Completion block that will be called when the operator succeeds or fails to resume the mission. If it fails, an error will be returned.
 */
- (void)resumeMissionWithCompletion:(DJICompletionBlock)completion;


/**
 *  Stops the executing or paused mission. It can only be called when the
 *  `currentState` is one of the following: - `DJIWaypointMissionStateExecuting` -
 *  `DJIWaypointMissionStateExecutionPaused` After a mission is stopped
 *  successfully, `currentState` will become `DJIWaypointMissionStateReadyToUpload`.
 *  
 *  @param completion Completion block that will be called when the operator succeeds or fails to stop the mission. If it fails, an error will be returned.
 */
- (void)stopMissionWithCompletion:(DJICompletionBlock)completion;

/*********************************************************************************/
#pragma mark - Mission Updates
/*********************************************************************************/


/**
 *  Set the flight speed while the mission is executing automatically (without
 *  manual joystick speed input). This is the only property or method in this class
 *  that can communicate with the aircraft during a mission. All other properties
 *  and methods are used offline to prepare the mission which is then uploaded to
 *  the aircraft.
 *  
 *  @param speed Auto flight speed to be set. The absolute value of the auto flight speed should be less than or equal to the `maxFlightSpeed`. Its range is [-`maxFlightSpeed`, `maxFlightSpeed`] m/s.
 *  @param completion Completion block.
 */
- (void)setAutoFlightSpeed:(float)speed withCompletion:(DJICompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END
