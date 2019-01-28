//
//  DUXCameraConfigEVWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Display:
 *  Camera's current EV setting.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: (variable, max:221):30.
 */
@interface DUXCameraConfigEVWidget : DUXCameraConfigWidget


/**
 *  Selects which camera index widget refers to. Default value is 0.
 */
@property (nonatomic) NSUInteger preferredCameraIndex;


/**
 *  The current exposure compensation value. Default to unknown until transformed.
 */
@property DJICameraExposureCompensation ev;

@end
