//
//  DUXTakeOffWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Current state of the takeoff widget.
 */
typedef NS_ENUM(NSUInteger, DUXAircraftTakeOffLandingState) {

    /**
     *  Widget is enabled and tapping it will cause the aircraft to take off.
     */
    DUXAircraftTakeOffLandingStateTakeOffEnabled,

    /**
     *  Widget is enabled and tapping it will cause the aircraft to land.
     */
    DUXAircraftTakeOffLandingStateLandEnabled,

    /**
     *  Widget is greyed out because drone can not currently perform  landing action.
     */
    DUXAircraftTakeOffLandingStateDisabled,

    /**
     *  Take off or landing is currently in progress and tapping the red cancel icon
     *  will  cause the action in progress to be cancelled.
     */
    DUXAircraftTakeOffLandingStateCancel
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
