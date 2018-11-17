//
//  DJIWaypointMission.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "DJIWaypointMissionTypes.h"
#import "DJIMission.h"

NS_ASSUME_NONNULL_BEGIN

@class DJIWaypoint;
@class DJIMutableWaypointMission;


/**
 *  In the waypoint mission, the aircraft will travel between waypoints, execute
 *  actions at waypoints, and  adjust heading and altitude between waypoints.
 *  Waypoints are physical locations to which the aircraft  will fly. Creating a
 *  series of waypoints, in effect, will program a flight route for the aircraft to
 *  follow. Actions can also be added to waypoints, which will be carried out when
 *  the aircraft reaches the  waypoint. The aircraft travels between waypoints
 *  automatically at a base speed. However, the user can  change the speed by using
 *  the pitch joystick. If the stick is pushed up, the speed will increase. If  the
 *  stick is pushed down, the speed will slow down. The stick can be pushed down to
 *  stop the aircraft  and further pushed to start making the aircraft travel back
 *  along the path it came. When the aircraft  is travelling through waypoints in
 *  the reverse order, it will not execute waypoint actions at each  waypoint. If
 *  the stick is released, the aircraft will again travel through the waypoints in
 *  the original  order, and continue to execute waypoint actions (even if executed
 *  previously). If the aircraft is pulled  back along the waypoint mission all the
 *  way to the first waypoint, then it will hover in place until the  stick is
 *  released enough for it to again progress through the mission from start to
 *  finish. It is not  supported by Mavic Pro when using WiFi connection. It is not
 *  supported by Spark.
 */
@interface DJIWaypointMission : DJIMission



/**
 *  Initialize a `DJIWaypointMission` by copying the parameters from the input
 *  mission.
 *  
 *  @param mission Mission to be copied from.
 */
-(instancetype)initWithMission:(DJIWaypointMission *)mission;


/**
 *  When downloading a waypoint mission, the number of waypoints in  `allWaypoints`
 *  will be less than  `waypointCount` until the download is complete. This property
 *  is `YES` when all the information in the waypoint mission is downloaded, and
 *  complete in this object.
 */
@property(nonatomic, readonly) BOOL isComplete;


/**
 *  Checks if the configuration for the mission is valid before loading it into
 *  `DJIWaypointMissionOperator`.
 *  
 *  @return Error found when checking parameters of the waypoint. `nil` if all the parameters are valid.
 */
- (nullable NSError *)checkParameters;

/*********************************************************************************/
#pragma mark - Mission Presets
/*********************************************************************************/


/**
 *  Number of waypoints in the waypoint mission. Note there are some cases when the
 *  waypoint count will be different to the waypoint array length from
 *  `allWaypoints`. This is usually the case when the waypoint  mission is still
 *  being downloaded from the aircraft and the mission object hasn't  existed
 *  previously (e.g. when the mobile device is connected to an aircraft with a
 *  previously uploaded mission). In these cases, `isComplete`  will return `NO`.
 */
@property(nonatomic, readonly) NSUInteger waypointCount;


/**
 *  While the aircraft is travelling between waypoints, you can offset its speed by
 *  using the throttle joystick  on the remote controller. `maxFlightSpeed` is this
 *  offset when the joystick is pushed  to maximum deflection. For example, If
 *  maxFlightSpeed is 10 m/s, then pushing the throttle joystick all the  way up
 *  will add 10 m/s to the aircraft speed, while pushing down will subtract 10 m/s
 *  from the aircraft  speed. If the remote controller stick is not at maximum
 *  deflection, then the offset speed will be  interpolated between [0,
 *  `maxFlightSpeed`] with a resolution of 1000 steps. If the  offset speed is
 *  negative, then the aircraft will fly backwards to previous waypoints. When it
 *  reaches the  first waypoint, it will then hover in place until a positive speed
 *  is  applied. `maxFlightSpeed` has a range of [2,15] m/s.
 */
@property(nonatomic, readonly) float maxFlightSpeed;


/**
 *  The base automatic speed of the aircraft as it moves between waypoints with
 *  range [-15, 15] m/s. The  aircraft's actual speed is a combination of the base
 *  automatic speed, and the speed control given by  the throttle joystick on the
 *  remote controller. If `autoFlightSpeed` >0: Actual  speed is `autoFlightSpeed` +
 *  Joystick Speed (with combined max  of `maxFlightSpeed`) If `autoFlightSpeed` =0:
 *  Actual speed is  controlled only by the remote controller joystick. If
 *  `autoFlightSpeed` <0 and the  aircraft is at the first waypoint, the aircraft
 *  will hover in place until the speed is made positive by  the remote controller
 *  joystick.
 */
@property(nonatomic, readonly) float autoFlightSpeed;


/**
 *  Action the aircraft will take when the waypoint mission is complete.
 */
@property(nonatomic, readonly) DJIWaypointMissionFinishedAction finishedAction;


/**
 *  Heading of the aircraft as it moves between waypoints. Default  is
 *  `DJIWaypointMissionHeadingAuto`.
 */
@property(nonatomic, readonly) DJIWaypointMissionHeadingMode headingMode;


/**
 *  The path the aircraft follows between waypoints. The aircraft can either fly
 *  directly between waypoints in a straight line, or turn near a waypoint in the
 *  curve where the waypoint location defines a part of the curve.
 */
@property(nonatomic, readonly) DJIWaypointMissionFlightPathMode flightPathMode;


/**
 *  Defines how the aircraft will go to the first waypoint from its current
 *  position. Default  is `DJIWaypointMissionGotoWaypointSafely`.
 */
@property(nonatomic, readonly) DJIWaypointMissionGotoWaypointMode gotoFirstWaypointMode;


/**
 *  Determines whether the mission should stop when connection between the  aircraft
 *  and remote controller is lost. Default is `NO`.
 */
@property(nonatomic, readonly) BOOL exitMissionOnRCSignalLost;


/**
 *  Aircraft heading will be fixed to the point of interest location during the
 *  waypoint mission. Used when `headingMode`  is
 *  `DJIWaypointMissionHeadingTowardPointOfInterest`.
 */
@property(nonatomic, readonly) CLLocationCoordinate2D pointOfInterest;


/**
 *  `YES` if the gimbal pitch rotation can be controlled during the waypoint
 *  mission. When `YES`, `gimbalPitch` in `DJIWaypoint` is used to control gimbal
 *  pitch.
 */
@property(nonatomic, readonly) BOOL rotateGimbalPitch;


/**
 *  Mission execution can be repeated more than once. A value of 0 means the mission
 *  only executes once, and does not repeat. A value of 1 means the mission will
 *  execute a total of two times.
 */
@property(nonatomic, readonly) int repeatTimes;


/**
 *  Gets the waypoint at the specified index in the mission waypoint array.
 *  
 *  @param index Index of the waypoint to be retrieved.
 *  
 *  @return The `DJIWaypoint` at the specified index.
 */
- (nullable DJIWaypoint *)waypointAtIndex:(NSUInteger)index;


/**
 *  Returns an array of all waypoints in the mission.
 *  
 *  @return An array of `DJIWaypoint` instances contained in the mission.
 */
- (NSArray<DJIWaypoint *> *)allWaypoints;


/**
 *  Creates a mutable copy of the mission.
 *  
 *  @return A mutable copy of the mission.
 */
- (DJIMutableWaypointMission *)mutableCopy;

@end


/**
 *  The class represents a waypoint mission that can be changed. This class should
 *  be  used to initialize the parameters of a waypoint mission.
 */
@interface DJIMutableWaypointMission : DJIWaypointMission


/**
 *  While the aircraft is travelling between waypoints, you can offset its speed by
 *  using the throttle joystick on the remote controller. "maxFlightSpeed" is this
 *  offset when the joystick is pushed to maximum deflection. For example, If
 *  maxFlightSpeed is 10 m/s, then pushing the throttle joystick all the way up will
 *  add 10 m/s to the aircraft speed, while pushing down will subtract 10 m/s from
 *  the aircraft speed. If the remote controller stick is not at maximum deflection,
 *  then the offset speed will be interpolated between "[0, maxFlightSpeed]"" with a
 *  resolution of 1000 steps. If the offset speed is negative, then the aircraft
 *  will fly backwards to previous waypoints. When it reaches the first waypoint, it
 *  will then hover in place until a positive speed is applied. "maxFlightSpeed" has
 *  a range of [2,15] m/s.
 */
@property(nonatomic, readwrite) float maxFlightSpeed;


/**
 *  The base automatic speed of the aircraft as it moves between waypoints with
 *  range [-15, 15] m/s. The aircraft's actual speed is a combination of the base
 *  automatic speed, and the speed control given by the throttle joystick on the
 *  remote controller. If "autoFlightSpeed >0": Actual speed is "autoFlightSpeed" +
 *  Joystick Speed (with combined max of "maxFlightSpeed") If "autoFlightSpeed =0":
 *  Actual speed is controlled only by the remote controller joystick. If
 *  "autoFlightSpeed <0" and the aircraft is at the first waypoint, the aircraft
 *  will hover in place until the speed is made positive by the remote controller
 *  joystick. In flight controller firmware 3.2.10.0 or above, different speeds
 *  between individual waypoints can also be set in waypoint objects which will
 *  overwrite "autoFlightSpeed".
 */
@property(nonatomic, readwrite) float autoFlightSpeed;


/**
 *  Action the aircraft will take when the waypoint mission is complete.
 */
@property(nonatomic, readwrite) DJIWaypointMissionFinishedAction finishedAction;


/**
 *  Heading of the aircraft as it moves between waypoints. Default is
 *  `DJIWaypointMissionHeadingAuto`.
 */
@property(nonatomic, readwrite) DJIWaypointMissionHeadingMode headingMode;


/**
 *  Flight path mode of the waypoint mission.
 */
@property(nonatomic, readwrite) DJIWaypointMissionFlightPathMode flightPathMode;


/**
 *  Determines how the aircraft will reach first waypoint from current position.
 *  Default is `DJIWaypointMissionGotoWaypointSafely`.
 */
@property(nonatomic, readwrite) DJIWaypointMissionGotoWaypointMode gotoFirstWaypointMode;


/**
 *  Determines whether exit mission when RC signal lost. Default is NO.
 */
@property(nonatomic, readwrite) BOOL exitMissionOnRCSignalLost;


/**
 *  Property is used when `DJIWaypointMissionHeadingMode` is
 *  `DJIWaypointMissionHeadingTowardPointOfInterest`. Aircraft will always be
 *  heading to point while executing mission. Default is
 *  "kCLLocationCoordinate2DInvalid".
 */
@property(nonatomic, readwrite) CLLocationCoordinate2D pointOfInterest;



/**
 *  Determines whether the aircraft can rotate gimbal pitch when executing waypoint
 *  mission. If `YES`, the aircraft will control gimbal pitch rotation between
 *  waypoints using the `gimbalPitch` of the `DJIWaypoint`.
 */
@property(nonatomic, readwrite) BOOL rotateGimbalPitch;


/**
 *  Repeat times for mission execution. Default is 1.
 */
@property(nonatomic, readwrite) int repeatTimes;


/**
 *  Add a waypoint to the waypoint mission. The number of waypoints should be in the
 *  range [2, 99]. When a waypoint is added successfully, `waypointCount` will
 *  increment by 1. A waypoint will only be valid if the distance (in three
 *  dimensions) between two adjacent waypoints is in range [0.5,2000] meters.
 *  
 *  @param waypoint to be added to the waypoint mission.
 */
- (void)addWaypoint:(DJIWaypoint *)waypoint;


/**
 *  Adds an array of waypoints to the waypoint mission. The number of waypoints
 *  should be in the range [2, 99]`. When  the waypoints are added successfully,
 *  `waypointCount` will increment by the number of added waypoints.
 *  
 *  @param waypoints Array of waypoints to be added to the waypoint mission.
 */
- (void)addWaypoints:(NSArray *)waypoints;


/**
 *  Removes the last waypoint stored in the mission. When  the waypoint is removed
 *  successfully, `waypointCount` will decrease by 1.
 *  
 *  @param waypoint Waypoint object to be removed.
 */
- (void)removeWaypoint:(DJIWaypoint *)waypoint;


/**
 *  Removes the waypoint at an index. When  the waypoint is removed successfully,
 *  `waypointCount` will decrease by 1.
 *  
 *  @param index Index of the waypoint to be removed from the waypoint mission.
 */
- (void)removeWaypointAtIndex:(NSInteger)index;


/**
 *  Removes all waypoints from the waypoint mission. When  all waypoints are removed
 *  successfully, `waypointCount` will be 0.
 */
- (void)removeAllWaypoints;

@end

NS_ASSUME_NONNULL_END
