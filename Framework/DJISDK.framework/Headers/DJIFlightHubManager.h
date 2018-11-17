//
//  DJIFlightHubManager.h
//  DJISDK
//
//  Copyright © 2018 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIFlightHubBaseTypes.h>
#import <DJISDK/DJISDKFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIFlightHubManager;


/**
 *  Delegate to receive updated states related to DJI FlightHub.
 */
@protocol DJIFlightHubManagerDelegate <NSObject>


/**
 *  Updates states for the uploading progress of flight data.
 *  
 *  @param flightHubManager The FlightHub Manager updates the state.
 *  @param state The updated state. When it is `DJIFlightHubUploadStateRejectedByServer`, refer to error for more detail.
 *  @param error The returned error when the upload request is rejected by the server. Use the error to check the reason.
 */
- (void)flightHubManager:(DJIFlightHubManager *)flightHubManager didUpdateUploadState:(DJIFlightHubUploadState)state error:(nullable NSError *)error;

@end


/**
 *  The FlightHubManager class provides methods to interact with DJI FlightHub
 *  (https://www.dji.com/flighthub). SDK provides interfaces to upload the states of
 *  the connected aircraft to the FlightHub server and download the flight data from
 *  the server. To access DJI FlightHub features through SDK, the logged-in user
 *  should be already activated with a valid FlightHub license. Use
 *  `isUserActivated` to check if the user is activated. Note: Invoke
 *  `updateActivationStateWithCompletion` before using any other method to verify
 *  your accessibility.
 */
@interface DJIFlightHubManager : NSObject

- (instancetype)init OBJC_UNAVAILABLE("You must use the singleton");

+ (instancetype)new OBJC_UNAVAILABLE("You must use the singleton");


/**
 *  Current interval for uploading real-time flight data.
 */
@property(nonatomic, readonly) NSTimeInterval uploadTimeInterval;


/**
 *  Gets current upload state.
 */
@property(atomic, readonly) DJIFlightHubUploadState uploadState;


/**
 *  Determines if the user has been activated. It is a cached data and it will be
 *  refreshed  when `updateActivationStateWithCompletion` is called.
 */
@property(atomic, readonly) BOOL isUserActivated;


/**
 *  Delegate to receive the updated state.
 */
@property(nonatomic, weak) id<DJIFlightHubManagerDelegate> delegate;


/**
 *  Sets the interval for uploading real-time flight data. By default, the interval
 *  is 5 seconds.
 *  
 *  @param interval Interval in seconds. The value should be in the range [1, 10].
 *  
 *  @return Error if the input is invalid.
 */
- (nullable NSError *)setUploadTimeInterval:(NSTimeInterval)interval;


/**
 *  Set `YES` to enable SDK to upload real-time flight data of the connected
 *  aircraft to DJI  FlightHub server. When it is enabled, SDK will start uploading
 *  flight data automatically when  the aircraft is flying. FlightHub user can
 *  access the uploaded flight data on the FlightHub  online system. Stop uploading
 *  data by setting `NO` as parameter. Use `uploadState`  to check current uploading
 *  state.
 *  
 *  @param enabled Interval in seconds. The value should be in the range [1, 10].
 */
- (void)setUploadEnabled:(BOOL)enabled;


/**
 *  Updates the logged-in user's activation state for DJI FlightHub. This method is
 *  only valid when the user  is logged in. When the state is updated, the state
 *  will be cached to `isUserActivated`.
 *  
 *  @param completion The completion block that receives the execution result.
 */
- (void)updateActivationStateWithCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the teams' information that is visible for the user.
 *  
 *  @param teams An array of information for each team. It is `nil` if there is an error.
 *  @param error Error if there is any.
 *  @param completion The completion block that receives the execution result.
 */
- (void)getTeamsInformationWithCompletion:(void (^)(NSArray<DJIFlightHubTeam *> *_Nullable teams, NSError *_Nullable error))completion;


/**
 *  Gets the flight path nodes of a historical flight path with the specific path
 *  ID. This information is  only visible for the administrator of the group and the
 *  captain of the team.
 *  
 *  @param orderID The order id of the flight path to fetch.
 *  @param nodes An array of nodes of which the flight path consists.
 *  @param error Error if there is any.
 *  @param completion The completion block that receives the execution result.
 */
- (void)getHistoricalFlightPath:(NSString *_Nullable)orderID withCompletion:(void (^)(NSArray<DJIFlightHubFlightPathNode *> *_Nullable nodes, NSError *_Nullable error))completion;


/**
 *  Gets flight statistics over a period of time. Specify the account to get the
 *  statistics related to one  user. Otherwise, statistics for the whole team will
 *  be fetched. Only `DJIFlightHubRoleAdministrator`  and `DJIFlightHubRoleCaptain`
 *  can access the flight statistics.
 *  
 *  @param startTime The start time of the duration (milliseconds).
 *  @param endTime The end time of the duration (milliseconds).
 *  @param account The user account to which the statistics related. `nil` to get the statistics of the whole team.
 *  @param teamID The ID of the team.
 *  @param flight Contains the overall statistics and the detail information for each flight included by the duration.
 *  @param error Error if there is any.
 *  @param completion The completion block that receives the execution result.
 */
- (void)getFlightStatisticsWithStartTime:(NSTimeInterval)startTime
                                 endTime:(NSTimeInterval)endTime
                                 account:(NSString *_Nullable)account
                                  teamID:(NSString *)teamID
                          withCompletion:(void (^)(DJIFlightHubHistoricalFlight *_Nullable flight, NSError *_Nullable error))completion;


/**
 *  Bind the connected aircraft to DJI FlightHub system. Specify the team ID that
 *  the aircraft will belongs to.
 *  
 *  @param teamID Team ID that current aircraft is expected to bind to.
 *  @param completion The completion block that receives the execution result.
 */
- (void)bindAircraftToTeam:(NSString *)teamID withCompletion:(DJICompletionBlock)completion;


/**
 *  Unbinds current aircraft from the certain team. Only
 *  `DJIFlightHubRoleAdministrator`  and `DJIFlightHubRoleCaptain` can do this
 *  operation.
 *  
 *  @param completion The completion block that receives the execution result.
 */
- (void)unbindAircraftWithCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the live view stream sourcing by the other aircraft to DJI FlightHub. The
 *  stream is using RTMP  (Real-Time Messaging Protocol). External libraries are
 *  required to decode and render the live view.  Only
 *  `DJIFlightHubRoleAdministrator` and `DJIFlightHubRoleCaptain` can do this
 *  operation.
 *  
 *  @param sn Serial number of the aircraft sourcing the live view stream.
 *  @param stream The stream information.
 *  @param error Error if there is any.
 *  @param completion The completion block that receives the execution result.
 */
- (void)getLiveViewStreamSourceWithSN:(NSString *)sn withCompletion:(void (^_Nonnull)(DJIFlightHubLiveStream *_Nullable stream, NSError *_Nullable error))completion;


/**
 *  Gets RTMP (Real-Time Messaging Protocol) url that the connected aircraft should
 *  stream to.
 *  
 *  @param upStream The RTMP url.eam.
 *  @param error Error if there is any.
 *  @param completion The completion block that receives the execution result.
 */
- (void)getLiveViewStreamDestinationWithCompletion:(void (^)(DJIFlightHubUpStream *_Nullable upStream, NSError *_Nullable error))completion;


/**
 *  Determines whether the live stream is stable from the server perspective.
 *  
 *  @param stable `YES` if the stream is stable.
 *  @param error Error if there is any.
 *  @param completion The completion block that receives the execution result.
 */
- (void)checkIfLiveStreamStableWithCompletion:(void (^)(BOOL stable, NSError *_Nullable error))completion;


/**
 *  Gets the list of devices streaming live video to DJI FlightHubManager.
 *  
 *  @param devices Devices that streaming live video.
 *  @param error Error if there is any.
 *  @param completion The completion block that receives the execution result.
 */
- (void)getStreamingDevicesWithCompletion:(void (^)(NSArray<DJIFlightHubOnlineDevice *> *_Nullable devices, NSError *_Nullable error))completion;


/**
 *  Gets the list of online devices visiable in DJI FlightHub.
 *  
 *  @param devices The online devices.
 *  @param error Error if there is any.
 *  @param completion The completion block that receives the execution result.
 */
- (void)getOnlineDevicesWithCompletion:(void (^)(NSArray<DJIFlightHubOnlineDevice *> *_Nullable devices, NSError *_Nullable error))completion;


/**
 *  Gets real time flight data of the given aircraft(s).
 *  
 *  @param SNs An NSArray of aircrafts' serial numbers.
 *  @param flightDatas An NSArray of `DJIFlightHubRealTimeFlightData` objects.
 *  @param error Error if there is any.
 *  @param completion The completion block that receives the execution result.
 */
- (void)getRealTimeDataWithSNs:(NSArray<NSString *> *)SNs withCompletion:(void (^)(NSArray<DJIFlightHubRealTimeFlightData *> *_Nullable flightDatas,
                                                                                   NSError *_Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
