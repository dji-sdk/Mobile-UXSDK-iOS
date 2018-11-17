//
//  DJIAccessoryAggregation.h
//  DJISDK
//
//  Copyright © 2018 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJISDK.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIAccessoryAggregationState;
@class DJISpotlight;
@class DJIBeacon;
@class DJIAccessoryAggregation;
@class DJISpeaker;

/*********************************************************************************/
#pragma mark - DJIAccessoryAggregationDelegate
/*********************************************************************************/


/**
 *  Delegate to receive the state change of accessories.
 */
@protocol DJIAccessoryAggregationDelegate <NSObject>

@optional

/**
 *  The accessory aggregation updates the accessory aggregation state.
 *  
 *  @param aggregation The accessory aggregation that updates connectivity state.
 *  @param state The accessory aggregation state.
 */
- (void)accessoryAggregation:(DJIAccessoryAggregation *_Nonnull)aggregation didUpdateState:(DJIAccessoryAggregationState *_Nonnull)state;

@end

/*********************************************************************************/
#pragma mark - DJIAccessoryAggregation
/*********************************************************************************/


/**
 *  This class contains all possible accessories (spotlight, beacon and speaker)
 *  supported by the aircraft. The  accessory aggregation component is available
 *  when Mavic 2 Enterprise is connected. An accessory becomes  available only when
 *  the accessory is connected to the aircraft.
 */
@interface DJIAccessoryAggregation : DJIBaseComponent


/**
 *  Delegate to receive the state change of accessories.
 */
@property(nonatomic, weak) id<DJIAccessoryAggregationDelegate> delegate;


/**
 *  The spotlight accessory. `nil` if it is not connected.
 */
@property (nonatomic, readonly) DJISpotlight *spotlight;


/**
 *  The beacon accessory. `nil` if it is not connected.
 */
@property (nonatomic, readonly) DJIBeacon *beacon;


/**
 *  The speaker accessory. `nil` if it is not connected.
 */
@property (nonatomic, readonly) DJISpeaker *speaker;

@end

NS_ASSUME_NONNULL_END
