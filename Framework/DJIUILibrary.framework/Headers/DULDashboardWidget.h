//
//  DULDashboardWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUILibrary/DJIUILibrary.h>

IB_DESIGNABLE

/**
 *  Display:
 *  Compound widget that aggregates important physical state information of the
 *  aircraft into a dashboard. It includes the circular `DULCompassWidget`, the
 *  `DULDistanceHomeWidget`, the `DULHorizontalVelocityWidget`, the
 *  `DULDistanceRCWidget`, the `DULVerticalVelocityWidget`, and the
 *  `DULAltitudeWidget`.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 541:91.
 */
@interface DULDashboardWidget : DULWidget

@end
