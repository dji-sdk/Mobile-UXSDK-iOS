//
//  DUXExposureFocusSwitchWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  The two modes that the switch can be in.  Also the 2 values that can be sent by
 *  the notification.
 */
typedef NS_ENUM(NSInteger, DUXExposureFocusSwitchMode)
{

    /**
     *  Exposure mode.
     */
    DUXExposureMode,

    /**
     *  Focus mode.
     */
    DUXFocusMode,
};


/**
 *  Display:
 *  Action widget that allows switching between between Exposure and Focus controls
 *  when touching. Not supported on Spark.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 35:35
 */
@interface DUXExposureFocusSwitchWidget : DUXWidget


/**
 *  The current state of the switch.
 */
@property DUXExposureFocusSwitchMode switchMode;


/**
 *  This is the name of the NSNotification that is posted everytime the switch
 *  changes state.
 */
extern NSString * const DUXExposureFocusSwitchModeChangedNotification;


/**
 *  Use this as the key for the dictionary that is sent with the notification to get
 *  the switch state.
 */
extern NSString * const DUXExposureFocusSwitchModeKey;

@end
