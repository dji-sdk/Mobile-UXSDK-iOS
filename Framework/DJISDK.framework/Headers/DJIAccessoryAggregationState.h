//
//  DJIAccessoryAggregationState.h
//  DJISDK
//
//  Copyright © 2018 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


/**
 *  This class contains the latest connectivity state of accessories.
 */
@interface DJIAccessoryAggregationState : NSObject


/**
 *  `YES` if the spotlight is connected.
 */
@property (nonatomic, readonly) BOOL isSpotlightConnected;


/**
 *  `YES` if the beacon is connected.
 */
@property (nonatomic, readonly) BOOL isBeaconConnected;


/**
 *  `YES` if the speaker is connected.
 */
@property (nonatomic, readonly) BOOL isSpeakerConnected;

@end

NS_ASSUME_NONNULL_END
