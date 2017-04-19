//
//  DULPictureVideoSwitchWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import "DULWidget.h"

IB_DESIGNABLE


/**
 *  Display:
 *  A switch button shows weather the camera mode is in shoot photo or record video.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 56:45. Check `DULTrailingBarViewController` for an
 *  example of its usage.
 *  
 *  Interaction:
 *  Use switch button to toggle the camera mode.
 */
@interface DULPictureVideoSwitchWidget : DULWidget


/**
 *  The current camera mode of the product. Defaults to still photo.
 */
@property DJICameraMode mode;

@end
