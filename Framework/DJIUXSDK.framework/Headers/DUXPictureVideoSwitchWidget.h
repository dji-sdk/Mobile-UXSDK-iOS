//
//  DUXPictureVideoSwitchWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DUXWidget.h>


/**
 *  Display:
 *  A switch button shows weather the camera mode is in shoot photo or record video.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 56:45. Check `DUXTrailingBarViewController` for an
 *  example of its usage.
 *  
 *  Interaction:
 *  Use switch button to toggle the camera mode.
 */
@interface DUXPictureVideoSwitchWidget : DUXWidget


/**
 *  The current camera mode of the product. Defaults to still photo.
 */
@property DJICameraMode mode;


/**
 *  The index of the camera the widget controls. Default value is 0.
 */
@property (nonatomic) NSUInteger preferredCameraIndex;

@end
