//
//  DULBatteryWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <DJIUILibrary/DULWidget.h>


/**
 *  Enum describing the battery state.
 */
typedef NS_ENUM(NSUInteger, DULBatteryIndicatorState) {

    /**
     *  Normal
     */
    DULBatteryIndicatorStateNormal,

    /**
     *  Error.
     */
    DULBatteryIndicatorStateError,

    /**
     *  Battery Warning level 1.
     */
    DULBatteryIndicatorStateWarningLevel1,

    /**
     *  Battery Warning level 2.
     */
    DULBatteryIndicatorStateWarningLevel2,

    /**
     *  Battery state unknown.
     */
    DULBatteryIndicatorStateUnknown
};


/**
 *  Display:
 *  Battery icon has two color states. White color indicates everything is ok. Icon
 *  will change into red color if aircraft needs to return home, land immediately,
 *  or battery connection is bad. Text shows percentage of charge remaining in
 *  battery. Text also has two color states. Green indicates the percentage is ok.
 *  Red indicates the percentage is either below or just enough for returning home
 *  or landing immediately.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 22:9.
 */
@interface DULBatteryWidget : DULWidget


/**
 *  Battery percentage with range [0,100].
 */
@property (nonatomic, assign, readonly) float battery1Percentage;


/**
 *  Battery percentage with range [0,100].
 */
@property (nonatomic, assign, readonly) float battery2Percentage;


/**
 *  The current state of the battery for the purpose of visual representation.
 */
@property (nonatomic, assign) DULBatteryIndicatorState battery1IndicatorState;


/**
 *  The current state of the 2nd battery for the purpose of visual representation.
 */
@property (nonatomic, assign) DULBatteryIndicatorState battery2IndicatorState;



@end
