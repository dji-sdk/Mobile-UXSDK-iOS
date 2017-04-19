//
//  DULCameraConfigIsoWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUILibrary/DJIUILibrary.h>


/**
 *  Display:
 *  Camera's current ISO setting.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: (variable, max:221):30.
 */
@interface DULCameraConfigIsoWidget : DULCameraConfigWidget


/**
 *  The current ISO value. Default to unknown until transformed.
 */
@property DJICameraISO iso;

@end
