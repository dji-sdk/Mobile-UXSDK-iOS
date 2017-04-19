//
//  DULCameraConfigApertureWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUILibrary/DJIUILibrary.h>


/**
 *  Display:
 *  Camera's current aperture setting.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: (variable, max:221):30.
 */
@interface DULCameraConfigApertureWidget : DULCameraConfigWidget


/**
 *  The current aperture value. Defaults to unknown until transformed.
 */
@property DJICameraAperture aperture;

@end
