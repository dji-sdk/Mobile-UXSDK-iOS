//
//  DJIWaypointMissionTypes.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#ifndef DJIWaypointMissionTypes_h
#define DJIWaypointMissionTypes_h

@class DJIWaypointMission;


/**
 *  Current waypoint mission state.
 */
typedef NS_ENUM (uint8_t, DJIWaypointMissionExecuteState){
    

    /**
     *  Waypoint mission is initializing, which means the mission has started and the
     *  aircraft is going to the first waypoint.
     */
    DJIWaypointMissionExecuteStateInitializing,
    

    /**
     *  Aircraft is currently moving toward the mission's next waypoint. This happens
     *  when  the `DJIWaypointMissionFlightPathMode` is set  to
     *  `DJIWaypointMissionFlightPathNormal`.
     */
    DJIWaypointMissionExecuteStateMoving,
    

    /**
     *  Aircraft is currently moving. This happens when the
     *  `DJIWaypointMissionFlightPathMode` is set  to
     *  `DJIWaypointMissionFlightPathCurved`.
     */
    DJIWaypointMissionExecuteStateCurveModeMoving,
    

    /**
     *  Aircraft is currently turning. This happens when the
     *  `DJIWaypointMissionFlightPathMode`  is set to
     *  `DJIWaypointMissionFlightPathCurved`.
     */
    DJIWaypointMissionExecuteStateCurveModeTurning,
    

    /**
     *  Aircraft has reached a waypoint, has rotated to the new heading and is now
     *  processing actions. This state  will be called before the waypoint actions
     *  starts executing and will occur for each waypoint action.
     */
    DJIWaypointMissionExecuteStateBeginAction,
    

    /**
     *  Aircraft is at a waypoint and is executing an action.
     */
    DJIWaypointMissionExecuteStateDoingAction,
    

    /**
     *  Aircraft is at a waypoint and has finished executing the current waypoint
     *  action. This state occurs once  for each waypoint action.
     */
    DJIWaypointMissionExecuteStateFinishedAction,
    

    /**
     *  Aircraft has returned to the first waypoint. This happens when the
     *  `finishedAction`  is set to
     *  `DJIWaypointMissionExecuteStateReturnToFirstWaypoint`.
     */
    DJIWaypointMissionExecuteStateReturnToFirstWaypoint,
    

    /**
     *  The mission is currently paused by the user.
     */
    DJIWaypointMissionExecuteStatePaused,
};


/**
 *  Actions taken when the waypoint mission has finished.
 */
typedef NS_ENUM (uint8_t, DJIWaypointMissionFinishedAction){
    

    /**
     *  No further action will be taken on completion of mission. At this point, the
     *  aircraft can be  controlled by the remote controller.
     */
    DJIWaypointMissionFinishedNoAction,
    

    /**
     *  The aircraft will go home when the mission is complete. If the aircraft is more
     *  than 20m away from  the home point it will go home and land. Otherwise, it will
     *  land directly at the current location.
     */
    DJIWaypointMissionFinishedGoHome,
    

    /**
     *  The aircraft will land automatically at the last waypoint.
     */
    DJIWaypointMissionFinishedAutoLand,
    

    /**
     *  The aircraft will go back to its first waypoint and hover in position.
     */
    DJIWaypointMissionFinishedGoFirstWaypoint,
    

    /**
     *  When the aircraft reaches its final waypoint, it will hover without ending the
     *  mission. The joystick  can still be used to pull the aircraft back along its
     *  previous waypoints. The only way this mission  can end is if stopMission is
     *  called.
     */
    DJIWaypointMissionFinishedContinueUntilStop
};


/**
 *  Current waypoint mission heading mode.
 */
typedef NS_ENUM (NSUInteger, DJIWaypointMissionHeadingMode){
    

    /**
     *  Aircraft's heading will always be in the direction of flight.
     */
    DJIWaypointMissionHeadingAuto,


    /**
     *  Aircraft's heading will be set to the heading when reaching the first waypoint.
     *  Before reaching the  first waypoint, the aircraft's heading can be controlled by
     *  the remote controller. When the aircraft  reaches the first waypoint, its
     *  heading will be fixed.
     */
    DJIWaypointMissionHeadingUsingInitialDirection,
    

    /**
     *  Aircraft's heading will be controlled by the remote controller.
     */
    DJIWaypointMissionHeadingControlledByRemoteController,
    

    /**
     *  Aircraft's heading will be gradually set to the next waypoint heading while
     *  travelling between two adjacent waypoints.
     */
    DJIWaypointMissionHeadingUsingWaypointHeading,
    

    /**
     *  Aircraft's heading will always toward point of interest.
     */
    DJIWaypointMissionHeadingTowardPointOfInterest,
};


/**
 *  Waypoint mission flight path mode.
 */
typedef NS_ENUM (NSUInteger, DJIWaypointMissionFlightPathMode){
    

    /**
     *  The flight path will be normal and the aircraft will move from one waypoint to
     *  the next in straight lines.
     */
    DJIWaypointMissionFlightPathNormal,
    

    /**
     *  The flight path will be curved and the aircraft will move from one waypoint to
     *  the next in a curved motion,  adhering to the `cornerRadiusInMeters`, which is
     *  set in `DJIWaypoint`.
     */
    DJIWaypointMissionFlightPathCurved
};


/**
 *  This enum will determine the goto point mode while the drone executes the
 *  flight.
 */
typedef NS_ENUM (NSInteger, DJIWaypointMissionGotoWaypointMode) {
    

    /**
     *  Go to the waypoint safely. The aircraft will rise to the same altitude of the
     *  waypoint if the current  altitude is lower then the waypoint altitude. It then
     *  goes to the waypoint coordinate from the current  altitude, and proceeds to the
     *  altitude of the waypoint.
     */
    DJIWaypointMissionGotoWaypointSafely,
    

    /**
     *  Go to the waypoint from the current aircraft point to the waypoint directly.
     */
    DJIWaypointMissionGotoWaypointPointToPoint,
};



/**
 *  The upload progress of the waypoint mission operator.
 */
@interface DJIWaypointUploadProgress : NSObject


/**
 *  The waypoint mission operator has uploaded the the mission's summary
 *  (information except waypoints).
 */
@property(nonatomic, readonly) BOOL isWaypointSummaryUploaded;


/**
 *  The index of the last uploaded waypoint. Information for each waypoint is
 *  uploaded one by one in ascending order. If no waypoint has been uploaded, the
 *  value will be -1.
 */
@property(nonatomic, readonly) NSInteger uploadedWaypointIndex;


/**
 *  The total count of waypoints in the waypoint mission.
 */
@property(nonatomic, readonly) NSUInteger totalWaypointCount;

@end


/**
 *  The download progress of the waypoint mission operator.
 */
@interface DJIWaypointDownloadProgress : NSObject


/**
 *  The index of the last downloaded waypoint. Information for each waypoint is
 *  downloaded one by one in ascending order. If no waypoint has been downloaded,
 *  the value will be -1.
 */
@property(nonatomic, readonly) NSInteger downloadedWaypointIndex;


/**
 *  The total count of waypoints in the waypoint mission.
 */
@property(nonatomic, readonly) NSUInteger totalWaypointCount;

@end


/**
 *  The mission execution progress of the waypoint mission operator.
 */
@interface DJIWaypointExecutionProgress : NSObject


/**
 *  Index of the waypoint for the next mission to which the aircraft will proceed.
 */
@property(nonatomic, readonly) NSInteger targetWaypointIndex;


/**
 *  YES when the aircraft reaches a waypoint. After the waypoint actions and heading
 *  change is complete,  the `targetWaypointIndex` will increment and this  property
 *  will become NO.
 */
@property(nonatomic, readonly) BOOL isWaypointReached;


/**
 *  Current execution state of the aircraft.
 */
@property(nonatomic, readonly) DJIWaypointMissionExecuteState execState;

@end

#endif /* DJIWaypointMissionTypes_h */
