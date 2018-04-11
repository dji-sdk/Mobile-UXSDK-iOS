//
//  DUXCameraConfigApertureWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Display:
 *  Camera's current aperture setting.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: (variable, max:221):30.
 */
@interface DUXCameraConfigApertureWidget : DUXCameraConfigWidget

@property (nonatomic) NSUInteger preferredCameraIndex;


/**
 *  The current aperture value. Defaults to unknown until transformed.
 */
@property DJICameraAperture aperture;

@end
