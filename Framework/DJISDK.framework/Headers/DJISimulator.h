//
//  DJISimulator.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#import <DJISDK/DJIBaseProduct.h>
#import <CoreLocation/CLLocation.h>
#import <DJISDK/DJISimulatorState.h>

NS_ASSUME_NONNULL_BEGIN

@class DJISimulator;
@class DJISimulatorWindSpeed;


/**
 *  This protocol provides the delegate method of the simulator.
 */
@protocol DJISimulatorDelegate <NSObject>
@optional


/**
 *  Updates the simulator's current state.
 *  
 *  @param simulator An instance of `DJISimulator`.
 *  @param state An instance of `DJISimulatorState`.
 */
- (void)simulator:(DJISimulator *_Nonnull)simulator didUpdateState:(DJISimulatorState *_Nonnull)state;

@end


/**
 *  DJI aircraft can be put into simulation mode using this class. Developers can
 *  start and stop the simulation, as well as monitor basic aircraft attitude and
 *  location information.
 */
@interface DJISimulator : NSObject


/**
 *  Returns the delegate of simulator.
 */
@property(nonatomic, weak) id<DJISimulatorDelegate> delegate;


/**
 *  `YES` if the simulator is started.
 */
@property(nonatomic, readonly) BOOL isSimulatorActive;


/**
 *  Start simulator. Will result in error if simulation is already started.
 *  
 *  @param location Simulator coordinate latitude and longitude, in degrees.
 *  @param frequency Aircraft simulator state push frequency, in Hz, with range [2, 150]. A setting of 10 Hz will result in  delegate method being called, 10 times per second.
 *  @param number The initial number of GPS satellites with range [0, 20].
 *  @param completion The completion block.
 */
- (void)startWithLocation:(CLLocationCoordinate2D)location
          updateFrequency:(NSUInteger)frequency
      GPSSatellitesNumber:(NSUInteger)number
           withCompletion:(DJICompletionBlock)completion;


/**
 *  Stop the simulator.
 *  
 *  @param completion The Completion block.
 */
- (void)stopWithCompletion:(DJICompletionBlock)completion;


/**
 *  Enable/disable the fly zone system in the simulator. By default, fly zone is
 *  disabled in the simulator.  Rebooting the aircraft is required for the settings
 *  to take effect.
 *  
 *  @param enabled `YES` to enable fly zone in the simulator.
 *  @param completion Completion block to receive the result.
 */
- (void)setFlyZoneLimitationEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets fly zone system simulator status (enabled/disabled). By default, fly zone
 *  is disabled in the simulator.
 *  
 *  @param enabled YES if the fly zone system is enabled.
 *  @param error Error retrieving the value.
 *  @param block Completion block to receive the result.
 */
- (void)getFlyZoneLimitationEnabledWithCompletion:(void(^)(BOOL enabled, NSError *_Nullable error))block;


/**
 *  Set simulator wind speed.
 *  
 *  @param windSpeed Simulator Wind Speed.
 *  @param completion Completion block to receive the result.
 */
- (void)setWindSpeed:(DJISimulatorWindSpeed *)windSpeed withCompletion:(DJICompletionBlock)completion;


/**
 *  Get simulator wind speed.
 *  
 *  @param windSpeed Simulator Wind Speed.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getWindSpeedWithCompletion:(void(^)(DJISimulatorWindSpeed *_Nullable windSpeed, NSError *_Nullable error))completion;

@end

NS_ASSUME_NONNULL_END

