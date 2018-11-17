//
//  DJIActiveTrackMission.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#ifndef DJIActiveTrackMission_h
#define DJIActiveTrackMission_h

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "DJIMission.h"

NS_ASSUME_NONNULL_BEGIN


/**
 *  The state of the target being tracked by the aircraft.
 */
typedef NS_ENUM(NSInteger, DJIActiveTrackTargetState) {

    /**
     *  The aircraft has recognized the target but the user is not allowed to confirm
     *  the target. Check `cannotConfirmReason` to get  more information.
     */
    DJIActiveTrackTargetStateCannotConfirm,

    /**
     *  The aircraft has recognized the target and is waiting for user's confirmation.
     *  If this state, the aircraft will hover in the current position while the camera
     *  is tracking the target (by rotating aircraft's yaw or gimbal's altitude). If
     *  user confirms the target, the aircraft will start to following the movement of
     *  the target.
     */
    DJIActiveTrackTargetStateWaitingForConfirmation,

    /**
     *  The aircraft has recognized the target with high confidence.
     */
    DJIActiveTrackTargetStateTrackingWithHighConfidence,

    /**
     *  The ActiveTrack Mission is tracking a target with low confidence. This is only
     *  an indication that either the aircraft will soon ask for confirmation that the
     *  target is correct, or may loose tracking the target entirely if confidence
     *  doesn't improve.
     */
    DJIActiveTrackTargetStateTrackingWithLowConfidence,

    /**
     *  Unknown.
     */
    DJIActiveTrackTargetStateUnknown = 0xFF
};


/**
 *  The type of ActiveTrack target.
 */
typedef NS_ENUM(NSInteger, DJIActiveTrackTargetType) {

    /**
     *  The ActiveTrack target is a human being.
     */
    DJIActiveTrackTargetTypeHuman,

    /**
     *  The ActiveTrack target is a car.
     */
    DJIActiveTrackTargetTypeCar,

    /**
     *  The ActiveTrack target is a van.
     */
    DJIActiveTrackTargetTypeVan,

    /**
     *  The ActiveTrack target is a bike.
     */
    DJIActiveTrackTargetTypeBike,

    /**
     *  The ActiveTrack target is a boat.
     */
    DJIActiveTrackTargetTypeBoat,

    /**
     *  The aircraft cannot recognize the target type.
     */
    DJIActiveTrackTargetTypeUnknown
};


/**
 *  Different modes of the ActiveTrack Mission. Defaults to
 *  `DJIActiveTrackModeTrace`, set to  others to enable the feature.
 */
typedef NS_ENUM (NSInteger, DJIActiveTrackMode) {


    /**
     *  Aircraft moves in behind the subject keeping a constant distance to it.  Mission
     *  with this mode can only be started when the aircraft is flying.
     */
    DJIActiveTrackModeTrace,


    /**
     *  Aircraft moves in parallel with the subject in the frame instead of behind.
     *  Mission with this mode can only be started when the aircraft is flying.
     */
    DJIActiveTrackModeProfile,


    /**
     *  In Spotlight mode, the aircraft camera automatically follows the subject by
     *  rotating the aircraft's yaw, but the aircraft does not automatically keep a
     *  constant distance with the subject. Mission with this mode can only be started
     *  when the aircraft is flying.
     */
    DJIActiveTrackModeSpotlight,


    /**
     *  In Spotlight Pro mode, the aircraft camera automatically follows the subject by
     *  rotating the gimbal's yaw, but the aircraft does not automatically keep a
     *  constant  distance with the subject.
     */
    DJIActiveTrackModeSpotlightPro,


	/**
	 *  In QuickShot mode, the aircraft will fly in one of four preset paths (see
	 *  `DJIActiveTrackQuickShotMode`)  while tracking the object recording a video.
	 *  When a QuickShot mission ends, a 10-second video will be  generated. It is only
	 *  supported by Spark.
	 */
	DJIActiveTrackModeQuickShot,
	

    /**
     *  The active track mode is unknown.
     */
    DJIActiveTrackModeUnknown = 0xFF
};


/**
 *  QuickShot modes, which define different preset path for a QuickShot mission.
 */
typedef NS_ENUM(NSUInteger, DJIActiveTrackQuickShotMode) {

	/**
	 *  Aircraft will circle around the object it is tracking.
	 */
	DJIActiveTrackQuickShotModeCircle,

	/**
	 *  Aircraft will fly backward and upward with camera locked on the object it is
	 *  tracking.
	 */
	DJIActiveTrackQuickShotModeDronie,

	/**
	 *  Aircraft will fly upward, spiraling around the object it is tracking.
	 */
	DJIActiveTrackQuickShotModeHelix,

	/**
	 *  The aircraft will ascend with the camera pointing downward on the object it is
	 *  tracking.
	 */
	DJIActiveTrackQuickShotModeRocket,

    /**
     *  The aircraft will fly around the tracking object in an upwardly sloped oval with
     *  the  video finishing at the start point. Only supported by DJI Mavic Air.
     */
    DJIActiveTrackQuickShotModeBoomerang,

    /**
     *  The aircraft will fly backward and upward while recording video, capture a
     *  sphere  panorama at the end of the flight path, then combine the footage and
     *  panorama into  a short video. Only supported by DJI Mavic Air.
     */
    DJIActiveTrackQuickShotModeAsteroid,

    /**
     *  The aircraft will fly backward and upward. It will adjust the zoom during flight
     *  to keep the selected subject the same while the background changes. Ensure there
     *  is sufficient space when using Dolly Zoom. Allow at least triple distance from
     *  aircraft to the subject behind the aircraft. Only supported by Mavic 2 Zoom.
     */
    DJIActiveTrackQuickShotModeDollyZoom,

	/**
	 *  Unknown.
	 */
	DJIActiveTrackQuickShotModeUnknown = 0xFF,
};



/**
 *  The reason why user is not allowed to confirm the current target.
 */
typedef NS_ENUM (NSInteger, DJIActiveTrackCannotConfirmReason) {

    /**
     *  None.
     */
    DJIActiveTrackCannotConfirmReasonNone,

    /**
     *  The target is unstable.
     */
    DJIActiveTrackCannotConfirmReasonUnstableTarget,

    /**
     *  The target position is too high.
     */
    DJIActiveTrackCannotConfirmReasonTargetTooHigh,

    /**
     *  There is an obstacle between the aircraft and the target that is blocking the
     *  target.
     */
    DJIActiveTrackCannotConfirmReasonBlockedByObstacle,

    /**
     *  The gimbal's attitude is pointing to the ground.
     */
    DJIActiveTrackCannotConfirmReasonGimbalAttitudeError,

    /**
     *  The target is too far away from the aircraft.
     */
    DJIActiveTrackCannotConfirmReasonTargetTooFar,

    /**
     *  The target is too close to the aircraft.
     */
    DJIActiveTrackCannotConfirmReasonTargetTooClose,

    /**
     *  The altitude of the aircraft is too high.
     */
    DJIActiveTrackCannotConfirmReasonAircraftTooHigh,

    /**
     *  The altitude of the aircraft is too low.
     */
    DJIActiveTrackCannotConfirmReasonAircraftTooLow,

    /**
     *  The obstacle vision sensor has errors.
     */
    DJIActiveTrackCannotConfirmReasonObstacleSensorError,

    /**
     *  Unknown.
     */
    DJIActiveTrackCannotConfirmReasonUnknown = 0xFF
};


/**
 *  The state of one of the auto-sensed subject after enabling auto sensing.  Only
 *  supported by DJI Mavic Air.
 */
@interface DJISubjectSensingState : NSObject


/**
 *  Index of the auto-sensed subjects. After enabling auto sensing, the aircraft
 *  may find multiple subjects and an index will be assigned to each subject.  Use
 *  this index to select the subject to track.
 */
@property (nonatomic, readonly) NSInteger index;


/**
 *  The target state of the auto-sensed subject.
 */
@property (nonatomic, readonly) DJIActiveTrackTargetState state;


/**
 *  The type of the auto-sensed subject.
 */
@property (nonatomic, readonly) DJIActiveTrackTargetType targetType;


/**
 *  A rectangle in the live video view image that represents the auto-sensed
 *  subject.  The rectangle is normalized to [0,1] where (0,0) is the top left of
 *  the video  preview and (1,1) is the bottom right.
 */
@property (nonatomic, readonly) CGRect targetRect;

@end


/**
 *  The tracking state of the ActiveTrack mission that is executing.
 */
@interface DJIActiveTrackTrackingState : NSObject

/**
 *  The state of the target being tracked.
 */
@property (nonatomic, readonly) DJIActiveTrackTargetState state;

/**
 *  The type of the target being tracked.
 */
@property (nonatomic, readonly) DJIActiveTrackTargetType targetType;


/**
 *  A rectangle in the live video view image that represents the target being
 *  tracked.  The rectangle is normalized to [0,1] where (0,0) is the top left of
 *  the video  preview and (1,1) is the bottom right.
 *  
 *  @return .
 */
@property (nonatomic, readonly) CGRect targetRect;


/**
 *  Reason why the target cannot be confirmed by the user. It is useful when
 *  `state` is  `DJIActiveTrackTargetStateCannotConfirm`.  Otherwise, it is
 *  `DJIActiveTrackCannotConfirmReasonNone`.
 */
@property (nonatomic, readonly) DJIActiveTrackCannotConfirmReason cannotConfirmReason;


/**
 *  The progress of the executing QuickShot mission. Only applicable when  `mode` is
 *  `DJIActiveTrackModeQuickShot`.  For other modes, it is always 0.
 */
@property (nonatomic, readonly) NSUInteger progress;


/**
 *  The auto-sensed subjects after enabling auto sensing.
 */
@property (nonatomic, readonly, nullable) NSArray<DJISubjectSensingState *> *autoSensedSubjects;

@end


/**
 *  ActiveTrack Mission allows an aircraft to track a moving subject using the
 *  vision system and without a GPS tracker on the subject.
 */
@interface DJIActiveTrackMission : DJIMission

/**
 *  A bounding box for the target. The rectangle is normalized to [0,1] where (0,0)
 *  is the top left  of the video preview and (1,1) is the bottom right. The `size`
 *  parameter of `CGRect` can be set  to 0 to initialize the mission with a point
 *  instead of a rectangle. If the mission is  initialized with a point, the vision
 *  system will try to recognize the object around the point  and return the
 *  representative rect in the status delegate.
 *   This property is used when  the `DJIActiveTrackMission` object is passed to
 *  `startMission:withCompletion`.  If the object is passed to
 *  `startAutoSensingMission:withCompletion`, this property  will be ignored. Use
 *  `subjectIndex` to select the target to track instead.
 */
@property (nonatomic, readwrite) CGRect targetRect;


/**
 *  The index of the subject to track. After starting auto sensing (by calling
 *  `enableAutoSensingWithCompletion`  or
 *  `enableAutoSensingForQuickShotWithCompletion`), the aircraft will push the
 *  sensed subjects  (`autoSensedSubjects`). Select the subject to track by passing
 *  the index of the subject.
 *  This  property is used when the `DJIActiveTrackMission` object is passed to
 *  `startAutoSensingMission:withCompletion`.  If the object is passed to
 *  `startMission:withCompletion`, this property will be ignored. Use `targetRect`
 *  to define the target to track.
 */
@property (nonatomic, readwrite) NSInteger subjectIndex;


/**
 *  ActiveTrack Mission mode. Defaults to `DJIActiveTrackModeTrace`.
 */
@property (nonatomic, readwrite) DJIActiveTrackMode mode;


/**
 *  The QuickShot mode determines the preset flight path. It is only used when
 *  `mode`  is `DJIActiveTrackModeQuickShot`.  Defaults to
 *  `DJIActiveTrackQuickShotModeUnknown`.  It is only supported by Spark.
 */
@property (nonatomic, readwrite) DJIActiveTrackQuickShotMode quickShotMode;

@end

NS_ASSUME_NONNULL_END

#endif /* DJIActiveTrackMission_h */
