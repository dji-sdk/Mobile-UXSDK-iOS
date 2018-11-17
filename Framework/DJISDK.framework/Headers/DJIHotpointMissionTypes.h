//
//  DJIHotpointMissionTypes.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import "DJISDKFoundation.h"

#ifndef DJIHotpointMissionTypes_h
#define DJIHotpointMissionTypes_h


/**
 *  Maximum radius, in meters, of the circular path the aircraft will fly around the
 *  point of interest. Currently 500m.
 */
DJI_API_EXTERN const float DJIHotpointMaxRadius;


/**
 *  Minimum radius, in meters, of the circular path the aircraft will fly around the
 *  point of interest.
 */
DJI_API_EXTERN const float DJIHotpointMinRadius;


/**
 *  Maximum altitude in meters for a Hotpoint mission.
 */
DJI_API_EXTERN const float DJIHotpointMaxAltitude;


/**
 *  Minimum altitude in meters for a Hotpoint mission.
 */
DJI_API_EXTERN const float DJIHotpointMinAltitude;



/**
 *  Aircraft starting point relative to the hot point.
 */
typedef NS_ENUM (NSUInteger, DJIHotpointStartPoint){
    

    /**
     *  Start from the North.
     */
    DJIHotpointStartPointNorth,
    

    /**
     *  Start from the South.
     */
    DJIHotpointStartPointSouth,
    

    /**
     *  Start from the West.
     */
    DJIHotpointStartPointWest,
    

    /**
     *  Start from the East.
     */
    DJIHotpointStartPointEast,
    

    /**
     *  Start the circle surrounding the hotpoint at the nearest point on the  circle to
     *  the aircraft's current location.
     */
    DJIHotpointStartPointNearest,
};


/**
 *  Heading of the aircraft while orbiting the hot point.
 */
typedef NS_ENUM (NSUInteger, DJIHotpointHeading){
    

    /**
     *  Heading is in the forward direction of travel along the circular path.
     */
    DJIHotpointHeadingAlongCircleLookingForward,
    

    /**
     *  Heading is in the backward direction of travel along the circular path.
     */
    DJIHotpointHeadingAlongCircleLookingBackward,
    

    /**
     *  Heading is toward the hot point.
     */
    DJIHotpointHeadingTowardHotpoint,
    

    /**
     *  Heading of the aircraft is looking away from the hot point. It is in the
     *  direction of the vector defined from the hot point to the aircraft.
     */
    DJIHotpointHeadingAwayFromHotpoint,
    

    /**
     *  Heading is controlled by the remote controller.
     */
    DJIHotpointHeadingControlledByRemoteController,
    

    /**
     *  The heading remains the same as the heading of the aircraft when the mission
     *  started.
     */
    DJIHotpointHeadingUsingInitialHeading
};


#endif /* DJIHotPointMissionTypes_h */
