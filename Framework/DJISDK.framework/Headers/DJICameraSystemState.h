//
//  DJICameraSystemState.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJICameraSettingsDef.h>

NS_ASSUME_NONNULL_BEGIN


/**
 *  This class provides general information and current status of the camera.
 */
@interface DJICameraSystemState : NSObject


/**
 *  `YES` when the camera is performing any photo capture in any
 *  `DJICameraShootPhotoMode`. Between photo capture in interval and time lapse
 *  mode, this property will be `NO`. The camera is shooting a single photo.
 */
@property(nonatomic, readonly) BOOL isShootingSinglePhoto;


/**
 *  `YES` when the camera is performing a photo capture in RAW or RAW+JPEG format.
 *  Between photo capture in interval and time lapse mode, this property will be
 *  `NO`. If saving the photo in JPEG only, this property will always be `NO`.
 */
@property(nonatomic, readonly) BOOL isShootingSinglePhotoInRAWFormat;


/**
 *  `YES` when the camera is performing an interval capture. `YES` after
 *  `startShootPhotoWithCompletion` is called, and `NO` after
 *  `stopShootPhotoWithCompletion` is called.
 */
@property(nonatomic, readonly) BOOL isShootingIntervalPhoto;


/**
 *  `YES` when the camera is performing a burst capture. `YES` after
 *  `startShootPhotoWithCompletion` is called, and `NO` after the burst is complete.
 *  The camera is shooting burst photos.
 */
@property(nonatomic, readonly) BOOL isShootingBurstPhoto;


/**
 *  `YES` when the camera is performing a RAW burst capture. `YES` after
 *  `startShootPhotoWithCompletion` is called, and `NO` after the RAW burst is
 *  complete. The camera is shooting RAW burst photos.
 */
@property(nonatomic, readonly) BOOL isShootingRAWBurstPhoto;


/**
 *  `YES` when the camera is performing a ShallowFocus capture.
 */
@property(nonatomic, readonly) BOOL isShootingShallowFocusPhoto;


/**
 *  `YES` when the camera is performing a Panorama capture.
 */
@property(nonatomic, readonly) BOOL isShootingPanoramaPhoto;


/**
 *  `YES` if the camera is recording video.
 */
@property(nonatomic, readonly) BOOL isRecording;


/**
 *  `YES` if the camera is storing a photo. When `isStoringPhoto` is `YES`, the user
 *  cannot change the camera mode or start to shoot another photo.
 */
@property(nonatomic, readonly) BOOL isStoringPhoto;


/**
 *  `YES` if the camera is too hot.
 */
@property(nonatomic, readonly) BOOL isOverheating;


/**
 *  `YES` if there is a camera sensor error.
 */
@property(nonatomic, readonly) BOOL hasError;

/**
 *  Indicate whether the camera is in USB mode.
 */
@property(nonatomic, readonly) BOOL isInUSBMode;


/**
 *  The current mode of the camera.
 */
@property(nonatomic, readonly) DJICameraMode mode;


/**
 *  The duration, in seconds, of the video currently being recorded by the camera.
 */
@property(nonatomic, readonly) NSUInteger currentVideoRecordingTimeInSeconds;


/**
 *  The current completed photo count of the executing panorama shot.
 */
@property(nonatomic, readonly) NSUInteger currentPanoramaPhotoCount;


/**
 *  The progress of the executing panorama shot. It is `nil` if there is no
 *  executing panorama shot.
 */
@property(nonatomic, readonly, nullable) NSProgress *panoramaProgress;

@end

NS_ASSUME_NONNULL_END

