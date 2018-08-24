//
//  DUXDistanceRCWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Display:
 *  Distance between current location of the aircraft and RC (pilot) in meters.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 16:5. Check `DUXDashboardWidget` for an example of its
 *  usage.
 */
@interface DUXDistanceRCWidget : DUXWidget


/**
 *  The distance between the aircraft and the RC in meters.
 */
@property (nonatomic, assign, readonly) CGFloat distance;


/**
 *  The accuracy needed for the CLLocationManager instance in the distance  RC
 *  widget. By default, the accuracy is best for navigation, but can be  reduced if
 *  needed.
 */
@property(assign, nonatomic) CLLocationAccuracy locationManagerAccuracy;


@end
