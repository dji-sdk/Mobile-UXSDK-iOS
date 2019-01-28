//
//  DUXFocusModeWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Display:
 *  Widget for controlling the focus mode. Not supported on Spark.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 30:35
 */
@interface DUXFocusModeWidget : DUXWidget


/**
 *  `YES` if widget is supported, `NO` otherwise. Widget will hide itself if not
 *  supported. It is not supported on Spark and Mavic Air.
 */
@property (readonly) BOOL isSupported;


/**
 *  Display:
 *  Current focus mode that the camera is in.
 */
@property DJICameraFocusMode focusMode;


/**
 *  The index representing the camera that the widget controls. Default value is 0.
 */
@property (nonatomic) NSUInteger preferredCameraIndex;

@end
