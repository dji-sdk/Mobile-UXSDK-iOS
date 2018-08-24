//
//  DUXCameraSettingsController.h
//  DJIUXSDK
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
 *  All the settings are presented in ListView hierarchy.
 */
@interface DUXCameraSettingsController : UIViewController


/**
 *  Creates a new instance, configured and ready to use of
 *  DULCameraSettingsController.
 */
+ (instancetype)cameraSettingsController;


/**
 *  Use this property to change which camera's settings are loaded into the panel.
 *  The default  value is 0 so you will only need to change this is working with an
 *  aircraft that supports dual cameras.
 */
@property (assign, nonatomic, readwrite) NSUInteger preferredCameraIndex;

@end
