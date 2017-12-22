//
//  DULDistanceHomeWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUILibrary/DJIUILibrary.h>
@import CoreLocation;


/**
 *  Display:
 *  Distance between current location of the aircraft and home in meters.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 16:5. Check `DULDashboardWidget` for an example of its
 *  usage.
 */
@interface DULDistanceHomeWidget : DULWidget


/**
 *  The distance the aircraft is from home measured in meters.
 */
@property (nonatomic, assign, readonly) CLLocationDistance distance;

@end
