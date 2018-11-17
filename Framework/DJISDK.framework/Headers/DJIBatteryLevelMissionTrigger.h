//
//  DJIBatteryLevelMissionTrigger.h
//  DJISDK
//
//  Copyright © 2017 DJI. All rights reserved.
//

#import <DJISDK/DJISDK.h>


/**
 *  The class can be used to trigger an action during the execution of a  timeline
 *  if the aircraft battery goes below a certain level.
 */
@interface DJIBatteryLevelMissionTrigger : DJIMissionTrigger


/**
 *  If the remaining percentage drops below or equal to this value, the action will
 *  be triggered.
 */
@property float batteryPercentageTriggerValue;

@end
