//
//  DJIFlyZoneInformation.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "DJISDKFoundation.h"

NS_ASSUME_NONNULL_BEGIN


/**
 *  DJI Fly Zone Information Invalid Timestamp.
 */
extern NSString *const DJIFlyZoneInformationInvalidTimestamp;


/**
 *  There are three types of fly zones, NFZ, GEO and Poly.
 */
typedef NS_ENUM (uint8_t, DJIFlyZoneType){

    /**
     *  The circle fly zone is a cylinder or truncated cone volume (see `shape`)  with
     *  one of the four restriction levels (see `category`). Some  restrictions can  be
     *  unlocked while others cannot. Some fly zones also have a 4km buffer around them
     *  where flight  height is restricted to 120m.
     */
    DJIFlyZoneTypeCircle,

    /**
     *  The Poly fly zone consists of one or more sub fly zones that are cylinders or
     *  complex volumes with different height limitations. A height limitation of 0m
     *  means flight is completely restricted. This is used by Mavic, Phantom 4 Pro,
     *  Inspire 2 and Phantom 4.
     */
    DJIFlyZoneTypePoly,

    /**
     *  The fly zone is of unknown type.
     */
    DJIFlyZoneTypeUnknown
};


/**
 *  An enum class represents the category of fly zone.
 */
typedef NS_ENUM (uint8_t, DJIFlyZoneCategory){


    /**
     *  Warning zones do not restrict flight and are informational to alert the user. In
     *  a warning zone, users should be  prompted with a warning message describing the
     *  zone.
     */
    DJIFlyZoneCategoryWarning,
    

    /**
     *  Authorization zones restrict flight by default, but can be unlocked by a GEO
     *  authorized user.
     */
    DJIFlyZoneCategoryAuthorization,
    

    /**
     *  Restricted zones restrict flight by default and cannot be unlocked by a GEO
     *  authorized user.  Users should contact flysafe@dji.com if they have
     *  authorization to fly in a restricted zone.
     */
    DJIFlyZoneCategoryRestricted,
    

    /**
     *  Enhanced warning zones do not restrict flight but are highly recommended to be
     *  informational  to alert the user. In an enhanced warning zone, users should be
     *  prompted with a warning message  describing the zone.
     */
    DJIFlyZoneCategoryEnhancedWarning,
    

    /**
     *  Unknown.
     */
    DJIFlyZoneCategoryUnknown = 0xFF
};


/**
 *  An enum class contains the reason for the fly zone.
 */
typedef NS_ENUM(uint8_t, DJIFlyZoneReason) {


    /**
     *  Airport that cannot be unlocked using GEO system.
     */
    DJIFlyZoneReasonAirport,
    

    /**
     *  Military authorized zone. This cannot be unlocked using the GEO system.
     */
    DJIFlyZoneReasonMilitary,
    

    /**
     *  Special Zone. This cannot be unlocked using the GEO system.
     */
    DJIFlyZoneReasonSpecial,
    

    /**
     *  Commercial airport.
     */
    DJIFlyZoneReasonCommercialAirport,
    

    /**
     *  Private commercial airport.
     */
    DJIFlyZoneReasonPrivateCommercialAirport,
    

    /**
     *  Recreational airport.
     */
    DJIFlyZoneReasonRecreationalAirport,
    

    /**
     *  National park.
     */
    DJIFlyZoneReasonNationalPark,
    

    /**
     *  The National Oceanic and Atmospheric Administration.
     */
    DJIFlyZoneReasonNOAA,
    

    /**
     *  Parcel.
     */
    DJIFlyZoneReasonParcel,
    

    /**
     *  Power plant.
     */
    DJIFlyZoneReasonPowerPlant,
    

    /**
     *  Prison.
     */
    DJIFlyZoneReasonPrison,
    

    /**
     *  School.
     */
    DJIFlyZoneReasonSchool,
    

    /**
     *  Stadium.
     */
    DJIFlyZoneReasonStadium,
    

    /**
     *  Prohibited special use.
     */
    DJIFlyZoneReasonProhibitedSpecialUse,
    

    /**
     *  Restriction special use.
     */
    DJIFlyZoneReasonRestrictedSpecialUse,
    

    /**
     *  Temporary flight restriction.
     */
    DJIFlyZoneReasonTemporaryFlightRestriction,
    

    /**
     *  Class B controlled airspace. See http://www.dji.com/flysafe/geo-system#notes for
     *  more information on the  controlled airspace (Class B, C, D, E) in the United
     *  States.
     */
    DJIFlyZoneReasonClassBAirSpace,
    

    /**
     *  Class C controlled airspace. See http://www.dji.com/flysafe/geo-system#notes for
     *  more information on the  controlled airspace (Class B, C, D, E) in the United
     *  States.
     */
    DJIFlyZoneReasonClassCAirSpace,
    

    /**
     *  Class D controlled airspace. See http://www.dji.com/flysafe/geo-system#notes for
     *  more information on the  controlled airspace (Class B, C, D, E) in the United
     *  States.
     */
    DJIFlyZoneReasonClassDAirSpace,


    /**
     *  Class E Controlled Airspace. See http://www.dji.com/flysafe/geo-system#notes for
     *  more information on the  controlled airspace (Class B, C, D, E) in the United
     *  States.
     */
    DJIFlyZoneReasonClassEAirSpace,
    

    /**
     *  Airport with unpaved runway.
     */
    DJIFlyZoneReasonUnpavedAirport,
    

    /**
     *  Heliport.
     */
    DJIFlyZoneReasonHeliport,
    

    /**
     *  Unknown.
     */
    DJIFlyZoneReasonUnknown = 0xFF,
};


/**
 *  An enum class containing the shape of the fly zone.
 */
typedef NS_ENUM(uint8_t, DJIFlyZoneShape) {


    /**
     *  Cylinder.
     */
    DJIFlyZoneShapeCylinder,
    

    /**
     *  Truncated cone that has a smaller radius on the ground and larger radius in the
     *  air.
     */
    DJIFlyZoneShapeCone,
    

    /**
     *  Unknown.
     */
    DJIFlyZoneShapeUnknown = 0xFF
};


/**
 *  This enum describes whether the aircraft is clear of, near, or actually in a fly
 *  zone.
 */
typedef NS_ENUM(uint8_t, DJIFlyZoneState) {


    /**
     *  The aircraft is not within 200 meters of any warning, enhanced warning,
     *  authorization or restricted zone.
     */
    DJIFlyZoneStateClear,
    

    /**
     *  The aircraft is within 200 meters of an authorization or restricted zone.
     */
     DJIFlyZoneStateNearRestrictedZone,


    /**
     *  The aircraft is currently in a warning or enhanced warning zone and this place
     *  will  limit max flight height to 120m.
     */
    DJIFlyZoneStateInWarningZoneWithHeightLimitation,
    

    /**
     *  The aircraft is currently in a warning or enhanced warning zone.
     */
    DJIFlyZoneStateInWarningZone,
    

    /**
     *  The aircraft is currently in an authorization or restricted zone.
     */
    DJIFlyZoneStateInRestrictedZone,
    

    /**
     *  Unknown.
     */
    DJIFlyZoneStateUnknown = 0xFF
};


/**
 *  This type of the geospatial information for the fly zone.
 */
typedef NS_ENUM(NSUInteger, DJISubFlyZoneShape) {

    /**
     *  Circle shape.
     */
    DJISubFlyZoneShapeCylinder,

    /**
     *  Polygon shape.
     */
    DJISubFlyZoneShapePolygon,

    /**
     *  Unknown.
     */
    DJISubFlyZoneShapeUnknown = 0xFF,
    
};


/**
 *  The state of the fly zone database on the aircraft.
 */
typedef NS_ENUM(NSUInteger, DJIFlyZoneDatabaseState) {

    /**
     *  SDK is fetching the information of the database.
     */
    DJIFlyZoneDatabaseStateInitializing,

    /**
     *  SDK cannot access the Internet, so it cannot compare the database version with
     *  the latest one on the Internet.
     */
    DJIFlyZoneDatabaseStateNoInternetConnection,

    /**
     *  Aircraft's database version is older than the latest one.  User should use DJI
     *  Go or Assistant 2 to upgrade the firmware in order  to keep the database up to
     *  date.
     */
    DJIFlyZoneDatabaseStateOutOfDate,

    /**
     *  The database in the aircraft is up to date.
     */
    DJIFlyZoneDatabaseStateUpToDate,

    /**
     *  Unknown state
     */
    DJIFlyZoneDatabaseStateUnknown = 0xFF,
    
};


/**
 *  This class contains information about a Sub fly zone.
 */
@interface DJISubFlyZoneInformation : NSObject


/**
 *  The fly zone's identifier.
 */
@property(nonatomic, readonly) NSInteger areaID;


/**
 *  The shape of the sub-fly-zone.
 *  
 *  @return An enum value of `DJISubFlyZoneShape`.
 */
@property(nonatomic, readonly) DJISubFlyZoneShape shape;


/**
 *  The vertices (locations) that make up the sub fly zone polygon shape. Only used
 *  when `shape` is `DJISubFlyZoneShapePolygon`.
 *  
 *  @return A List of CLLocationCoordinate2D object.
 */
@property(nonatomic, readonly) NSArray *vertices;


/**
 *  Maximum flight height in meters allowed in the sub fly zone. A height of 0m will
 *  restrict flight completely within the zone.
 */
@property(nonatomic, readonly) NSInteger maximumFlightHeight;


/**
 *  The location of the fly zone's center. Only used when `shape` is
 *  `DJISubFlyZoneShapeCylinder`.
 *  
 *  @return A LocationCoordinate2D object.
 */
@property(nonatomic, readonly) CLLocationCoordinate2D center;


/**
 *  The radius of the fly zone in meters. Only used when `shape` is
 *  `DJISubFlyZoneShapeCylinder`.
 */
@property(nonatomic, readonly) double radius;

@end


/**
 *  This class contains information about a fly zone. `type`  should be used to
 *  understand the type of fly zone to know which information in this class is
 *  valid.
 */
@interface DJIFlyZoneInformation : NSObject


/**
 *  Returns the type fly zone.
 */
@property(nonatomic, readonly) DJIFlyZoneType type;


/**
 *  Returns the fly zone's ID. This is required if unlocking a fly zone.
 */
@property(nonatomic, readonly) NSUInteger flyZoneID;


/**
 *  The name of the fly zone.
 */
@property(nonatomic, readonly) NSString* name;


/**
 *  The coordinate of the fly zone's center. Only used for GEO and NFZ fly zones.
 */
@property(nonatomic, readonly) CLLocationCoordinate2D center;


/**
 *  The radius of the fly zone in meters. If the fly zone is a truncated cone, then
 *  the radius is the bottom of the cone. Only used for GEO and NFZ fly zones.
 */
@property(nonatomic, readonly) double radius;


/**
 *  The timestamp of when the flight warning or flight restriction begins, formatted
 *  in UTC (YYYY-MM-DD hh:mm:ss). This is used for temporary flight  restrictions.
 *  When the time is not available from the server,
 *  `DJIFlyZoneInformationInvalidTimestamp` will be returned.
 */
@property(nonatomic, readonly) NSString* startTime;


/**
 *  The timestamp of when the flight warning or flight restriction ends, formatted
 *  in UTC (YYYY-MM-DD hh:mm:ss). When the time is not available from the server,
 *  `DJIFlyZoneInformationInvalidTimestamp` will be returned.
 */
@property(nonatomic, readonly) NSString* endTime;


/**
 *  The timestamp when the fly zone is unlocked, formatted in UTC (YYYY-MM-DD
 *  hh:mm:ss). When the time is  not available from the server,
 *  `DJIFlyZoneInformationInvalidTimestamp` will be returned.
 */
@property(nonatomic, readonly) NSString* unlockStartTime;


/**
 *  The timestamp the unlocked zone expires, formatted in UTC (YYYY-MM-DD hh:mm:ss).
 *  When the time is  not available from the server,
 *  `DJIFlyZoneInformationInvalidTimestamp` will be returned.
 */
@property(nonatomic, readonly) NSString* unlockEndTime;


/**
 *  Returns the reason of the fly zone `DJIFlyZoneReason`.
 */
@property(nonatomic, readonly) DJIFlyZoneReason reason;


/**
 *  The shape of the fly zone. This shape is only used for GEO (always cylinder) and
 *  NFZ fly zones.
 */
@property(nonatomic, readonly) DJIFlyZoneShape shape;


/**
 *  The category of the fly zone.
 */
@property(nonatomic, readonly) DJIFlyZoneCategory category;


/**
 *  Information about the Sub fly zones. If empty, then the fly zone is a circle fly
 *  zone. If  populated, this fly zone is a Poly fly zone and the sub fly zone
 *  information will take  precedence over information in `DJIFlyZoneInformation`.
 *  `DJIFlyZoneInformation` should only be used for fly zone identifying
 *  information.
 *  
 *  @return An array of `DJISubFlyZoneInformation` objects.
 */
@property(nonatomic, readonly, nullable) NSArray<DJISubFlyZoneInformation *> *subFlyZones;


/**
 *  Disables the unlocked fly zones. This is useful if the aircraft is shared
 *  between users. It is not  supported by Inspire 1 series or Phantom 3 series. For
 *  the other products, it is supported  when `isCustomUnlockZoneSupported` is
 *  `YES`.
 *  
 *  @param enabled `YES` to enable the unlocked fly zone.
 *  @param completion `completion block` to receive the result.
 */
-(void)setUnlockingEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  `YES` if the unlocked fly zone is enabled. It is not supported by Inspire 1
 *  series or Phantom 3  series. For the other products, it is supported when
 *  `isCustomUnlockZoneSupported` is `YES`.
 *  
 *  @param enabled `YES` if the visual stabilization is enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
-(void)getUnlockingEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
