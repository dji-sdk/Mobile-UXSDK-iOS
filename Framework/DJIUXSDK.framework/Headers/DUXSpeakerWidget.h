//
//  DUXSpeakerWidget.h
//  DJIUXSDK
//
//  Copyright © 2018 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Tapping the widget opens the speaker settings panel. The widget will be hidden
 *  automatically if the accessory is not present or not supported.
 */
@interface DUXSpeakerWidget : DUXWidget


/**
 *  `YES` if speaker accessory is supported, `NO` otherwise.
 */
@property (readonly) BOOL isSupported;


/**
 *  Current state of the speaker accessory. It will be toggled when user taps on the
 *  widget.
 */
@property (readonly) BOOL isEnabled;

@end
