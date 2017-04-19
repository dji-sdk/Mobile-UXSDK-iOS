//
//  DULCameraConfigWBWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUILibrary/DJIUILibrary.h>


/**
 *  Display:
 *  Camera's current White Balance setting.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: (variable, max:221):30.
 */
@interface DULCameraConfigWBWidget : DULCameraConfigWidget


/**
 *  The current white balance value. Defaults to unknown until transformed.
 */
@property (strong, nonatomic) DJICameraWhiteBalance *wb;

@end
