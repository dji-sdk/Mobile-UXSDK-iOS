//
//  DJIGimbal.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIBaseComponent.h>
#import <DJISDK/DJIGimbalBaseTypes.h>
#import <DJISDK/DJIGimbalState.h>
#import <DJISDK/DJIGimbalMovementSettings.h>

@class DJIGimbal;

NS_ASSUME_NONNULL_BEGIN

/*********************************************************************************/
#pragma mark - DJIGimbalDelegate
/*********************************************************************************/


/**
 *  This protocol provides delegate methods to receive the updated state and user
 *  configuration.
 */
@protocol DJIGimbalDelegate <NSObject>

@optional


/**
 *  Updates the gimbal's current state.
 *  
 *  @param gimbal The gimbal object.
 *  @param state The gimbal state.
 */
- (void)gimbal:(DJIGimbal *)gimbal didUpdateState:(DJIGimbalState *)state;


/**
 *  Update the gimbal's user configuration data. This method is only supported by
 *  Osmo series.
 *  
 *  @param gimbal An instance of `DJIGimbal`.
 *  @param settings An instance of `DJIGimbalMovementSettings`.
 */
- (void)gimbal:(DJIGimbal *)gimbal didUpdateMovementSettings:(DJIGimbalMovementSettings *)settings;


/**
 *  Update the gimbal's remaining energy in percentage.
 *  
 *  @param gimbal An instance of `DJIGimbal`.
 *  @param remainingChargeInPercent An NSInteger value.
 */
- (void)gimbal:(DJIGimbal *)gimbal didUpdateBatteryRemainingCharge:(NSInteger)remainingChargeInPercent;

@end

/*********************************************************************************/
#pragma mark - DJIGimbal
/*********************************************************************************/


/**
 *  This class provides multiple methods to control the gimbal. These include
 *  setting the gimbal work mode, rotating the gimbal with angle, starting the
 *  gimbal auto calibration, etc. This object is available from the `DJIAircraft` or
 *  `DJIHandheld` object which is a subclass of `DJIBaseProduct`.
 */
@interface DJIGimbal : DJIBaseComponent


/**
 *  Returns the delegate of DJIGimbal.
 */
@property(nonatomic, weak) id<DJIGimbalDelegate> delegate;


/**
 *  Returns the gimbal's features and possible range of settings. Each dictionary
 *  key is a possible gimbal feature and uses the DJIGimbalParam prefix. The value
 *  for each key is an instance of `DJIParamCapability` or its sub-classes. The
 *  `isSupported` property can be used to query if a feature is supported by the
 *  gimbal and the `min` and `max` properties of `DJIParamCapabilityMinMax` can be
 *  used to query the valid range for the setting. When a feature is not supported,
 *  the values for `min` and `max` are undefined.
 */
@property(nonatomic, readonly) NSDictionary *_Nonnull capabilities;

/*********************************************************************************/
#pragma mark Set Gimbal Work Mode
/*********************************************************************************/


/**
 *  Sets the gimbal's work mode. See enum `DJIGimbalMode` for modes.
 *  
 *  @param mode Gimbal work mode to be set.
 *  @param completion Remote execution result error block.
 */
- (void)setMode:(DJIGimbalMode)mode
 withCompletion:(DJICompletionBlock)completion;

/*********************************************************************************/
#pragma mark Gimbal Control
/*********************************************************************************/

/**
 *  Rotate gimbal's pitch, roll, and yaw with `DJIGimbalRotation`. For X5S, X4S and
 *  X7, rotating the gimbal with mode `DJIGimbalRotationModeRelativeAngle` or
 *  `DJIGimbalRotationModeAbsoluteAngle`, will reset the gimbal mode to
 *  `DJIGimbalModeFree`.
 *  
 *  @param rotation An instance of `DJIGimbalRotation`.
 *  @param completion Completion block.
 */
- (void)rotateWithRotation:(DJIGimbalRotation *)rotation
                completion:(DJICompletionBlock)completion;


/**
 *  Resets the gimbal. The behaviors are product-dependent. Osmo series (e.g. Osmo,
 *  Osmo Pro): The gimbal's pitch and yaw will be set to the origin, which is the
 *  standard position for the gimbal. Phantom series (e.g. Phantom 3 Professional,
 *  Phantom 4 series): The first call sets gimbal to point down vertically to the
 *  earth. The second call sets gimbal to the standard position. Other products
 *  (e.g. Inspire 1): Only the gimbal's pitch will the set to the origin.
 *  
 *  @param completion Remote execution result error block.
 */
- (void)resetWithCompletion:(DJICompletionBlock)completion;

/*********************************************************************************/
#pragma mark Gimbal Calibration
/*********************************************************************************/


/**
 *  Starts calibrating the gimbal. The product should be stationary (not flying, or
 *  being held) and horizontal during calibration. For gimbal's with adjustable
 *  payloads, the payload should be present and balanced before doing a calibration.
 *  For Osmo Mobile series, user should double-click the trigger (or mode button on
 *  Osmo Mobile 2) or restart the device to re-center the gimbal after the
 *  calibration.
 *  
 *  @param completion Remote execution result error block.
 */
- (void)startCalibrationWithCompletion:(DJICompletionBlock)completion;


/**
 *  The gimbal roll can be fine tuned with a custom offset. The range for the custom
 *  offset is [-2.0, 2.0] degrees. If the offset is negative, the gimbal will be
 *  fine tuned the specified number of degrees in the counterclockwise direction.
 *  
 *  @param offset Fine-tuned offset, in degrees, to be tuned.
 *  @param completion Completion block.
 */
- (void)fineTuneRollInDegrees:(float)offset withCompletion:(DJICompletionBlock)completion;


/**
 *  The gimbal pitch can be fine tuned with a custom offset. The range for the
 *  custom offset is [-2.0, 2.0] degrees. If the offset is negative, the gimbal will
 *  be fine tuned the specified number of degrees in the counterclockwise direction.
 *  It is only supported by Spark and Mavic 2 Series.
 *  
 *  @param offset Fine-tuned offset, in degrees, to be tuned.
 *  @param completion Completion block.
 */
- (void)fineTunePitchInDegrees:(float)offset withCompletion:(DJICompletionBlock)completion;


/**
 *  The gimbal yaw can be fine tuned with a custom offset. The range for the custom
 *  offset is [-2.0, 2.0] degrees. If the offset is negative, the gimbal will be
 *  fine tuned the specified number of degrees in the counterclockwise direction. It
 *  is only supported by Mavic Air and Mavic 2 Series.
 *  
 *  @param offset Fine-tuned offset, in degrees, to be tuned.
 *  @param completion Completion block.
 */
- (void)fineTuneYawInDegrees:(float)offset withCompletion:(DJICompletionBlock)completion;


/**
 *  Starts testing the balance of the gimbal payload. For gimbals that allow
 *  payloads to be changed, a balance test should be performed to ensure the camera
 *  is mounted correctly. The product should be stationary (not flying, or being
 *  held) and horizontal during testing. See `DJIGimbalState` for the test result.
 *  
 *  @param completion Completion block that receives the execution result. The completion block will return when the balance test is successfully started.
 */
- (void)startBalanceTestWithCompletion:(DJICompletionBlock)completion;

/*********************************************************************************/
#pragma mark - Gimbal Advanced Setting
/*********************************************************************************/


/**
 *  Sets the movement settings profile. The movement settings profile has options
 *  for both preset and custom profiles for SmoothTrack and Controller settings.
 *  Settings for SmoothTrack and Controller can only be set manually when using a
 *  custom profile.
 *  
 *  @param profile Profile to set.
 *  @param completion Completion block that receives the execution result.
 */
- (void)setMovementSettingsProfile:(DJIGimbalMovementSettingsProfile)profile
                    withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the advanced settings profile. Use `DJIGimbalMovementSettingsProfile` to
 *  check if it is supported by the gimbal.
 *  
 *  @param profile The advanced settings profile.
 *  @param error Error retrieving the value.
 *  @param completion Completion block that receives the execution result.
 */
- (void)getMovementSettingsProfileWithCompletion:(void (^_Nonnull)(DJIGimbalMovementSettingsProfile profile,
                                                                   NSError *_Nullable error))completion;


/**
 *  Restores the gimbal's settings to factory settings.
 *  
 *  @param completion The completion block that receives execution result.
 */
- (void)restoreFactorySettings:(DJICompletionBlock)completion;

/*********************************************************************************/
#pragma mark Gimbal Range Extension
/*********************************************************************************/


/**
 *  Extends the pitch range of gimbal. If extended, the gimbal's pitch control range
 *  can be [-30, 90], otherwise, it's [0, 90]. Use
 *  `DJIGimbalParamPitchRangeExtensionEnabled` to check if it is supported by the
 *  gimbal.
 *  
 *  @param isEnabled Whether the pitch range should be extended
 *  @param completion The completion block that receives execution result.
 */
- (void)setPitchRangeExtensionEnabled:(BOOL)isEnabled
                       withCompletion:(DJICompletionBlock)completion;


/**
 *  Get the extend gimbal pitch range state. Use
 *  `DJIGimbalParamPitchRangeExtensionEnabled` to check if it is supported by the
 *  gimbal.
 *  
 *  @param isExtended Whether the pitch range should be extended.
 *  @param error Error retrieving the value.
 *  @param completion The completion block that receives execution result.
 */
- (void)getPitchRangeExtensionEnabledWithCompletion:(void (^_Nonnull)(BOOL isExtended,
                                                                      NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Gimbal Motor Control Configuration
/*********************************************************************************/


/**
 *  Configures gimbal's motor control with a preset configuration applicable for
 *  most popular cameras. In order to the optimize the performance, motor control
 *  tuning is still required.
 *  
 *  @param preset The preset configuration to set.
 *  @param completion The completion block that receives execution result.
 */
- (void)applyMotorControlPreset:(DJIGimbalMotorControlPreset)preset
                 withCompletion:(DJICompletionBlock)completion;


/**
 *  Sets the coefficient of speed error control. It can be seen as the coefficient
 *  for the proportional term in the PID controller. Use
 *  `DJIGimbalParamPitchMotorControlStiffness`,
 *  `DJIGimbalParamYawMotorControlStiffness` and
 *  `DJIGimbalParamRollMotorControlStiffness` with `capabilities` to check if the
 *  gimbal supports this feature and the range of possible values (unitless).
 *  
 *  @param stiffness The stiffness value to set.
 *  @param axis The axis that the setting is applied to.
 *  @param completion The completion block that receives execution result.
 */
- (void)setMotorControlStiffness:(NSInteger)stiffness
                          onAxis:(DJIGimbalAxis)axis
                  withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the coefficient of speed error control. It can be seen as the coefficient
 *  for the proportional term in the PID controller. Use
 *  `DJIGimbalParamPitchMotorControlStiffness`,
 *  `DJIGimbalParamYawMotorControlStiffness` and
 *  `DJIGimbalParamRollMotorControlStiffness` with `capabilities` to check if the
 *  gimbal supports this feature and the range of possible values (unitless).
 *  
 *  @param axis The axis to query.
 *  @param stiffness The proportional term in the PID controller.
 *  @param error Error retrieving the value.
 *  @param completion The completion block that receives execution result.
 */
- (void)getMotorControlStiffnessOnAxis:(DJIGimbalAxis)axis
                        withCompletion:(void (^_Nonnull)(NSInteger stiffness,
                                                         NSError *_Nullable error))completion;


/**
 *  Sets the coefficient of attitude accuracy control. It can be seen as the
 *  coefficient for the integral term in the PID controller. Use
 *  `DJIGimbalParamPitchMotorControlStrength`,
 *  `DJIGimbalParamYawMotorControlStrength` and
 *  `DJIGimbalParamRollMotorControlStrength` with `capabilities` to check if the
 *  gimbal supports this feature and the range of possible values (unitless).
 *  
 *  @param strength The strength value to set.
 *  @param axis The axis that the setting is applied to.
 *  @param completion The completion block that receives execution result.
 */
- (void)setMotorControlStrength:(NSInteger)strength
                         onAxis:(DJIGimbalAxis)axis
                 withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the coefficient of attitude accuracy control. It can be seen as the
 *  coefficient for the integral term in the PID controller. Use
 *  `DJIGimbalParamPitchMotorControlStrength`,
 *  `DJIGimbalParamYawMotorControlStrength` and
 *  `DJIGimbalParamRollMotorControlStrength` with `capabilities` to check if the
 *  gimbal supports this feature and the range of possible values (unitless).
 *  
 *  @param axis The axis to query.
 *  @param strength The strength value.
 *  @param error Error retrieving the value.
 *  @param completion The completion block that receives execution result.
 */
- (void)getMotorControlStrengthOnAxis:(DJIGimbalAxis)axis
                       withCompletion:(void (^_Nonnull)(NSInteger strength,
                                                        NSError *_Nullable error))completion;


/**
 *  Sets the coefficient of denoising the output. Use
 *  `DJIGimbalParamPitchMotorControlGyroFilteringFactor`,
 *  `DJIGimbalParamYawMotorControlGyroFilteringFactor` and
 *  `DJIGimbalParamRollMotorControlGyroFilteringFactor` with `capabilities` to check
 *  if the gimbal supports this feature and the range of possible values (unitless).
 *  
 *  @param filteringFactor The gyro filtering value to set.
 *  @param axis The axis that the setting is applied to.
 *  @param completion Asynchronous execution result.
 */
- (void)setMotorControlGyroFilteringFactor:(NSInteger)filteringFactor
                                    onAxis:(DJIGimbalAxis)axis
                            withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the coefficient of denoising the output. Use
 *  `DJIGimbalParamPitchMotorControlGyroFilteringFactor`,
 *  `DJIGimbalParamYawMotorControlGyroFilteringFactor` and
 *  `DJIGimbalParamRollMotorControlGyroFilteringFactor` with `capabilities` to check
 *  if the gimbal supports this feature and the range of possible values (unitless).
 *  
 *  @param axis The axis to query.
 *  @param filteringFactor The smoothing factor.
 *  @param error Error retrieving the value.
 *  @param completion The completion block that receives execution result.
 */
- (void)getMotorControlGyroFilteringFactorOnAxis:(DJIGimbalAxis)axis
                                  withCompletion:(void (^_Nonnull)(NSInteger filteringFactor,
                                                                   NSError *_Nullable error))completion;


/**
 *  Sets the value for pre-adjust. It can be seen as the coefficient for the
 *  derivative term in the PID controller. Use
 *  `DJIGimbalParamPitchMotorControlPreControl`,
 *  `DJIGimbalParamYawMotorControlPreControl` and
 *  `DJIGimbalParamRollMotorControlPreControl` with `capabilities` to check if the
 *  gimbal supports this feature and the range of possible values (unitless).
 *  
 *  @param axis The axis that the setting is applied to.
 *  @param preControl The Precontrol value to set.
 *  @param completion Asynchronous execution result.
 */
- (void)setMotorControlPreControl:(NSInteger)preControl
                           onAxis:(DJIGimbalAxis)axis
                   withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the value for pre-adjust. It can be seen as the coefficient for the
 *  derivative term in the PID controller. Only supported by Ronin-MX. Use
 *  `DJIGimbalParamPitchMotorControlPreControl`,
 *  `DJIGimbalParamYawMotorControlPreControl` and
 *  `DJIGimbalParamRollMotorControlPreControl` with `capabilities` to check if the
 *  gimbal supports this feature and the range of possible values (unitless).
 *  
 *  @param axis The axis to query.
 *  @param preControl The derivative term in the PID controller.
 *  @param error Error retrieving the value.
 *  @param completion The completion block that receives execution result.
 */
- (void)getMotorControlPreControlOnAxis:(DJIGimbalAxis)axis
                         withCompletion:(void (^_Nonnull)(NSInteger preControl,
                                                          NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Gimbal Controller Setting
/*********************************************************************************/


/**
 *  Sets physical controller (e.g. the joystick on Osmo or the remote controller of
 *  the aircraft) deadband on an axis. A larger deadband requires more controller
 *  movement to start gimbal motion. Use `DJIGimbalParamYawControllerDeadband` and
 *  `DJIGimbalParamPitchControllerDeadband` with `capabilities` to check if the
 *  gimbal supports this feature and the range of possible values (unitless).
 *  
 *  @param deadband The deadband value to be set.
 *  @param axis The axis that the setting will be applied to.
 *  @param completion The completion block that receives execution result.
 */
- (void)setControllerDeadband:(NSInteger)deadband
                       onAxis:(DJIGimbalAxis)axis
               withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets physical controller deadband value on an axis. A larger deadband requires
 *  more controller movement to start gimbal motion. Use
 *  `DJIGimbalParamYawControllerDeadband` and
 *  `DJIGimbalParamPitchControllerDeadband` with `capabilities` to check if the
 *  gimbal supports this feature and the range of possible values (unitless).
 *  
 *  @param axis The axis to query.
 *  @param deadband The deadband value.
 *  @param error Error retrieving the value.
 *  @param completion The completion block that receives execution result.
 */
- (void)getControllerDeadbandOnAxis:(DJIGimbalAxis)axis
                     withCompletion:(void (^_Nonnull)(NSInteger deadband,
                                                      NSError *_Nullable error))completion;


/**
 *  Sets physical controller (e.g. the joystick on Osmo or the remote controller of
 *  the aircraft) speed on an axis. Speed setting controls the mapping between the
 *  movement of the controller and the gimbal speed. Use
 *  `DJIGimbalParamYawControllerSpeedCoefficient` and
 *  `DJIGimbalParamPitchControllerSpeedCoefficient` with `capabilities` to check if
 *  the gimbal supports this feature and the range of possible values (unitless).
 *  
 *  @param speedCoefficient The speed value to be set.
 *  @param axis The axis that the setting will be applied to.
 *  @param completion Asynchronous execution result.
 */
- (void)setControllerSpeedCoefficient:(NSInteger)speedCoefficient
                               onAxis:(DJIGimbalAxis)axis
                       withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets physical controller speed value on an axis. Speed setting controls the
 *  mapping between the movement of the controller and the gimbal speed. Use
 *  `DJIGimbalParamYawControllerSpeedCoefficient` and
 *  `DJIGimbalParamPitchControllerSpeedCoefficient` with `capabilities` to check if
 *  the gimbal supports this feature and the range of possible values (unitless).
 *  
 *  @param axis The axis to query.
 *  @param speedCoefficient The coefficient value.
 *  @param error Error retrieving the value.
 *  @param completion The completion block that receives execution result.
 */
- (void)getControllerSpeedCoefficientOnAxis:(DJIGimbalAxis)axis
                             withCompletion:(void (^_Nonnull)(NSInteger speedCoefficient,
                                                              NSError *_Nullable error))completion;


/**
 *  Sets physical controller (e.g. the joystick on Osmo or the remote controller of
 *  the aircraft) smoothing on an axis. Smoothing controls the deceleration of the
 *  gimbal. Use `DJIGimbalParamYawControllerSmoothingFactor` and
 *  `DJIGimbalParamPitchControllerSmoothingFactor` with `capabilities` to check if
 *  the gimbal supports this feature and the range of possible values (unitless).
 *  
 *  @param smoothingFactor The smoothing value to be set.
 *  @param axis The axis that the setting will be applied to.
 *  @param completion The completion block that receives execution result.
 */
- (void)setControllerSmoothingFactor:(NSInteger)smoothingFactor
                              onAxis:(DJIGimbalAxis)axis
                      withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets physical controller smoothing value on an axis. Smoothing controls the
 *  deceleration of the gimbal. Use `DJIGimbalParamYawControllerSmoothingFactor` and
 *  `DJIGimbalParamPitchControllerSmoothingFactor` with `capabilities` to check if
 *  the gimbal supports this feature and the range of possible values (unitless).
 *  
 *  @param axis The axis to query.
 *  @param smoothingFactor The smoothing value.
 *  @param error Error retrieving the value.
 *  @param completion The completion block that receives execution result.
 */
- (void)getControllerSmoothingFactorOnAxis:(DJIGimbalAxis)axis
                            withCompletion:(void (^_Nonnull)(NSInteger smoothingFactor,
                                                             NSError *_Nullable error))completion;


/**
 *  Gets physical controller max speed value on an axis. It controls the mapping
 *  between the movement of the controller and the gimbal speed. Use
 *  `DJIGimbalParamPitchControllerMaxSpeed` and
 *  `DJIGimbalParamYawControllerMaxSpeed` with "capabilities" to check if the gimbal
 *  supports this feature and the range of possible values (unitless).
 *  
 *  @param maxSpeed The maximum speed to set for one axis.
 *  @param axis The axis that the setting will be applied to.
 *  @param completion The completion block that receives execution result.
 */
- (void)setControllerMaxSpeed:(NSInteger)maxSpeed onAxis:(DJIGimbalAxis)axis withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets physical controller max speed value on an axis. It controls the mapping
 *  between the movement of the controller and the gimbal speed. Use
 *  `DJIGimbalParamPitchControllerMaxSpeed` and
 *  `DJIGimbalParamYawControllerMaxSpeed` with "capabilities" to check if the gimbal
 *  supports this feature and the range of possible values (unitless).
 *  
 *  @param axis The axis to query.
 *  @param maxSpeed The maximum speed of the axis.
 *  @param error Error retrieving the value.
 *  @param completion The completion block that receives execution result.
 */
- (void)getControllerMaxSpeedOnAxis:(DJIGimbalAxis)axis withCompletion:(void (^_Nonnull)(NSInteger maxSpeed,
                                                                                         NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Gimbal Smooth Track Setting
/*********************************************************************************/


/**
 *  Enables SmoothTrack for the axis. Only supported by Osmo. Ronin-MX supports
 *  SmoothTrack but it is always enabled for both pitch axis and yaw axis. Use
 *  `DJIGimbalParamPitchSmoothTrackEnabled` and
 *  `DJIGimbalParamYawSmoothTrackEnabled` with `capabilities` to check if the gimbal
 *  supports this feature.
 *  
 *  @param enabled `YES` to enable SmoothTrack on the axis.
 *  @param axis The axis that the setting will be applied to.
 *  @param completion The completion block that receives execution result.
 */
- (void)setSmoothTrackEnabled:(BOOL)enabled
                       onAxis:(DJIGimbalAxis)axis
               withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets whether an axis has SmoothTrack enabled. Only supported by Osmo. Ronin-MX
 *  supports SmoothTrack but it is always enabled for both pitch axis and yaw axis.
 *  Use `DJIGimbalParamPitchSmoothTrackEnabled` and
 *  `DJIGimbalParamYawSmoothTrackEnabled` with `capabilities` to check if the gimbal
 *  supports this feature.
 *  
 *  @param axis The axis to query.
 *  @param isEnabled YES if smooth track enabled.
 *  @param error Error retrieving the value.
 *  @param completion The completion block that receives execution result.
 */
- (void)getSmoothTrackEnabledOnAxis:(DJIGimbalAxis)axis
                     withCompletion:(void (^_Nonnull)(BOOL isEnabled,
                                                      NSError *_Nullable error))completion;


/**
 *  Sets gimbal SmoothTrack catch up speed on an axis. SmoothTrack speed determines
 *  how fast the gimbal will catch up with a large, translated handle movement. Use
 *  `DJIGimbalParamPitchSmoothTrackSpeed` and `DJIGimbalParamYawSmoothTrackSpeed`
 *  with `capabilities` to check if the gimbal supports this feature and the range
 *  of possible values (unitless).
 *  
 *  @param speed SmoothTrack speed [0,100].
 *  @param axis The axis that the setting will be applied to.
 *  @param completion The completion block that receives execution result.
 */
- (void)setSmoothTrackSpeed:(NSInteger)speed
                     onAxis:(DJIGimbalAxis)axis
             withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets gimbal SmoothTrack speed on an axis. SmoothTrack speed determines how fast
 *  the gimbal will catch up with a large, translated handle movement. Use
 *  `DJIGimbalParamPitchSmoothTrackSpeed` and `DJIGimbalParamYawSmoothTrackSpeed`
 *  with `capabilities` to check if the gimbal supports this feature and the range
 *  of possible values (unitless).
 *  
 *  @param axis The axis to query.
 *  @param speed The gimbal smoothTrack speed.
 *  @param error Error retrieving the value.
 *  @param completion The completion block that receives execution result.
 */
- (void)getSmoothTrackSpeedOnAxis:(DJIGimbalAxis)axis
                   withCompletion:(void (^_Nonnull)(NSInteger speed,
                                                    NSError *_Nullable error))completion;


/**
 *  Sets SmoothTrack deadband on an axis. A larger deadband requires more handle
 *  movement to translate into gimbal motion. Use
 *  `DJIGimbalParamPitchSmoothTrackDeadband` and
 *  `DJIGimbalParamYawSmoothTrackDeadband` with `capabilities` to check if the
 *  gimbal supports this feature and the range of possible values in degrees.
 *  
 *  @param deadband SmoothTrack deadband [0,90].
 *  @param axis The axis that the setting will be applied to.
 *  @param completion The completion block that receives execution result.
 */
- (void)setSmoothTrackDeadband:(NSInteger)deadband
                        onAxis:(DJIGimbalAxis)axis
                withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets SmoothTrack deadband on an axis. A larger deadband requires more handle
 *  movement to translate into gimbal motion. Use
 *  `DJIGimbalParamPitchSmoothTrackDeadband` and
 *  `DJIGimbalParamYawSmoothTrackDeadband` with `capabilities` to check if the
 *  gimbal supports this feature and the range of possible values in degrees.
 *  
 *  @param axis Gimbal axis.
 *  @param deadband The deadband value.
 *  @param error Error retrieving the value.
 *  @param completion The completion block that receives execution result.
 */
- (void)getSmoothTrackDeadbandOnAxis:(DJIGimbalAxis)axis
                      withCompletion:(void (^_Nonnull)(NSInteger deadband,
                                                       NSError *_Nullable error))completion;


/**
 *  Sets SmoothTrack acceleration on an axis. Acceleration determines how closely
 *  the camera will follow the translated yaw handle movement. Use
 *  `DJIGimbalParamPitchSmoothTrackAcceleration` and
 *  `DJIGimbalParamYawSmoothTrackAcceleration` with `capabilities` to check if the
 *  gimbal supports this feature and the range of possible values (unitless).
 *  
 *  @param acceleration SmoothTrack acceleration [0,30].
 *  @param axis The axis that the setting will be applied to.
 *  @param completion The completion block that receives execution result.
 */
- (void)setSmoothTrackAcceleration:(NSInteger)acceleration
                            onAxis:(DJIGimbalAxis)axis
                    withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets SmoothTrack acceleration on an axis. Acceleration determines how closely
 *  the camera will follow the translated yaw handle movement. Use
 *  `DJIGimbalParamPitchSmoothTrackAcceleration` and
 *  `DJIGimbalParamYawSmoothTrackAcceleration` with `capabilities` to check if the
 *  gimbal supports this feature and the range of possible values (unitless).
 *  
 *  @param axis Gimbal axis.
 *  @param acceleration The acceleration value.
 *  @param error Error retrieving the value.
 *  @param completion The completion block that receives execution result.
 */
- (void)getSmoothTrackAccelerationOnAxis:(DJIGimbalAxis)axis
                          withCompletion:(void (^_Nonnull)(NSInteger acceleration,
                                                           NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Gimbal Endpoint Setting
/*********************************************************************************/


/**
 *  Endpoint settings determine the farthest points to which the gimbal will rotate
 *  during manual controller input. Only supported by Ronin-MX. Use
 *  `DJIGimbalParamPitchUpEndpoint`, `DJIGimbalParamPitchDownEndpoint`,
 *  `DJIGimbalParamYawLeftEndpoint` and `DJIGimbalParamYawRightEndpoint` in
 *  `capabilities` to check if the gimbal supports this feature and what the valid
 *  range of endpoints are.
 *  
 *  @param endpoint The endpoint value to set.
 *  @param direction The direction that the setting will be applied to.
 *  @param completion The completion block that receives execution result.
 */
- (void)setEndpoint:(NSInteger)endpoint
       forDirection:(DJIGimbalEndpointDirection)direction
     withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the farthest points to which the gimbal will rotate during manual
 *  controller input. Use `DJIGimbalParamPitchUpEndpoint`,
 *  `DJIGimbalParamPitchDownEndpoint`, `DJIGimbalParamYawLeftEndpoint` and
 *  `DJIGimbalParamYawRightEndpoint` with `capabilities` to check if the gimbal
 *  supports this feature.
 *  
 *  @param direction The endpoint direction.
 *  @param endpoint The endpoint value.
 *  @param error Error retrieving the value.
 *  @param completion The completion block that receives execution result.
 */
- (void)getEndpointForDirection:(DJIGimbalEndpointDirection)direction
                 withCompletion:(void (^_Nonnull)(NSInteger endpoint,
                                                  NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Others
/*********************************************************************************/


/**
 *  Turns on and off the gimbal motors. `NO` means the gimbal power remains on,
 *  however the motors will not work.
 *  
 *  @param enabled `YES` to enable the motor.
 *  @param completion The completion block that receives execution result.
 */
- (void)setMotorEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether the gimbal motors are enabled to work or not.
 *  
 *  @param enabled The enabled value.
 *  @param error Error retrieving the value.
 *  @param completion The completion block that receives execution result.
 */
- (void)getMotorEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled,
                                                        NSError *_Nullable error))completion;


/**
 *  Resets gimbal position to selfie setup. If the gimbal yaw is not at 180
 *  degrees, then calling this method will rotate the gimbal yaw to 180  degrees
 *  (effectively pointing the camera to the person holding the gimbal).  If the
 *  gimbal yaw is at 180 degrees, then the gimbal will rotate in yaw to 0 degrees.
 *  It's only supported by DJI OSMO, OSMO Pro and OSMO Raw.
 *  
 *  @param completion The completion block that receives execution result.
 */
- (void)toggleSelfieWithCompletion:(DJICompletionBlock)completion;


/**
 *  Inverts the physical control for gimbal movement on an axis. The setting can
 *  only be applied to the pitch or yaw axis.
 *  
 *  @param enabled `YES` to enable inverted control.
 *  @param axis The axis that the setting will be applied to.
 *  @param completion The completion block that receives execution result.
 */
- (void)setInvertedControlEnabled:(BOOL)enabled
                           onAxis:(DJIGimbalAxis)axis
                   withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether the physical control is inverted for gimbal movement on an
 *  axis. The setting can only be applied to the pitch or yaw axis.
 *  
 *  @param axis The axis to query.
 *  @param enabled The enabled value.
 *  @param error Error retrieving the value.
 *  @param completion The completion block that receives execution result.
 */
-(void)getInvertedControlEnabledOnAxis:(DJIGimbalAxis)axis
                        withCompletion:(void (^_Nonnull)(BOOL enabled,
                                                         NSError *_Nullable error))completion;


/**
 *  Synchronizes the attitude of port (left) gimbal and starboard (right) gimbal. It
 *  is only valid when both gimbals are connected. If only 1 gimbal is connected,
 *  this setting will be reset to `NO`. Enables this setting will reset
 *  `getControllingGimbalIndexWithCompletion` to index 0. It is only supported by
 *  M210 and M210 RTK.
 *  
 *  @param enabled `YES` to enable the synchronization.
 *  @param completion The completion block that receives execution result.
 */
- (void)setAttitudeSynchronizationEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether both gimbals' attitudes are synchronized. If only 1 gimbal is
 *  connected, this setting will be reset to `NO`. It is only supported by M210 and
 *  M210 RTK.
 *  
 *  @param enabled `YES` to enable the synchronization.
 *  @param error The encountered error if any.
 *  @param completion The completion block that receives execution result.
 */
- (void)getAttitudeSynchronizationEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Enables this to make the gimbal respond to the controller command to rotate
 *  aircraft's heading.  Enabling this setting makes gimbal rotate simultaneously
 *  with aircraft's heading when the user  is controlling the aircraft's heading
 *  with the remote controller.
 *  
 *  @param enabled `YES` to enable yaw simultaneous follow.
 *  @param completion The completion block that receives execution result.
 */
- (void)setYawSimultaneousFollowEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether yaw simultaneous follow is enabled. Enabling this setting
 *  makes gimbal rotate  simultaneously with aircraft's heading when the user is
 *  controlling the aircraft's heading with the remote controller.
 *  
 *  @param enabled `YES` if it is enabled.
 *  @param error The encountered error if any.
 *  @param completion The completion block that receives execution result.
 */
- (void)getYawSimultaneousFollowEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
