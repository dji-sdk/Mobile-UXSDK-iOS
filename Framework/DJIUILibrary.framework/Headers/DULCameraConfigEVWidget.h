//
//  DULCameraConfigEVWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUILibrary/DJIUILibrary.h>


/**
 *  Display:
 *  Camera's current EV setting.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: (variable, max:221):30.
 */
@interface DULCameraConfigEVWidget : DULCameraConfigWidget


/**
 *  The current exposure compensation value. Default to unknown until transformed.
 */
@property DJICameraExposureCompensation ev;

@end
