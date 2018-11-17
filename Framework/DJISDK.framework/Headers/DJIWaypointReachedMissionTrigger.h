//
//  DJIWaypointReachedMissionTrigger.h
//  DJISDK
//
//  Copyright © 2017 DJI. All rights reserved.
//

#import <DJISDK/DJISDK.h>


/**
 *  This class can be used to trigger an action during the execution of a waypoint
 *  mission when the aircraft reaches a certain waypoint index.
 */
@interface DJIWaypointReachedMissionTrigger : DJIMissionTrigger


/**
 *  If the waypoint mission reaches this index, the action will be triggered.
 */
@property(nonatomic) NSInteger waypointIndex;

@end
