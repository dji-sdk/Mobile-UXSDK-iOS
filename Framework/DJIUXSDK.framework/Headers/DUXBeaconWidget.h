//
//  DUXBeaconWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Widget is used to turn on and turn off the Beacon accessory on Mavic 2
 *  Enterprise.
 *  
 *  Interaction:
 *  Tapping the widget will enable/disable the flashing of the external beacon
 *  accessory.  The widget will be hidden automatically if the accessory is not
 *  present or not supported.
 */
@interface DUXBeaconWidget : DUXWidget


/**
 *  `YES` if beacon accessory is supported, `NO` otherwise.
 */
@property (readonly) BOOL isSupported;


/**
 *  Current state of the beacon accessory. It will be toggled when user taps on the
 *  widget.
 */
@property (readonly) BOOL isEnabled;

@end
