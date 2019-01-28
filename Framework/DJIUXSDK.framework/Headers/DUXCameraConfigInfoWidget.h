//
//  DUXCameraConfigInfoWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Display:
 *  Widget that is an aggregate of camera exposure settings and white balance. This
 *  contains state for ISO, aperture, shutter speed, white balance and exposure
 *  compensation value.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: (variable, max:221):30
 */
@interface DUXCameraConfigInfoWidget : DUXWidget


/**
 *  Selects which camera index widget refers to. Default value is 0.
 */
@property (nonatomic) NSUInteger preferredCameraIndex;

@end
