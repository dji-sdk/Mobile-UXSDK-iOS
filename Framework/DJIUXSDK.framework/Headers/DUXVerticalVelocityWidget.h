//
//  DUXVerticalVelocityWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DUXWidget.h>


/**
 *  Display:
 *  Text shows the aircraft's current vertical velocity in m/s. Arrow indicates
 *  whether the aircraft is going up or down.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 18:3. Check `DUXDashboardWidget` for an example of its
 *  usage.
 */
@interface DUXVerticalVelocityWidget : DUXWidget


/**
 *  The vertical velocity of the aircraft measured in m/s.
 */
@property (nonatomic, assign, readonly) CGFloat velocity;

@end
