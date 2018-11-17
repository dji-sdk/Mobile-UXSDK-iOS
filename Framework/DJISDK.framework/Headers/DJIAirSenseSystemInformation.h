//
//  DJIAirSenseSystemInformation.h
//  DJISDK
//
//  Copyright © 2017 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>


NS_ASSUME_NONNULL_BEGIN


/**
 *  The warning level determined by the DJI AirSense system. The warning level is
 *  based on the distance between the airplane and the DJI aircraft, and the heading
 *  of the airplane.
 */
typedef NS_ENUM(NSUInteger, DJIAirSenseWarningLevel) {

    /**
     *  The system detects the airplane but the DJI aircraft is either far away from the
     *  airplane or is in the opposite direction of the airplane's heading.
     */
    DJIAirSenseWarningLevel0,

    /**
     *  The system detects the airplane. The probability that it will pass through the
     *  location of the DJI aircraft is considered low.
     */
    DJIAirSenseWarningLevel1,

    /**
     *  The system detects the airplane. The probability that it will pass through the
     *  location of the DJI aircraft is considered medium.
     */
    DJIAirSenseWarningLevel2,

    /**
     *  The system detects the airplane. The probability that it will pass through the
     *  location of the DJI aircraft is considered high.
     */
    DJIAirSenseWarningLevel3,

    /**
     *  The system detects the airplane. The probability that it will pass through the
     *  location of the DJI aircraft is very high.
     */
    DJIAirSenseWarningLevel4,

    /**
     *  Unknown.
     */
    DJIAirSenseWarningLevelUnknown = 0xFF
};


/**
 *  Directions.
 */
typedef NS_ENUM(NSUInteger, DJIAirSenseDirection) {

    /**
     *  North.
     */
    DJIAirSenseDirectionNorth,

    /**
     *  North east.
     */
    DJIAirSenseDirectionNorthEast,

    /**
     *  East.
     */
    DJIAirSenseDirectionEast,

    /**
     *  South east.
     */
    DJIAirSenseDirectionSouthEast,

    /**
     *  South.
     */
    DJIAirSenseDirectionSouth,

    /**
     *  South west.
     */
    DJIAirSenseDirectionSouthWest,

    /**
     *  West.
     */
    DJIAirSenseDirectionWest,

    /**
     *  North west.
     */
    DJIAirSenseDirectionNorthWest,

    /**
     *  Unknown.
     */
    DJIAirSenseDirectionUnknown = 0xFF
};


/**
 *  The AirSense state of an airplane.
 *  DJI AirSense only sends out warnings of nearby civil aircraft under certain
 *  circumstances; it will NOT control DJI aircraft to avoid other aircraft
 *  automatically. Make sure to fly with your aircraft within visual line of sight
 *  at all times, and always fly with caution. After receiving warnings, lower your
 *  aircraft to a safe height. In addition, DJI AirSense has the following
 *  limitations:
 *  1. DJI AirSense can only receive messages sent from civil aircraft equipped with
 *  an ADS-B out device under 1090ES (RTCA DO-260) or UAT (RTCA Do-282) standards.
 *  For civil aircraft without ADS-B outs or with malfunctioning ADS-B outs, DJI
 *  AirSense cannot receive related broadcasted messages or send out warnings.
 *  2. When there are obstacles in between a civil aircraft and DJI aircraft, DJI
 *  AirSense will fail to receive ADS-B messages sent from civil aircraft or to send
 *  out warnings.
 *  3. DJI AirSense may fail to receive ADS-B messages sent from civil aircraft or
 *  send out warnings due to ever changing circumstances and interference. It is
 *  highly recommended to fly with caution and stay aware of your surroundings
 *  during flight.
 *  4. DJI AirSense cannot send out warnings when the DJI aircraft cannot accurately
 *  determine its location.
 *  5. DJI AirSense cannot receive ADS-B messages sent from civil aircraft or send
 *  out warnings when it is disabled or misconfigured.
 */
@interface DJIAirSenseAirplaneState : NSObject


/**
 *  The unique code (ICAO) of the airplane.
 */
@property (nonatomic, readonly) NSString *code;

/**
 *  The warning level determined by DJI AirSense system.
 */
@property (nonatomic, readonly) DJIAirSenseWarningLevel warningLevel;


/**
 *  The direction of the airplane relative to the DJI aircraft.
 */
@property (nonatomic, readonly) DJIAirSenseDirection relativeDirection;

/**
 *  The heading of the airplane.
 */
@property (nonatomic, readonly) float heading;

/**
 *  The distance between the airplane and DJI aircraft in meters.
 */
@property (nonatomic, readonly) NSInteger distance;

@end


/**
 *  The state of DJI AirSense system. It contains the overall warning level and the
 *  detailed state of each detected airplane.
 */
@interface DJIAirSenseSystemInformation : NSObject


/**
 *  The overall system warning level. This will be the worst case of all individual
 *  aircraft warning levels.
 */
@property (nonatomic, readonly) DJIAirSenseWarningLevel systemWarningLevel;


/**
 *  The state of all airplanes detected by DJI AirSense system.
 */
@property (nonatomic, readonly) NSArray<DJIAirSenseAirplaneState *> *airplaneStates;

@end

NS_ASSUME_NONNULL_END

