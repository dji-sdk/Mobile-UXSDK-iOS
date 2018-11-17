//
//  DJIGimbalBaseTypes.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Data Structs and Enums

/*********************************************************************************/
#pragma mark DJIGimbalRotationMode
/*********************************************************************************/

/**
 *  The mode of the gimbal rotation operation.
 */
typedef NS_ENUM(NSInteger, DJIGimbalRotationMode) {


    /**
     *  The angle value, when the gimbal is rotating, relative to the current angle.
     */
    DJIGimbalRotationModeRelativeAngle,


    /**
     *  The angle value, when the gimbal is rotating, relative to 0 degrees (aircraft
     *  heading).
     */
    DJIGimbalRotationModeAbsoluteAngle,


    /**
     *  Rotate the gimbal's pitch, roll, and yaw in SPEED Mode. The direction can either
     *  be set to clockwise or counter-clockwise.
     *   For Phantom 3 Professional, Phantom 3 Advanced and Phantom 3 Standard, roll and
     *  yaw rotations are not available.
     *   For Inspire 1, Inspire Pro and M100, pitch, roll and yaw rotations are
     *  available.
     *   For Osmo, roll rotation is not available. The yaw angleVelocity of
     *  DJIGimbalSpeedRotation range is (-120, 120).
     */
    DJIGimbalRotationModeSpeed
};

/*********************************************************************************/
#pragma mark DJIGimbalRotation
/*********************************************************************************/

/**
 *  Represents a gimbal speed or angular rotation operation.
 */
@interface DJIGimbalRotation : NSObject


/**
 *  Type of gimbal rotation operation mode.
 */
@property (nonatomic, assign, readonly) DJIGimbalRotationMode mode;


/**
 *  The pitch property of a gimbal rotation operation, how much the gimbal rotates
 *  on the pitch axis. When it is `nil`, no operation will be applied to the pitch
 *  axis.
 */
@property (nonatomic, strong, nullable, readonly) NSNumber *pitch;


/**
 *  The roll property of a gimbal rotation operation, how much the gimbal rotates on
 *  the roll axis. When it is `nil`, no operation will be applied to the roll axis.
 */
@property (nonatomic, strong, nullable, readonly) NSNumber *roll;


/**
 *  The yaw property of a gimbal rotation operation, how much the gimbal rotates on
 *  the yaw axis. When the rotation mode is `DJIGimbalRotationModeAbsoluteAngle`,
 *  the yaw value is relative to the aircraft's heading. When it is `nil`, no
 *  operation will be applied to the yaw axis.
 */
@property (nonatomic, strong, nullable, readonly) NSNumber *yaw;


/**
 *  The time of the gimbal speed rotation operation.
 */
@property (nonatomic, assign, readonly) NSTimeInterval time;


/**
 *  Constructor for `DJIGimbalRotation`.
 *  
 *  @param pitchValue NSNumber object of pitch value.
 *  @param rollValue NSNumber object of roll value.
 *  @param yawValue NSNumber object of yaw value.
 *  @param time NSTimeInterval value of rotation time.
 *  @param mode An enum value of `DJIGimbalRotationMode`.
 *  
 *  @return Instance of `DJIGimbalRotation`.
 */
+ (nonnull instancetype)gimbalRotationWithPitchValue:(nullable NSNumber *)pitchValue
                                           rollValue:(nullable NSNumber *)rollValue
                                            yawValue:(nullable NSNumber *)yawValue
                                                time:(NSTimeInterval)time
                                                mode:(DJIGimbalRotationMode)mode;

@end

/*********************************************************************************/
#pragma mark DJIGimbalAttitude
/*********************************************************************************/


/**
 *  The gimbal's attitude in degrees relative to the aircraft.
 */
typedef struct
{

    /**
     *  Pitch value in degrees.
     */
    float pitch;
 

    /**
     *  Roll value in degrees.
     *  
     *  @return <<android:A float value.>
     */
    float roll;


    /**
     *  Yaw value in degrees.
     *  
     *  @return <<android:A float value.>
     */
    float yaw;
} DJIGimbalAttitude;

/*********************************************************************************/
#pragma mark DJIGimbalMode
/*********************************************************************************/


/**
 *  Gimbal work modes.
 */
typedef NS_ENUM (uint8_t, DJIGimbalMode){


    /**
     *  The gimbal can move independently of the aircraft's yaw. In this mode, even if
     *  the aircraft yaw changes, the camera will continue pointing in the same world
     *  direction. This mode is only available for the Ronin-MX when the M600 or M600
     *  Pro landing gear is retracted.
     */
    DJIGimbalModeFree,


    /**
     *  The gimbal's work mode is FPV mode. In this mode, the gimbal yaw will follow the
     *  aircraft's heading, and the gimbal roll will follow the RC's roll channel value.
     *  The pitch will be available to move. This mode is only available for the Ronin-
     *  MX when the M600 landing gear is retracted.
     */
    DJIGimbalModeFPV,


    /**
     *  The gimbal's work mode is such that it will follow the yaw. In this mode, the
     *  gimbal yaw will be fixed, while pitch and roll will be available to move.
     */
    DJIGimbalModeYawFollow,


    /**
     *  The gimbal's work mode is unknown.
     */
    DJIGimbalModeUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark DJIGimbalMovementSettingsProfile
/*********************************************************************************/


/**
 *  The Movement Settings Profile contains presets for SmoothTrack and the Physical
 *  Controller sensitivity. SmoothTrack and Controller settings can only be manually
 *  changed if Custom1 or Custom2 profiles are selected.
 */
typedef NS_ENUM (uint8_t, DJIGimbalMovementSettingsProfile){


    /**
     *  The gimbal's SmoothTrack and Controller sensitivity is high. When the gimbal is
     *  using this profile, user cannot change the Movement Settings manually.
     */
    DJIGimbalMovementSettingsProfileFast,


    /**
     *  The gimbal's SmoothTrack and Controller sensitivity is medium. When the gimbal
     *  is using this profile, user cannot change the Movement Settings manually.
     */
    DJIGimbalMovementSettingsProfileMedium,
    

    /**
     *  The gimbal's SmoothTrack and Controller sensitivity is slow. When the gimbal is
     *  using this profile, user cannot change the Movement Settings manually.
     */
    DJIGimbalMovementSettingsProfileSlow,


    /**
     *  The gimbal uses a custom configuration in memory slot 1 where the yaw and pitch
     *  speed, deadband, and acceleration can be defined.
     */
    DJIGimbalMovementSettingsProfileCustom1,


    /**
     *  The gimbal uses a custom configuration in memory slot 2 where the yaw and pitch
     *  speed, deadband, and acceleration can be defined.
     */
    DJIGimbalMovementSettingsProfileCustom2,


    /**
     *  The gimbal's user config type is unknown.
     */
    DJIGimbalMovementSettingsProfileUnknown = 0xFF,
    
};

/*********************************************************************************/
#pragma mark DJIGimbalAxis
/*********************************************************************************/


/**
 *  Gimbal Axis.
 */
typedef NS_ENUM (uint8_t, DJIGimbalAxis){


    /**
     *  Gimbal's yaw axis.
     */
    DJIGimbalAxisYaw,


    /**
     *  Gimbal's pitch axis.
     */
    DJIGimbalAxisPitch,


    /**
     *  Gimbal's roll axis.
     */
    DJIGimbalAxisRoll
};

/*********************************************************************************/
#pragma mark DJIGimbalEndpointDirection
/*********************************************************************************/


/**
 *  Gimbal endpoint setting.
 */
typedef NS_ENUM (uint8_t, DJIGimbalEndpointDirection){
 

    /**
     *  Pitch (also called tilt) endpoint setting in the upwards direction.
     */
    DJIGimbalEndpointDirectionPitchUp,
 

    /**
     *  Pitch (also called tilt) endpoint setting in the downwards direction.
     */
    DJIGimbalEndpointDirectionPitchDown,
 

    /**
     *  Yaw (also called pan) endpoint setting in the left direction.
     */
    DJIGimbalEndpointDirectionYawLeft,
 

    /**
     *  Yaw (also called pan) endpoint setting in the right direction.
     */
    DJIGimbalEndpointDirectionYawRight,
};

/*********************************************************************************/
#pragma mark DJIGimbalMotorControlPreset
/*********************************************************************************/


/**
 *  For gimbals that allow payloads to be changed, the motor control configuration
 *  can be used to optimize gimbal performance for the different payloads.
 */
typedef NS_ENUM (uint8_t, DJIGimbalMotorControlPreset){


    /**
     *  The gimbal's motor control configuration is optimized for RED cameras.
     */
    DJIGimbalMotorControlPresetRED,


    /**
     *  The gimbal's motor control configuration is optimized for most DSLR cameras.
     */
    DJIGimbalMotorControlPresetDSLR,


    /**
     *  The gimbal's motor control configuration is optimized for most mirrorless
     *  cameras.
     */
    DJIGimbalMotorControlPresetMirrorless
};

/*********************************************************************************/
#pragma mark DJIGimbalBalanceTestResult
/*********************************************************************************/


/**
 *  For gimbals that allow payloads to be changed, a balance test should be
 *  performed to ensure the camera is mounted correctly.
 */
typedef NS_ENUM (uint8_t, DJIGimbalBalanceTestResult){
 

    /**
     *  The balance test result is great.
     */
    DJIGimbalBalanceTestResultPass,
 

    /**
     *  The balance test result is good. When this result is returned, it is possible
     *  there was some noise in the balance measurement. For best results, it is
     *  recommended to run the balance test again and adjust the payload position until
     *  the result becomes great.
     */
    DJIGimbalBalanceTestResultMarginal,
 

    /**
     *  The balance test result is bad. The payload should be adjusted when this result
     *  is returned.
     */
    DJIGimbalBalanceTestResultFail,
 

    /**
     *  The balance test result is unknown.
     */
    DJIGimbalBalanceTestResultUnknown = 0xFF
};


/**
 *  The loading balance status of the gimbal. The gimbal loading is changeable for
 *  Osmo Mobile. When the mounted mobile device is changed, in order to  optimize
 *  the gimbal performance, user can adjust the gimbal physically based on the
 *  status.
 */
typedef NS_ENUM (uint8_t, DJIGimbalBalanceState){
 

    /**
     *  The gimbal is balanced.
     */
    DJIGimbalBalanceStateBalanced,
 

    /**
     *  The gimbal is tilting left. Adjust the photo to the right hand side to balance
     *  the gimbal.
     */
    DJIGimbalBalanceStateTiltingLeft,
 

    /**
     *  The gimbal is tilting right. Adjust the photo to the left hand side to balance
     *  the gimbal.
     */
    DJIGimbalBalanceStateTiltingRight,
 

    /**
     *  The balance status is unknown.
     */
    DJIGimbalBalanceStateUnknown = 0xFF,
};


/*********************************************************************************/
#pragma mark - Gimbal Capability Keys
/*********************************************************************************/


/**
 *  Key string in the `capabilities` dictionary that holds the complete capability
 *  of the gimbal. A negative value in the valid range represents counter-clockwise
 *  rotation. A positive value in the valid range represents clockwise rotation.
 */
extern NSString *const DJIGimbalParamAdjustPitch;


/**
 *  Key string in `capabilities` associated with whether the gimbal supports yaw
 *  axis adjustment. The corresponding value in `capabilities` is an instance of
 *  `DJIParamCapabilityMinMax` meaning both the feature's existence as well as its
 *  possible range in degrees is returned. A negative value in the valid range
 *  represents counter-clockwise rotation. A positive value in the valid range
 *  represents clockwise rotation. For Gimbal's that allow a pitch range extension
 *  (see `DJIGimbalParamPitchRangeExtensionEnabled`, the range will be
 *  representative of the extended range whether it is enabled or not.
 */
extern NSString *const DJIGimbalParamAdjustYaw;


/**
 *  Key string in `capabilities` associated with whether the gimbal supports roll
 *  axis adjustment. The corresponding value in `capabilities` is an instance of
 *  `DJIParamCapabilityMinMax` meaning both the feature's existence as well as its
 *  possible range in degrees is returned. A negative value in the valid range
 *  represents counter-clockwise rotation. A positive value in the valid range
 *  represents clockwise rotation.
 */
extern NSString *const DJIGimbalParamAdjustRoll;


/**
 *  Key string string in `capabilities` associated with whether the gimbal supports
 *  Advanced Settings Profiles. The corresponding value in `capabilities` is an
 *  instance of `DJIParamCapability`.
 */
extern NSString *const DJIGimbalParamMovementSettingsProfile;


/**
 *  Key string in `capabilities` associated with whether the gimbal supports a range
 *  extension in pitch. The corresponding value in `capabilities` is an instance of
 *  `DJIParamCapabilityMinMax` meaning both the feature's existence as well as its
 *  possible range in degrees is returned.
 */
extern NSString *const DJIGimbalParamPitchRangeExtensionEnabled;


/**
 *  Key string in `capabilities` associated with whether the gimbal's pitch axis
 *  response speed to manual control can be adjusted. The corresponding value in
 *  `capabilities` is an instance of `DJIParamCapabilityMinMax` meaning both the
 *  feature's existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamPitchControllerSpeedCoefficient;


/**
 *  Key string in `capabilities` associated with whether the gimbal's yaw axis
 *  response speed to manual control can be adjusted. The corresponding value in
 *  `capabilities` is an instance of `DJIParamCapabilityMinMax` meaning both the
 *  feature's existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamYawControllerSpeedCoefficient;


/**
 *  Key string in `capabilities` associated with whether the gimbal's pitch axis
 *  smoothing can be adjusted when using manual control. The corresponding value in
 *  `capabilities` is an instance of `DJIParamCapabilityMinMax` meaning both the
 *  feature's existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamPitchControllerSmoothingFactor;


/**
 *  Key string in `capabilities` associated with whether the gimbal's yaw axis
 *  smoothing can be adjusted when using manual control. The corresponding value in
 *  `capabilities` is an instance of `DJIParamCapabilityMinMax` meaning both the
 *  feature's existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamYawControllerSmoothingFactor;


/**
 *  Key string in `capabilities` associated with whether the gimbal's manual control
 *  pitch axis deadband can be adjusted. The corresponding value in `capabilities`
 *  is an instance of `DJIParamCapabilityMinMax` meaning both the feature's
 *  existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamPitchControllerDeadband;


/**
 *  Key string in `capabilities` associated with whether the gimbal's manual control
 *  yaw axis deadband can be adjusted. The corresponding value in `capabilities` is
 *  an instance of `DJIParamCapabilityMinMax` meaning both the feature's existence
 *  as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamYawControllerDeadband;


/**
 *  Key string in `capabilities` associated with whether the gimbal's manual control
 *  pitch axis max speed can be adjusted. The corresponding value in `capabilities`
 *  is an instance of `DJIParamCapabilityMinMax` meaning both the feature's
 *  existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamPitchControllerMaxSpeed;


/**
 *  Key string in `capabilities` associated with whether the gimbal's manual control
 *  yaw axis max speed can be adjusted. The corresponding value in `capabilities` is
 *  an instance of `DJIParamCapabilityMinMax` meaning both the feature's existence
 *  as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamYawControllerMaxSpeed;


/**
 *  Key string in `capabilities` associated with whether the gimbal's pitch axis
 *  SmoothTrack can be toggled. The corresponding value in `capabilities` is an
 *  instance of `DJIParamCapability`. Ronin-MX cannot toggle the SmoothTrack
 *  functionality and it is always enabled.
 */
extern NSString *const DJIGimbalParamPitchSmoothTrackEnabled;


/**
 *  Key string in `capabilities` associated with whether the gimbal's yaw axis
 *  SmoothTrack can be toggled. The corresponding value in `capabilities` is an
 *  instance of `DJIParamCapability`. Ronin-MX cannot toggle the SmoothTrack
 *  functionality and it is always enabled.
 */
extern NSString *const DJIGimbalParamYawSmoothTrackEnabled;


/**
 *  Key string in `capabilities` associated with whether the gimbal's pitch axis
 *  SmoothTrack acceleration can be adjusted. The corresponding value in
 *  `capabilities` is an instance of `DJIParamCapabilityMinMax` meaning both the
 *  feature's existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamPitchSmoothTrackAcceleration;


/**
 *  Key string in `capabilities` associated with whether the gimbal's yaw axis
 *  SmoothTrack acceleration can be adjusted. The corresponding value in
 *  `capabilities` is an instance of `DJIParamCapabilityMinMax` meaning both the
 *  feature's existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamYawSmoothTrackAcceleration;


/**
 *  Key string in `capabilities` associated with whether the gimbal's pitch axis
 *  SmoothTrack speed can be adjusted. The corresponding value in `capabilities` is
 *  an instance of `DJIParamCapabilityMinMax` meaning both the feature's existence
 *  as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamPitchSmoothTrackSpeed;


/**
 *  Key string in `capabilities` associated with whether the gimbal's yaw axis
 *  SmoothTrack speed can be adjusted. The corresponding value in `capabilities` is
 *  an instance of `DJIParamCapabilityMinMax` meaning both the feature's existence
 *  as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamYawSmoothTrackSpeed;


/**
 *  Key string in `capabilities` associated with whether the gimbal's pitch axis
 *  SmoothTrack deadband can be adjusted. The corresponding value in `capabilities`
 *  is an instance of `DJIParamCapabilityMinMax` meaning both the feature's
 *  existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamPitchSmoothTrackDeadband;


/**
 *  Key string in `capabilities` associated with whether the gimbal's yaw axis
 *  SmoothTrack deadband can be adjusted. The corresponding value in `capabilities`
 *  is an instance of `DJIParamCapabilityMinMax` meaning both the feature's
 *  existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamYawSmoothTrackDeadband;


/**
 *  Key string in `capabilities` associated with whether the gimbal's pitch up
 *  endpoint can be adjusted. The corresponding value in `capabilities` is an
 *  instance of `DJIParamCapabilityMinMax` meaning both the feature's existence as
 *  well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamPitchUpEndpoint;


/**
 *  Key string in `capabilities` associated with whether the gimbal's pitch down
 *  endpoint can be adjusted. The corresponding value in `capabilities` is an
 *  instance of `DJIParamCapabilityMinMax` meaning both the feature's existence as
 *  well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamPitchDownEndpoint;


/**
 *  Key string in `capabilities` associated with whether the gimbal's yaw left
 *  endpoint can be adjusted. The corresponding value in `capabilities` is an
 *  instance of `DJIParamCapabilityMinMax` meaning both the feature's existence as
 *  well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamYawLeftEndpoint;


/**
 *  Key string in `capabilities` associated with whether the gimbal's yaw right
 *  endpoint can be adjusted. The corresponding value in `capabilities` is an
 *  instance of `DJIParamCapabilityMinMax` meaning both the feature's existence as
 *  well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamYawRightEndpoint;


/**
 *  Key string in `capabilities` associated with whether the gimbal's pitch axis
 *  motor control stiffness can be adjusted. The corresponding value in
 *  `capabilities` is an instance of `DJIParamCapabilityMinMax` meaning both the
 *  feature's existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamPitchMotorControlStiffness;


/**
 *  Key string in `capabilities` associated with whether the gimbal's yaw axis motor
 *  control stiffness can be adjusted. The corresponding value in `capabilities` is
 *  an instance of `DJIParamCapabilityMinMax` meaning both the feature's existence
 *  as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamYawMotorControlStiffness;


/**
 *  Key string in `capabilities` associated with whether the gimbal's roll axis
 *  motor control stiffness can be adjusted. The corresponding value in
 *  `capabilities` is an instance of `DJIParamCapabilityMinMax` meaning both the
 *  feature's existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamRollMotorControlStiffness;


/**
 *  Key string in `capabilities` associated with whether the gimbal's pitch axis
 *  motor control strength can be adjusted. The corresponding value in
 *  `capabilities` is an instance of `DJIParamCapabilityMinMax` meaning both the
 *  feature's existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamPitchMotorControlStrength;


/**
 *  Key string in `capabilities` associated with whether the gimbal's yaw axis motor
 *  control strength can be adjusted. The corresponding value in `capabilities` is
 *  an instance of `DJIParamCapabilityMinMax` meaning both the feature's existence
 *  as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamYawMotorControlStrength;


/**
 *  Key string in `capabilities` associated with whether the gimbal's roll axis
 *  motor control strength can be adjusted. The corresponding value in
 *  `capabilities` is an instance of `DJIParamCapabilityMinMax` meaning both the
 *  feature's existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamRollMotorControlStrength;


/**
 *  Key string in `capabilities` associated with whether the gimbal's pitch axis
 *  motor control gyro filtering can be adjusted. The corresponding value in
 *  `capabilities` is an instance of `DJIParamCapabilityMinMax` meaning both the
 *  feature's existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamPitchMotorControlGyroFilteringFactor;


/**
 *  Key string in `capabilities` associated with whether the gimbal's yaw axis motor
 *  control gyro filtering can be adjusted. The corresponding value in
 *  `capabilities` is an instance of `DJIParamCapabilityMinMax` meaning both the
 *  feature's existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamYawMotorControlGyroFilteringFactor;


/**
 *  Key string in `capabilities` associated with whether the gimbal's roll axis
 *  motor control gyro filtering can be adjusted. The corresponding value in
 *  `capabilities` is an instance of `DJIParamCapabilityMinMax` meaning both the
 *  feature's existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamRollMotorControlGyroFilteringFactor;


/**
 *  Key string in `capabilities` associated with whether the gimbal's pitch axis
 *  motor control "precontrol" can be adjusted. The corresponding value in
 *  `capabilities` is an instance of `DJIParamCapabilityMinMax` meaning both the
 *  feature's existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamPitchMotorControlPreControl;


/**
 *  Key string in `capabilities` associated with whether the gimbal's yaw axis motor
 *  control "precontrol" can be adjusted. The corresponding value in `capabilities`
 *  is an instance of `DJIParamCapabilityMinMax` meaning both the feature's
 *  existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamYawMotorControlPreControl;


/**
 *  Key string in `capabilities` associated with whether the gimbal's roll axis
 *  motor control "precontrol" can be adjusted. The corresponding value in
 *  `capabilities` is an instance of `DJIParamCapabilityMinMax` meaning both the
 *  feature's existence as well as its possible range (unitless) is returned.
 */
extern NSString *const DJIGimbalParamRollMotorControlPreControl;

NS_ASSUME_NONNULL_END

