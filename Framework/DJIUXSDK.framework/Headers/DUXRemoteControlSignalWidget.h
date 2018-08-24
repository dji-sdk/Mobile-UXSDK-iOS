//
//  DUXRemoteControlSignalWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DUXWidget.h>


/**
 *  Number of bars to show in widget
 */
typedef NS_ENUM(NSUInteger, DUXRemoteSignalBars) {

    /**
     *  Show no bars.
     */
    DUXRemoteSignalBarsLevel0,

    /**
     *  Show 1 bar.
     */
    DUXRemoteSignalBarsLevel1,

    /**
     *  Show 2 bars.
     */
    DUXRemoteSignalBarsLevel2,

    /**
     *  Show 3 bars.
     */
    DUXRemoteSignalBarsLevel3,

    /**
     *  Show 4 bars.
     */
    DUXRemoteSignalBarsLevel4,

    /**
     *  Show 5 bars.
     */
    DUXRemoteSignalBarsLevel5
};


/**
 *  Display:
 *  Icon with 5 vertical bars total represents the current signal strength between
 *  RC and aircraft.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 19:9.
 */
@interface DUXRemoteControlSignalWidget : DUXWidget


/**
 *  Signal strength represented in percent.
 */
@property (nonatomic, assign, readonly) NSInteger remoteSignalStrength;


/**
 *  Signal strength broken into threasholds which relate to the number of bars to
 *  show.
 */
@property (nonatomic, assign, readonly) DUXRemoteSignalBars bars;

@end
