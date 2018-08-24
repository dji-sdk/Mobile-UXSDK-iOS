//
//  DUXFlightModeWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Display:
 *  Has the same behavior as DJIGO's element. 1. The text inside white bubble shows
 *  the remaining flight time in minutes and seconds. 2. The middle line stretches
 *  along the width of the widget represents remaining battery percentage of the
 *  aircraft. If remaining battery is 100%, the line will cover the whole width of
 *  widget. If remaining battery is 0%, the line will disappear.
 *    - Red part of the line represents the battery percentage needed
 *    to land aircraft immediately.
 *    - Yellow part of the line represents the battery percentage needed to
 *    return aircraft home.
 *    - Green part of the line represents the battery percentage left to fly safely.
 *  3. The two white dots represent the two settable battery threshold.
 *    - The first one from the left represents the land immediately threshold.
 *    - The second one represents the go home threshold.
 *  4. The `H` icon is an addition to yellow part of the line. It represents the
 *  battery percentage needed to go home.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 612:12
 */
@interface DUXRemainingFlightTimeWidget : DUXWidget

@end
