//
//  DJIUnlockedZoneGroup.h
//  DJISDK
//
//  Copyright © 2018, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIFlyZoneInformation;
@class DJICustomUnlockZone;


/**
 *  An unlocked zone group contains the self-unlocked fly zones and custom unlock
 *  zones for an aircraft.
 */
@interface DJIUnlockedZoneGroup : NSObject


/**
 *  The serial number of the aircraft.
 */
@property(nonatomic, readonly) NSString *SN;


/**
 *  The self-unlocked authorization fly zones for the aircraft.
 */
@property(nonatomic, readonly) NSArray<DJIFlyZoneInformation *> *selfUnlockedFlyZones;


/**
 *  The custom unlock zones for the aircraft.
 */
@property(nonatomic, readonly) NSArray<DJICustomUnlockZone *> *customUnlockZones;

@end

NS_ASSUME_NONNULL_END
