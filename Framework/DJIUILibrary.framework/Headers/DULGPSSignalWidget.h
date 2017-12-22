//
//  DULGPSSignalWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUILibrary/DULWidget.h>

typedef NS_ENUM(NSUInteger, DULGPSSatelliteStrength) {
    DULGPSSatelliteStrengthLevel0,
    DULGPSSatelliteStrengthLevel1,
    DULGPSSatelliteStrengthLevel2,
    DULGPSSatelliteStrengthLevel3,
    DULGPSSatelliteStrengthLevel4,
    DULGPSSatelliteStrengthLevel5,
    DULGPSSatelliteStrengthNone
};


/**
 *  Display:
 *  Small number on top of satellite icon shows the number of satellite available. 5
 *  vertical bars represents the current GPS signal strength. Small 'R' letter shown
 *  or hidden indicates weather RTK is enabled or not.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 38:15.
 */
@interface DULGPSSignalWidget : DULWidget


/**
 *  The number of satellites in use.
 */
@property (nonatomic, assign, readonly) NSInteger satelliteCount;


/**
 *  The value representing signal strength.
 */
@property (nonatomic, assign, readonly) DULGPSSatelliteStrength satelliteSignal;


/**
 *  Indicates whether RTK is enabled.
 */
@property (nonatomic, assign, readonly, getter=isRTKEnabled) BOOL RTKEnabled;

@end
