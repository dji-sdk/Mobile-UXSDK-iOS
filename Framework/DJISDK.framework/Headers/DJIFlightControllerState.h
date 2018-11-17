//
//  DJIFlightControllerState.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <DJISDK/DJIFlightControllerBaseTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*********************************************************************************/
#pragma mark - DJIFlightControllerState
/*********************************************************************************/


/**
 *  This class represents the current state of the flight controller.
 */
@interface DJIFlightControllerState : NSObject


/**
 *  GPS satellite count.
 */
@property(nonatomic, readonly) NSUInteger satelliteCount;


/**
 *  Home location of the aircraft as a coordinate.
 */
@property(nonatomic, readonly, nullable) CLLocation *homeLocation;


/**
 *  The current location of the aircraft as a coordinate. `nil` if the location is
 *  invalid.
 */
@property(nonatomic, readonly, nullable) CLLocation *aircraftLocation;


/**
 *  Current speed of the aircraft in the x direction, in meters per second, using
 *  the N-E-D (North-East-Down)  coordinate system.
 */
@property(nonatomic, readonly) float velocityX;


/**
 *  Current speed of the aircraft in the y direction, in meters per second, using
 *  the N-E-D (North-East-Down)  coordinate system.
 */
@property(nonatomic, readonly) float velocityY;


/**
 *  Current speed of the aircraft in the z direction, in meters per second, using
 *  the N-E-D (North-East-Down)  coordinate system.
 */
@property(nonatomic, readonly) float velocityZ;


/**
 *  Relative altitude of the aircraft relative to take off location, measured by the
 *  barometer, in meters.
 */
@property(nonatomic, readonly) double altitude;


/**
 *  Relative altitude of the aircraft home location relative to sea level, in
 *  meters.
 */
@property(nonatomic, readonly) float takeoffLocationAltitude;


/**
 *  The attitude of the aircraft, where the pitch, roll, and yaw values will be  in
 *  the range of [-180, 180] degrees. If its pitch, roll, and yaw values are 0, the
 *  aircraft will  be hovering level with a True North heading.
 */
@property(nonatomic, readonly) DJIAttitude attitude;


/**
 *  Recommended action based on remaining battery life.
 */
@property(nonatomic, readonly) DJIBatteryThresholdBehavior batteryThresholdBehavior;


/**
 *  `YES` if aircraft is flying.
 */
@property(nonatomic, readonly) BOOL isFlying;


/**
 *  The accumulated flight time, in seconds, since the aircraft was powered on.
 */
@property(nonatomic, readonly) NSUInteger flightTimeInSeconds;


/**
 *  Flight controller flight mode. For more info, see
 *  http://wiki.dji.com/en/index.php/Phantom_3_Professional-Aircraft
 */
@property(nonatomic, readonly) DJIFlightMode flightMode;


/**
 *  Aircraft's smart go home data. If smart go home is enabled, all the  smart go
 *  home data will be available  in `DJIFlightControllerGoHomeAssessment`.
 */
@property(nonatomic, readonly) DJIFlightControllerGoHomeAssessment goHomeAssessment;


/**
 *  The current status of go-home execution.
 */
@property(nonatomic, readonly) DJIGoHomeExecutionState goHomeExecutionState;


/**
 *  Gets the height when the aircraft is going home in meters.
 */
@property(nonatomic, readonly) NSUInteger goHomeHeight;


/**
 *  The aircraft's current orientation mode.
 */
@property(nonatomic, readonly) DJIFlightOrientationMode orientationMode;


/**
 *  Aircraft's current GPS signal quality.
 */
@property(nonatomic, readonly) DJIGPSSignalLevel GPSSignalLevel;


/**
 *  Determines whether multiple flight modes are open. This will reflect whether
 *  navigation mode (ground  station) is enabled.
 */
@property(nonatomic, readonly) BOOL isMultipleModeOpen;


/**
 *  `YES` if the signal is lost between remote controller and aircraft, and FailSafe
 *  is enabled.
 */
@property(nonatomic, readonly) BOOL isFailsafeEnabled;


/**
 *  `YES` if IMU is preheating.
 */
@property(nonatomic, readonly) BOOL isIMUPreheating;


/**
 *  `YES` if the ultrasonic sensor is being used. Variables that can impact the
 *  quality  of the ultrasound measurement, or whether it's being used, are height
 *  above ground and the type of ground  (if it reflects sound waves well). Usually,
 *  the ultrasonic sensor works when the aircraft is less than 8m  above ground.
 */
@property(nonatomic, readonly) BOOL isUltrasonicBeingUsed;


/**
 *  Height of aircraft measured by the ultrasonic sensor in meters. The data will
 *  only be available  if `isUltrasonicBeingUsed` returns `YES`. Height has a
 *  precision of 0.1m. This value has reference significance when the height  is
 *  below 5 meters.
 */
@property(nonatomic, readonly) double ultrasonicHeightInMeters;


/**
 *  `YES` if ultrasonic sensor has error.
 *  
 *  @return `YES` if ultrasonic sensor has error.
 */
@property(nonatomic, readonly) BOOL doesUltrasonicHaveError;


/**
 *  `YES` if a vision sensor is being used. Variables that can impact the quality of
 *  the  vision measurement, or whether it's being used, are height above ground and
 *  the type of ground (if it has  sufficiently rich texture). Usually, the vision
 *  sensor works when the aircraft is less than 3m above ground.
 */
@property(nonatomic, readonly) BOOL isVisionPositioningSensorBeingUsed;


/**
 *  `YES` if motors are on.
 */
@property(nonatomic, readonly) BOOL areMotorsOn;


/**
 *  Gets the flight mode as a string.
 */
@property(nonatomic, readonly) NSString *_Nonnull flightModeString;


/**
 *  `YES` if the home point has been set.
 */
@property(nonatomic, readonly) BOOL isHomeLocationSet;


/**
 *  `YES` if the clearance between the aircraft and the ground is less than 0.3m,
 *  and  confirmation from the user is needed to continue the landing. When the
 *  confirmation is needed, `confirmLandingWithCompletion` in `DJIFlightController`
 *  can be used to continue landing. It is
 *   supported by flight controller firmware 3.2.0.0 or above.
 */
@property(nonatomic, readonly) BOOL isLandingConfirmationNeeded;


/**
 *  `YES` if the aircraft has reached its flight height limit.
 */
@property(nonatomic, readonly) BOOL hasReachedMaxFlightHeight;


/**
 *  `YES` if the aircraft has reached its flight radius limit.
 */
@property(nonatomic, readonly) BOOL hasReachedMaxFlightRadius;


/**
 *  `YES` if the battery is lower than the low battery warning threshold.
 */
@property(nonatomic, readonly) BOOL isLowerThanBatteryWarningThreshold;


/**
 *  `YES` if the battery is lower than the serious low battery warning threshold.
 */
@property(nonatomic, readonly) BOOL isLowerThanSeriousBatteryWarningThreshold;


/**
 *  Warning related to high winds.
 */
@property(nonatomic, readonly) DJIFlightWindWarning windWarning;

@end

NS_ASSUME_NONNULL_END
