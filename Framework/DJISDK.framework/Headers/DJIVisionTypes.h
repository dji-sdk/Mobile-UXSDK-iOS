//
//  DJIVisionTypes.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "DJISDKFoundation.h"

NS_ASSUME_NONNULL_BEGIN


/**
 *  Position of the sensor on the aircraft.
 */
typedef NS_ENUM(NSUInteger, DJIVisionSensorPosition) {
 

    /**
     *  The sensor is on the front or nose of the aircraft.
     */
    DJIVisionSensorPositionNose,
 

    /**
     *  The sensor is on the back or tail of the aircraft.
     */
    DJIVisionSensorPositionTail,
 

    /**
     *  The sensor is on the right or starboard side of the aircraft.
     */
    DJIVisionSensorPositionRight,
 

    /**
     *  The sensor is on the left or port side of the aircraft.
     */
    DJIVisionSensorPositionLeft,
    

    /**
     *  Unknown.
     */
    DJIVisionSensorPositionUnknown,
};


/**
 *  Distance warning returned by each sector of the front vision system. Warning
 *  Level 6 is the most serious level. For different aircraft, the same warning
 *  level will refer to different distances. Spark only supports the follow warning
 *  levels:
 *      - `DJIObstacleDetectionSectorWarningInvalid`
 *      - `DJIObstacleDetectionSectorWarningLevel1`
 *      - `DJIObstacleDetectionSectorWarningLevel2`
 *      - `DJIObstacleDetectionSectorWarningLevel3`
 *      - `DJIObstacleDetectionSectorWarningUnknown`
 */
typedef NS_ENUM (NSInteger, DJIObstacleDetectionSectorWarning){
 

    /**
     *  The warning level is invalid. The sector cannot determine depth of the scene in
     *  front of it.
     */
    DJIObstacleDetectionSectorWarningInvalid,
 

    /**
     *  Warning level 1.
     *   - Phantom 4 and Mavic Pro: the distance between the obstacle detected by  the
     *  sector and the aircraft is over 10 meters.
     *   - Spark: the distance between the obstacle  detected by the sector and the
     *  aircraft is over 4 meters.
     *   - Others: the distance between  the obstacle detected by the sector and the
     *  aircraft is over 20 meters.
     */
    DJIObstacleDetectionSectorWarningLevel1,
 

    /**
     *  Warning level 2.
     *   - Phantom 4 and Mavic Pro: the distance between the obstacle detected by the
     *  sector and the aircraft is between 8 - 10 meters.
     *   - Spark: the distance between the obstacle  detected by the sector and the
     *  aircraft is between 2 - 4 meters.
     *   - Others: the distance between  the obstacle detected by the sector and the
     *  aircraft is between 15 - 20 meters.
     */
    DJIObstacleDetectionSectorWarningLevel2,


    /**
     *  Warning level 3.
     *   - Phantom 4 and Mavic Pro: the distance between the obstacle detected by the
     *  sector  and the aircraft is between 6 - 8 meters.
     *   - Spark: the distance between the obstacle detected by the  sector and the
     *  aircraft is less than 2 meters.
     *   - Others: the distance between the obstacle detected  by the sector and the
     *  aircraft is between 10 - 15 meters.
     */
    DJIObstacleDetectionSectorWarningLevel3,
 

    /**
     *  Warning level 4.
     *   - Phantom 4 and Mavic Pro: the distance between the obstacle detected by the
     *  sector and the  aircraft is between 4 - 6 meters.
     *   - Others: the distance between the obstacle detected by the sector and the
     *  aircraft is between 6 - 10 meters. Spark does not support this warning level.
     */
    DJIObstacleDetectionSectorWarningLevel4,
    

    /**
     *  Warning level 5.
     *   - Phantom 4 and Mavic Pro: the distance between the obstacle detected by the
     *  sector and the  aircraft is between 2 - 4 meters.
     *   - Others: the distance between the obstacle detected by the sector and the
     *  aircraft is between 3 - 6 meters. Spark does not support this warning level.
     */
    DJIObstacleDetectionSectorWarningLevel5,
    

    /**
     *  Warning level 6.
     *   - Phantom 4 and Mavic Pro: the distance between the obstacle detected by the
     *  sector and the  aircraft is less than 2 meters.
     *   - Others: the distance between the obstacle detected by the sector and the
     *  aircraft is less than 3 meters. Spark does not support this warning level.
     */
    DJIObstacleDetectionSectorWarningLevel6,
 

    /**
     *  The distance warning is unknown. This warning is returned when an exception
     *  occurs.
     */
    DJIObstacleDetectionSectorWarningUnknown = 0xFF
};


/**
 *  Distance warning returned by the front vision system. Warning Level 4 is the
 *  most serious level.
 */
typedef NS_ENUM (NSInteger, DJIVisionSystemWarning){
 

    /**
     *  The warning is invalid. The front vision system cannot determine depth of the
     *  scene in front of it.
     */
    DJIVisionSystemWarningInvalid,
 

    /**
     *  The distance between the obstacle detected by the vision system and the aircraft
     *  is safe (over 2 meters).
     */
    DJIVisionSystemWarningSafe,
 

    /**
     *  The distance between the obstacle detected by the vision system and the aircraft
     *  is dangerous (less than 2 meters).
     */
    DJIVisionSystemWarningDangerous,
 

    /**
     *  The distance warning is unknown. This warning is returned when an exception
     *  occurs.
     */
    DJIVisionSystemWarningUnknown = 0xFF
};


/**
 *  States of PalmControl.
 */
typedef NS_ENUM(NSUInteger, DJIVisionPalmControlState) {

	/**
	 *  The aircraft is initializing for PalmControl.
	 */
	DJIVisionPalmControlStateInitializing,

	/**
	 *  The aircraft is recognizing the palm.
	 */
	DJIVisionPalmControlStateRecognizingPalm,

	/**
	 *  The aircraft is moving into position for the PalmControl Follow command. In this
	 *  state, the  aircraft is ascending and flying backward to a position that is 3m
	 *  horizontally away from  the user and 2.3m above the ground. Once it has reached
	 *  this position, the state will move  to `DJIVisionPalmControlStateFollowing` and
	 *  the aircraft will then follow the user. The  Follow command can be initiated by
	 *  raising one arm and quickly waving your hand at the camera.
	 */
	DJIVisionPalmControlStateStartingFollow,
    

	/**
	 *  The aircraft is currently following the user. To reach this state, the user
	 *  first raises  one arm and quickly waves their hand at the aircraft's camera. The
	 *  aircraft will then move  into position (3m from the user and 2.3m above the
	 *  ground), and reach this state.
	 */
	DJIVisionPalmControlStateFollowing,

	/**
	 *  The aircraft's position is being adjusted by the moving palm.
	 */
	DJIVisionPalmControlStateAdjustingPosition,

	/**
	 *  PalmControl is stopped. PalmControl can be stopped by moving the sticks on the
	 *  physical remote  controller or sending commands through
	 *  `DJIMobileRemoteController` when the physical remote  controller is absent.
	 */
	DJIVisionPalmControlStatePalmControlStopped,

	/**
	 *  Unknown.
	 */
	DJIVisionPalmControlStateUnknown = 0xFF
};


/**
 *  FaceAware states. FaceAware is a step of PalmLaunch. Tapping the battery battery
 *  power  button twice, FaceAware will start to work automatically. If FaceAware is
 *  activated successfully,  the aircraft will takeoff from the palm.
 */
typedef NS_ENUM(NSUInteger, DJIVisionFaceAwareState) {

	/**
	 *  The aircraft is not executing FaceAware.
	 */
	DJIVisionFaceAwareStateIdle,

	/**
	 *  The aircraft is in the process of detecting a human face in front of the camera.
	 */
	DJIVisionFaceAwareStateActivating,

	/**
	 *  FaceAware has been activated. The aircraft will beep twice and the motors will
	 *  start spinning.
	 */
	DJIVisionFaceAwareStateActivated,

	/**
	 *  FaceAware has failed to activate because no face was detected.
	 */
	DJIVisionFaceAwareStateFailedNoFaceDetected,

	/**
	 *  Unknown.
	 */
	DJIVisionFaceAwareStateUnknown = 0xFF,
};


/**
 *  The vision system can see in front of the aircraft with a 60 degree horizontal
 *  field of view (FOV) and 55 degree  vertical FOV. The horizontal FOV is split
 *  into four equal sectors, and this class gives the distance and warning  level
 *  for one sector.
 */
@interface DJIObstacleDetectionSector : NSObject


/**
 *  The detected obstacle distance to the aircraft in meters.
 */
@property(nonatomic, readonly) double obstacleDistanceInMeters;


/**
 *  The warning level based on distance.
 */
@property(nonatomic, readonly) DJIObstacleDetectionSectorWarning warningLevel;

@end


/**
 *  This class gives state information about the product's vision sensors used for
 *  obstacle detection. The two types of sensors used are dual camera sensors
 *  operating in the visible spectrum (dual-camera sensor) and infrared time of
 *  flight (TOF) sensors. Note, Inspire 2's upwards-facing infrared TOF sensor is
 *  not returned in this state. It is accessed through `DJIVisionControlState`.
 */
@interface DJIVisionDetectionState : NSObject


/**
 *  The vision sensor's position on the aircraft. For Phantom 4 Pro, there are 4
 *  vision sensors on the aircraft.  The sensors on the nose and tail are dual-
 *  camera sensors. The sensors on the left and right are infrared  time-of-flight
 *  (TOF) sensors.
 */
@property(nonatomic, readonly) DJIVisionSensorPosition position;


/**
 *  `YES` if the vision sensor is working.
 */
@property(nonatomic, readonly) BOOL isSensorBeingUsed;


/**
 *  Distance warning level between the obstacle and the aircraft. This is a
 *  combination of warning levels from each sector.
 */
@property(nonatomic, readonly) DJIVisionSystemWarning systemWarning;


/**
 *  The distance to the closest detected obstacle, in meters. It is only used when
 *  the sensor is an infrared TOF  sensor. The valid range is [0.3, 5.0]. Phantom 4
 *  Pro has two infrared sensors on its left and right. Both sensors have a
 *  70-degree horizontal field of view (FOV) and 20-degree vertical FOV. The value
 *  is always 0.0 if the sensor is a dual-camera sensor or the sensor is not working
 *  properly.
 */
@property(nonatomic, readonly) double obstacleDistanceInMeters;


/**
 *  The vision system can see in front of the aircraft with a 70 degree horizontal
 *  field of view (FOV) and 55-degree  vertical FOV for the Phantom 4. The
 *  horizontal FOV is split into four equal sectors and this array contains the
 *  distance and warning information for each sector. For Phantom 4, the horizontal
 *  FOV is separated into 4 sectors.
 */
@property(nullable, nonatomic, readonly) NSArray<DJIObstacleDetectionSector *> *detectionSectors;

@end


/**
 *  Landing protection status returned by the downward vision sensor.
 */
typedef NS_ENUM (NSInteger, DJIVisionLandingProtectionState){
 

    /**
     *  The aircraft is not executing auto-landing or the downward vision sensor has not
     *  started to analyze the ground yet.
     */
    DJIVisionLandingProtectionStateNone,
 

    /**
     *  The downward vision sensor is analyzing the ground at the landing zone.
     */
    DJIVisionLandingProtectionStateAnalyzing,
 

    /**
     *  The downward vision sensor's analysis failed. Either the auto-landing can be
     *  attempted again, or the user needs  to land the aircraft manually.
     */
    DJIVisionLandingProtectionStateAnalysisFailed,
 

    /**
     *  The ground is flat and the aircraft is safe to land automatically.
     */
    DJIVisionLandingProtectionStateSafeToLand,
 

    /**
     *  Landing area is not flat enough to be considered safe for landing. The aircraft
     *  should be moved to an area that  is more flat and an auto-land should be
     *  attempted again or the user should land the aircraft manually.
     */
    DJIVisionLandingProtectionStateNotSafeToLand,
 

    /**
     *  Unknown.
     */
    DJIVisionLandingProtectionStateUnknown = 0xFF
};


/**
 *  This class gives the aircraft's state, which is controlled by the intelligent
 *  flight assistant.
 */
@interface DJIVisionControlState : NSObject


/**
 *  `YES` if the aircraft is braking automatically to avoid collision.
 */
@property (nonatomic, readonly) BOOL isBraking;


/**
 *  YES if the aircraft will not ascend further because of an obstacle detected
 *  within 1m above it.
 */
@property (nonatomic, readonly) BOOL isAscentLimitedByObstacle;


/**
 *  `YES` if the aircraft is avoiding collision from an obstacle moving towards the
 *  aircraft.
 */
@property (nonatomic, readonly) BOOL isAvoidingActiveObstacleCollision;


/**
 *  YES if the aircraft is landing precisely.
 */
@property (nonatomic, readonly) BOOL isPerformingPrecisionLanding;


/**
 *  The aircraft's landing protection state. This status is valid when landing
 *  protection is enabled.
 */
@property (nonatomic, readonly) DJIVisionLandingProtectionState landingProtectionState;


/**
 *  `YES` if Advanced Pilot Assistance System (APAS) is active. When it is active,
 *  the aircraft will change  flight path automatically to avoid obstacles.
 */
@property (nonatomic, readonly) BOOL isAdvancedPilotAssistanceSystemActive;

@end


/**
 *  The system status of SmartCapture.
 */
typedef NS_ENUM(NSInteger, DJISmartCaptureSystemStatus) {

    /**
     *  SmartCapture is initializing.
     */
    DJISmartCaptureSystemStatusInitializing,

    /**
     *  The aircraft is not flying and detecting a human face in front of the camera.
     */
    DJISmartCaptureSystemStatusNotFlyingAndFaceAwareActivating,

    /**
     *  The aircraft is not flying and FaceAware has been activated. The aircraft will
     *  push the dimension of the target through `targetRect`  of
     *  `DJISmartCaptureState`.
     */
    DJISmartCaptureSystemStatusNotFlyingAndFaceAwareActivated,

    /**
     *  GestureLaunch is recognized and the aircraft is taking off.
     */
    DJISmartCaptureSystemStatusGestureLaunch,

    /**
     *  The aircraft is flying and detecting human faces in front of the camera.
     */
    DJISmartCaptureSystemStatusFlyingAndFaceAwareActivating,

    /**
     *  The aircraft is flying and detected one or more than one human faces in front of
     *  the camera.  One of the detected human can raise a hand to confirm the control.
     *  Then the SmartCapture  state will change to
     *  `DJISmartCaptureSystemStatusFollowing`.
     */
    DJISmartCaptureSystemStatusFlyingAndFaceAwareActivated,

    /**
     *  The aircraft is following the target but not SmartCapture action is recognized.
     */
    DJISmartCaptureSystemStatusFollowing,

    /**
     *  The aircraft is executing PalmControl (controlling the position or the
     *  distance).  See `action` of `DJISmartCaptureState` for more detail.
     */
    DJISmartCaptureSystemStatusPalmControl,

    /**
     *  The aircraft is executing camera related action (e.g. shoot photos).  See
     *  `action` of `DJISmartCaptureState` for more detail.
     */
    DJISmartCaptureSystemStatusCameraCaptureAction,

    /**
     *  GestureLand is recognized and the aircraft is landing.
     */
    DJISmartCaptureSystemStatusGestureLand,

    /**
     *  Unknown.
     */
    DJISmartCaptureSystemStatusUnknown = 0xFF,
};


/**
 *  Different actions supported by SmartCapture.
 */
typedef NS_ENUM(NSInteger, DJISmartCaptureAction) {

    /**
     *  No action is being executed.
     */
    DJISmartCaptureActionNone,

    /**
     *  The user is adjusting the aircraft's position. Move the palm up  or down slowly
     *  to control the aircraft's altitude. Move the arm  left or right to control the
     *  aircraft's orientation.
     */
    DJISmartCaptureActionAdjustingPosition,

    /**
     *  The user is adjusting distance between the aircraft and the user.  Move two
     *  hands apart and the aircraft will fly away from the user.  The maximum distance
     *  is 19.7ft (6m). Move two hands together and  the aircraft will fly towards the
     *  user. The minimum distance is 6.6ft (2m).
     */
    DJISmartCaptureActionAdjustingDistance,

    /**
     *  The control of the aircraft is being switched from one person to the other.  The
     *  current user drops hand towards the floor. The Front LEDs will turn solid green.
     *  The person who would like to control the aircraft raise palm in front of the
     *  aircraft.  When the Front LEDs blinks green slowly, it indicates the control is
     *  switched successfully.
     */
    DJISmartCaptureActionSwitchingControl,

    /**
     *  The camera is shooting photos. Make a V gesture with one hand to trigger the
     *  action. Once the  gesture is recognized, two-second countdown will begin
     *  (`photoCountdown`  of `DJISmartCaptureState`).
     */
    DJISmartCaptureShootingPhoto,

    /**
     *  The camera is recording video. To start this, make a frame gesture with fingers
     *  from both hands.  Once the gesture is recognized, the aircraft's front LEDs will
     *  turn off and the camera will start  recording. After five seconds, use the same
     *  gesture to stop the recording.
     */
    DJISmartCaptureActionRecordingVideo,

    /**
     *  Unknown.
     */
    DJISmartCaptureActionUnknown = 0xFF,
};


/**
 *  Different following modes of SmartCapture.
 */
typedef NS_ENUM(NSInteger, DJISmartCaptureFollowingMode) {

    /**
     *  Aircraft follows the target at constant distance.
     */
    DJISmartCaptureFollowingModeTrace,

    /**
     *  Aircraft follows the target at constant angle and distance from the side.
     */
    DJISmartCaptureFollowingModeProfile,

    /**
     *  Unknown.
     */
    DJISmartCaptureFollowingModeUnknown = 0xFF,
};


/**
 *  The object includes all information related to SmartCapture.
 */
@interface DJISmartCaptureState : NSObject

/**
 *  The system status of SmartCapture.
 */
@property (nonatomic, readonly) DJISmartCaptureSystemStatus systemStatus;

/**
 *  The executing SmartCapture action.
 */
@property (nonatomic, readonly) DJISmartCaptureAction action;

/**
 *  The following mode of SmartCapture.
 */
@property (nonatomic, readonly) DJISmartCaptureFollowingMode followingMode;

/**
 *  The countdown for shooting photo.
 */
@property (nonatomic, readonly) NSTimeInterval photoCountdown;

/**
 *  The dimension of the detected target. It is `CGRectNull` when the target is
 *  invalid.
 */
@property (nonatomic, readonly) CGRect targetRect;

@end


/**
 *  Modes for the auxiliary light at the bottom of the aircraft.
 */
typedef NS_ENUM(NSInteger, DJIBottomAuxiliaryLightMode) {

    /**
     *  The auto mode. In this mode, the auxiliary light will be turned on automatically
     *  when the downward vision system is active but the environment is too dark.
     */
    DJIBottomAuxiliaryLightModeAuto,

    /**
     *  The auxiliary light is on.
     */
    DJIBottomAuxiliaryLightModeOn,

    /**
     *  The auxiliary light is off.
     */
    DJIBottomAuxiliaryLightModeOff,
    

    /**
     *  Beacon mode. In this mode, the auxiliary light will have different  behaviors in
     *  different conditions:
     *  - When the aircraft just takes off,  the auxiliary light will have the same
     *  behavior  as ''DJIBottomAuxiliaryLightMode_Auto''.
     *  - When the aircraft ascends  above 5.5 meters, the auxiliary light starts to
     *  blink in 1Hz.
     *  - When  the aircraft descends below 4.5 meters, the auxiliary light will have
     *  the  same behavior as ''DJIBottomAuxiliaryLightMode_Auto''. This mode is only
     *  supported by Mavic 2 Enterprise.
     */
    DJIBottomAuxiliaryLightModeBeacon,


    /**
     *  Unknown.
     */
    DJIBottomAuxiliaryLightModeUnknown = 0xFF,
};

NS_ASSUME_NONNULL_END
