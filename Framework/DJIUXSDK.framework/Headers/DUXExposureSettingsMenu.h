//
//  DUXExposureSettingsMenu.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Usage:
 *  Preferred Aspect Ratio: 13:15. Check `DUXTrailingBarViewController` for an
 *  example of its usage.
 *  
 *  Interaction:
 *  Tapping the button will toggle between show and hide
 *  `DUXExposureSettingsController`.
 */
@interface DUXExposureSettingsMenu : DUXWidget


/**
 *  Usage:
 *  The current exposure mode of the camera.
 */
@property DJICameraExposureMode exposureMode;

@end
