//
//  DJILandingGearStructs.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#ifndef DJILandingGearStructs_h
#define DJILandingGearStructs_h


/**
 *  Current state of landing gear.
 */
typedef NS_ENUM (uint8_t, DJILandingGearState){
 

    /**
     *  Landing gear is in unknown state. This will be returned if the aircraft can't
     *  get the landing gear status.
     */
    DJILandingGearStateUnknown,
 

    /**
     *  Landing gear is fully deployed (ready for landing)
     */
    DJILandingGearStateDeployed,
 

    /**
     *  Landing gear is fully retracted (ready for flying).
     */
    DJILandingGearStateRetracted,
 

    /**
     *  Landing gear is deploying (getting ready for landing).
     */
    DJILandingGearStateDeploying,
 

    /**
     *  Landing gear is retracting (getting ready for flying).
     */
    DJILandingGearStateRetracting,
 

    /**
     *  Landing gear is stopped.
     */
    DJILandingGearStateStopped,
};


/**
 *  Current Mode of the landing gear.
 */
typedef NS_ENUM (uint8_t, DJILandingGearMode){
 

    /**
     *  Landing gear can be deployed and retracted through function calls.
     */
    DJILandingGearModeManual,
 

    /**
     *  Landing gear is in transport mode (either it is moving into, moving out of, or
     *  stopped in transport position).
     */
    DJILandingGearModeTransport,
 

    /**
     *  Landing gear automatically transitions between deployed and retracted depending
     *  on altitude. During take-off,  the transition point is 1.2m above ground. After
     *  take-off (during flight or when landing), the transition point  is 0.5m above
     *  ground.
     */
    DJILandingGearModeAuto,
 

    /**
     *  Landing Gear is in an unknown mode.
     */
    DJILandingGearModeUnknown,
};

#endif /* DJILandingGearStructs_h */
