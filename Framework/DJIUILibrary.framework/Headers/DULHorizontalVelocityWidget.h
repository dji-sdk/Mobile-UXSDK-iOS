//
//  DULHorizontalVelocityWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUILibrary/DULWidget.h>


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
 *  The horizontal velocity in meters/second.
 */
@property (nonatomic, assign, readonly) CGFloat velocityValue;

@end
