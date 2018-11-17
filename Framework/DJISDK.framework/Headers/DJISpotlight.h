//
//  DJISpotlight.h
//  DJISDK
//
//  Copyright © 2018 DJI. All rights reserved.
//

#import <DJISDK/DJISDK.h>

NS_ASSUME_NONNULL_BEGIN

@class DJISpotlightState;


/**
 *  Block to receive the spotlight's state.
 *  
 *  @param state An object of `DJISpotlightState`.
 */
typedef void (^DJISpotlightStateBlock) (DJISpotlightState* state);


/**
 *  The state of the spotlight accessory.
 */
@interface DJISpotlightState : NSObject


/**
 *  Returns the temperature of the Spotlight in Celsius.
 */
@property (nonatomic, readonly) float temperature;


/**
 *  The configurable brightness of the spotlight.
 */
@property (nonatomic, readonly) NSUInteger brightness;

@end


/**
 *  This class represents the spotlight accessory mounted on the aircraft. It
 *  provides methods to control the spotlight and get the related states.
 */
@interface DJISpotlight : DJIBaseComponent


/**
 *  Gets the state of the spotlight.
 */
@property (nonatomic, readonly, nullable) DJISpotlightState *state;


/**
 *  Gets on/off status of Spotlight.
 *  
 *  @param enabled Check if spotlight is turned on.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Enables the spotlight to turn it on.
 *  
 *  @param enabled `YES` to turn on the spotlight.
 *  @param completion Completion block to receive the result.
 */
- (void)setEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Sets the brightness of the spotlight. The valid range is [1, 100]. 100 means the
 *  brightest.
 *  
 *  @param brightness Brightness of the spotlight.
 *  @param completion Completion block to receive the result.
 */
- (void)setBrightness:(NSUInteger)brightness withCompletion:(DJICompletionBlock)completion;

#pragma mark - Listener


/**
 *  Adds listener to receive the latest state of the spotlight.
 *  
 *  @param listener Listener that is interested on upload event.
 *  @param queue The dispatch queue that `block` will be called on.
 *  @param block Block will be called when there is event updated related to upload.
 */
- (void)addSpotlightStateListener:(id)listener
                        withQueue:(nullable dispatch_queue_t)queue
                         andBlock:(DJISpotlightStateBlock)block;


/**
 *  Removes the listener of the spotlight state.
 *  
 *  @param listener The listener to remove.
 */
- (void)removeSpotlightStateListener:(id)listener;

@end

NS_ASSUME_NONNULL_END
