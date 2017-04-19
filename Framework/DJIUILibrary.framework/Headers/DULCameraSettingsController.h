//
//  DULCameraSettingsController.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>


/**
 *  Display:
 *  This panel shows all the camera settings that are not related to exposure. It is
 *  segmented in three parts:
 *      - Picture Settings
 *      - Video Settings
 *      - Common Settings
 *  
 *  Interaction:
 *  All the settings are presented in ListView hierachy.
 */
@interface DULCameraSettingsController : UIViewController


/**
 *  Usage:
 *  Creates a new instance, configured and ready to use of
 *  DULCameraSettingsController.
 */
+ (instancetype)cameraSettingsController;

@end
