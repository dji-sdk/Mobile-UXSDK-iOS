//
//  DUXCameraConfigWBWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Display:
 *  Camera's current White Balance setting.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: (variable, max:221):30.
 */
@interface DUXCameraConfigWBWidget : DUXCameraConfigWidget


/**
 *  Selects which camera index widget refers to. Default value is 0.
 */
@property (nonatomic) NSUInteger preferredCameraIndex;


/**
 *  The current white balance value. Defaults to unknown until transformed.
 */
@property (strong, nonatomic) DJICameraWhiteBalance *wb;

@end
