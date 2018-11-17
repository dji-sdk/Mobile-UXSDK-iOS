//
//  DJIFollowMeMission.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>
#import "DJIMission.h"

NS_ASSUME_NONNULL_BEGIN



/**
 *  Aircraft's heading during a follow me mission.
 */
typedef NS_ENUM (uint8_t, DJIFollowMeHeading){


    /**
     *  Aircraft's heading remains toward the coordinate it is following.
     */
    DJIFollowMeHeadingTowardFollowPosition,


    /**
     *  Aircraft's heading will be controlled by the remote controller.
     */
    DJIFollowMeHeadingControlledByRemoteController,
};


/**
 *  The class represents a Follow Me mission. In a Follow Me mission, the aircraft
 *  is programmed to track and maintain a constant distant relative to some object,
 *  such as a person or a moving vehicle. You can use it to make the aircraft follow
 *  a GPS device, such as a remote controller with a GPS signal or a mobile device.
 *  It is not supported by Mavic Pro when using WiFi connection. It is not supported
 *  by Spark.
 */
@interface DJIFollowMeMission : DJIMission

/*********************************************************************************/
#pragma mark - Mission Presets
/*********************************************************************************/


/**
 *  Location of the mission's initial target.
 */
@property(nonatomic, assign) CLLocationCoordinate2D followMeCoordinate;


/**
 *  Initial altitude (above sea level) in meters.
 */
@property(nonatomic, assign) float followMeAltitude;


/**
 *  The aircraft's heading during the mission.
 *  
 *  @return An enum value of `DJIFollowMeHeading`.
 */
@property(nonatomic, assign) DJIFollowMeHeading heading;

@end

NS_ASSUME_NONNULL_END
