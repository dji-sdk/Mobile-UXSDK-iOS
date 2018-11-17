//
//  DJIRTK.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <DJISDK/DJIBaseProduct.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIRTK;
@class DJIRTKState;


/**
 *  This enum defines the positioning solution currently being used.
 */
typedef NS_ENUM (NSInteger, DJIRTKPositioningSolution){


    /**
     *  No positioning solution. This can be caused by an insufficient number of
     *  satellites in view, insufficient time to lock onto the satellites, or a loss in
     *  communication link between the mobile station and base station.
     */
    DJIRTKPositioningSolutionNone,


    /**
     *  RTK point positioning.
     */
    DJIRTKPositioningSolutionSinglePoint,


    /**
     *  Float solution positioning.
     */
    DJIRTKPositioningSolutionFloat,


    /**
     *  Fixed-point solution positioning (most accurate).
     */
    DJIRTKPositioningSolutionFixedPoint,
};


/**
 *  This protocol provides a delegate method to update the RTK state.
 */
@protocol DJIRTKDelegate <NSObject>

@optional


/**
 *  Callback function that updates the RTK state data.
 *  
 *  @param rtk Instance of the RTK.
 *  @param state Current state of the RTK.
 */
- (void)rtk:(DJIRTK *_Nonnull)rtk didUpdateState:(DJIRTKState *_Nonnull)state;

@end


/**
 *  Single RTK receiver information. Each receiver is connected to a single antenna.
 */
@interface DJIRTKReceiverInfo : NSObject


/**
 *  `YES` if constellation is supported. The European and American versions of RTK
 *  support GPS and GLONASS, while the Asia Pacific version supports GPS and BeiDou.
 */
@property(nonatomic, readonly) BOOL isConstellationSupported;


/**
 *  Valid satellite count for this receiver.
 */
@property(nonatomic, readonly) NSInteger satelliteCount;

@end


/**
 *  This class holds the state of the RTK system, including position, positioning
 *  solution, and receiver information.
 */
@interface DJIRTKState : NSObject


/**
 *  Gets RTK errors, if any. Returns `nil` when RTK is normal.
 */
@property(nonatomic, readonly) NSError *_Nullable error;


/**
 *  The positioning solution describes the method used to determine positioning. The
 *  solutions vary in accuracy, from `DJIRTKPositioningSolutionNone` (no
 *  positioning) to `DJIRTKPositioningSolutionFixedPoint`.
 */
@property(nonatomic, readonly) DJIRTKPositioningSolution positioningSolution;


/**
 *  Mobile station (aircraft) receiver 1 GPS info.
 */
@property(nonatomic, readonly) DJIRTKReceiverInfo *_Nonnull mobileStationReceiver1GPSInfo;


/**
 *  Mobile station (aircraft) receiver 1 BeiDou info.
 */
@property(nonatomic, readonly) DJIRTKReceiverInfo *_Nonnull mobileStationReceiver1BeiDouInfo;


/**
 *  Mobile station (aircraft) receiver 1 GLONASS info.
 */
@property(nonatomic, readonly) DJIRTKReceiverInfo *_Nonnull mobileStationReceiver1GLONASSInfo;


/**
 *  Mobile station (aircraft) receiver 2 GPS info.
 */
@property(nonatomic, readonly) DJIRTKReceiverInfo *_Nonnull mobileStationReceiver2GPSInfo;


/**
 *  Mobile station (aircraft) receiver 2 BeiDou info.
 */
@property(nonatomic, readonly) DJIRTKReceiverInfo *_Nonnull mobileStationReceiver2BeiDouInfo;


/**
 *  Mobile station (aircraft) receiver 2 GLONASS info.
 */
@property(nonatomic, readonly) DJIRTKReceiverInfo *_Nonnull mobileStationReceiver2GLONASSInfo;


/**
 *  Base station receiver GPS info.
 */
@property(nonatomic, readonly) DJIRTKReceiverInfo *_Nonnull baseStationReceiverGPSInfo;


/**
 *  Base station receiver BeiDou info.
 */
@property(nonatomic, readonly) DJIRTKReceiverInfo *_Nonnull baseStationReceiverBeiDouInfo;


/**
 *  Base station receiver GLONASS info.
 */
@property(nonatomic, readonly) DJIRTKReceiverInfo *_Nonnull baseStationReceiverGLONASSInfo;


/**
 *  Location information of the mobile station's receiver 1 antenna. This location
 *  information is relative to the base station location and is in degrees.
 */
@property(nonatomic, readonly) CLLocationCoordinate2D mobileStationLocation;


/**
 *  Altitude of the mobile station's receiver 1 antenna relative, to sea level.
 *  Units are meters.
 */
@property(nonatomic, readonly) float mobileStationAltitude;


/**
 *  The fusion location of the mobile station (in degrees). It is the combination of
 *  GPS and RTK. The flight controller uses this location for navigation (e.g.
 *  waypoint mission) when RTK is available.
 */
@property(nonatomic, readonly) CLLocationCoordinate2D mobileStationFusionLocation;


/**
 *  The fusion altitude of the mobile station. It is the combination of GPS, RTK and
 *  the barometer. The flight controller uses this altitude for navigation (e.g.
 *  waypoint mission) when RTK is available.
 */
@property(nonatomic, readonly) float mobileStationFusionAltitude;


/**
 *  The fusion heading of the mobile station. It is the combination of RTK and the
 *  compass. The flight controller uses this heading for navigation (e.g. waypoint
 *  mission) when RTK is available.
 */
@property(nonatomic, readonly) float mobileStationFusionHeading;


/**
 *  Base station's location coordinates, in degrees.
 */
@property(nonatomic, readonly) CLLocationCoordinate2D baseStationLocation;


/**
 *  Altitude of the base station above sea level, in meters.
 */
@property(nonatomic, readonly) float baseStationAltitude;


/**
 *  Heading relative to True North as defined by the vector formed from Antenna 2 to
 *  Antenna 1 on the mobile station. Unit is degrees.
 */
@property(nonatomic, readonly) float heading;


/**
 *  `YES` if heading value is valid. Heading is invalid when a satellite fix hasn't
 *  been obtained.
 */
@property(nonatomic, readonly) BOOL isHeadingValid;


/**
 *  Returns state of RTK (enabled/disabled).
 */
@property(nonatomic, readonly) BOOL isRTKEnabled;


/**
 *  Whether the RTK is being used.
 */
@property(nonatomic, readonly) BOOL isRTKBeingUsed;

@end


/**
 *  Real Time Kinematic
 */
@interface DJIRTK : NSObject


/**
 *  DJI RTK delegate.
 */
@property(nonatomic, weak) id<DJIRTKDelegate> delegate;


/**
 *  `YES` if RTK is connected to the aircraft.
 */
@property(nonatomic, readonly) BOOL isConnected;


/**
 *  Enables RTK positioning. Disable RTK when in poor signal environments, where
 *  incorrect positioning information might make controlling the aircraft difficult.
 *  Can only be set when the motors are off.
 *  
 *  @param enabled `YES` to enable RTK positioning.
 *  @param completion Completion block that receives setter result.
 */
- (void)setRTKEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END
