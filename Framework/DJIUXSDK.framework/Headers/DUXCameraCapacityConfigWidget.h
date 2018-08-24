//
//  DUXCameraCapacityConfigWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Display:
 *  Camera state widget that reports remaining capacity of the media storage.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: (variable, max:221):30
 */
@interface DUXCameraCapacityConfigWidget : DUXCameraConfigWidget


/**
 *  This widget may be used with both SD and SSD storage. This enum differentiates
 *  between the two.
 */
@property DUXCameraConfigWidgetStorageType storageType;


/**
 *  The amount of remaining photos that can be stored assuming the current camera
 *  photo settings.
 */
@property (nonatomic, readonly) NSInteger remainingPhotoCount;


/**
 *  The remaining storage space left in MegaBytes.
 */
@property (nonatomic, readonly) NSInteger remainingSpaceMB;


/**
 *  The amount of remaining video in seconds that can be stored assuming the current
 *  video settings
 */
@property (nonatomic, readonly) NSInteger remainingRecordingTime;

@property (nonatomic) NSUInteger preferredCameraIndex;

@end
