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

@property (nonatomic) NSUInteger preferredCameraIndex;

@property DJICameraExposureSensitivityMode exposureSensitivityMode;


/**
 *  The current ISO value. Default to unknown until transformed.
 */
@property DJICameraISO iso;

@property NSUInteger ei;

@end
