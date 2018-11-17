//
//  DJITapFlyMission.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#import "DJIMission.h"
#import "DJISDKFoundation.h"
#import <CoreGraphics/CoreGraphics.h>
#import "DJITapFlyMissionTypes.h"
#import "DJISDKVector3D.h"

NS_ASSUME_NONNULL_BEGIN


/**
 *  This class provides the detailed state of a TapFly Mission that is executing.
 */
@interface DJITapFlyExecutionState : NSObject


/**
 *  The direction vector the aircraft is travelling in using the N-E-D  (North-East-
 *  Down) coordinate system.
 */
@property(nonatomic, readonly) DJISDKVector3D *direction;


/**
 *  The image point from the video feed where the vision system should calculate the
 *  flight direction from. The image point is normalized to [0,1] where (0,0) is the
 *  top left corner and (1,1) is the bottom right.
 */
@property(nonatomic, readonly) CGPoint imageLocation;


/**
 *  The real-time speed of the aircraft in m/s.
 */
@property(nonatomic, readonly) float speed;


/**
 *  The direction the aircraft is moving around or bypassing an obstacle in. Will be
 *  `DJIBypassDirectionNone` if the aircraft is not executing  an avoidance
 *  maneuver.
 */
@property(nonatomic, readonly) DJIBypassDirection bypassDirection;


/**
 *  Aircraft's heading relative to the flight direction.
 */
@property(nonatomic, readonly) float relativeHeading;

@end


/**
 *  A TapFly Mission is initialized with a position target from the live video
 *  stream. The 3D direction of the coordinate is calculated, and the aircraft  will
 *  proceed to fly in that direction. The aircraft can automatically avoid
 *  obstacles when the scene is sufficiently illuminated (more than 300 lux but
 *  less than 10,000 lux). The aircraft will stop flying in the direction if it
 *  reaches its radius limitation, the mission is stopped, the user pulls back on
 *  the pitch stick or if it comes to an obstacle it cannot bypass. The Remote
 *  Controller yaw stick can be used to adjust the heading of the aircraft during
 *  mission execution, which also adjusts the direction of flight to the new yaw.
 *  Using any other stick controls will cancel the mission.
 */
@interface DJITapFlyMission : DJIMission


/**
 *  The image point from the video feed where the vision system should calculate
 *  the flight direction from. The image point is normalized to [0,1] where (0,0)
 *  is the top left corner and (1,1) is the bottom right.
 */
@property(nonatomic, assign) CGPoint imageLocationToCalculateDirection;


/**
 *  TapFly Mission mode. Defaults to `DJITapFlyModeForward`.  Additional modes only
 *  supported by the Phantom 4 Pro.
 */
@property(nonatomic) DJITapFlyMode tapFlyMode;
@end

NS_ASSUME_NONNULL_END
