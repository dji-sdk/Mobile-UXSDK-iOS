//
//  DUXManualFocusAdjustmentWidget.h
//  DJIUXSDK
//
//  Copyright © 2017 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Display:
 *  Widget for controlling the manual focus of the camera. Not supported on Spark.
 *  
 *  Usage:
 *  Preferred Aspect Ration: 35:150
 */
@interface DUXManualFocusAdjustmentWidget : DUXWidget


/**
 *  `YES` if widget is supported, `NO` otherwise. It is not supported when focus
 *  mode is automatic or AFC.
 */
@property (readonly) BOOL isSupported;


/**
 *  The index representing the camera that the widget controls. Default is 0.
 */
@property (nonatomic) NSUInteger preferredCameraIndex;

@end
