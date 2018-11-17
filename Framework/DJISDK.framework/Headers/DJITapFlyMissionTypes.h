//
//  DJITapFlyMissionTypes.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#ifndef DJITapFlyMissionTypes_h
#define DJITapFlyMissionTypes_h


/**
 *  Direction aircraft is moving around or bypassing an obstacle in.
 */
typedef NS_ENUM (NSInteger, DJIBypassDirection){
    

    /**
     *  Flying normally, no obstacle to be avoided.
     */
    DJIBypassDirectionNone,
    

    /**
     *  Avoiding the obstacle by going over the top of it.
     */
    DJIBypassDirectionOver,
    

    /**
     *  Avoiding the obstacle by going to the left of it.
     */
    DJIBypassDirectionLeft,
    

    /**
     *  Avoiding the obstacle by going to the right of it.
     */
    DJIBypassDirectionRight,
    

    /**
     *  Unknown obstacle avoidance direction
     */
    DJIBypassDirectionUnknown,
};


/**
 *  Different modes of the TapFly Mission. Defaults to  `DJITapFlyModeForward`, set
 *  to others to enable  the feature.
 */
typedef NS_ENUM (NSInteger, DJITapFlyMode) {
    

    /**
     *  Aircraft will fly towards the target. Forward Obstacle  Sensing System is
     *  active.
     */
    DJITapFlyModeForward,
    

    /**
     *  Aircraft will fly in the opposite direction from the target.  Backward Obstacle
     *  Sensing System is active.
     */
    DJITapFlyModeBackward,
    

    /**
     *  Aircraft will fly towards the target. User can control the heading  by remote
     *  controller's stick. Obstacle Sensing Systems may fail to  work when aircraft is
     *  flying sideward.
     */
    DJITapFlyModeFree,
    

    /**
     *  The TapFly mode is unknown.
     */
    DJITapFlyModeUnknown
};


#endif /* DJITapFlyMissionTypes_h */
