//
//  DUXTakeOffWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Flying state of the aircraft
 */
typedef NS_ENUM(NSUInteger, DUXAircraftTakeOffLandingState) {

    /**
     *  Aircraft is not flying.
     */
    DUXAircraftTakeOffLandingStateLanded,

    /**
     *  Aircraft is currently flying.
     */
    DUXAircraftTakeOffLandingStateFlying,

    /**
     *  Aircraft is currently in the process of landing.
     */
    DUXAircraftTakeOffLandingStateLanding
};


/**
 *  Display:
 *  Widget has three states with three different interactions.
 *   - White icon with arrow up indicates the aircraft is not flying and the widget
 *  interaction is to start taking off.
 *   - White icon with arrow down indicates the aircraft is flying and the widget
 *   interaction is to start landing.
 *   - Red icon indicates the aircraft is landing and the widget interaction is
 *   to cancel landing.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 1:1
 *  
 *  Interaction:
 *  Tapping the widget will open up a Dialog to confirm the desired action. Slide
 *  the dialog from left to right to start the action.
 */
@interface DUXTakeOffWidget : DUXWidget


/**
 *  The current flying state of the aircraft used to determine which image to use
 *  with the widget.
 */
@property DUXAircraftTakeOffLandingState aircraftState;

@end
