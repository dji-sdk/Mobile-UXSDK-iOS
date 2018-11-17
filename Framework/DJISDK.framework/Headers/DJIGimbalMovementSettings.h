//
//  DJIGimbalMovementSettings.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DJIGimbalBaseTypes.h"


/**
 *  The current movement settings of the gimbal. These include settings for
 *  SmoothTrack and the Controller.
 */
@interface DJIGimbalMovementSettings : NSObject


/**
 *  Advanced settings profile. `DJIGimbalMovementSettingsProfileFast`,
 *  `DJIGimbalMovementSettingsProfileMedium` and
 *  `DJIGimbalMovementSettingsProfileSlow` are preset profiles. In these profiles,
 *  SmoothTrack and Controller settings cannot be manually changed. When the profile
 *  is `DJIGimbalMovementSettingsProfileCustom1` or
 *  `DJIGimbalMovementSettingsProfileCustom2`, the SmoothTrack and Controller
 *  settings can be manually changed. When a profile is changed from a custom
 *  setting, the current settings will be saved in that custom setting.
 */
@property(nonatomic, readonly) DJIGimbalMovementSettingsProfile profile;


/**
 *  `YES` if gimbal SmoothTrack is enabled for the yaw axis.
 */
@property(nonatomic, readonly) BOOL isYawSmoothTrackEnabled;


/**
 *  `YES` if gimbal SmoothTrack is enabled for the pitch axis.
 */
@property(nonatomic, readonly) BOOL isPitchSmoothTrackEnabled;


/**
 *  SmoothTrack yaw axis speed determines how fast the gimbal will catch up with the
 *  translated yaw handle movement. Range is [0,100].
 */
@property(nonatomic, readonly) NSInteger yawSmoothTrackSpeed;


/**
 *  SmoothTrack pitch axis speed determines how fast the gimbal will catch up with
 *  the translated pitch handle movement. Range is [0,100].
 */
@property(nonatomic, readonly) NSInteger pitchSmoothTrackSpeed;


/**
 *  A larger SmoothTrack yaw axis deadband requires more yaw handle movement to
 *  translate into gimbal motion. Range is [0,90] degrees.
 */
@property(nonatomic, readonly) NSInteger yawSmoothTrackDeadband;


/**
 *  A larger SmoothTrack pitch axis deadband requires more pitch handle movement to
 *  translate into gimbal motion. Range is [0,90] degrees.
 */
@property(nonatomic, readonly) NSInteger pitchSmoothTrackDeadband;


/**
 *  SmoothTrack yaw axis acceleration determines how closely the gimbal's yaw axis
 *  will follow the translated controller movement. Range is [0,30].
 */
@property(nonatomic, readonly) NSInteger yawSmoothTrackAcceleration;


/**
 *  SmoothTrack pitch axis acceleration determines how closely the camera will
 *  follow the translated pitch handle movement. Range is [0,30].
 */
@property(nonatomic, readonly) NSInteger pitchSmoothTrackAcceleration;


/**
 *  Controller yaw axis smoothing controls the deceleration of the gimbal. A small
 *  value will cause the gimbal to stop abruptly. Range is [0,30].
 */
@property(nonatomic, readonly) NSInteger yawControllerSmoothingFactor;


/**
 *  Controller pitch axis smoothing controls the deceleration of the gimbal. A small
 *  value will cause the gimbal to stop abruptly. Range is [0,30].
 */
@property(nonatomic, readonly) NSInteger pitchControllerSmoothingFactor;


/**
 *  Controller yaw axis speed determines how sensitively the gimbal's yaw axis will
 *  follow the controller movement. Range is [0,100].
 */
@property(nonatomic, readonly) NSInteger yawControllerSpeedCoefficient;


/**
 *  Controller pitch axis speed determines how sensitively the gimbal's pitch axis
 *  will follow the controller movement. Range is [0,100].
 */
@property(nonatomic, readonly) NSInteger pitchControllerSpeedCoefficient;

@end
