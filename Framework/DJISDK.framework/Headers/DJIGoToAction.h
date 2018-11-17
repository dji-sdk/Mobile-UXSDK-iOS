//
//  DJIGoToAction.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <DJISDK/DJISDK.h>

NS_ASSUME_NONNULL_BEGIN


/**
 *  The error domain for errors specific to the `DJIGoToAction`.
 */
extern const NSErrorDomain DJIGoToActionErrorDomain;


/**
 *  The error codes for the `DJIGoToAction`.
 */
typedef NS_ENUM(NSInteger, DJIGoToActionError) {


    /**
     *  Default placeholder error.
     */
    DJIGoToActionErrorUnknown = -1,
    

    /**
     *  Altitude value is invalid.
     */
    DJIGoToActionErrorInvalidAltitude = 100,
    

    /**
     *  GPS Coordinates of the GoToAction Waypoint is not valid. Latitude value should
     *  be in  the range [-90f, 90f] and longitude value should be in the range [-180f,
     *  180f].
     */
    DJIGoToActionErrorInvalidCoordinates = 101,
    

    /**
     *  Flight speed of the GoToAction Waypoint is not valid. Value should be in range
     *  [2, 15] m/s.
     */
    DJIGoToActionErrorInvalidFlightSpeed = 102,
};


/**
 *  This class represents a go-to action used as an element in a Timeline mission.
 *  By creating an object of this class and adding it to Mission Control's Timeline,
 *  the aircraft will go to a specified location when the Timeline reaches the
 *  action.
 */
@interface DJIGoToAction : DJIMissionAction


/**
 *  Flight speed of the aircraft when going to the target location. Default is 8
 *  m/s.
 */
@property(nonatomic, assign) float flightSpeed;


/**
 *  The target coordinate of the go-to action.
 */
@property (readonly) CLLocationCoordinate2D coordinate;


/**
 *  The target altitude in meters.
 */
@property (readonly) CLLocationDistance altitude;


/**
 *  Go to the specified coordinate from the current aircraft position.
 *  
 *  @param coordinate Target coordinate.
 *  
 *  @return An instance of `DJIGoToAction`.
 */
- (instancetype _Nullable)initWithCoordinate:(CLLocationCoordinate2D)coordinate;


/**
 *  Go to the specified altitude (in meters) from the current aircraft position.
 *  
 *  @param altitude Target altitude in meters.
 *  
 *  @return An instance of `DJIGoToAction`.
 */
- (instancetype _Nullable)initWithAltitude:(CLLocationDistance)altitude;


/**
 *  Go to the specified coordinate and altitude (in meters) from the current
 *  aircraft position.
 *  
 *  @param coordinate Target coordinate.
 *  @param altitude Target altitude in meters.
 *  
 *  @return An instance of `DJIGoToAction`.
 */
- (instancetype _Nullable)initWithCoordinate:(CLLocationCoordinate2D)coordinate altitude:(CLLocationDistance)altitude;



@end

NS_ASSUME_NONNULL_END
