//
//  DJISimulatorState.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>


/**
 *  Aircraft simulator state data.
 */
@interface DJISimulatorState : NSObject


/**
 *  YES if motors are on in simulator.
 */
@property(nonatomic, readonly) BOOL areMotorsOn;


/**
 *  YES if aircraft is flying in simulator.
 */
@property(nonatomic, readonly) BOOL isFlying;


/**
 *  Simulated aircraft location.
 *  
 *  @return Location object.
 */
@property(nonatomic, readonly) CLLocationCoordinate2D location;


/**
 *  Simulated aircraft pitch with range [-30, 30] degrees.
 */
@property(nonatomic, readonly) float pitch;


/**
 *  Simulated aircraft roll with range [-30, 30] degrees.
 */
@property(nonatomic, readonly) float roll;


/**
 *  Simulated aircraft yaw with range [-180, 180] degrees.
 */
@property(nonatomic, readonly) float yaw;


/**
 *  Gets East-West distance from initial simulator location, where East is positive,
 *  and  North-East-Down coordinate system is used.
 */
@property(nonatomic, readonly) float positionX;


/**
 *  Gets North-South distance from initial simulator location, where North is
 *  positive, and  North-East-Down coordinate system is used.
 */
@property(nonatomic, readonly) float positionY;


/**
 *  Gets vertical distance from initial simulator location. The value should be
 *  negative if the height of aircraft is higher  than initial home point's height.
 */
@property(nonatomic, readonly) float positionZ;

@end
