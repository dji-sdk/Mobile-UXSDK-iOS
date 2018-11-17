//
//  DJIGimbalKey.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import "DJIKey.h"

NS_ASSUME_NONNULL_BEGIN

EXTERN_KEY NSString *const DJIGimbalComponent;
EXTERN_KEY NSString *const DJIGimbalParamCapabilities;
EXTERN_KEY NSString *const DJIGimbalParamAttitudeYawRelativeToAircraft;
EXTERN_KEY NSString *const DJIGimbalParamAttitudeInDegrees;
EXTERN_KEY NSString *const DJIGimbalParamReset;

EXTERN_KEY NSString *const DJIGimbalParamIsAttitudeReset;
EXTERN_KEY NSString *const DJIGimbalParamIsCalibrationSuccessful;
EXTERN_KEY NSString *const DJIGimbalParamIsCalibrating;
EXTERN_KEY NSString *const DJIGimbalParamCalibrationProgress;
EXTERN_KEY NSString *const DJIGimbalParamIsCalibratingStateDependProgress;
EXTERN_KEY NSString *const DJIGimbalParamIsPitchAtStop;
EXTERN_KEY NSString *const DJIGimbalParamIsRollAtStop;
EXTERN_KEY NSString *const DJIGimbalParamIsYawAtStop;
EXTERN_KEY NSString *const DJIGimbalParamIsGimbalOverloaded;

EXTERN_KEY NSString *const DJIGimbalParamMode;
EXTERN_KEY NSString *const DJIGimbalParamRotate;
EXTERN_KEY NSString *const DJIGimbalParamStartCalibration;
EXTERN_KEY NSString *const DJIGimbalParamFineTuneRollInDegrees;
EXTERN_KEY NSString *const DJIGimbalParamFineTunePitchInDegrees;
EXTERN_KEY NSString *const DJIGimbalParamStartBalanceTest;
EXTERN_KEY NSString *const DJIGimbalParamMovementSettingsProfile;
EXTERN_KEY NSString *const DJIGimbalParamRestoreFactorySettings;
EXTERN_KEY NSString *const DJIGimbalParamPitchRangeExtensionEnabled;
EXTERN_KEY NSString *const DJIGimbalParamApplyMotorControlPreset;

EXTERN_KEY NSString *const DJIGimbalParamPitchMotorControlStiffness;
EXTERN_KEY NSString *const DJIGimbalParamRollMotorControlStiffness;
EXTERN_KEY NSString *const DJIGimbalParamYawMotorControlStiffness;

EXTERN_KEY NSString *const DJIGimbalParamPitchMotorControlStrength;
EXTERN_KEY NSString *const DJIGimbalParamRollMotorControlStrength;
EXTERN_KEY NSString *const DJIGimbalParamYawMotorControlStrength;

EXTERN_KEY NSString *const DJIGimbalParamPitchMotorControlGyroFilteringFactor;
EXTERN_KEY NSString *const DJIGimbalParamRollMotorControlGyroFilteringFactor;
EXTERN_KEY NSString *const DJIGimbalParamYawMotorControlGyroFilteringFactor;

EXTERN_KEY NSString *const DJIGimbalParamPitchMotorControlPreControl;
EXTERN_KEY NSString *const DJIGimbalParamRollMotorControlPreControl;
EXTERN_KEY NSString *const DJIGimbalParamYawMotorControlPreControl;

EXTERN_KEY NSString *const DJIGimbalParamYawControllerDeadband;
EXTERN_KEY NSString *const DJIGimbalParamPitchControllerDeadband;

EXTERN_KEY NSString *const DJIGimbalParamYawControllerSpeedCoefficient;
EXTERN_KEY NSString *const DJIGimbalParamPitchControllerSpeedCoefficient;

EXTERN_KEY NSString *const DJIGimbalParamYawControllerSmoothingFactor;
EXTERN_KEY NSString *const DJIGimbalParamPitchControllerSmoothingFactor;

EXTERN_KEY NSString *const DJIGimbalParamYawSmoothTrackEnabled;
EXTERN_KEY NSString *const DJIGimbalParamPitchSmoothTrackEnabled;

EXTERN_KEY NSString *const DJIGimbalParamYawSmoothTrackSpeed;
EXTERN_KEY NSString *const DJIGimbalParamPitchSmoothTrackSpeed;

EXTERN_KEY NSString *const DJIGimbalParamYawSmoothTrackDeadband;
EXTERN_KEY NSString *const DJIGimbalParamPitchSmoothTrackDeadband;

EXTERN_KEY NSString *const DJIGimbalParamYawSmoothTrackAcceleration;
EXTERN_KEY NSString *const DJIGimbalParamPitchSmoothTrackAcceleration;

EXTERN_KEY NSString *const DJIGimbalParamPitchUpEndpoint;
EXTERN_KEY NSString *const DJIGimbalParamPitchDownEndpoint;
EXTERN_KEY NSString *const DJIGimbalParamYawLeftEndpoint;
EXTERN_KEY NSString *const DJIGimbalParamYawRightEndpoint;

EXTERN_KEY NSString *const DJIGimbalParamMotorEnabled;
EXTERN_KEY NSString *const DJIGimbalParamToggleSelfie;
EXTERN_KEY NSString *const DJIGimbalParamYawInvertedControlEnabled;
EXTERN_KEY NSString *const DJIGimbalParamPitchInvertedControlEnabled;

EXTERN_KEY NSString *const DJIGimbalParamLandingGearProtectionEnabled;
EXTERN_KEY NSString *const DJIGimbalParamStickControlMode;

EXTERN_KEY NSString *const DJIGimbalParamPitchControllerMaxSpeed;
EXTERN_KEY NSString *const DJIGimbalParamYawControllerMaxSpeed;

EXTERN_KEY NSString *const DJIGimbalParamAttitudeSynchronizationEnabled;
EXTERN_KEY NSString *const DJIGimbalParamYawSimultaneousFollowEnabled;


/**
 *  `DJIGimbalKey` is an object providing access to Gimbal attributes.
 */
@interface DJIGimbalKey : DJIKey

@end

NS_ASSUME_NONNULL_END
