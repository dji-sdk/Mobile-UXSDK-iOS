//
//  DJIFlightController.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <DJISDK/DJIBaseComponent.h>
#import <DJISDK/DJIFlightControllerState.h>
#import <DJISDK/DJIIMUState.h>
#import <DJISDK/DJIFlightControllerBaseTypes.h>

@class DJIFlightController;
@class DJILandingGear;
@class DJICompass;
@class DJIRTK;
@class DJIFlightAssistant;
@class DJISimulator;
@class DJIAirSenseSystemInformation;
@class DJIOnboardSDKDevice;
@class DJIAccessLocker;

NS_ASSUME_NONNULL_BEGIN

/**
 *  No fly zone. Check flysafe.dji.com for all no fly
 *  zones that are pre-set by DJI. A user or developer
 *  is not allowed to set their own no fly zone.
 *
 *  The zone radius is a radius around the no fly zone
 *  center coordinate that determines how large the
 *  no fly zone is around the center coordinate.
 *
 *  Once the aircraft is 100 meters away from a no fly
 *  zone, the user should be continuously notified that
 *  the aircraft is approaching a no fly zone. If the
 *  aircraft enters a no fly zone, it will stop and hover
 *  at the border.
 */

/*********************************************************************************/
#pragma mark DJIFlightControl
/*********************************************************************************/


/**
 *  Defines aircraft failsafe action when signal between the remote controller and
 *  the aircraft is lost.
 */
typedef NS_ENUM (uint8_t, DJIConnectionFailSafeBehavior){


    /**
     *  Hover.
     */
    DJIConnectionFailSafeBehaviorHover,


    /**
     *  Landing.
     */
    DJIConnectionFailSafeBehaviorLanding,


    /**
     *  Return-to-Home.
     */
    DJIConnectionFailSafeBehaviorGoHome,


    /**
     *  Unknown.
     */
    DJIConnectionFailSafeBehaviorUnknown = 0xFF
};


/*********************************************************************************/
#pragma mark - DJIFlightControllerDelegate
/*********************************************************************************/


/**
 *  This protocol provides delegate methods to update the flight controller's
 *  current state.
 */
@protocol DJIFlightControllerDelegate <NSObject>

@optional


/**
 *  Called when the flight controller's current state data has been updated. This
 *  method is called 10 times per second.
 *  
 *  @param fc Instance of the flight controller for which the data will be updated.
 *  @param state Current state of the flight controller.
 */
- (void)flightController:(DJIFlightController *_Nonnull)fc didUpdateState:(DJIFlightControllerState *_Nonnull)state;


/**
 *  Called when the flight controller pushes an IMU state update. The callback
 *  method would not be called if the aircraft is flying.
 *  
 *  @param fc Instance of the flight controller for which the data will be updated.
 *  @param imuState DJIIMUState object.
 */
- (void)flightController:(DJIFlightController *_Nonnull)fc didUpdateIMUState:(DJIIMUState *_Nonnull)imuState;


/**
 *  Called when the flight controller pushes a DJI AirSense system update. Only
 *  supported by M200 series.
 *  
 *  @param fc Instance of the flight controller for which the data will be updated.
 *  @param information DJI AirSense system information.
 */
- (void)flightController:(DJIFlightController *_Nonnull)fc didUpdateAirSenseSystemInformation:(DJIAirSenseSystemInformation *_Nonnull)information;

@end

/*********************************************************************************/
#pragma mark - DJIFlightController
/*********************************************************************************/


/**
 *  This class contains components of the flight controller and provides methods to
 *  send different commands to the flight controller. This object is available from
 *  the `DJIAircraft` object which is a subclass of `DJIBaseProduct`.
 */
@interface DJIFlightController : DJIBaseComponent


/**
 *  Flight controller delegate.
 */
@property(nonatomic, weak) id<DJIFlightControllerDelegate> delegate;


/**
 *  Landing Gear object. For products with movable landing gear only.
 */
@property(nonatomic, readonly) DJILandingGear *_Nullable landingGear;


/**
 *  Compass object.
 */
@property(nonatomic, readonly) DJICompass *_Nullable compass;


/**
 *  RTK positioning object. Nil if the flight controller doesn't support it.
 */
@property(nonatomic, readonly) DJIRTK *_Nullable RTK;


/**
 *  Intelligent flight assistant. Nil if the flight controller doesn't support it.
 */
@property(nonatomic, readonly) DJIFlightAssistant *_Nullable flightAssistant;


/**
 *  Gets the instance of the access locker. It is used to encapsulate the access
 *  protection features on the aircraft.
 */
@property(nonatomic, readonly) DJIAccessLocker *accessLocker;


/**
 *  Simulator object.
 */
@property(nonatomic, readonly) DJISimulator *_Nullable simulator;


/**
 *  Number of IMU modules in the flight controller. Most products have one IMU.
 *   Exceptions:
 *   - Phantom 4, Phantom 4 Pro, Mavic Pro, and Inspire 2 each have two IMUs
 *   - A3, Matrice 600, and Matrice 600 Pro each have one inner IMU and can have at
 *  most two external IMUs.
 *   - N3 has two inner IMUs and can have one external IMU.
 */
@property(nonatomic, readonly) NSUInteger IMUCount;


/**
 *  The object representing the optional onboardsdk device.
 */
@property (nonatomic, readonly, nullable) DJIOnboardSDKDevice *onboardSDKDevice;

/*********************************************************************************/
#pragma mark Flight Limitation
/*********************************************************************************/


/**
 *  Sets the maximum flight height limitation of the aircraft. The
 *  <code>maxHeight</code> value must be in the  range [20, 500] m.
 *  
 *  @param maxHeight Maximum height of the aircraft.
 *  @param completion Completion block.
 */
- (void)setMaxFlightHeight:(NSUInteger)maxHeight withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the maximum flight height limitation of the aircraft.
 *  
 *  @param height Maximum flight height of the aircraft.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getMaxFlightHeightWithCompletion:(void (^_Nonnull)(NSUInteger height, NSError *_Nullable error))completion;


/**
 *  Sets the maximum flight radius limitation of the aircraft. The radius is
 *  calculated from the home point.  The <code>maxRadius</code> value must be in the
 *  range [15, 8000] m.
 *  
 *  @param maxRadius Maximum flight radius of the aircraft.
 *  @param completion Completion block.
 */
- (void)setMaxFlightRadius:(NSUInteger)maxRadius withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the maximum flight radius limitation of the aircraft.
 *  
 *  @param radius Maximum flight radius of the aircraft.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getMaxFlightRadiusWithCompletion:(void (^_Nonnull)(NSUInteger radius, NSError *_Nullable error))completion;


/**
 *  Sets whether the maximum flight radius limitation is enabled. If enabled is
 *  `NO`,  there is no maximum flight radius limitation.
 *  
 *  @param enabled Maximum flight radius limitation is enabled.
 *  @param completion Completion block.
 */
- (void)setMaxFlightRadiusLimitationEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the maximum flight radius limitation status (enabled/disabled).
 *  
 *  @param enabled YES if the maximum flight radius limitation is enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getMaxFlightRadiusLimitationEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Methods
/*********************************************************************************/


/**
 *  `YES` if landing gear is supported for the connected aircraft.
 *  
 *  @return A boolean value.
 */
- (BOOL)isLandingGearMovable;


/**
 *  Starts aircraft takeoff. Takeoff is considered complete when the aircraft is
 *  hovering 1.2 meters (4 feet) above the ground. Completion block is called when
 *  aircraft crosses 0.5 meters (1.6 feet). If the motors are already on, this
 *  command cannot be executed.
 *  
 *  @param completion Completion block.
 */
- (void)startTakeoffWithCompletion:(DJICompletionBlock)completion;


/**
 *  Stops aircraft takeoff. If called before `startTakeoffWithCompletion` is
 *  complete, the aircraft will cancel takeoff (`startTakeoffWithCompletion`
 *  completion block will return an error) and hover at the current height.
 *  
 *  @param completion Completion block.
 */
- (void)cancelTakeoffWithCompletion:(DJICompletionBlock)completion;


/**
 *  Starts auto-landing of the aircraft. Returns completion block once aircraft
 *  begins to descend for auto-land.
 *  
 *  @param completion Completion block.
 */
- (void)startLandingWithCompletion:(DJICompletionBlock)completion;


/**
 *  Stops auto-landing of the aircraft. If called before
 *  `startLandingWithCompletion` is complete, then the auto landing will be canceled
 *  (`startLandingWithCompletion` completion block will return an error) and the
 *  aircraft will hover at its current location.
 *  
 *  @param completion Completion block.
 */
- (void)cancelLandingWithCompletion:(DJICompletionBlock)completion;


/**
 *  Turns on the aircraft's motors. Supported by flight controller firmware 3.1.0.0
 *  or above.
 *  
 *  @param completion Completion block.
 */
- (void)turnOnMotorsWithCompletion:(DJICompletionBlock)completion;


/**
 *  Turns off the aircraft's motors. The method can only be called when the aircraft
 *  is on the ground.
 *  
 *  @param completion Completion block.
 */
- (void)turnOffMotorsWithCompletion:(DJICompletionBlock)completion;


/**
 *  Enables ESC beeping.
 *  
 *  @param enabled `YES` to enable ESC beeping.
 *  @param completion Completion block to receive the result.
 */
- (void)setESCBeepEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines if ESC beeping is enabled.
 *  
 *  @param enabled `YES` if ESC beeping is enabled.
 *  @param error Encountered error if any.
 *  @param completion Completion block to receive the result.
 */
- (void)getESCBeepEnabledWithCompletion:(void (^_Nullable)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  The aircraft will start to go home. The `completion block` will return execution
 *  result once this method is invoked.
 *  
 *  @param completion Completion block.
 */
- (void)startGoHomeWithCompletion:(DJICompletionBlock)completion;


/**
 *  The aircraft will stop going home and will hover in place.
 *  
 *  @param completion Completion block.
 */
- (void)cancelGoHomeWithCompletion:(DJICompletionBlock)completion;


/**
 *  Sets the home location of the aircraft. The home location is where the aircraft
 *  returns when commanded by `startGoHomeWithCompletion`, when its signal is lost
 *  or when the battery is below the lowBatteryWarning threshold. The user should be
 *  careful setting a new home point location, as sometimes the product will not be
 *  under user control when returning home. A home location is valid if it is within
 *  30m of one of the following:
 *   - initial take-off location
 *   - aircraft's current location
 *   - current mobile location with at least kCLLocationAccuracyNearestTenMeters
 *  accuracy level
 *   - current remote controller's location as shown by RC GPS.
 *   Note: If setting home point around mobile location, before calling this method,
 *  the locationServicesEnabled must be true in CLLocationManager, the
 *  NSLocationWhenInUseUsageDescription or NSLocationAlwaysUsageDescription key
 *  needs to be specified in the applications Info.plist and the
 *  requestWhenInUseAuthorization or requestAlwaysAuthorization method of
 *  CLLocationManager object needs to be called to get the user's permission to
 *  access location services.
 *  
 *  @param homeLocation Home location latitude and longitude in degrees.
 *  @param completion Completion block.
 */
- (void)setHomeLocation:(CLLocation *)homeLocation
         withCompletion:(DJICompletionBlock)completion;


/**
 *  Sets the home location of the aircraft to the current location of the aircraft.
 *  See `setHomeLocation:withCompletion` for details on home point use.
 *  
 *  @param completion Completion block.
 */
- (void)setHomeLocationUsingAircraftCurrentLocationWithCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the home point of the aircraft.
 *  
 *  @param homeLocation The CLLocationCoordinate2D Struct.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getHomeLocationWithCompletion:(void (^_Nonnull)(CLLocation *_Nullable homeLocation, NSError *_Nullable error))completion;


/**
 *  Sets the minimum altitude, relative to where the aircraft took off, at which the
 *  aircraft must be before going home. This can be useful when the user foresees
 *  obstacles in the aircraft's flight path. If the aircraft's current altitude is
 *  higher than the minimum go home altitude, it will go home at its current
 *  altitude. The valid range for the altitude is from 20m to 500m.
 *  
 *  @param height The aircraft's default go home altitude.
 *  @param completion Completion block.
 */
- (void)setGoHomeHeightInMeters:(NSUInteger)height withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the minimum altitude (relative to the take-off location in meters) at which
 *  the aircraft must be before going home.
 *  
 *  @param height The minimum altitude.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getGoHomeHeightInMetersWithCompletion:(void (^_Nonnull)(NSUInteger height, NSError *_Nullable error))completion;


/**
 *  Sets the FailSafe action for when the connection between remote controller and
 *  aircraft is lost.
 *  
 *  @param behavior The `DJIConnectionFailSafeBehavior` object.
 *  @param completion Completion block to receive the result.
 */
- (void)setConnectionFailSafeBehavior:(DJIConnectionFailSafeBehavior)behavior
                       withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the FailSafe action for when the connection between remote controller and
 *  aircraft is lost.
 *  
 *  @param behavior The value of the `DJIConnectionFailSafeBehavior` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getConnectionFailSafeBehaviorWithCompletion:(void (^_Nonnull)(DJIConnectionFailSafeBehavior behavior, NSError *_Nullable error))completion;


/**
 *  Returns if the Onboard SDK feature is available on the connected product.
 *  
 *  @return A boolean value.
 */
- (BOOL)isOnboardSDKAvailable;


/**
 *  Sets the low battery warning threshold as a percentage. The percentage must be
 *  in the range of [15, 50].
 *  
 *  @param percent Low battery warning percentage.
 *  @param completion Completion block.
 */
- (void)setLowBatteryWarningThreshold:(uint8_t)percent
                       withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the low battery warning threshold as a percentage.
 *  
 *  @param percent The go home battery percentage threshold.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getLowBatteryWarningThresholdWithCompletion:(void (^_Nonnull)(uint8_t percent, NSError *_Nullable error))completion;


/**
 *  Sets the serious low battery warning threshold as a percentage. The minimum
 *  value is 10. The maximum value is value from
 *  `getLowBatteryWarningThresholdWithCompletion` minus 5.
 *  
 *  @param percent Critically low battery warning percentage.
 *  @param completion Completion block.
 */
- (void)setSeriousLowBatteryWarningThreshold:(uint8_t)percent
                              withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the serious low battery warning threshold in percentage.
 *  
 *  @param completion The completion block with the value returned
 *  @param percent Battery threshold percentage
 *  @param error Error message
 */
- (void)getSeriousLowBatteryWarningThresholdWithCompletion:(void (^_Nonnull)(uint8_t percent, NSError *_Nullable error))completion;


/**
 *  Enables/disables Smart Return-To-Home (RTH) feature. When it is enabled,
 *  aircraft will request to go home when remaining battery is only enough for
 *  completing the go-home action.
 *  
 *  @param enabled `YES` to enable smart RTH.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setSmartReturnToHomeEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether Smart Return-To-Home (RTH) feature is enabled or not. When it
 *  is enabled, aircraft will request to go home when remaining battery is only
 *  enough for completing the go-home action.
 *  
 *  @param enabled `YES` if Smart RTH is enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)getSmartReturnToHomeEnabledWithCompletion:(void (^)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Confirms or cancels the Smart Return-To-Home (RTH) request. When Smart RTH is
 *  enabled, the aircraft will request to go home when the battery is only enough
 *  for going home. Before executing the go-home action, the aircraft will wait for
 *  the confirmation from users with 10 seconds count-down. If the "confirmed"
 *  parameter is `NO`, the request is canceled and the aircraft will not execute go-
 *  home action. Otherwise, go-home action will start. Smart RTH will be triggered
 *  only once during the same flight. Flight controller with firmware version lower
 *  than 3.0.0.0 does not support confirming the Smart RTH request. User can either
 *  cancel the request or wait for the countdown to start go-home action.
 *  
 *  @param confirmed `YES` to confirm the request and the aircraft will start go-home immediately.
 *  @param completion Completion block to receive the result.
 */
- (void)confirmSmartReturnToHomeRequest:(BOOL)confirmed withCompletion:(DJICompletionBlock)completion;


/**
 *  Starts IMU calibration. For aircraft with multiple IMUs, this method will start
 *  the calibration of all IMUs. Keep the aircraft stationary and horizontal during
 *  calibration, which will take 5 to 10 minutes. The completion block will be
 *  called once the calibration is started. Use the
 *  `flightController:didUpdateIMUState` method to check the execution status of the
 *  IMU calibration.
 *  
 *  @param completion Completion block to check if the calibration starts successfully.
 */
- (void)startIMUCalibrationWithCompletion:(DJICompletionBlock)completion;


/**
 *  Starts the calibration for IMU with a specific ID. Keep the aircraft stationary
 *  and horizontal during calibration, which will take 5 to 10 minutes. The
 *  completion block will be called once the calibration is started. Use the
 *  `flightController:didUpdateIMUState` method to check the execution status of the
 *  IMU calibration.
 *  
 *  @param index The IMU with the specific ID to calibrate.
 *  @param completion Completion block to check if the calibration starts successfully.
 */
- (void)startIMUCalibrationForIndex:(NSUInteger)index withCompletion:(DJICompletionBlock)completion;


/**
 *  Confirms continuation of landing action. When the clearance between the aircraft
 *  and the ground is less than 0.3m, the aircraft will pause landing and wait for
 *  user's confirmation. Can use `isLandingConfirmationNeeded` in
 *  `DJIFlightControllerState` to check if confirmation is needed. It is supported
 *  by flight controller firmware 3.2.0.0 and above.
 *  
 *  @param completion Completion block to check if confirm landing successful.
 */
- (void)confirmLandingWithCompletion:(DJICompletionBlock)completion;


/**
 *  Turns on/off different sets of LEDs on the aircraft. All the LEDs are on by
 *  default.
 *  
 *  @param ledsSettings Settings to control LEDs.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setLEDsEnabledSettings:(DJIMutableFlightControllerLEDsSettings *)ledsSettings withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines the status of LEDs on the aircraft.
 *  
 *  @param ledsSettings An object of `DJIFlightControllerLEDsSettings`.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getLEDsEnabledSettingsWithCompletion:(void (^)(DJIFlightControllerLEDsSettings *ledsSettings, NSError *_Nullable error))completion;


/**
 *  Sets the control mode of the flight controller. It is highly recommended you
 *  keep the default value of `DJIFlightControllerControlModeSmart`. See
 *  `DJIFlightControllerControlMode` for details. Only supported by stand-alone A3.
 *  
 *  @param mode Control mode to set.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setControlMode:(DJIFlightControllerControlMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the control mode of the flight controller.
 *  
 *  @param mode The value of the `DJIFlightControllerControlMode` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getControlModeWithCompletion:(void (^_Nonnull)(DJIFlightControllerControlMode mode, NSError *_Nullable error))completion;


/**
 *  Enables/disables tripod mode. Tripod Mode drops the aircraft's maximum speed to
 *  2.2mph (3.6kph), and significantly reduces the control stick sensitivity of the
 *  remote controller to give the user the precision needed for accurate framing.
 *  When tripod mode is enabled, missions, terrain follow mode, course lock, and
 *  home lock are not allowed. Tripod mode is not allowed if the aircraft is running
 *  a mission. If GPS or vision positioning aren't available, tripod mode cannot be
 *  enabled. If the GPS and/or the vision system is providing the flight controller
 *  with velocity information, the aircraft will be able to automatically compensate
 *  for wind. If however, position information is not available, manual intervention
 *  will be required. User should beware that any manual compensation will be
 *  limited due to the reduced maximum velocity and sensitivity. If GPS and vision
 *  position become unavailable while in tripod mode, it is advisable to alert the
 *  user and disable Tripod Mode.
 *  
 *  @param enabled `YES` to enable tripod mode.
 *  @param completion Completion block that receives the setter result.
 */
- (void)setTripodModeEnabled:(BOOL)enabled
              withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets tripod mode status (enabled/disabled).
 *  
 *  @param enabled Yes if tripod mode is enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getTripodModeEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Enables/disables cinematic mode. In Cinematic Mode, you can shoot more stable
 *  and smooth photos and videos. Aircraft yaw speed will be lower and braking
 *  distance will be longer. It's only supported by Mavic Pro, Spark, Mavic 2 Zoom
 *  and Mavic 2 Pro.
 *  
 *  @param enabled `YES` to enable cinematic mode.
 *  @param completion Completion block to receive the result.
 */
- (void)setCinematicModeEnabled:(BOOL)enabled
                 withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets cinematic mode status (enabled/disabled). It's only supported by Mavic Pro,
 *  Spark, Mavic 2 Zoom and  Mavic 2 Pro.
 *  
 *  @param enabled `YES` to enable cinematic mode.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getCinematicModeEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Adjusts the braking sensitivity when cinematic mode is enabled. Higher
 *  sensitivity can shorten the  braking distance in cinematic mode. It's supported
 *  by Mavic Pro, Spark, Mavic 2 Zoom and  Mavic 2 Pro.
 *  
 *  @param brakeSensitivity Brake sensitivity in cinematic mode.
 *  @param completion Completion block to receive the result.
 */
- (void)setCinematicBrakeSensitivity:(NSUInteger)brakeSensitivity withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the braking sensitivity when cinematic mode is enabled. Higher sensitivity
 *  can shorten the  braking distance in cinematic mode. It's supported by Mavic
 *  Pro, Spark, Mavic 2 Zoom and  Mavic 2 Pro.
 *  
 *  @param brakeSensitivity Brake sensitivity in cinematic mode.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getCinematicBrakeSensitivityWithCompletion:(void (^_Nonnull)(NSUInteger brakeSensitivity, NSError *_Nullable error))completion;


/**
 *  Adjusts the aircraft's yaw speed when cinematic mode is enabled. It's supported
 *  by Mavic Pro, Spark, Mavic 2 Zoom and  Mavic 2 Pro.
 *  
 *  @param yawSpeed The aircraft's yaw speed in cinematic mode.
 *  @param completion Completion block to receive the result.
 */
- (void)setCinematicYawSpeed:(NSUInteger)yawSpeed withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the aircraft's yaw speed when cinematic mode is enabled. It's supported by
 *  Mavic Pro, Spark, Mavic 2 Zoom and  Mavic 2 Pro.
 *  
 *  @param yawSpeed The aircraft's yaw speed in cinematic mode.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getCinematicYawSpeedWithCompletion:(void (^_Nonnull)(NSUInteger yawSpeed, NSError *_Nullable error))completion;


/**
 *  Enable/disable terrain follow mode. The aircraft uses height information
 *  gathered by the onboard ultrasonic system and its downward facing cameras to
 *  keep flying at the same height above the ground.
 *  
 *  @param enabled The execution callback with the returned value(s).
 *  @param completion Completion block that receives the setter result.
 */
- (void)setTerrainFollowModeEnabled:(BOOL)enabled
                     withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets terrain mode status (enabled/disabled).
 *  
 *  @param enabled `YES` if terrain follow mode is enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getTerrainFollowModeEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Enable/disable Auto Quick Spin. When the gimbal reaches a yaw movement limit,
 *  the aircraft will automatically rotate 360 degrees to unwind the gimbal,
 *  allowing it to continue moving in the yaw direction. This method is only
 *  available when the aircraft is flying at least 3m above the ground.
 *  
 *  @param enabled `YES` to enable Auto Quick Spin.
 *  @param completion Completion block that receives the setter result.
 */
- (void)setAutoQuickSpinEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets current Auto Quick Spin mode (enabled/disabled).
 *  
 *  @param enabled `YES` if Auto Quick Spin is enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getAutoQuickSpinEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Gets the mapping between the flight modes and the flight mode switch positions
 *  on the remote controller. Elements 0, 1, and 2 of the returned array map to
 *  `DJIRCFlightModeSwitchOne`, `DJIRCFlightModeSwitchTwo`, and
 *  `DJIRCFlightModeSwitchThree` of the `flightModeSwitch`. The value of each Enum
 *  item represents the corresponding value of the
 *  `DJIFlightControllerRemoteControllerFlightMode` Enum representing the flight
 *  mode.
 *  The mapping is fixed for the Phantom series, Inspire series, Mavic Pro, and
 *  M100. For N3, A3, Matrice 600, and Matrice 600 Pro the mapping is firmware
 *  dependent. With firmware version 3.2.11.0 or above, the mapping can be
 *  customized in DJI Assistant 2.
 *  
 *  @param mapping The array of the NSNumber.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getRCSwitchFlightModeMappingWithCompletion:(void (^_Nonnull)(NSArray<NSNumber *> *_Nullable mapping, NSError *_Nullable error))completion;


/**
 *  Enable vision positioning. Vision positioning is used to augment GPS to improve
 *  location accuracy when hovering and improve velocity calculation when flying.
 *  
 *  @param enabled `YES` to enable vision assisted positioning.
 *  @param completion Completion block that receives the execution result.
 */
- (void)setVisionAssistedPositioningEnabled:(BOOL)enabled
                             withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets vision positioning status (enabled/disabled).
 *  
 *  @param enabled YES if the vision position is enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getVisionAssistedPositioningEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled,
                                                                            NSError *_Nullable error))completion;


/**
 *  Enables/disables multiple-flight mode. When multiple-flight mode is enabled,
 *  user can change the aircraft's mode to P/F/A/S mode by toggling the switch on
 *  the remote controller. If it is disabled, the aircraft will be in P mode.
 *  
 *  @param enabled `YES` to enable multiple-flight mode.
 *  @param completion Completion block that receives the execution result.
 */
- (void)setMultipleFlightModeEnabled:(BOOL)enabled
                      withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether multiple-flight mode is enabled. When multiple-flight mode is
 *  enabled, user can change the aircraft's mode to P/F/A/S mode by toggling the
 *  switch on the remote controller. If it is disabled, the aircraft will be in P
 *  mode.
 *  
 *  @param enabled `YES` if the multiple-flight mode is enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block that receives the execution result.
 */
- (void)getMultipleFlightModeEnabledWithCompletion:(void (^)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Enables novice mode. When novice mode is enabled, the flight speed will become
 *  slower and less responsive handling. For Phantom 4 Pro, enabling novice mode
 *  will enable the infrared time-of-flight (TOF) sensors on the left and right.
 *  
 *  @param enabled `YES` to enable novice mode.
 *  @param completion Completion block that receives the execution result.
 */
- (void)setNoviceModeEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether novice mode is enabled or not. If novice mode is enabled, the
 *  flight speed is slower and less responsive handling. For Phantom 4 Pro, enabling
 *  novice mode will enable the infrared time-of-flight (TOF) sensors on the left
 *  and right.
 *  
 *  @param enabled `YES` if novice mode is enabled.
 *  @param error Error if there is any.
 *  @param completion Completion block that receives the execution result.
 */
- (void)getNoviceModeEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Virtual Stick Mode
/*********************************************************************************/

/**
 *  Indicates whether the virtual stick control interface can be used. Virtual stick
 *  mode is only available when all of the follow requirements are met:
 *   - Virtual stick mode is enabled.
 *   - No waypoint, hotpoint, or follow-me mission is running.
 *   - `DJIFlightOrientationMode` is set to
 *  `DJIFlightOrientationModeAircraftHeading`
 *   - Terrain-follow is disabled if the aircraft supports this feature.
 *   - Tripod mode is disabled if the aircraft supports this feature.
 *  
 *  @return `YES` if virtual stick mode is available.
 */
- (BOOL)isVirtualStickControlModeAvailable;


/**
 *  Enables/disables virtual stick control mode. By enabling virtual stick control
 *  mode, the aircraft can be controlled using
 *  `sendVirtualStickFlightControlData:withCompletion`. Not supported by Mavic Pro
 *  when using the WiFi connection.
 *  
 *  @param enabled `YES` to enable virtual stick mode.
 *  @param completion The execution completion block with the returned execution result.
 */
- (void)setVirtualStickModeEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets virtual stick mode status (enabled/disabled). Not supported by Mavic Pro
 *  when using the WiFi connection.
 *  
 *  @param enabled `YES` if enabled.
 *  @param completion The execution completion block with the returned execution result.
 *  @param error Error (if any) of the operation.
 */
- (void)getVirtualStickModeEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Sends flight control data using virtual stick commands. The
 *  `isVirtualStickControlModeAvailable` method must return `YES` to use virtual
 *  stick commands. Virtual stick commands should be sent to the aircraft between 5
 *  Hz and 25 Hz. If virtual stick commands are not sent frequently enough, the
 *  aircraft may regard the connection as broken, which will cause the aircraft to
 *  hover in place until the next command comes through.
 *  
 *  @param controlData Flight control data.
 *  @param completion Completion block.
 */
- (void)sendVirtualStickFlightControlData:(DJIVirtualStickFlightControlData)controlData
                           withCompletion:(DJICompletionBlock)completion;


/**
 *  The vertical control mode for virtual stick. CAUTION: It will be reset to
 *  `DJIVirtualStickVerticalControlModeVelocity` when the flight controller is
 *  reconnected.
 */
@property(nonatomic, assign) DJIVirtualStickVerticalControlMode verticalControlMode;


/**
 *  The roll and pitch control mode for virtual stick. CAUTION: It will be reset to
 *  `DJIVirtualStickRollPitchControlModeAngle` when the flight controller is
 *  reconnected.
 */
@property(nonatomic, assign) DJIVirtualStickRollPitchControlMode rollPitchControlMode;


/**
 *  The yaw control mode for virtual stick. CAUTION: It will be reset to
 *  `DJIVirtualStickYawControlModeAngle` when the flight controller is reconnected.
 */
@property(nonatomic, assign) DJIVirtualStickYawControlMode yawControlMode;


/**
 *  The coordinate system for virtual stick. CAUTION: It will be reset to
 *  `DJIVirtualStickFlightCoordinateSystemGround` when the flight controller is
 *  reconnected.
 */
@property(nonatomic, assign) DJIVirtualStickFlightCoordinateSystem rollPitchCoordinateSystem;


/**
 *  `YES` if Virtual Stick advanced mode is enabled. By default, it is `NO`.
 *  Assuming GPS signal is good, advanced mode will allow aircraft to compensate for
 *  wind when hovering. For the Phantom 4, collision avoidance can be enabled for
 *  virtual stick control if advanced mode is on, and collision avoidance is enabled
 *  in `DJIFlightAssistant`. Only supported by flight controller firmware versions
 *  3.1.x.x or above. CAUTION: It will be reset to `NO` when the flight controller
 *  is reconnected.
 */
@property(nonatomic, assign) BOOL isVirtualStickAdvancedModeEnabled;
@end


/**
 *  This class provides method to set flight orientation mode of the flight
 *  controller. Also, it provides a method for you to lock the current heading
 *  of the aircraft as the Course Lock.
 */
@interface DJIFlightController (DJIFlightOrientationMode)


/**
 *  Sets the aircraft flight orientation relative to the Aircraft Heading, Course
 *  Lock, or Home Lock. See the <i>Flight Controller User Guide</i> for more
 *  information about flight orientation.
 *  
 *  @param type The orientation mode.
 *  @param completion Completion block.
 */
- (void)setFlightOrientationMode:(DJIFlightOrientationMode)type
                  withCompletion:(DJICompletionBlock)completion;


/**
 *  Locks the current heading of the aircraft as the Course Lock. Used when Flight
 *  Orientation Mode is `DJIFlightOrientationModeCourseLock`.
 *  
 *  @param completion Completion block.
 */
- (void)lockCourseUsingCurrentHeadingWithCompletion:(DJICompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END
