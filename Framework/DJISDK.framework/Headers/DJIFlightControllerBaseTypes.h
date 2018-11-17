//
//  DJIFlightControllerBaseTypes.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#ifndef DJIFlightControllerBaseTypes_h
#define DJIFlightControllerBaseTypes_h

#import "DJISDKFoundation.h"

/*********************************************************************************/
#pragma mark DJIAttitude
/*********************************************************************************/


/**
 *  Aircraft attitude. The attitude of the aircraft is made up of the pitch, roll,
 *  and yaw.
 */
typedef struct
{

    /**
     *  Aircraft's pitch attitude value.
     */
    double pitch;


    /**
     *  Aircraft's roll attitude value.
     */
    double roll;


    /**
     *  Aircraft's yaw attitude value.
     */
    double yaw;
} DJIAttitude;

/*********************************************************************************/
#pragma mark DJIFlightMode
/*********************************************************************************/


/**
 *  Flight controller flight modes. For more information, see
 *  http://wiki.dji.com/en/index.php/Phantom_3_Professional-Aircraft.
 */
typedef NS_ENUM (NSUInteger, DJIFlightMode){
 

    /**
     *  Manual mode.
     */
    DJIFlightModeManual = 0,


    /**
     *  Attitude mode.
     */
    DJIFlightModeAtti = 1,


    /**
     *  Attitude course lock mode.
     */
    DJIFlightModeAttiCourseLock = 2,
    

    /**
     *  GPS Attitude mode.
     */
    DJIFlightModeGPSAtti = 6,


    /**
     *  GPS course lock mode.
     */
    DJIFlightModeGPSCourseLock = 7,


    /**
     *  GPS Home mode.
     */
    DJIFlightModeGPSHomeLock = 8,


    /**
     *  GPS hot point mode.
     */
    DJIFlightModeGPSHotPoint = 9,


    /**
     *  Assisted takeoff mode.
     */
    DJIFlightModeAssistedTakeoff = 10,


    /**
     *  Auto takeoff mode.
     */
    DJIFlightModeAutoTakeoff = 11,


    /**
     *  Auto landing mode.
     */
    DJIFlightModeAutoLanding = 12,


    /**
     *  GPS waypoint mode.
     */
    DJIFlightModeGPSWaypoint = 14,


    /**
     *  Go home mode.
     */
    DJIFlightModeGoHome = 15,
 

    /**
     *  Joystick mode.
     */
    DJIFlightModeJoystick = 17,
 

    /**
     *  Attitude limited mode.
     */
    DJIFlightModeGPSAttiWristband = 18,
 

    /**
     *  Draw mode.
     */
    DJIFlightModeDraw = 24,
 

    /**
     *  GPS follow me mode.
     */
    DJIFlightModeGPSFollowMe = 25,
 

    /**
     *  ActiveTrack mode.
     */
    DJIFlightModeActiveTrack = 26,
 

    /**
     *  TapFly mode.
     */
    DJIFlightModeTapFly = 27,
 

    /**
     *  Sport mode.
     */
    DJIFlightModeGPSSport = 31,
 

    /**
     *  GPS Novice mode.
     */
    DJIFlightModeGPSNovice = 32,
 

    /**
     *  Confirm landing mode.
     */
    DJIFlightModeConfirmLanding = 33,
 

    /**
     *  The aircraft should move following the terrain.
     */
    DJIFlightModeTerrainFollow = 35,
 

    /**
     *  Tripod mode.
     */
    DJIFlightModeTripod = 38,
 

    /**
     *  Active track mode, corresponds to Spotlight active track mode.
     */
    DJIFlightModeActiveTrackSpotlight = 39,
 

    /**
     *  The motors are just started.
     */
    DJIFlightModeMotorsJustStarted = 41,
 

    /**
     *  The main controller flight mode is unknown.
     */
    DJIFlightModeUnknown = 0xFF,

};

/*********************************************************************************/
#pragma mark DJIGoHomeExecutionState
/*********************************************************************************/


/**
 *  An enum used to identify the different stages of the go-home command.
 */
typedef NS_ENUM (NSUInteger, DJIGoHomeExecutionState){
 

    /**
     *  The aircraft is not executing a Go-Home command.
     */
    DJIGoHomeExecutionStateNotExecuting,
 

    /**
     *  The aircraft is turning the heading direction to the home point.
     */
    DJIGoHomeExecutionStateTurnDirectionToHomePoint,
 

    /**
     *  The aircraft is going up to the height for go-home command.
     */
    DJIGoHomeExecutionStateGoUpToHeight,
 

    /**
     *  The aircraft is flying horizontally to home point.
     */
    DJIGoHomeExecutionStateAutoFlyToHomePoint,


    /**
     *  The aircraft is going down after arriving at the home point.
     */
    DJIGoHomeExecutionStateGoDownToGround,


    /**
     *  The aircraft is braking to avoid collision.
     */
    DJIGoHomeExecutionStateBraking,


    /**
     *  The aircraft is bypassing over the obstacle.
     */
    DJIGoHomeExecutionStateBypassing,


    /**
     *  The go-home command is completed.
     */
    DJIGoHomeExecutionStateCompleted,


    /**
     *  The go-home status is unknown.
     */
    DJIGoHomeExecutionStateUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJIGPSSignalLevel
/*********************************************************************************/


/**
 *  GPS signal levels, which are used to measure the signal quality.
 */
typedef NS_ENUM (uint8_t, DJIGPSSignalLevel){
 

    /**
     *  The GPS has almost no signal, which is very bad.
     */
    DJIGPSSignalLevel0,


    /**
     *  The GPS signal is very weak.
     */
    DJIGPSSignalLevel1,


    /**
     *  The GPS signal is weak. At this level, the aircraft's go home functionality will
     *  still work.
     */
    DJIGPSSignalLevel2,


    /**
     *  The GPS signal is good. At this level, the aircraft can hover in the air.
     */
    DJIGPSSignalLevel3,


    /**
     *  The GPS signal is very good. At this level, the aircraft can record the home
     *  point.
     */
    DJIGPSSignalLevel4,


    /**
     *  The GPS signal is very strong.
     */
    DJIGPSSignalLevel5,


    /**
     *  There is no GPS signal.
     */
    DJIGPSSignalLevelNone,
};

/*********************************************************************************/
#pragma mark DJIVirtualStickFlightControlData
/*********************************************************************************/


/**
 *  Contains all the virtual stick control data needed to move the aircraft in all
 *  directions.
 */
typedef struct
{

    /**
     *  Gets aircraft's velocity (m/s) along the y-axis or angle value (in degrees) for
     *  pitch. Use `DJIVirtualStickRollPitchControlMode` to set the velocity or angle
     *  mode. Note that the argument has different meanings in different coordinate
     *  systems. See the <i>Flight Controller User Guide</i> for more information.
     */
    float pitch;
    

    /**
     *  Gets aircraft's velocity (m/s) along the x-axis or angle value (in degrees) for
     *  roll. Use `DJIVirtualStickRollPitchControlMode` to set the velocity or angle
     *  mode. Note that the argument has different meanings in different coordinate
     *  systems. See the <i>Flight Controller User Guide</i> for more information.
     */
    float roll;
    

    /**
     *  Angular velocity (degrees/s) or angle (degrees) value for yaw. Use
     *  `DJIVirtualStickYawControlMode` to set angular velocity or angle mode.
     */
    float yaw;
    

    /**
     *  Gets aircraft's velocity (m/s) or altitude (m) value for verticalControl. Use
     *  `DJIVirtualStickYawControlMode` to set velocity or altitude mode.
     */
    float verticalThrottle;
} DJIVirtualStickFlightControlData;

/*********************************************************************************/
#pragma mark DJIVirtualStickVerticalControlMode
/*********************************************************************************/


/**
 *  Defines how vertical control values are interpreted by the aircraft.
 */
typedef NS_ENUM (uint8_t, DJIVirtualStickVerticalControlMode){
 

    /**
     *  Sets the virtual stick vertical control values to be a vertical velocity.
     *  Positive and negative vertical velocity is for the aircraft ascending and
     *  descending respectively. Maximum vertical velocity is defined as 4 m/s. Minimum
     *  vertical velocity is defined as -4 m/s.
     */
    DJIVirtualStickVerticalControlModeVelocity,
 

    /**
     *  Sets the virtual stick vertical control values to be an altitude. Maximum
     *  position is defined as 500 m. Minimum position is defined as 0 m.
     */
    DJIVirtualStickVerticalControlModePosition,
};

/*********************************************************************************/
#pragma mark DJIVirtualStickRollPitchControlMode
/*********************************************************************************/


/**
 *  Defines how manual roll and pitch values are interpreted by the aircraft.
 */
typedef NS_ENUM (uint8_t, DJIVirtualStickRollPitchControlMode){
 

    /**
     *  Sets the roll and pitch values to be an angle relative to a level aircraft. In
     *  the body coordinate system, positive and negative pitch angle is for the
     *  aircraft rotating about the y-axis in the positive direction or negative
     *  direction, respectively. Positive and negative roll angle is the positive
     *  direction or negative direction rotation angle about the x-axis, respectively.
     *  However in the ground coordinate system, positive and negative pitch angle is
     *  the angle value for the aircraft moving south and north, respectively. Positive
     *  and negative roll angle is the angle when the aircraft is moving east and west,
     *  respectively. Maximum angle is defined as 30 degrees. Minimum angle is defined
     *  as -30 degrees.
     */
    DJIVirtualStickRollPitchControlModeAngle,
 

    /**
     *  Sets the roll and pitch values to be a velocity. In the body coordinate system,
     *  positive and negative pitch velocity is for the aircraft moving towards the
     *  positive direction or negative direction along the pitch axis and y-axis,
     *  respectively. Positive and negative roll velocity is when the aircraft is moving
     *  towards the positive direction or negative direction along the roll axis and
     *  x-axis, respectively. However, in the ground coordinate system, positive and
     *  negative pitch velocity is for the aircraft moving east and west, respectively.
     *  Positive and negative roll velocity is when the aircraft is moving north and
     *  south, respectively. Maximum velocity is defined as 15 meters/s. Minimum
     *  velocity is defined as -15 meters/s.
     */
    DJIVirtualStickRollPitchControlModeVelocity,
};

/*********************************************************************************/
#pragma mark DJIVirtualStickYawControlMode
/*********************************************************************************/


/**
 *  Defines how manual yaw values are interpreted by the aircraft.
 */
typedef NS_ENUM (uint8_t, DJIVirtualStickYawControlMode){
 

    /**
     *  Sets the yaw values to be an angle relative to the front of the aircraft.
     *  Positive and negative yaw angle is for the aircraft rotating clockwise and
     *  counterclockwise, respectively. Maximum yaw angle is defined as 180 degrees.
     *  Minimum yaw angle is defined as -180 degrees.
     */
    DJIVirtualStickYawControlModeAngle,
 

    /**
     *  Sets the yaw values to be an angular velocity. Positive and negative angular
     *  velocity is for the aircraft rotating clockwise and counterclockwise,
     *  respectively. Maximum yaw angular velocity is defined as 100 degrees/s. Minimum
     *  yaw angular velocity is defined as -100 degrees/s.
     */
    DJIVirtualStickYawControlModeAngularVelocity,
};

/*********************************************************************************/
#pragma mark DJIVirtualStickFlightCoordinateSystem
/*********************************************************************************/


/**
 *  Flight control coordinate system.
 */
typedef NS_ENUM (uint8_t, DJIVirtualStickFlightCoordinateSystem){
 

    /**
     *  Ground coordinate system.
     */
    DJIVirtualStickFlightCoordinateSystemGround,
 

    /**
     *  Body coordinate system.
     */
    DJIVirtualStickFlightCoordinateSystemBody,
};

/*********************************************************************************/
#pragma mark DJIFlightControllerControlMode
/*********************************************************************************/


/**
 *  Control mode of the flight controller. It determines how the pilot can control
 *  the aircraft. By default, it is in smart control mode.
 */
typedef NS_ENUM(uint8_t, DJIFlightControllerControlMode) {
 

    /**
     *  Smart control mode. The aircraft can stabilize its altitude and attitude in
     *  smart mode.
     */
    DJIFlightControllerControlModeSmart,
 

    /**
     *  Manual control mode. The aircraft will not stabilize its altitude and attitude
     *  in manual mode. This mode is for advanced pilots only, and should only be used
     *  when the pilot understands the risk of operating in this mode. Any damage to the
     *  product when operating in this mode will not be covered under warranty.
     */
    DJIFlightControllerControlModeManual,
 

    /**
     *  Unknown control mode.
     */
    DJIFlightControllerControlModeUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJIFlightControllerRemoteControllerFlightMode
/*********************************************************************************/


/**
 *  Flight modes that map to the flight mode switch on the remote controller.
 */
typedef NS_ENUM(uint8_t, DJIFlightControllerRemoteControllerFlightMode) {


    /**
     *  Positioning mode. GNSS and Vision Positioning Systems are used for positioning
     *  if they are available. For products without F mode, intelligent functions such
     *  as missions and intelligent orientation control can be performed in P-mode.
     */
    DJIFlightControllerRemoteControllerFlightModeP,


    /**
     *  Attitude mode. The GNSS and Vision Positioning Systems are not used for
     *  positioning. The aircraft only uses the barometer to maintain altitude. If
     *  receiving a GNSS signal, the aircraft can automatically return home if the
     *  Remote Controller signal is lost and if the Home Point has been recorded
     *  successfully.
     */
    DJIFlightControllerRemoteControllerFlightModeA,
    

    /**
     *  Sport mode. The maximum flight speed and responsiveness of the aircraft is
     *  increased in this mode.
     */
    DJIFlightControllerRemoteControllerFlightModeS,
    

    /**
     *  Gentle mode. The sensitivity and speed of aircraft will be substantially
     *  decreased in gentle mode.
     */
    DJIFlightControllerRemoteControllerFlightModeG,


    /**
     *  Manual mode. The aircraft will not stabilize its altitude nor attitude in manual
     *  mode. This mode is for advanced pilots only, and should only be used when the
     *  pilot understands the risk of operating in this mode. Any damage to the product
     *  when operating in this mode will not be covered under warranty. It is supported
     *  by stand-alone A3 and N3 and can be enabled in Assistant 2.
     */
    DJIFlightControllerRemoteControllerFlightModeM,


    /**
     *  Function mode. Performs the same as Positioning mode with intelligent functions
     *  such as missions and intelligent orientation control enabled.
     */
    DJIFlightControllerRemoteControllerFlightModeF,
    

    /**
     *  Tripod Mode. This mode drops the aircraft's maximum speed and significantly
     *  reduces the control stick sensitivity of the remote controller to give the  user
     *  the precision needed for accurate framing. It is only supported by Mavic 2.
     */
    DJIFlightControllerRemoteControllerFlightModeT,


    /**
     *  Unknown mode.
     */
    DJIFlightControllerRemoteControllerFlightModeUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark DJIFlightControllerGoHomeAssessment
/*********************************************************************************/

/**
 *  State of Smart Return-To-Home (RTH). It is only used when Smart RTH is enabled.
 */
typedef NS_ENUM(uint8_t, DJIFlightControllerSmartRTHState) {

    /**
     *  Smart RTH is not triggered yet in the current flight. The Smart RTH state will
     *  be reset to this value when the aircraft lands.
     */
    DJIFlightControllerSmartRTHStateIdle = 0,

    /**
     *  Smart RTH is triggered and the aircraft is counting down. If no response is
     *  received within 10 seconds or the user confirms the request, the aircraft will
     *  start to go home and the state will change to
     *  `DJIFlightControllerSmartRTHStateExecuted`. If user cancels the request, the
     *  state will change to `DJIFlightControllerSmartRTHStateCancelled`.
     */
    DJIFlightControllerSmartRTHStateCountingDown,

    /**
     *  Smart RTH is already executed in the current flight. The state will not be reset
     *  until the aircraft lands.
     */
    DJIFlightControllerSmartRTHStateExecuted,

    /**
     *  Smart RTH request is cancelled by the user. The state will not be reset until
     *  the aircraft lands.
     */
    DJIFlightControllerSmartRTHStateCancelled,

    /**
     *  Unknown.
     */
    DJIFlightControllerSmartRTHStateUnknown = 0xFF,
};


/**
 *  The Flight Controller Smart Go Home Status
 */
typedef struct
{

    /**
     *  The estimated remaining time, in seconds, it will take the aircraft to go home
     *  with a 10% battery buffer remaining. This time includes landing the aircraft. If
     *  the aircraft is using the simulator, this value will be 0.
     */
    NSUInteger remainingFlightTime;


    /**
     *  The estimated time, in seconds, needed for the aircraft to go home from its
     *  current location.
     */
    NSUInteger timeNeededToGoHome;


    /**
     *  The estimated time, in seconds, needed for the aircraft to move downward from
     *  its current position and land.
     */
    NSUInteger timeNeededToLandFromCurrentHeight;


    /**
     *  The estimated battery percentage, in the range of [0,100], needed for the
     *  aircraft to go home and have 10% battery remaining. This includes landing of the
     *  aircraft.
     */
    NSUInteger batteryPercentageNeededToGoHome;


    /**
     *  The battery percentage, in the range of [0,100], needed for the aircraft to move
     *  downward from its current position and land.
     */
    NSUInteger batteryPercentageNeededToLandFromCurrentHeight;


    /**
     *  The maximum radius, in meters, an aircraft can fly from its home location and
     *  still make it all the way back home, based on altitude, distance, battery, etc.
     *  If the  aircraft goes out farther than the max radius, it will fly as far back
     *  home as it can and land. If the aircraft is using the simulator, this value will
     *  be 0.
     */
    float maxRadiusAircraftCanFlyAndGoHome;


    /**
     *  The Smart Return-To-Home (RTH) state for the current flight.
     */
    DJIFlightControllerSmartRTHState smartRTHState;


    /**
     *  The countdown (in seconds) for the Smart Return-To-Home (RTH). Once the
     *  countdown reaches 0, the aircraft will  execute an automatic go-home procedure.
     *  It is only valid when  `smartRTHState`  is
     *  `DJIFlightControllerSmartRTHStateCountingDown`.
     */
    NSInteger smartRTHCountdown;
} DJIFlightControllerGoHomeAssessment;

/*********************************************************************************/
#pragma mark DJIAircraftPowerLevel
/*********************************************************************************/


/**
 *  Remaining battery life state. This state describes the recommended action based
 *  on remaining battery life.
 */
typedef NS_ENUM (uint8_t, DJIBatteryThresholdBehavior){


    /**
     *  Remaining battery life sufficient for normal flying.
     */
    DJIBatteryThresholdBehaviorFlyNormally,


    /**
     *  Remaining battery life sufficient to go home.
     */
    DJIBatteryThresholdBehaviorGoHome,


    /**
     *  Remaining battery life sufficient to land immediately.
     */
    DJIBatteryThresholdBehaviorLandImmediately,
};

/*********************************************************************************/
#pragma mark - DJIFlightOrientationMode
/*********************************************************************************/


/**
 *  Tells the aircraft how to interpret flight commands for forward, backward, left
 *  and right. See the <i>Flight Controller User Guide</i> for more information.
 */
typedef NS_ENUM (uint8_t, DJIFlightOrientationMode){


    /**
     *  The aircraft should move relative to a locked course heading.
     */
    DJIFlightOrientationModeCourseLock,


    /**
     *  The aircraft should move relative radially to the Home Point.
     */
    DJIFlightOrientationModeHomeLock,


    /**
     *  The aircraft should move relative to the front of the aircraft.
     */
    DJIFlightOrientationModeAircraftHeading,
};

/*********************************************************************************/
#pragma mark - DJIFlightWindWarning
/*********************************************************************************/

/**
 *  Warning caused by the strong wind.
 */
typedef NS_ENUM(NSUInteger, DJIFlightWindWarning) {

    /**
     *  No wind warning.
     */
    DJIFlightWindWarningLevel0,

    /**
     *  The wind speed is high. Fly with caution and ensure the aircraft remains within
     *  the line of sight.
     */
    DJIFlightWindWarningLevel1,

    /**
     *  Strong Wind. Fly with caution and ensure the aircraft remains within line of
     *  sight. It is more serious than `DJIFlightWindWarningLevel1`.
     */
    DJIFlightWindWarningLevel2,

    /**
     *  Unknown.
     */
    DJIFlightWindWarningUnknown = 0xFF,
};


/**
 *  Settings for the aircraft's LEDs.
 */
@interface DJIFlightControllerLEDsSettings : NSObject<NSCopying, NSMutableCopying>


/**
 *  `YES` if the LEDs on the front arms are turned on.
 */
@property (nonatomic, readonly) BOOL frontLEDsOn;


/**
 *  `YES` if the status indicator is on. It is supported by Inspire 2, Matrice 200
 *  series and Mavic 2 series. The other products will ignore this property. For
 *  Mavic 2  series, there are two status indicators and they are on the rear arms.
 */
@property (nonatomic, readonly) BOOL statusIndicatorOn;


/**
 *  `YES` if the LEDs on the rear arms are turned on. It is  supported by Inspire 2,
 *  Matrice 200 series and Mavic 2 series.  The other products will ignore this
 *  property.
 */
@property (nonatomic, readonly) BOOL rearLEDsOn;

@end


/**
 *  Mutable sub-class of `DJIFlightControllerLEDsSettings`.  Use this for setter.
 */
@interface DJIMutableFlightControllerLEDsSettings : DJIFlightControllerLEDsSettings


/**
 *  `YES` to turn on the LEDs on the front arms.
 */
@property (nonatomic, readwrite) BOOL frontLEDsOn;

/**
 *  `YES` to turn on the LEDs on the rear arms. It is supported by Inspire 2,
 *  Matrice 200 series and Mavic 2 series. The other products will always return
 *  `NO`.
 */
@property (nonatomic, readwrite) BOOL rearLEDsOn;

/**
 *  `YES` to turn on thestatus indicator. It is supported by Inspire 2 and Matrice
 *  200 series.  The other products will always return `NO`.
 */
@property (nonatomic, readwrite) BOOL statusIndicatorOn;

@end


/**
 *  DJI Simulator Wind Speed.
 */
@interface DJISimulatorWindSpeed : NSObject


/**
 *  DJI Simulator Wind Speed X value.
 */
@property (nonatomic, assign) NSUInteger windSpeedX;


/**
 *  DJI Simulator Wind Speed Y value.
 */
@property (nonatomic, assign) NSUInteger windSpeedY;


/**
 *  DJI Simulator Wind Speed Z value.
 */
@property (nonatomic, assign) NSUInteger windSpeedZ;

@end

#endif /* DJIFlightControllerBaseTypes_h */
