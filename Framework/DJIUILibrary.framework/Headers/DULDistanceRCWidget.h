//
//  DULDistanceRCWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUILibrary/DJIUILibrary.h>


/**
 *  Display:
 *  Distance between current location of the aircraft and RC (pilot) in meters.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 16:5. Check `DULDashboardWidget` for an example of its
 *  usage.
 */
@interface DULDistanceRCWidget : DULWidget


/**
 *  The distance between the aircraft and the RC in meters.
 */
@property (nonatomic, assign, readonly) CGFloat distance;

@end
