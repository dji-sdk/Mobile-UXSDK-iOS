//
//  DUXSpotlightWidget.h
//  DJIUXSDK
//
//  Created by Jason Rinn on 10/12/18.
//  Copyright © 2018 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Tapping the widget opens the spotlight settings panel. The widget will be hidden
 *  automatically if the accessory is not present or not supported.
 */
@interface DUXSpotlightWidget : DUXWidget


/**
 *  `YES` if spotlight accessory is supported, `NO` otherwise.
 */
@property (readonly) BOOL isSupported;


/**
 *  Current state of the spotlight. It is enabled from the spotlight settings panel.
 */
@property (readonly) BOOL isEnabled;

@end
