//
//  DJICameraSSDState.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJICameraSettingsDef.h>


/**
 *  This class contains the information about camera's Solid State Drive (SSD)
 *  information, including state, whether it is connected, its capacity, video size
 *  and rate, etc.
 */
@interface DJICameraSSDState : NSObject


/**
 *  SSD state information for currently executing operations.
 */
@property (nonatomic, readonly) DJICameraSSDOperationState operationState;


/**
 *  `YES` if the SSD is connected. Note, if the camera is disconnected, the values
 *  for other properties in `DJICameraSSDState` are undefined.
 */
@property (nonatomic, readonly) BOOL isConnected;


/**
 *  SSD's total capacity. @return Total SSD capacity.
 */
@property (nonatomic, readonly) DJICameraSSDCapacity capacity;


/**
 *  SSD's remaining time in seconds, based on the current `DJICameraVideoResolution`
 *  and `DJICameraVideoFrameRate`. @return SSD's remaining time measured in seconds.
 */
@property (nonatomic, readonly) NSUInteger availableRecordingTimeInSeconds;


/**
 *  SSD's remaining capacity in MB. @return SSD's remaining capacity measured in MB.
 */
@property (nonatomic, readonly) NSUInteger remainingSpaceInMB;


/**
 *  Video resolution to be saved to SSD. @return SSD's video resolution.
 */
@property (nonatomic, readonly) DJICameraVideoResolution videoResolution;


/**
 *  Video framerate to be saved to SSD.
 */
@property (nonatomic, readonly) DJICameraVideoFrameRate videoFrameRate;


/**
 *  Number of photos that are shot in RAW burst mode.
 */
@property(nonatomic, readonly) NSUInteger rawPhotoBurstCount;

@end
