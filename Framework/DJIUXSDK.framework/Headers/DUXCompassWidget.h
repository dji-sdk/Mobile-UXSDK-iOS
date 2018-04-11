//
//  DUXCompassWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Display:
 *  Compound widget that aggregates attitude and location data into one widget. The
 *  widget shows:
 *    - Heading of the aircraft relative to the pilot
 *    - True north relative to pilot and aircraft
 *    - Roll and pitch of aircraft
 *    - Yaw and pitch of gimbal
 *    - Position of aircraft relative to pilot
 *    - Distance of aircraft from pilot
 *    - Home location
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 1:1. Check `DUXDashboardWidget` for an example of its
 *  usage.
 */
@interface DUXCompassWidget : DUXWidget

@end
