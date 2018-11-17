//
//  DJIHotpointAction.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <DJISDK/DJISDK.h>

@class DJIHotpointMission;


/**
 *  This class represents a hotpoint action used as an element in a Timeline
 *  mission. By creating an object of this class and adding it to Mission Control's
 *  Timeline,  the aircraft will fly along a portion of a circle centered on a
 *  location of interest when the Timeline reaches the action.
 */
@interface DJIHotpointAction : DJIMissionAction


/**
 *  The angular distance in degrees the aircraft will travel in the  orbit of the
 *  hotpoint. The default is 360 degrees.
 */
@property(nonatomic, assign) float surroundingAngle;


/**
 *  The hotpoint mission which is associated with this action.
 */
@property(nonatomic, readonly) DJIHotpointMission *mission;


/**
 *  Initialize with hotpoint mission. The Hotpoint action  will automatically stop
 *  after one complete orbit (360 degrees).
 *  
 *  @param mission An object of `DJIHotpointMission`.
 */
- (instancetype)initWithMission:(DJIHotpointMission*)mission;


/**
 *  Initialize with a hotpoint mission and the angular distance the  aircraft should
 *  travel within the orbit.
 *  
 *  @param mission An object of `DJIHotpointMission`.
 *  @param surroundingAngle Angle in degrees.
 */
- (instancetype)initWithMission:(DJIHotpointMission*)mission surroundingAngle:(float)surroundingAngle;

@end
