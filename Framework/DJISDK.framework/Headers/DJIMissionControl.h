//
//  DJIMissionControl.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIMission.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIWaypointMissionOperator;
@class DJIHotpointMissionOperator;
@class DJIFollowMeMissionOperator;
@class DJIActiveTrackMissionOperator;
@class DJITapFlyMissionOperator; 
@class DJIMissionTrigger;
@class DJIPanoramaMissionOperator;



/**
 *  Required behavior of elements that run in a Timeline.
 *   In addition to implementing this behavior, a Timeline element must communicate
 *  with Mission Control to let it know its state. Mission Control will wait for
 *  updates from the Timeline element before it itself progresses. Refer to
 *  `DJIMissionControlTimelineElementFeedback` for the methods Mission Control
 *  exposes for the Timeline element to use to communicate.
 */
@protocol DJIMissionControlTimelineElement <NSObject>


/**
 *  If Implemented, this is called by Mission Control right before running the
 *  element.
 */
@optional
- (void)willRun;

/**
 *  If implemented, Mission Control loads and activates the triggers for the
 *  duration that the Timeline element is executing.
 *  
 *  @return An array of `DJIMissionTrigger` object.
 */
@optional
- (NSArray <DJIMissionTrigger *> *)triggers;


/**
 *  Starts execution of Timeline element. Missions adopting this behavior are being
 *  run with their respective operators.
 */
@required
- (void)run;


/**
 *  `YES` if the element can be paused. If `NO`, then when the Timeline is asked  to
 *  pause when this element is running, nothing will happen.
 *  
 *  @return `YES` if the element can be paused.
 */
@required
- (BOOL)isPausable;


/**
 *  Pauses the execution of the element. Must be implemented if `isPausable` returns
 *  `YES`.
 */
@optional
- (void)pauseRun;


/**
 *  Resumes the execution of the element. Must be implemented if `isPausable`
 *  returns `YES`.
 */
@optional
- (void)resumeRun;


/**
 *  Stops execution of the element.
 */
@required
- (void)stopRun;


/**
 *  Called after element execution, regardless of whether or not it was successful.
 */
@optional
- (void)didRun;


/**
 *  Returns an error if there is a configuration or parameter error in the element.
 *  Returns `nil` if there is no issue.
 *  
 *  @return An NSError object.
 */
@required
- (NSError *_Nullable)checkValidity;

@end


/**
 *  This protocol defines how the timeline element may contact mission control  to
 *  notify it of its own execution. This protocol is not intended to be  implemented
 *  by any other object and the use of a protocol is primarily  organizational.
 */
@protocol DJIMissionControlTimelineElementFeedback <NSObject>


/**
 *  Used by elements to notify Mission Control of their successful start.
 *  
 *  @param element A previously scheduled element. Should also be the element running.
 */
- (void)elementDidStartRunning:(id <DJIMissionControlTimelineElement>)element;


/**
 *  Used by elements to notify Mission Control of a failure preventing to start.
 *  
 *  @param element A previously scheduled element. Should also be the element running.
 *  @param error A valid error object.
 */
- (void)element:(id <DJIMissionControlTimelineElement>)element failedStartingWithError:(NSError *)error;


/**
 *  Used by elements to notify Mission Control of a progress in the execution.
 *  Additional information may be pulled by mission control depending on the
 *  element. Calling this method with an error means the element is still running
 *  and the error did not cause it to stop.
 *  
 *  @param element A previously scheduled element. Should also be the element running.
 *  @param error An optional error if something went wrong.
 */
- (void)element:(id <DJIMissionControlTimelineElement>)element progressedWithError:(NSError * _Nullable)error;


/**
 *  Used by elements to notify Mission Control of a successful pausing.
 *  
 *  @param element A previously scheduled element. Should also be the element running.
 */
- (void)elementDidPause:(id <DJIMissionControlTimelineElement>)element;


/**
 *  Used by elements to notify Mission Control of a failure to pause. The element is
 *  expected to be still running.
 *  
 *  @param element A previously scheduled element. Should also be the element running.
 *  @param error A valid error object.
 */
- (void)element:(id <DJIMissionControlTimelineElement>)element failedPausingWithError:(NSError *)error;


/**
 *  Used by elements to notify Mission Control of a successful resuming of a
 *  previously paused element.
 *  
 *  @param element A previously scheduled element. Should also be the element running.
 */
- (void)elementDidResume:(id <DJIMissionControlTimelineElement>)element;


/**
 *  Used by elements to notify Mission Control of a failure to resume. The element
 *  is expected to be still paused.
 *  
 *  @param element A previously scheduled element. Should also be the element running.
 *  @param error A valid error object.
 */
- (void)element:(id <DJIMissionControlTimelineElement>)element failedResumingWithError:(NSError *)error;


/**
 *  Used by elements to notify Mission Control of the end of the execution of it.
 *  
 *  @param element A previously scheduled element. Should also be the element running.
 *  @param error An optional error if the execution end was the result of it.
 */
- (void)element:(id <DJIMissionControlTimelineElement>)element didFinishRunningWithError:(NSError * _Nullable)error;


/**
 *  Used by elements to notify Mission Control of their successful manual stop.
 *  
 *  @param element A previously scheduled element. Should also be the element running.
 */
- (void)elementDidStopRunning:(id <DJIMissionControlTimelineElement>)element;


/**
 *  Used by elements to notify Mission Control of a failure to stop the execution of
 *  the element. This should only be used to handle error after stopRun is called.
 *  
 *  @param element A previously scheduled element. Should also be the element running.
 *  @param error A valid error object.
 */
- (void)element:(id <DJIMissionControlTimelineElement>)element failedStoppingWithError:(NSError *)error;

@end



/**
 *  The domain associated with errors specific to Mission Control.
 */
extern const NSErrorDomain DJIMissionControlErrorDomain;


/**
 *  Defines all MissionControl related errors.
 */
typedef NS_ENUM(NSInteger, DJIMissionControlError) {

    /**
     *  Default placeholder when no other code matches.
     */
    DJIMissionControlErrorUnknown = -1,
    

    /**
     *  Can't pause an element which is not pausbile.
     */
    DJIMissionControlTimelineErrorCannotPauseUnpausableElement = 10001,
    

    /**
     *  Tried to schedule new element while the Timeline was running.
     */
    DJIMissionControlTimelineErrorCannotScheduleWhileRunning = 10002,
    

    /**
     *  Can't start a timeline whose marker is already at the end.
     */
    DJIMissionControlTimelineStartErrorAlreadyAtEnd = 10003,
    

    /**
     *  Can't start a timeline which was already running.
     */
    DJIMissionControlTimelineStartErrorAlreadyRunning = 10004,
    

    /**
     *  Can't start a paused timeline. Need to call resume instead.
     */
    DJIMissionControlTimelineStartErrorTimelineIsPaused = 10005,
    

    /**
     *  Can't pause a timeline which is not running.
     */
    DJIMissionControlTimelinePauseErrorNotRunning = 10006,
    

    /**
     *  Can't pause a timeline which is already paused.
     */
    DJIMissionControlTimelinePauseErrorAlreadyPaused = 10007,
    

    /**
     *  Can't resume a timeline which is not running.
     */
    DJIMissionControlTimelineResumeErrorNotRunning = 10008,
    

    /**
     *  Can't resume a timeline which is not paused.
     */
    DJIMissionControlTimelineResumeErrorNotPaused = 10009,
    

    /**
     *  Can't resume an element which is not pausbile.
     */
    DJIMissionControlTimelineErrorCannotResumeUnpausableElement = 10010,
    

    /**
     *  Can't stop a timeline which is not running.
     */
    DJIMissionControlTimelineStopErrorNotRunning = 10011,
        

    /**
     *  Element passed does not conform to DJIMissionControlTimelineElement protocol
     */
    DJIMissionControlElementErrorProtocolNotConform = 20001,
    

    /**
     *  The element passed is a mission without a valid operator.
     */
    DJIMissionControlElementErrorInvalidMissionOperator = 20002,
    

    /**
     *  IsPausable was set to yes but the item doesn't implement pauseRun and/or
     *  resumeRun methods.
     */
    DJIMissionControlElementErrorInvalidPauseImplementation = 20003,
    

    /**
     *  Timeline trigger does not have an action implemented.
     */
    DJIMissionControlTimelineTriggerErrorActionNotImplemented = 30000,
};


/**
 *  Mission Control handles execution of missions. Either single missions can be run
 *  through dedicated mission operators, or a series of missions and actions can be
 *  run serially using the Timeline.
 *   Mission operators look after execution of a single mission. A mission operator
 *  has APIs to control the mission (e.g. start, stop, pause etc.) and provides
 *  mission state through listeners.
 *   Mission Control's Timeline is made up of a series of Timeline elements which
 *  can be Waypoint missions, Hotpoint missions (through the Hotpoint action
 *  `DJIHotpointAction`) or objects that follow the
 *  `DJIMissionControlTimelineElement` protocol. `DJIMissionAction` is a Timeline
 *  element, with `DJIAircraftYawAction` and `DJIGimbalAttitudeAction` subclasses
 *  being examples of specific actions. If a mission is being executed in a
 *  Timeline, the mission operator can still be used to get state information of the
 *  mission as well as change mission execution parameters.
 *   Timeline elements can also have triggers (`DJIMissionTrigger`) associated with
 *  them. Triggers are separate objects that are run in parallel with a Timeline
 *  element. The trigger object is used to initiate actions if a set of criteria are
 *  met. For example, a trigger could be used to monitor battery level, and then
 *  initiate an action once a threshold is passed. Mission Control's Timeline is
 *  only supported by aircrafts. Handheld devices (e.g. OSMO) do not support this
 *  feature.
 *   The listening mechanism for Mission Control is block based. To listen to an
 *  event, a listener object and a block to execute when the event occurs is passed
 *  to Mission Control. The listener object is only used by Mission Control to keep
 *  track of whether it should execute the listener block or not. Mission Control
 *  would not execute the listener block if the listener object was removed from the
 *  listener pool.
 *   Mission Control is accessed from `missionControl` in `DJISDKManager`.
 */
@interface DJIMissionControl : NSObject <DJIMissionControlTimelineElementFeedback>

/*********************************************************************************/
#pragma mark - Mission Operators
/*********************************************************************************/


/**
 *  Returns the operator for waypoint missions.
 *  
 *  @return A Waypoint mission operator object.
 */
- (DJIWaypointMissionOperator *)waypointMissionOperator;


/**
 *  Returns the operator for Hotpoint missions.
 *  
 *  @return A Hotpoint mission operator object.
 */
- (DJIHotpointMissionOperator *)hotpointMissionOperator;


/**
 *  Returns the operator for Follow Me missions.
 *  
 *  @return A Follow Me mission operator object.
 */
- (DJIFollowMeMissionOperator *)followMeMissionOperator;


/**
 *  Returns the operator for ActiveTrack missions.
 *  
 *  @return An ActiveTrack mission operator object.
 */
- (DJIActiveTrackMissionOperator *)activeTrackMissionOperator;


/**
 *  Returns the operator for TapFly missions.
 *  
 *  @return A TapFly mission operator object.
 */
- (DJITapFlyMissionOperator *)tapFlyMissionOperator;


/**
 *  Returns the operator for Panorama missions.
 *  
 *  @return A Panorama mission operator object.
 */
- (DJIPanoramaMissionOperator *)panoramaMissionOperator;

/*********************************************************************************/
#pragma mark - Timeline
/*********************************************************************************/


/**
 *  `YES` if the Timeline is running.
 */
@property (nonatomic, readonly) BOOL isTimelineRunning;


/**
 *  The current element index in the Timeline that is being executed.  This value
 *  can be set only when a Timeline is stopped (not executing or paused).
 */
@property (nonatomic) NSUInteger currentTimelineMarker;


/**
 *  `YES` if Timeline is paused.
 */
@property (nonatomic, readonly) BOOL isTimelinePaused;


/**
 *  The current element that is running in the Timeline. If the Timeline is not
 *  running, then this is `nil`.
 */
@property (readonly, nonatomic, nullable) id <DJIMissionControlTimelineElement> runningElement;


/**
 *  Start Timeline execution from the current element index `currentTimelineMarker`.
 */
- (void)startTimeline;


/**
 *  Pause execution of the Timeline, and current element (if pausible). If the
 *  current element is not pausible then this method will do nothing.
 */
- (void)pauseTimeline;


/**
 *  Resume element and Timeline execution.
 */
- (void)resumeTimeline;


/**
 *  Stops the execution of the Timeline, resets the marker index to 0.
 */
- (void)stopTimeline;


/**
 *  Adds an element to the end of the Timeline.
 *  
 *  @param element A `DJIMissionControlTimelineElement` element.
 *  
 *  @return The first error if one occurred.
 */
- (NSError * _Nullable)scheduleElement:(id <DJIMissionControlTimelineElement>)element;


/**
 *  Adds an array of elements to the end of the Timeline.
 *  
 *  @param elements An array of `DJIMissionControlTimelineElement` elements.
 *  
 *  @return The first error if one occurred. <code>userInfo</code> will hold a dictionary with two keys: @"element" -> holding the elemnt involved in the error and @"index" -> the index in the array for the element.
 */
- (NSError * _Nullable)scheduleElements:(NSArray <id <DJIMissionControlTimelineElement>> *)elements;


/**
 *  Insert an element into the Timeline at an index.
 *  
 *  @param element A `DJIMissionControlTimelineElement` element
 *  @param index The element index to insert the new element before.
 *  
 *  @return The first error if one occurred.
 */
- (NSError * _Nullable)scheduleElement:(id <DJIMissionControlTimelineElement>)element atIndex:(NSUInteger)index;


/**
 *  Remove element from the Timeline. If the same element was used more than once in
 *  the  Timeline, then the first one will be removed.
 *  
 *  @param element A `DJIMissionControlTimelineElement` element that is already in the Timeline.
 */
- (void)unscheduleElement:(id <DJIMissionControlTimelineElement>)element;


/**
 *  Removes the Element at an index in the Timeline.
 *  
 *  @param index Index of element to remove.
 */
- (void)unscheduleElementAtIndex:(NSUInteger)index;


/**
 *  Returns the element at a given index in the Timeline.
 *  
 *  @param index An element index in the Timeline.
 *  
 *  @return Either a mission, an element or `nil` if nothing was at the given index.
 */
- (nullable id)scheduledElementAtIndex:(NSUInteger)index;


/**
 *  Returns the number of elements within the Timeline.
 *  
 *  @return Element count.
 */
- (NSUInteger)scheduledElementsCount;


/**
 *  Gets the index of an element among the scheduled elements.
 *  
 *  @param element The element whose index is to be returned.
 *  
 *  @return The index of an element.
 */
- (NSUInteger)indexOfScheduledElement:(id <DJIMissionControlTimelineElement>)element;


/**
 *  Clears the Timeline, removing all elements.
 */
- (void)unscheduleEverything;


/**
 *  Adds triggers to be living along the whole timeline.
 *  
 *  @param triggers An object of `DJIMissionTrigger`.
 */
- (void)scheduleTriggers:(NSArray <DJIMissionTrigger *> *)triggers;


/**
 *  Clears all the triggers living along the whole timeline.
 *  
 *  @param triggers An object of `DJIMissionTrigger`.
 */
- (void)unscheduleTriggers:(NSArray <DJIMissionTrigger *> *)triggers;


/**
 *  Return the triggers' count living along the whole timeline.
 *  
 *  @return An NSUInteger value of scheduled Triggers Count.
 */
- (NSUInteger)scheduledTriggersCount;

/*********************************************************************************/
#pragma mark - Listener Progress
/*********************************************************************************/


/**
 *  Events that can initiate a call to the Mission Control listener.
 */
typedef NS_ENUM(NSInteger, DJIMissionControlTimelineEvent) {


    /**
     *  Unknown event type. This is a default value if no other event is matching.
     */
    DJIMissionControlTimelineEventUnknown = -1,
    

    /**
     *  Timeline successfully started.
     */
    DJIMissionControlTimelineEventStarted,
    

    /**
     *  Timeline failed to start.
     */
    DJIMissionControlTimelineEventStartError,
    

    /**
     *  Timeline element progressed.
     */
    DJIMissionControlTimelineEventProgressed,
    

    /**
     *  Timeline successfully paused.
     */
    DJIMissionControlTimelineEventPaused,
    

    /**
     *  Timeline failed to be paused.
     */
    DJIMissionControlTimelineEventPauseError,
    

    /**
     *  Timeline successfully resumed.
     */
    DJIMissionControlTimelineEventResumed,
    

    /**
     *  Timeline failed to resume.
     */
    DJIMissionControlTimelineEventResumeError,
    

    /**
     *  Timeline Stopped successfully.
     */
    DJIMissionControlTimelineEventStopped,
    

    /**
     *  Timeline failed to stop and is still continuing in its previous state.
     */
    DJIMissionControlTimelineEventStopError,
    

    /**
     *  Timeline completed its execution normally.
     */
    DJIMissionControlTimelineEventFinished,
};


/**
 *  Block used to process Timeline events.
 *  
 *  @param element The Timeline element associated with the event, or `nil` if the  event is global to the whole Timeline (e.g. start, finish the  Timeline).
 *  @param event Event.
 *  @param error The optional error if the event was error-related.
 *  @param info An optional object containing additional information.
 */
typedef void (^DJIMissionControlTimelineEventBlock)(DJIMissionControlTimelineEvent event, id <DJIMissionControlTimelineElement> _Nullable element, NSError *_Nullable error, id _Nullable info);


/**
 *  Adds a listener to all Timeline events.
 *  
 *  @param listener A listener object.
 *  @param eventBlock A block to be called for each Timeline event
 */
- (void)addListener:(id)listener toTimelineProgressWithBlock:(DJIMissionControlTimelineEventBlock)eventBlock;


/**
 *  Removes the listener from the Timeline events listeners pool.
 *  
 *  @param listener A previously added listener object.
 */
- (void)removeListener:(id)listener;


/**
 *  Removes all listeners from the Timeline events listeners pool.
 */
- (void)removeAllListeners;

@end

NS_ASSUME_NONNULL_END
