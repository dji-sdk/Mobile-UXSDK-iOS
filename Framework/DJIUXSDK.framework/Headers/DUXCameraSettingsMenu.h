//
//  DUXCameraSettingsMenu.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DUXWidget.h>


/**
 *  Display:
 *  A simple widget showing the word MENU to be used to show the camera settings
 *  panel.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 200:120
 */
@interface DUXCameraSettingsMenu : DUXWidget


/**
 *  The index of the camera whose settings will be controlled by the settings panel.
 *  Default value is 0.
 */
@property (nonatomic) NSUInteger preferredCameraIndex;

@end
