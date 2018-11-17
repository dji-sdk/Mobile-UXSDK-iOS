//
//  DJIPanoramaMissionTypes.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 *  Defines options for different types of modes for Panorama mission.
 */
typedef NS_ENUM (NSUInteger, DJIPanoramaMode) {


    /**
     *  360 Degree Panorama mode.
     */
    DJIPanoramaModeFullCircle = 0,


    /**
     *  180 Degree Panorama mode. Also known as selfie mode.
     */
    DJIPanoramaModeHalfCircle,


    /**
     *  Unknown mode.
     */
    DJIPanoramaModeUnknown = 0xFF
};


/**
 *  This class provides the real-time status of an executing Panorama mission.
 */
@interface DJIPanoramaMissionExecutionState : NSObject


/**
 *  The total number of photos that will be shot during the mission. In full circle
 *  mode,  the number should be 8. In the half circle mode, the number should be 5.
 */
@property(nonatomic, readonly) NSUInteger totalNumber;


/**
 *  The number of photos that have been shot.
 */
@property(nonatomic, readonly) NSUInteger currentShotNumber;


/**
 *  The number of photos that have been saved to SD card.
 */
@property(nonatomic, readonly) NSUInteger currentSavedNumber;


@end
