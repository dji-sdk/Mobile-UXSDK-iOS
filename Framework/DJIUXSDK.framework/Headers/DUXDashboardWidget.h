//
//  DUXDashboardWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Display:
 *  Compound widget that aggregates important physical state information of the
 *  aircraft into a dashboard. It includes the circular `DUXCompassWidget`, the
 *  `DUXDistanceHomeWidget`, the `DUXHorizontalVelocityWidget`, the
 *  `DUXDistanceRCWidget`, the `DUXVerticalVelocityWidget`, and the
 *  `DUXAltitudeWidget`.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 541:91.
 */
@interface DUXDashboardWidget : DUXWidget


/**
 *  The accuracy needed for the CLLocationManager instance in the distance dashboard
 *  widget. By default, the accuracy is best for navigation, but can be reduced if
 *  needed.
 */
@property(assign, nonatomic) CLLocationAccuracy locationManagerAccuracy;

@end
