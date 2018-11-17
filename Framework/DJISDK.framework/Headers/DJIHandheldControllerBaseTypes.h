//
//  DJIHandheldControllerBaseTypes.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DJIStick.h"

NS_ASSUME_NONNULL_BEGIN

/*********************************************************************************/
#pragma mark DJIHandheldPowerMode Type
/*********************************************************************************/


/**
 *  Handheld Power Mode.
 */
typedef NS_ENUM (uint8_t, DJIHandheldPowerMode){
 

    /**
     *  The handheld product is awake. For Osmo, when it is in this mode, all the
     *  components in `DJIHandheld` are accessible.
     */
    DJIHandheldPowerModeOn,
 

    /**
     *  The handheld product is sleeping. The handheld controller keeps the wireless
     *  connection to the mobile device alive but most other components are off. The
     *  power consumption is low in this mode. For Osmo in this mode, only the
     *  `DJIHandheldController`, `DJIAirLink`, and `DJIBattery` are accessible.
     */
    DJIHandheldPowerModeSleeping,
 

    /**
     *  The handheld product is powered off. Once this mode is set the delegate will
     *  receive this mode until the handheld device is shut down completely. It is not
     *  supported by Osmo Mobile.
     */
    DJIHandheldPowerModeOff,
 

    /**
     *  The Handheld Power Mode in unknown.
     */
    DJIHandheldPowerModeUnknown = 0xFF
};


/**
 *  The status of the shutter button and record button on the handheld controller.
 */
typedef NS_ENUM (uint8_t, DJIHandheldRecordAndShutterButtons) {
 

    /**
     *  No buttons have been pressed.
     */
    DJIHandheldRecordAndShutterButtonsIdle,
 

    /**
     *  Only the shutter button was pressed and released.
     */
    DJIHandheldRecordAndShutterButtonsShutterClick,
 

    /**
     *  Only the record button was pressed and released.
     */
    DJIHandheldRecordAndShutterButtonsRecordClick,
 

    /**
     *  The shutter button is being pressed without release.
     */
    DJIHandheldRecordAndShutterButtonsShutterLongClick,
 

    /**
     *  The button status is unknown.
     */
    DJIHandheldRecordAndShutterButtonsUnknown = 0xFF,
};


/**
 *  The status of the shutter button and record button on the handheld controller.
 */
typedef NS_ENUM (uint8_t, DJIHandheldButtonClickEvent) {
 

    /**
     *  Trigger button status is idle.
     */
    DJIHandheldButtonClickEventIdle,
 

    /**
     *  Trigger button is pressed and released.
     */
    DJIHandheldButtonClickEventSingleClick,
 

    /**
     *  Trigger button is pressed twice quickly.
     */
    DJIHandheldButtonClickEventDoubleClick,
 

    /**
     *  Trigger button is pressed three times quickly.
     */
    DJIHandheldButtonClickEventTripleClick,
 

    /**
     *  Trigger button status is unknown.
     */
    DJIHandheldButtonClickEventUnknown = 0xFF,
};


/**
 *  Status of the handheld joystick in vertical direction.
 */
typedef NS_ENUM (uint8_t, DJIHandheldStickVerticalDirection) {
 

    /**
     *  Joystick has no movement in the vertical direction.
     */
    DJIHandheldStickVerticalDirectionMiddle,
 

    /**
     *  Joystick is moved up in the vertical direction.
     */
    DJIHandheldStickVerticalDirectionUp,
 

    /**
     *  Joystick is moved down in the vertical direction.
     */
    DJIHandheldStickVerticalDirectionDown,
 

    /**
     *  Joystick status in the vertical direction is unknown.
     */
    DJIHandheldStickVerticalDirectionUnknown = 0xFF,
};


/**
 *  Status of the handheld joystick in horizontal direction.
 */
typedef NS_ENUM (uint8_t, DJIHandheldStickHorizontalDirection) {
 

    /**
     *  Joystick has no movement in the horizontal direction.
     */
    DJIHandheldStickHorizontalDirectionMiddle,
 

    /**
     *  Joystick is moved left in the horizontal direction.
     */
    DJIHandheldStickHorizontalDirectionLeft,
 

    /**
     *  Joystick is moved right in the horizontal direction.
     */
    DJIHandheldStickHorizontalDirectionRight,
 

    /**
     *  Joystick status in the horizontal direction is unknown.
     */
    DJIHandheldStickHorizontalDirectionUnknown = 0xFF,
};


/**
 *  The control mode for the gimbal physical controller (joystick for Osmo). The
 *  total controller deflection is a combination of horizontal and vertical
 *  deflection. This translates to gimbal movement around the yaw and pitch axes.
 *  The gimbal can be set to either move in both yaw and pitch simultaneously based
 *  on horizontal and vertical deflection of the controller, or move in only yaw or
 *  pitch exclusively based on whether horizontal or vertical deflection is larger.
 */
typedef NS_ENUM (uint8_t, DJIHandheldControllerStickControlMode){


    /**
     *  Gimbal movement will be exclusively in yaw or pitch depending on whether the
     *  controller horizontal or vertical deflection is greater respectively.
     */
    DJIHandheldControllerStickControlModeOneAxis,
 

    /**
     *  Gimbal movement will be in both yaw and pitch simultaneously relative to the
     *  horizontal and vertical deflection of the controller respectively.
     */
    DJIHandheldControllerStickControlModeTwoAxis,
 

    /**
     *  The gimbal controller control mode is unknown.
     */
    DJIHandheldControllerStickControlModeUnknown = 0xFF,
};


/**
 *  The state of the zoom slider on the handheld controller. Used by Osmo Mobile 2
 *  only.
 */
typedef NS_ENUM (uint8_t, DJIHandheldZoomSlider){

	/**
	 *  Zoom slider is idle.
	 */
	DJIHandheldZoomSliderIdle,
	

	/**
	 *  The slider is pushed up and the camera should zoom in.
	 */
	DJIHandheldZoomSliderZoomIn,
	

	/**
	 *  The slider is pushed down and the camera should zoom out.
	 */
	DJIHandheldZoomSliderZoomOut,
	

	/**
	 *  Unknown.
	 */
	DJIHandheldZoomSliderZoomUnknown,
};


/**
 *  The status of the shutter button and record button on the handheld controller.
 *  Used by Osmo Mobile only.
 */
@interface DJIHandheldControllerHardwareState : NSObject


/**
 *  Status of the shutter button and record button.
 */
@property(nonatomic, readonly) DJIHandheldRecordAndShutterButtons recordAndShutterButtons;


/**
 *  `YES` when the trigger is being pressed. It is only supported in firmware
 *  version 1.2.0.40 or above.
 */
@property(nonatomic, readonly) BOOL isTriggerBeingPressed;


/**
 *  `YES` when the mode button is being pressed. It is only supported by OSMO Mobile
 *  2.
 */
@property(nonatomic, readonly) BOOL isModeButtonBeingPressed;


/**
 *  Status of the trigger button.
 */
@property(nonatomic, readonly) DJIHandheldButtonClickEvent triggerButton;


/**
 *  Status of the mode button. It is only supported by Osmo Mobile 2.
 */
@property(nonatomic, readonly) DJIHandheldButtonClickEvent modeButton;


/**
 *  Status of the joystick in vertical direction.
 */
@property(nonatomic, readonly) DJIHandheldStickVerticalDirection stickVerticalDirection;


/**
 *  Status of the joystick in horizontal direction.
 */
@property(nonatomic, readonly) DJIHandheldStickHorizontalDirection stickHorizontalDirection;


/**
 *  Position of the stick in both vertical and horizontal direction. Only supported
 *  in firmware version 1.2.0.40 or above.
 */
@property(nonatomic, readonly) DJIStick stick;


/**
 *  Status of the zoom slider. It is only supported by Osmo Mobile 2.
 */
@property(nonatomic, readonly) DJIHandheldZoomSlider zoomSlider;

@end


/**
 *  Pattern used to control a single color (red, green or blue) of the handheld
 *  controller's LED.
 */
@interface DJIHandheldControllerLEDColorPattern : NSObject


/**
 *  Pattern to control the time varying behaviour of the LED color. Each element of
 *  <code>pattern</code> is a boolean `NSNumber` representing the LED on/off state
 *  for 0.125 seconds where `YES` means the LED is on. The length of the pattern
 *  cannot exceed 32. By default, the array is empty, which will turn the LED color
 *  off.
 */
@property (nonatomic) NSArray<NSNumber *> *pattern;


/**
 *  The number of times to repeat the sequence with range [1, 255]. A value of 255
 *  will repeat the sequence indefinitely until a new  command is sent. The default
 *  value is 255.
 */
@property (nonatomic) uint8_t repeatTimes;

@end


/**
 *  Command used to control different colors (red, green and blue) of the handheld
 *  controller's LED.
 */
@interface DJIHandheldControllerLEDCommand : NSObject


/**
 *  Pattern to control the red color.
 */
@property(nonatomic) DJIHandheldControllerLEDColorPattern *red;


/**
 *  Pattern to control the green color.
 */
@property(nonatomic) DJIHandheldControllerLEDColorPattern *green;


/**
 *  Pattern to control the blue color.
 */
@property(nonatomic) DJIHandheldControllerLEDColorPattern *blue;

@end

NS_ASSUME_NONNULL_END
