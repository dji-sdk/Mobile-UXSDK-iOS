//
//  DULAircraftBatteryChecklistItem.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUILibrary/DULPreflightChecklistItem.h>


/**
 *  Preflight checklist item that reports aircraft battery levels and states.
 */
@interface DULAircraftBatteryChecklistItem : DULPreflightChecklistItem


/**
 *  Property that sets a minimum value threshold the battery percentage must be at
 *  in order to show a good state.  The default value is 0.
 */
@property (nonatomic, assign) NSInteger minimumOperationalThreshold;


/**
 *  Custom initializer that will set the minimum battery threshold.
 *  
 *  @param minimumOperationalThreshold Minimum operational threshold.
 */
- (instancetype)initWithMinimumOperationalThreshold:(NSInteger)minimumOperationalThreshold;

@end
