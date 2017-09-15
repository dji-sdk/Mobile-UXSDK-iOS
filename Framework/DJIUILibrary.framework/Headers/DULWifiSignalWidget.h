//
//  DULWifiSignalWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUILibrary/DJIUILibrary.h>


/**
 *  Display:
 *  Widget that displays the aircraft's WiFi signal strength and channel.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 1:1
 */
@interface DULWifiSignalWidget : DULWidget


/**
 *  WiFi signal strength.
 */
@property (nonatomic, assign, readonly) NSInteger wifiSignalStrength;


/**
 *  The channel that WiFi is currently using.
 */
@property (nonatomic, assign, readonly) NSInteger wifiChannelNumber;

@end
