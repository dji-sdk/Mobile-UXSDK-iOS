//
//  DJIHotpointMission.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>
#import "DJIHotpointMissionTypes.h"
#import "DJIMission.h"

NS_ASSUME_NONNULL_BEGIN

@class DJIHotpointMission;



/**
 *  This class represents a Hotpoint mission. In a Hotpoint mission, the aircraft
 *  will repeatedly fly circles of a constant radius around a specified point called
 *  a Hot Point. The user can control the aircraft to fly around the Hotpoint with a
 *  specific radius and altitude. During execution, the user can also use the
 *  physical remote controller to modify its radius and speed. It is not supported
 *  by Mavic Pro when using WiFi connection. It is not supported by Spark.
 */
@interface DJIHotpointMission : DJIMission


/**
 *  Checks if the configuration for mission is valid before calling
 *  `startMission:withCompletion` of `DJIHotpointMissionOperator`.
 *  
 *  @return Error found when checking parameters of the waypoint. `nil` if all the parameters are valid.
 */
- (nullable NSError *)checkParameters;


/**
 *  Sets the coordinate of the hot point.
 */
@property(nonatomic, assign) CLLocationCoordinate2D hotpoint;


/**
 *  Set aircraft's initial point on the circular flight path when starting the hot
 *  point  mission.
 */
@property(nonatomic, assign) DJIHotpointStartPoint startPoint;


/**
 *  Aircraft's heading while flying around the hot point. It can be pointed toward
 *  or  away from the hot point, forward or backward along its flight route, or can
 *  be  manually controlled by the remote controller.
 */
@property(nonatomic, assign) DJIHotpointHeading heading;


/**
 *  Sets the altitude of the hot point orbit with a range [5,500] meters.  The
 *  altitude is relative to the ground altitude from which the aircraft took off.
 */
@property(nonatomic, assign) float altitude;


/**
 *  Sets the circular flight path radius with which the aircraft will fly around the
 *  hotpoint. The value of this property should be in the range  of
 *  [`DJIHotpointMinRadius`, `DJIHotpointMaxRadius`] meters.
 */
@property(nonatomic, assign) float radius;


/**
 *  Sets the angular velocity in degrees/s of the aircraft as it orbits the hot
 *  point. The default value is 20 degrees/s. The maximum angular velocity allowed
 *  is relative to the orbit radius.
 */
@property(nonatomic, assign) float angularVelocity;

@end

NS_ASSUME_NONNULL_END
