//
//  DJIHandheldController.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIBaseComponent.h>
#import <DJISDK/DJIHandheldControllerBaseTypes.h>

@class DJIWiFiLink;

NS_ASSUME_NONNULL_BEGIN

@class DJIHandheldController;

/*********************************************************************************/
#pragma mark - DJIHandheldControllerDelegate
/*********************************************************************************/


/**
 *  This protocol provides a delegate method to receive the updated power mode of
 *  the handheld controller.
 */
@protocol DJIHandheldControllerDelegate <NSObject>

@optional


/**
 *  Called when the handheld controller's power mode has been updated.
 *  
 *  @param controller The handheld controller that updates the power mode.
 *  @param powerMode The handheld controller's current power mode.
 */
- (void)handheldController:(DJIHandheldController *_Nonnull)controller didUpdatePowerMode:(DJIHandheldPowerMode)powerMode;


/**
 *  Called when the handheld controller's current hardware state (e.g. the state of
 *  the physical buttons and joysticks) has been updated.
 *  
 *  @param controller The handheld controller that updates the hardware state.
 *  @param state The handheld controller's current hardware state.
 */
- (void)handheldController:(DJIHandheldController *_Nonnull)controller didUpdateHardwareState:(DJIHandheldControllerHardwareState *)state;
@end

/*********************************************************************************/
#pragma mark - DJIHandheldController
/*********************************************************************************/


/**
 *  This class contains interfaces related to the hand controller of a handheld
 *  device (such as Osmo). This object is available from the `DJIHandheld` subclass
 *  off `DJIBaseProduct`.
 */
@interface DJIHandheldController : DJIBaseComponent


/**
 *  Returns the `DJIHandheldController` delegate.
 */
@property(nonatomic, weak) id <DJIHandheldControllerDelegate> delegate;


/**
 *  Set the power mode for the handheld controller.
 *  
 *  @param mode The power mode to set. CAUTION! When the mode is `DJIHandheldPowerModeOff`, the handheld product will be shut down and the connection will be broken. The user must then power on the device manually.
 *  @param completion Remote execution result callback block.
 */
- (void)setPowerMode:(DJIHandheldPowerMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Controls the LED of the handheld controller.
 *  
 *  @param command The command to control the LED.
 *  @param completion Remote execution result callback block.
 */
- (void)controlLEDWithCommand:(DJIHandheldControllerLEDCommand *)command
               withCompletion:(DJICompletionBlock)completion;


/**
 *  Enables/disables the gimbal control with the joystick. By default, it is
 *  enabled. The handheld will be reset to the default value  when it reboots or SDK
 *  reinitializes. When gimbal control is disabled, the joystick can be used for
 *  other purposes in an SDK application by reading its position values with
 *  `DJIHandheldStickVerticalDirection` and `DJIHandheldStickHorizontalDirection`.
 *  Only supported in firmware version 1.2.0.40 or above.
 *  
 *  @param enabled `YES` to enable the gimbal control.
 *  @param completion Remote execution result callback block.
 */
- (void)setStickGimbalControlEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  `YES` if gimbal control with the joystick is enabled. Only supported in firmware
 *  version 1.2.0.40 or above.
 *  
 *  @param enabled The enabled value.
 *  @param error Error retrieving the value.
 *  @param completion Remote execution result callback block.
 */
- (void)getStickGimbalControlEnabledWithCompletion:(void(^)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Sets the gimbal's controller mode. The control mode for the gimbal controller
 *  (joystick for Osmo). The total controller deflection is a combination of
 *  horizontal and vertical deflection. This translates to gimbal movement around
 *  the yaw and pitch axes. The gimbal can be set to either move in both yaw and
 *  pitch simultaneously based on horizontal and vertical deflection of the
 *  controller, or move in only yaw or pitch exclusively based on whether horizontal
 *  or vertical deflection is larger.
 *  
 *  @param mode The stick control mode to set.
 *  @param completion The completion block that receives execution result.
 */
- (void)setStickControllerMode:(DJIHandheldControllerStickControlMode)mode
                withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the gimbal's controller mode.
 *  
 *  @param mode The gimbal controller mode.
 *  @param error Error retrieving the value.
 *  @param completion The completion block that receives execution result.
 */
- (void)getStickControllerModeWithCompletion:(void (^_Nonnull)(DJIHandheldControllerStickControlMode mode,
                                                          NSError *_Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
