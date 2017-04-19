//
//  DULRemoteControlSignalWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import "DULWidget.h"


/**
 *  Number of bars to show in widget
 */
typedef NS_ENUM(NSUInteger, DULRemoteSignalBars) {

    /**
     *  Show no bars.
     */
    DULRemoteSignalBarsLevel0,

    /**
     *  Show 1 bar.
     */
    DULRemoteSignalBarsLevel1,

    /**
     *  Show 2 bars.
     */
    DULRemoteSignalBarsLevel2,

    /**
     *  Show 3 bars.
     */
    DULRemoteSignalBarsLevel3,

    /**
     *  Show 4 bars.
     */
    DULRemoteSignalBarsLevel4,

    /**
     *  Show 5 bars.
     */
    DULRemoteSignalBarsLevel5
};

IB_DESIGNABLE

/**
 *  Display:
 *  Icon with 5 vertical bars total represents the current signal strength between
 *  RC and aircraft.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 19:9.
 */
@interface DULRemoteControlSignalWidget : DULWidget


/**
 *  Signal strength represented in percent.
 */
@property (nonatomic, assign, readonly) NSInteger remoteSignalStrength;


/**
 *  Signal strength broken into threasholds which relate to the number of bars to
 *  show.
 */
@property (nonatomic, assign, readonly) DULRemoteSignalBars bars;

@end
