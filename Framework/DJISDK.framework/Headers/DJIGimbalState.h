//
//  DJIGimbalState.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#import "DJISDKFoundation.h"
#import "DJIGimbalBaseTypes.h"


/**
 *  This class provides the current state of the gimbal.
 */
@interface DJIGimbalState : NSObject


/**
 *  The current gimbal attitude in degrees. Roll, pitch and yaw are 0 if the gimbal
 *  is level with the aircraft and points in the forward direction of North Pole.
 */
@property(nonatomic, readonly) DJIGimbalAttitude attitudeInDegrees;


/**
 *  This function will return the angle between gimbal and the drone heading.
 */
@property(nonatomic, readonly) double yawRelativeToAircraftHeading;


/**
 *  Returns the gimbal's roll fine-tuned value. The range for the fine-tuned value
 *  is [-10, 10] degrees. If the fine-tune value is negative, the gimbal will be
 *  fine- tuned to the specified number of degrees in the counterclockwise
 *  direction.
 */
@property(nonatomic, readonly) float fineTunedRoll;


/**
 *  Returns the gimbal's pitch fine-tuned value. The range for the fine-tuned value
 *  is [-10, 10] degrees. If the fine-tune value is negative, the gimbal will be
 *  fine-tuned to the specified number of degrees in the downward direction. It is
 *  only supported by Spark.
 */
@property(nonatomic, readonly) float fineTunedPitch;


/**
 *  Returns the gimbal's yaw fine-tuned value. The range for the fine-tuned value is
 *  [-10, 10] degrees. If the fine-tune value is negative, the gimbal will be fine-
 *  tuned to the specified number of degrees in the port (left) direction. Only
 *  supported by DJI Mavic Air.
 */
@property(nonatomic, readonly) float fineTunedYaw;


/**
 *  Returns the gimbal's current work mode.
 */
@property(nonatomic, readonly) DJIGimbalMode mode;

/**
 *  `YES` if the attitude has been reset. If the gimbal is not in the original
 *  position, this value will return `NO`.
 *  @deprecated Not supported by firmware any more.
 */
@property(nonatomic, readonly) BOOL isAttitudeReset DJI_API_DEPRECATED("Not supported by firmware any more. ");


/**
 *  `YES` if the gimbal calibration succeeded.
 */
@property(nonatomic, readonly) BOOL isCalibrationSuccessful;


/**
 *  `YES` if the gimbal is calibrating.
 */
@property(nonatomic, readonly) BOOL isCalibrating;


/**
 *  Current progress (percentage) for calibration.
 */
@property(nonatomic, readonly) NSInteger calibrationProgress;


/**
 *  `YES` if the gimbal's pitch value is at its limit.
 */
@property(nonatomic, readonly) BOOL isPitchAtStop;


/**
 *  `YES` if the gimbal's roll value is at its limit.
 */
@property(nonatomic, readonly) BOOL isRollAtStop;


/**
 *  `YES` if the gimbal's yaw value is at its limit.
 */
@property(nonatomic, readonly) BOOL isYawAtStop;


/**
 *  `YES` if the gimbal is currently testing payload balance.
 */
@property(nonatomic, readonly) BOOL isBalanceTesting;


/**
 *  Returns the pitch axis balance test result.
 */
@property(nonatomic, readonly) DJIGimbalBalanceTestResult pitchBalanceTestResult;


/**
 *  Returns the roll axis balance test result.
 */
@property(nonatomic, readonly) DJIGimbalBalanceTestResult rollBalanceTestResult;


/**
 *  Returns the yaw axis balance test result.
 */
@property(nonatomic, readonly) DJIGimbalBalanceTestResult yawBalanceTestResult;


/**
 *  `YES` if the mobile device is mounted on the gimbal.
 */
@property(nonatomic, readonly) BOOL isMobileDeviceMounted;


/**
 *  `YES` if one of the gimbal motors is overloaded.
 */
@property(nonatomic, readonly) BOOL isMotorOverloaded;


/**
 *  Returns the balance status of the gimbal.
 */
@property(nonatomic, readonly) DJIGimbalBalanceState balanceState;


/**
 *  `YES` if the gimbal is mounted upwards on the aircraft. It is only supported by
 *  M210 and M210 RTK.
 */
@property(nonatomic, readonly) BOOL isMountedUpwards;

@end
