//
//  DUXCameraConfigExposureSensitivityWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Display:
 *  Camera's current ISO setting.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: (variable, max:221):30.
 */
@interface DUXCameraConfigExposureSensitivityWidget : DUXCameraConfigWidget


/**
 *  Selects which camera index widget refers to. Default value is 0.
 */
@property (nonatomic) NSUInteger preferredCameraIndex;


/**
 *  The current exposure sensitivity mode of the camera.
 */
@property DJICameraExposureSensitivityMode exposureSensitivityMode;


/**
 *  The current ISO value. Default to unknown until transformed.
 */
@property DJICameraISO iso;


/**
 *  The current EI of the camera. This value is only valid when the exposure
 *  sensitivity mode of the camera is set to EI.
 */
@property NSUInteger ei;

@end
