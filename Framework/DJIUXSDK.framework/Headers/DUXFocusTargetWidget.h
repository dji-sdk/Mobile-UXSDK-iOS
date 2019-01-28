//
//  DUXFocusTargetWidget.h
//  DJIUXSDK
//
//  Copyright © 2017 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Display:
 *  Widget for displaying current focus point. Not supported on Spark.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 40:50
 */
@interface DUXFocusTargetWidget : DUXWidget


/**
 *  The index representing the camera that the widget controls. Default value is 0.
 */
@property (nonatomic) NSUInteger preferredCameraIndex;

@end
