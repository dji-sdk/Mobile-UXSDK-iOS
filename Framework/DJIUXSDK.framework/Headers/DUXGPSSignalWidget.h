//
//  DUXGPSSignalWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DUXWidget.h>

typedef NS_ENUM(NSUInteger, DUXGPSSatelliteStrength) {
    DUXGPSSatelliteStrengthLevel0,
    DUXGPSSatelliteStrengthLevel1,
    DUXGPSSatelliteStrengthLevel2,
    DUXGPSSatelliteStrengthLevel3,
    DUXGPSSatelliteStrengthLevel4,
    DUXGPSSatelliteStrengthLevel5,
    DUXGPSSatelliteStrengthNone
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
@interface DUXGPSSignalWidget : DUXWidget


/**
 *  The number of satellites in use.
 */
@property (nonatomic, assign, readonly) NSInteger satelliteCount;


/**
 *  The value representing signal strength.
 */
@property (nonatomic, assign, readonly) DUXGPSSatelliteStrength satelliteSignal;


/**
 *  Indicates whether RTK is enabled.
 */
@property (nonatomic, assign, readonly, getter=isRTKEnabled) BOOL RTKEnabled;

@end
