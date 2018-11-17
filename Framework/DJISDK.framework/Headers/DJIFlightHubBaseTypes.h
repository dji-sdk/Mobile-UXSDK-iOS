//
//  DJIFlightHubBaseTypes.h
//  DJISDK
//
//  Copyright © 2018 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN


/**
 *  The FlightHub histogram distribution of the flight durations key "0-5".
 */
extern NSString *const DJIFlightHubDurationRange0To5Keys;


/**
 *  The FlightHub histogram distribution of the flight durations key "5-10".
 */
extern NSString *const DJIFlightHubDurationRange5To10Keys;


/**
 *  The FlightHub histogram distribution of the flight durations key "10-15".
 */
extern NSString *const DJIFlightHubDurationRange10To15Keys;


/**
 *  The FlightHub histogram distribution of the flight durations key "15-20".
 */
extern NSString *const DJIFlightHubDurationRange15To20Keys;


/**
 *  The FlightHub histogram distribution of the flight durations key "20+".
 */
extern NSString *const DJIFlightHubDurationRange20PlusKeys;

/*********************************************************************************/
#pragma mark DJIFlightHubUploadState
/*********************************************************************************/

/**
 *  The uploading state of the flight data for DJI FlightHub system.
 */
typedef NS_ENUM(NSUInteger, DJIFlightHubUploadState) {

    /**
     *  The uploading process is disabled.
     */
    DJIFlightHubUploadStateDisabled,

    /**
     *  The uploading process is enabled but it is not started because the network is
     *  not reachable.
     */
    DJIFlightHubUploadStateNetworkNotReachable,

    /**
     *  The uploading process is enabled but it is not started because no account is
     *  logged in.
     */
    DJIFlightHubUploadStateNotLoggedIn,

    /**
     *  The uploading process is enabled but it is not started because the aircraft is
     *  disconnected.
     */
    DJIFlightHubUploadStateAircraftDisconnected,

    /**
     *  The uploading process is enabled but the uploading request is rejected by the
     *  server.
     */
    DJIFlightHubUploadStateRejectedByServer,

    /**
     *  The uploading process is enabled and it will start when the aircraft takes off.
     */
    DJIFlightHubUploadStateReadyToUpload,

    /**
     *  SDK is uploading flight data to DJI FlightHub system.
     */
    DJIFlightHubUploadStateUploading,

    /**
     *  Unknown.
     */
    DJIFlightHubUploadStateUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark DJIFlightHubRole
/*********************************************************************************/

/**
 *  Different roles of members in a FlightHub group. Different roles will have
 *  different  permissions to access data in the sytem.
 */
typedef NS_ENUM(NSUInteger, DJIFlightHubRole) {

    /**
     *  The administrator is the leader of a group (a group consists of several teams).
     *  This role  will appear in the member list of all the teams and this role can
     *  access all the data of the group.
     */
    DJIFlightHubRoleAdministrator,

    /**
     *  A captain is the leader of a team. `DJIFlightHubRoleAdministrator` can define a
     *  captain for a  team in the group but it is not compulsory for a team to have a
     *  captain. The captain can access the data of the team.
     */
    DJIFlightHubRoleCaptain,

    /**
     *  A pilot is a member in the team without special permissions.
     */
    DJIFlightHubRolePilot,

    /**
     *  Unknown.
     */
    DJIFlightHubRoleUnknown = 0XFF,
};

/*********************************************************************************/
#pragma mark DJIFlightHubOnlineDevice
/*********************************************************************************/

/**
 *  Device information in the DJIFlightHubManager, including serial number and team
 *  id.
 */
@interface DJIFlightHubOnlineDevice : NSObject


/**
 *  Gets the serial number of current device.
 */
@property (nonatomic, readonly) NSString *sn;


/**
 *  Gets the team ID that online device belongs to.
 */
@property (nonatomic, readonly) NSString *teamID;

@end

/*********************************************************************************/
#pragma mark DJIFlightHubBoundDevice
/*********************************************************************************/

/**
 *  The device bound in DJI FlightHub.
 */
@interface DJIFlightHubBoundDevice : NSObject


/**
 *  Gets the serial number of the device.
 */
@property (nonatomic, readonly) NSString *sn;


/**
 *  Gets device name.
 */
@property (nonatomic, readonly) NSString *name;


/**
 *  Gets device model.
 */
@property (nonatomic, readonly) NSString *model;

@end

/*********************************************************************************/
#pragma mark DJIFlightHubUser
/*********************************************************************************/

/**
 *  A user in FlightHub.
 */
@interface DJIFlightHubUser : NSObject


/**
 *  Gets the account of the user.
 */
@property (nonatomic, readonly) NSString *account;


/**
 *  Gets the nick name of the user.
 */
@property (nonatomic, readonly) NSString *nickName;


/**
 *  Gets the role of the user. Different roles will have different permissions to
 *  access the  data in DJI FlightHub.
 */
@property (nonatomic, readonly) DJIFlightHubRole role;

@end

/*********************************************************************************/
#pragma mark DJIFlightHubTeam
/*********************************************************************************/

/**
 *  A team in DJI FlightHub. A group can contain several teams.
 */
@interface DJIFlightHubTeam : NSObject


/**
 *  Gets the ID of the team. Each team in a group will have a unique ID.
 */
@property (nonatomic, readonly) NSUInteger teamID;


/**
 *  Gets group's ID that current team belongs to.
 */
@property (nonatomic, readonly) NSUInteger groupID;


/**
 *  Gets the team's name.
 */
@property (nonatomic, readonly) NSString *name;


/**
 *  Get devices of the team.
 */
@property (nonatomic, readonly) NSArray<DJIFlightHubBoundDevice *> *devices;


/**
 *  Gets members of the team.
 */
@property (nonatomic, readonly) NSArray<DJIFlightHubUser *> *members;

@end

/*********************************************************************************/
#pragma mark DJIFlightHubUpStream
/*********************************************************************************/

/**
 *  This class contains RTMP URL of up stream.
 */
@interface DJIFlightHubUpStream : NSObject


/**
 *  Gets up stream RTMP URL of live stream.
 */
@property (nonatomic, readonly) NSString *rtmpURL;

@end

/*********************************************************************************/
#pragma mark DJIFlightHubLiveStream
/*********************************************************************************/

/**
 *  This class represents the live stream information of devices in the same team.
 */
@interface DJIFlightHubLiveStream : NSObject


/**
 *  Gets the RTMP(Real-Time Messaging Protocol) URL of the live stream. When the
 *  device is broadcasting, user can receive the live stream's video data and audio
 *  data through RTMP.
 */
@property (nonatomic, readonly) NSString *rtmpURL;


/**
 *  Determines if the live stream is valid. When the team member stops live
 *  streaming or the device  is disconnected, the live stream will become invalid.
 */
@property (nonatomic, readonly) BOOL isValid;

@end

/*********************************************************************************/
#pragma mark DJIFlightHubFlightPathNode
/*********************************************************************************/

/**
 *  The class provide flight information of a node in flight path.
 */
@interface DJIFlightHubFlightPathNode : NSObject


/**
 *  Gets the flight date.
 */
@property (nonatomic, readonly) NSDate *date;


/**
 *  Gets flight device's model.
 */
@property (nonatomic, readonly) NSString *deviceModel;


/**
 *  Gets the flight time.
 */
@property (nonatomic, readonly) NSUInteger flightTime;


/**
 *  Gets the location coordinate of the flight node.
 */
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;


/**
 *  Gets the altitude of the flight node.
 */
@property (nonatomic, readonly) float altitude;


/**
 *  Gets the flight speed (m/s).
 */
@property (nonatomic, readonly) double speed;


/**
 *  Gets flight yaw in degree.
 */
@property (nonatomic, readonly) double yaw;

@end

/*********************************************************************************/
#pragma mark DJIFlightHubFlightHistoricalDetail
/*********************************************************************************/

/**
 *  This class provides the detail information for one flight. It includes aircraft
 *  information,  flight location and statistics data.
 */
@interface DJIFlightHubFlightHistoricalDetail : NSObject


/**
 *  Gets the order ID of the flight.
 */
@property (nonatomic, readonly) NSString *orderID;


/**
 *  Gets the aircraft's serial number of the flight.
 */
@property (nonatomic, readonly) NSString *sn;


/**
 *  Gets the device model of the flight.
 */
@property (nonatomic, readonly) NSString *deviceModel;


/**
 *  Gets the team ID of the flight.
 */
@property (nonatomic, readonly) NSString* teamID;


/**
 *  Gets the account of the flight.
 */
@property (nonatomic, readonly) NSString *account;


/**
 *  Gets the address of the flight.
 */
@property (nonatomic, readonly) NSString *address;


/**
 *  Gets the start time of the flight.
 */
@property (nonatomic, readonly) NSDate *startTime;


/**
 *  Gets flight account's contact.
 */
@property (nonatomic, readonly) NSString *contact;


/**
 *  Gets the maximum flight time during the flight in seconds.
 */
@property (nonatomic, readonly) NSUInteger maxFlightTime;


/**
 *  Gets the minimum flight time during the flight in seconds.
 */
@property (nonatomic, readonly) NSInteger minFlightTime;


/**
 *  Gets the flight distance in meters.
 */
@property (nonatomic, readonly) NSInteger distance;


/**
 *  Gets flight duration in seconds.
 */
@property (nonatomic, readonly) double duration;


/**
 *  Gets the peak height in meters during the flight.
 */
@property (nonatomic, readonly) double peakHeight;

@end

/*********************************************************************************/
#pragma mark DJIFlightHubStatistics
/*********************************************************************************/

/**
 *  The flight statistics includes total and average flight duration. It also
 *  provides a distributed  diagram data of flight duration.
 */
@interface DJIFlightHubStatistics : NSObject


/**
 *  Gets total flight duration over a period of time in minutes.
 */
@property (nonatomic, readonly) double totalDuration;


/**
 *  Gets average flight duration over a period of time in minutes.
 */
@property (nonatomic, readonly) double averageDuration;


/**
 *  Gets the histogram distribution of the flight durations (in minutes). The
 *  duration intervals  are [0, 5), [5, 10), [10, 15), [15, 20) and [20, +&#x221E;).
 *  Return A NSDictionary with string  keys `DJIFlightHubDurationRange0To5Keys`,
 *  DJIFlightHubManager_DJIFlightHubDurationRange5To10Keys,
 *  `DJIFlightHubDurationRange10To15Keys`, `DJIFlightHubDurationRange15To20Keys`
 *  and `DJIFlightHubDurationRange20PlusKeys` in order. The values are the number of
 *  flights  in the duration range.
 */
@property (nonatomic, readonly) NSDictionary<NSString *, NSNumber *> *durationDistribution;

@end

/*********************************************************************************/
#pragma mark DJIFlightHubHistoricalFlight
/*********************************************************************************/

/**
 *  Class that constructed with flight statistics data and flight history in
 *  FlightHubManager.
 */
@interface DJIFlightHubHistoricalFlight : NSObject


/**
 *  Gets the statistics of flights.
 */
@property (nonatomic, readonly) DJIFlightHubStatistics *statistics;


/**
 *  Gets the history of flight.
 */
@property (nonatomic, readonly) NSArray<DJIFlightHubFlightHistoricalDetail*> *history;

@end


/**
 *  This class includes detail of current flight.
 */
@interface DJIFlightHubRealTimeFlightData : NSObject


/**
 *  Gets current device's serial number.
 */
@property (nonatomic, readonly) NSString *sn;


/**
 *  Gets the model of the device.
 */
@property (nonatomic, readonly) NSString *deviceModel;


/**
 *  Gets the team's id that current device belongs to.
 */
@property (nonatomic, readonly) NSString *teamID;


/**
 *  Gets flight date.
 */
@property (nonatomic, readonly) NSDate *date;


/**
 *  Gets current location coordinate.
 */
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;


/**
 *  Gets current altitude in meters.
 */
@property (nonatomic, readonly) float altitude;


/**
 *  Gets flight speed.
 */
@property (nonatomic, readonly) NSUInteger speed;


/**
 *  Gets flight yaw.
 */
@property (nonatomic, readonly) NSInteger yaw;

@end

NS_ASSUME_NONNULL_END

