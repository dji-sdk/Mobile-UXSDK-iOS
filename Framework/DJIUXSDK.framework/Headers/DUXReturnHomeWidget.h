//
//  DUXReturnHomeWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Display:
 *  Widget has two states with two different interactions.
 *   - White icon with arrow down indicates the aircraft is flying and the widget
 *   interaction is to start returning home.
 *   - Red icon indicates the aircraft is returning home and the widget interaction
 *  is
 *   to cancel returning home.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 23:22.
 *  
 *  Interaction:
 *  Tapping the widget will open up a Dialog to confirm the desired action. Slide
 *  the dialog from left to right to start the action.
 */
@interface DUXReturnHomeWidget : DUXWidget

@end
