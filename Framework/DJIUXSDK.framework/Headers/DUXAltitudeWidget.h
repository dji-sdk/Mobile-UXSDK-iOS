//
//  DUXAltitudeWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Display:
 *  Current altitude of the aircraft in meters.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 16:5. Check `DUXDashboardWidget` for an example of its
 *  usage.
 */
@interface DUXAltitudeWidget : DUXWidget


/**
 *  The altitude in meters.
 */
@property (nonatomic, assign, readonly) CGFloat altitude;

@end
