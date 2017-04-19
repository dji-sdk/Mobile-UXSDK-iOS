//
//  DULCameraConfigShutterWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUILibrary/DJIUILibrary.h>


/**
 *  Display:
 *  Camera's current shutter speed setting.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: (variable, max:221):30.
 */
@interface DULCameraConfigShutterWidget : DULCameraConfigWidget


/**
 *  Usage:
 *  The current shutterSpeed value. Defaults to unknown until transformed.
 */
@property DJICameraShutterSpeed shutterSpeed;

@end
