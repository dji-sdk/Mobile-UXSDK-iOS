//
//  DULAltitudeWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUILibrary/DJIUILibrary.h>


/**
 *  Display:
 *  Current altitude of the aircraft in meters.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 16:5. Check `DULDashboardWidget` for an example of its
 *  usage.
 */
@interface DULAltitudeWidget : DULWidget


/**
 *  The altitude in meters.
 */
@property (nonatomic, assign, readonly) CGFloat altitude;

@end
