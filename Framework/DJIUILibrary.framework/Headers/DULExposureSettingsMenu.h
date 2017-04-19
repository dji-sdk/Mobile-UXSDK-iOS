//
//  DULExposureSettingsMenu.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUILibrary/DJIUILibrary.h>

IB_DESIGNABLE

/**
 *  Usage:
 *  Preferred Aspect Ratio: 13:15. Check `DULTrailingBarViewController` for an
 *  example of its usage.
 *  
 *  Interaction:
 *  Tapping the button will toggle between show and hide
 *  `DULExposureSettingsController`.
 */
@interface DULExposureSettingsMenu : DULWidget


/**
 *  Usage:
 *  The current exposure mode of the camera.
 */
@property DJICameraExposureMode exposureMode;

@end
