//
//  DUXDistanceHomeWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>
@import CoreLocation;


/**
 *  Display:
 *  Distance between current location of the aircraft and home in meters.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 16:5. Check `DUXDashboardWidget` for an example of its
 *  usage.
 */
@interface DUXDistanceHomeWidget : DUXWidget


/**
 *  The distance the aircraft is from home measured in meters.
 */
@property (nonatomic, assign, readonly) CLLocationDistance distance;

@end
