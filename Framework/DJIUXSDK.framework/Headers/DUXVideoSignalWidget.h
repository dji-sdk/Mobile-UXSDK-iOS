//
//  DUXVideoSignalWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DUXWidget.h>

// ICR: Remove None or 0. (Same as DUXRemoteSignalStrength)

/**
 *  Number of bars to show in widget
 */
typedef NS_ENUM(NSUInteger, DUXVideoSignalStrength) {

    /**
     *  0 Bars.
     */
    DUXVideoSignalStrengthLevel0,

    /**
     *  1 Bar.
     */
    DUXVideoSignalStrengthLevel1,

    /**
     *  2 Bars.
     */
    DUXVideoSignalStrengthLevel2,

    /**
     *  3 Bars.
     */
    DUXVideoSignalStrengthLevel3,

    /**
     *  4 Bars.
     */
    DUXVideoSignalStrengthLevel4,

    /**
     *  5 Bars.
     */
    DUXVideoSignalStrengthLevel5,

    /**
     *  0 Bars.
     */
    DUXVideoSignalStrengthNone
};


/**
 *  Display:
 *  5 vertical bars represents the current Video signal strength.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 19:11.
 */
@interface DUXVideoSignalWidget : DUXWidget


/**
 *  The value in a percentage that represents signal strength.
 */
@property (nonatomic, assign, readonly) NSInteger videoSignalStrength;


/**
 *  Signal strength broken into threasholds which relate to the number of bars to
 *  show.
 */
@property (nonatomic, assign, readonly) DUXVideoSignalStrength videoSignal;


@end
