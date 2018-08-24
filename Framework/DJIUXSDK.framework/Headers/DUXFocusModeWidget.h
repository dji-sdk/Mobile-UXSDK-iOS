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
 *  Display:
 *  Current focus mode that the camera is in.
 */
@property DJICameraFocusMode focusMode;


@end
