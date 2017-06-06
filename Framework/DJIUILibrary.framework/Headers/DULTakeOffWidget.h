//
//  DULTakeOffWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUILibrary/DJIUILibrary.h>


/**
 *  Flying state of the aircraft
 */
typedef NS_ENUM(NSUInteger, DULAircraftTakeOffLandingState) {

    /**
     *  Aircraft is not flying.
     */
    DULAircraftTakeOffLandingStateLanded,

    /**
     *  Aircraft is currently flying.
     */
    DULAircraftTakeOffLandingStateFlying,

    /**
     *  Aircraft is currently in the process of landing.
     */
    DULAircraftTakeOffLandingStateLanding
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
@interface DULTakeOffWidget : DULWidget


/**
 *  The current flying state of the aircraft used to determine which image to use
 *  with the widget.
 */
@property DULAircraftTakeOffLandingState aircraftState;

@end
