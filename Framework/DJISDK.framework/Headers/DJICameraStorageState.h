//
//  DJICameraStorageState.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJICameraSettingsDef.h>

/*********************************************************************************/
#pragma mark - DJICameraStorageState
/*********************************************************************************/


/**
 *  This class provides the general information and state of the storage (SD card or
 *  the internal storage).
 */
@interface DJICameraStorageState : NSObject


/**
 *  The location of the storage.
 */
@property(nonatomic, readonly) DJICameraStorageLocation location; 


/**
 *  `YES` if the storage is initializing. Note that if the storage is initializing,
 *  the value for other properties in `DJICameraStorageState` is undefined.
 */
@property(nonatomic, readonly) BOOL isInitializing;


/**
 *  `YES` if there is an error with the storage.
 */
@property(nonatomic, readonly) BOOL hasError;


/**
 *  `YES` if the storage is read-only.
 */
@property(nonatomic, readonly) BOOL isReadOnly;


/**
 *  `YES` if the storage filesystem format is invalid.
 */
@property(nonatomic, readonly) BOOL isInvalidFormat;


/**
 *  `YES` if the storage is formatted.
 */
@property(nonatomic, readonly) BOOL isFormatted;


/**
 *  `YES` if the storage is formatting.
 */
@property(nonatomic, readonly) BOOL isFormatting;


/**
 *  `YES` if the storage cannot save any more media.
 */
@property(nonatomic, readonly) BOOL isFull;


/**
 *  `YES` if the SD card is verified as genuine. The SD card is not valid if it is
 *  fake, which can be a problem if the SD card was purchased by a non-reputable
 *  retailer. It is always `YES` when it is the internal storage.
 */
@property(nonatomic, readonly) BOOL isVerified;


/**
 *  `YES` if the SD card is inserted in the camera. It is always `YES` when it is
 *  the internal storage.
 */
@property(nonatomic, readonly) BOOL isInserted;


/**
 *  Total space in Megabytes (MB) available on the storage.
 */
@property(nonatomic, readonly) NSUInteger totalSpaceInMB;


/**
 *  Remaining space in Megabytes (MB) on the storage.
 */
@property(nonatomic, readonly) NSUInteger remainingSpaceInMB;


/**
 *  Returns the number of pictures that can be taken with the remaining space
 *  available on the storage.
 */
@property(nonatomic, readonly) NSUInteger availableCaptureCount;


/**
 *  Returns the number of seconds available for recording with the remaining space
 *  available on the storage.
 */
@property(nonatomic, readonly) NSUInteger availableRecordingTimeInSeconds;

@end
