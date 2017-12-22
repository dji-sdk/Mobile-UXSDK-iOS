//
//  DULVideoSignalWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUILibrary/DULWidget.h>

// ICR: Remove None or 0. (Same as DULRemoteSignalStrength)

/**
 *  Number of bars to show in widget
 */
typedef NS_ENUM(NSUInteger, DULVideoSignalStrength) {

    /**
     *  0 Bars.
     */
    DULVideoSignalStrengthLevel0,

    /**
     *  1 Bar.
     */
    DULVideoSignalStrengthLevel1,

    /**
     *  2 Bars.
     */
    DULVideoSignalStrengthLevel2,

    /**
     *  3 Bars.
     */
    DULVideoSignalStrengthLevel3,

    /**
     *  4 Bars.
     */
    DULVideoSignalStrengthLevel4,

    /**
     *  5 Bars.
     */
    DULVideoSignalStrengthLevel5,

    /**
     *  0 Bars.
     */
    DULVideoSignalStrengthNone
};


/**
 *  Display:
 *  5 vertical bars represents the current Video signal strength.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 19:11.
 */
@interface DULVideoSignalWidget : DULWidget


/**
 *  The value in a percentage that represents signal strength.
 */
@property (nonatomic, assign, readonly) NSInteger videoSignalStrength;


/**
 *  Signal strength broken into threasholds which relate to the number of bars to
 *  show.
 */
@property (nonatomic, assign, readonly) DULVideoSignalStrength videoSignal;


@end
