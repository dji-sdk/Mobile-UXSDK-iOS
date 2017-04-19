//
//  DULHorizontalVelocityWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import "DULWidget.h"

IB_DESIGNABLE

/**
 *  Display:
 *  Horizontal velocity of aircraft in m/s.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 16:5. Check `DULDashboardWidget` for an example of its
 *  usage.
 */
@interface DULHorizontalVelocityWidget : DULWidget


/**
 *  The horizonal veloctity in meters/second.
 */
@property (nonatomic, assign, readonly) CGFloat velocityValue;

@end
