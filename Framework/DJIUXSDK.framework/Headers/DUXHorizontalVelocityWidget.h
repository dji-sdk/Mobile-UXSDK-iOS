//
//  DUXHorizontalVelocityWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DUXWidget.h>


/**
 *  Display:
 *  Horizontal velocity of aircraft in m/s.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 16:5. Check `DUXDashboardWidget` for an example of its
 *  usage.
 */
@interface DUXHorizontalVelocityWidget : DUXWidget


/**
 *  The horizontal velocity in meters/second.
 */
@property (nonatomic, assign, readonly) CGFloat velocityValue;

@end
