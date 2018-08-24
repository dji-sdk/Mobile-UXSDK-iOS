//
//  DUXPreFlightStatusWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>

typedef NS_ENUM(NSInteger, DUXPreFlightStatusWidgetState) {
    DUXPreFlightStatusWidgetStateDisconnected,
    DUXPreFlightStatusWidgetStateSafe,
    DUXPreFlightStatusWidgetStateWarning,
    DUXPreFlightStatusWidgetStateError,
};


/**
 *  Display:
 *  The text shows a summary of the preflight checklist situation of the aircraft.
 *  The color of the background changes depends on how severe the situation is.
 *  Green indicates everything is ok. Yellow indicates something is at warning
 *  level. Red indicates something is wrong and aircraft won't take off.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 297:32.
 *  
 *  Interaction:
 *  Tapping on status text will toggle between show and hide
 *  `DUXPreflightChecklistController`.
 */
@interface DUXPreFlightStatusWidget : DUXWidget


/**
 *  The current state of the preflight checklist system used by this widget
 */
@property DUXPreFlightStatusWidgetState currentState;

@end
