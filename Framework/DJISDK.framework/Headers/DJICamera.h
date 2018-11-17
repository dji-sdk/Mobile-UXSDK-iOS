//
//  DJICamera.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <DJISDK/DJIBaseComponent.h>
#import <DJISDK/DJICameraSSDState.h>
#import <DJISDK/DJICameraSettingsDef.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIMediaFile;
@class DJICamera;
@class DJICameraSystemState;
@class DJICameraStorageState;
@class DJICameraPlaybackState;
@class DJICameraFocusState;
@class DJIMediaManager;
@class DJIPlaybackManager;
@class DJICameraCapabilities;
@class DJICameraWatermarkSettings;
@class UIImage;


/**
 *  Define the upper bound for thermal brightness setting.
 */
#define DJI_THERMAL_BRIGHTNESS_UPPER_BOUND (16383)

/*********************************************************************************/
#pragma mark - DJICameraDelegate
/*********************************************************************************/


/**
 *  This protocol provides delegate methods to receive the updated video data,
 *  camera's current state and lens information.
 */
@protocol DJICameraDelegate <NSObject>

@optional


/**
 *  Called when the camera's current state has been updated.
 *  
 *  @param camera Camera that updates the current state.
 *  @param systemState The camera's system state.
 */
- (void)camera:(DJICamera *_Nonnull)camera didUpdateSystemState:(DJICameraSystemState *_Nonnull)systemState;


/**
 *  Called when the camera's lens and focus state has been updated.
 *  
 *  @param camera Camera that sends out the updated lens information.
 *  @param lensState The camera's lens and focus state.
 */
- (void)camera:(DJICamera *_Nonnull)camera didUpdateFocusState:(DJICameraFocusState *_Nonnull)lensState;


/**
 *  Called when a new media file (photo or video) has been generated.
 *   In this delegate method, the `DJIMediaFile` instance properties `thumbnail`,
 *  `durationInSeconds` and `videoOrientation` require special consideration. The
 *  `thumbnail` property normally has a pointer to a UIImage of the thumbnail, but
 *  this is only available when the camera is in `DJICameraModeMediaDownload` work
 *  mode. Additionally, for this instance of `DJIMediaFile`, the `durationInSeconds`
 *  property is 0 and the `videoOrientation` property is
 *  `DJICameraOrientationLandscape`.
 *  
 *  @param camera Camera that generates the new media file.
 *  @param newMedia The new media file.
 */
- (void)camera:(DJICamera *_Nonnull)camera didGenerateNewMediaFile:(DJIMediaFile *_Nonnull)newMedia;


/**
 *  Called when a time-lapse preview image has been generated. This method is only
 *  available on Osmo with firmware version v1.5.2.0 or above.
 *  
 *  @param camera Camera that generates the time-lapse preview image.
 *  @param preview The new generated preview image.
 */
- (void)camera:(DJICamera *_Nonnull)camera didGenerateTimeLapsePreview:(UIImage *_Nonnull)preview;


/**
 *  Called when the camera's SD card state has been updated. This method is now
 *  deprecated.
 *  
 *  @param camera Camera that sends out the updated SD card state.
 *  @param sdCardState The camera's SD card state.
 */
- (void)camera:(DJICamera *_Nonnull)camera didUpdateSDCardState:(DJICameraStorageState *_Nonnull)sdCardState DJI_API_DEPRECATED("Use camera:didUpdateStorageState:. ");


/**
 *  Called when the camera's storage state has been updated. Use
 *  `DJICameraStorageState`'s `location` to determine if the updated state is for SD
 *  card or the internal storage.
 *  
 *  @param camera Camera that sends out the updated storage state.
 *  @param storageState The camera storage state. If the camera supports internal storage (e.g. Mavic Air), use `location` to determine whether the state is for SD card or internal storage.
 */
- (void)camera:(DJICamera *_Nonnull)camera didUpdateStorageState:(DJICameraStorageState *_Nonnull)storageState;


/**
 *  Called when the camera's SSD state has been updated. This method is available
 *  only when `isSSDSupported` is `YES`.
 *  
 *  @param camera Camera that sends out the updated SSD state.
 *  @param ssdState The camera's SSD state.
 */
- (void)camera:(DJICamera *_Nonnull)camera didUpdateSSDState:(DJICameraSSDState *_Nonnull)ssdState;


/**
 *  Called when there are new min, max, and average temperature values available for
 *  the set spot metering area. Supported only by Zenmuse XT containing Advanced
 *  Radiometry capabilities.
 *  
 *  @param camera Camera that sends out the aggregate temperature values.
 *  @param temperatureAggregations The updated aggregate temperature values.
 */
- (void)camera:(DJICamera *_Nonnull)camera didUpdateAreaTemperatureAggregations:(DJICameraThermalAreaTemperatureAggregations)temperatureAggregations;


/**
 *  Called when updated external scene settings are available. Supported only by
 *  Zenmuse XT containing Advanced Radiometry capabilities.
 *  
 *  @param camera Camera that sends out the external scene setting values.
 *  @param settings The updated external scene settings values
 */
- (void)camera:(DJICamera *_Nonnull)camera didUpdateExternalSceneSettings:(DJICameraThermalExternalSceneSettings)settings;


/**
 *  Called whenever the camera parameters change. In automatic exposure modes
 *  (Program, Shutter Priority and Aperture Priority) the camera may be
 *  automatically changing aperture, shutter speed and ISO (depending on the mode
 *  and camera) when lighting conditions change. In Manual mode, the exposure
 *  compensation is automatically updated to let the user know how much compensation
 *  the exposure needs to get to an exposure the camera calculates as correct.
 *  
 *  @param camera Camera that sends out the video data.
 *  @param settings The updated real values for parameters.
 */
- (void)camera:(DJICamera *_Nonnull)camera didUpdateExposureSettings:(DJICameraExposureSettings)settings;


/**
 *  Received temperature in degrees Celsius of image. The thermal imaging camera
 *  will only update the temperature if the temperature data is enabled. For the XT
 *  Standard version, the temperature measurement data is the average of the center
 *  four pixels of the image. For the XT Advanced Radiometry version, the
 *  temperature measurement point can be set using
 *  `setThermalSpotMeteringTargetPoint:withCompletion`.
 *  
 *  @param camera Camera that sends out the updated center temperature.
 *  @param temperature The camera's temperature data in degrees Celsius.
 */
- (void)camera:(DJICamera *_Nonnull)camera didUpdateTemperatureData:(float)temperature;

@end

/*********************************************************************************/
#pragma mark - DJICamera
/*********************************************************************************/


/**
 *  This class contains the media manager and playback manager, which manage the
 *  camera's media content. It provides methods to change camera settings and
 *  perform camera actions. This object is available from the `DJIAircraft` or
 *  `DJIHandheld` object, which is a subclass of `DJIBaseProduct`.
 */
@interface DJICamera : DJIBaseComponent


/**
 *  Delegate that receives the information sent by the camera.
 */
@property(nonatomic, weak) id<DJICameraDelegate> delegate;


/**
 *  String that represents name of the camera.
 */
@property(nonatomic, readonly) NSString *_Nonnull displayName;


/**
 *  Media Manager is used for interaction when camera is in
 *  `DJICameraModeMediaDownload`. The user can only access the manager when
 *  `isMediaDownloadModeSupported` returns `YES`. @return The `DJIMediaManager`
 *  object if the aircraft supports media list feature. Otherwise, returns `nil`.
 */
@property(nonatomic, readonly) DJIMediaManager *_Nullable mediaManager;


/**
 *  Playback Manager is used for interaction when camera is in
 *  `DJICameraModePlayback`. User can only access to the manager when
 *  `isPlaybackSupported` returns `YES`.
 */
@property(nonatomic, readonly) DJIPlaybackManager *_Nullable playbackManager;


/**
 *  Camera capabilities.
 */
@property(nonatomic, readonly) DJICameraCapabilities *capabilities;

/*********************************************************************************/
#pragma mark Camera work mode
/*********************************************************************************/


/**
 *  Sets the camera's work mode to taking pictures, video, playback or download.
 *  Please note that you cannot change the mode when a certain task is executing,
 *  such as taking photo(s), recording video, or downloading and saving files. Also
 *  supported by thermal imaging camera.
 *  
 *  @param mode Camera work mode.
 *  @param completion Remote execution result error block.
 */
- (void)setMode:(DJICameraMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's current work mode. Also supported by thermal imaging camera.
 *  
 *  @param mode The value of the `DJICameraMode` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getModeWithCompletion:(void (^_Nonnull)(DJICameraMode mode, NSError *_Nullable error))completion;


/**
 *  Check if the current device supports Media Download Mode.
 *  
 *  @return `YES` if the current device supports Media Download Mode, `NO` otherwise.
 */
- (BOOL)isMediaDownloadModeSupported;


/**
 *  Check if the current device supports Playback Mode.
 *  
 *  @return A boolean value.
 */
- (BOOL)isPlaybackSupported;

/*********************************************************************************/
#pragma mark Shoot photos
/*********************************************************************************/


/**
 *  Check if the current device supports time-lapse shoot mode. Supported only on
 *  the Osmo camera.
 *  
 *  @return `YES` if timelapse is supported.
 */
- (BOOL)isTimeLapseSupported;


/**
 *  Sets the photo shooting mode for the camera.
 *  
 *  @param mode `DJICameraShootPhotoMode` enum value.
 *  @param completion Asynchronous execution result.
 */
- (void)setShootPhotoMode:(DJICameraShootPhotoMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Returns the current photo shooting mode of the camera.
 *  
 *  @param mode `DJICameraShootPhotoMode` enum value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getShootPhotoModeWithCompletion:(void (^_Nonnull)(DJICameraShootPhotoMode mode, NSError *_Nullable error))completion;


/**
 *  Camera starts to take photo with one of the camera capture modes (shoot photo
 *  modes).Also,
 *   Precondition:
 *   1. Camera must be in ShootPhoto mode. Check the enum named CameraShootPhotoMode
 *  in DJICameraSettingsDef to find all possible camera capture modes. For thermal
 *  imaging camera, Single photo can be taken while recording video.
 *  2. The SD card state should be checked before this method is used to ensure
 *  sufficient space exists.
 *   Post condition:
 *   If the capture mode is either Burst or Interval, calling stopShootPhoto will be
 *  required for the camera to stop taking photos.
 *  
 *  @param completion The execution callback with the returned execution result.
 */
- (void)startShootPhotoWithCompletion:(DJICompletionBlock)completion;


/**
 *  Camera stops taking photos.
 *   Precondition:
 *   1. `startShootPhotoWithCompletion` has been invoked and the shoot mode is
 *  either Interval or Time-lapse.
 *   2. If the capture mode is set to Single, the camera will automatically stop
 *  taking the photo once the individual photo is taken.
 *  
 *  @param completion The execution callback with the returned execution result.
 */
- (void)stopShootPhotoWithCompletion:(DJICompletionBlock)completion;

/*********************************************************************************/
#pragma mark Record video
/*********************************************************************************/


/**
 *  Starts recording video.
 *   Precondition:
 *   Camera must be in `DJICameraModeRecordVideo` mode.
 *  For thermal imaging camera, user can take Single photo when recording video.
 *  
 *  @param completion The execution callback with the returned execution result.
 */
- (void)startRecordVideoWithCompletion:(DJICompletionBlock)completion;


/**
 *  Stops recording video.
 *   Precondition:
 *   The camera is recording currently.
 *  
 *  @param completion The execution callback with the returned execution result.
 */
- (void)stopRecordVideoWithCompletion:(DJICompletionBlock)completion;

@end

/*********************************************************************************/
#pragma mark - DJICamera (CameraSettings)
/*********************************************************************************/

@interface DJICamera (CameraSettings)

/*********************************************************************************/
#pragma mark Camera basic settings
/*********************************************************************************/


/**
 *  Sets the camera's file index mode for the SD card. The default value of
 *  `DJICameraFileIndexMode` is set to `DJICameraFileIndexModeReset`.
 *  
 *  @param mode File index mode to be set for the camera's SD card.
 *  @param completion Remote execution result error block.
 */
- (void)setFileIndexMode:(DJICameraFileIndexMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's file index mode.
 *  
 *  @param mode The value of the `DJICameraFileIndexMode` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getFileIndexModeWithCompletion:(void (^_Nonnull)(DJICameraFileIndexMode mode, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Video related
/*********************************************************************************/


/**
 *  Sets the camera's video resolution and frame rate. @warning The supported
 *  resolutions and frame rates for the two different analog television standards
 *  PAL and NTSC are below:
 *   <b>NTSC:</b>
 *   Resolution_4096x2160, FrameRate_24fps
 *   Resolution_3840x2160, FrameRate_30fps
 *   Resolution_3840x2160, FrameRate_24fps
 *   Resolution_2704X1520, FrameRate_30fps
 *   Resolution_2704X1520, FrameRate_24fps
 *   Resolution_1920x1080, FrameRate_120fps (Slow Motion)
 *   Resolution_1920x1080, FrameRate_60fps
 *   Resolution_1920x1080, FrameRate_48fps
 *   Resolution_1920x1080, FrameRate_30fps
 *   Resolution_1920x1080, FrameRate_24fps
 *   Resolution_1280x720,  FrameRate_60fps
 *   Resolution_1280x720,  FrameRate_48fps
 *   Resolution_1280x720,  FrameRate_30fps
 *   Resolution_1280x720,  FrameRate_24fps
 *   <b>PAL:</b>
 *   Resolution_4096x2160, FrameRate_25fps
 *   Resolution_4096x2160, FrameRate_24fps
 *   Resolution_3840x2160, FrameRate_25fps
 *   Resolution_3840x2160, FrameRate_24fps
 *   Resolution_2704X1520, FrameRate_25fps
 *   Resolution_2704X1520, FrameRate_24fps
 *   Resolution_1920x1080, FrameRate_120fps (Slow Motion)
 *   Resolution_1920x1080, FrameRate_50fps
 *   Resolution_1920x1080, FrameRate_48fps
 *   Resolution_1920x1080, FrameRate_25fps
 *   Resolution_1920x1080, FrameRate_24fps
 *   Resolution_1280x720, FrameRate_50fps
 *   Resolution_1280x720, FrameRate_48fps
 *   Resolution_1280x720, FrameRate_25fps
 *   Resolution_1280x720, FrameRate_24fps
 *  
 *  @param resolutionAndFrameRate Resolution to be set for the video.
 *  @param completion Remote execution result error block.
 */
- (void)setVideoResolutionAndFrameRate:(DJICameraVideoResolutionAndFrameRate *)resolutionAndFrameRate
                        withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's video resolution and frame rate values.
 *  
 *  @param resolutionAndFrameRate The value of the `DJICameraVideoResolutionAndFrameRate` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getVideoResolutionAndFrameRateWithCompletion:(void (^_Nonnull)(DJICameraVideoResolutionAndFrameRate *_Nullable resolutionAndFrameRate,
                                                                       NSError *_Nullable error))completion;


/**
 *  Sets the camera's video file format. The default value is
 *  `DJICameraVideoFileFormatMOV`.
 *  
 *  @param format Video file format to be set for videos.
 *  @param completion Remote execution result error block.
 */
- (void)setVideoFileFormat:(DJICameraVideoFileFormat)format withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's video file format.
 *  
 *  @param format The value of the `DJICameraVideoFileFormat` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to return the current video file format.
 */
- (void)getVideoFileFormatWithCompletion:(void (^_Nonnull)(DJICameraVideoFileFormat format, NSError *_Nullable error))completion;


/**
 *  Sets the camera's analog video standard. Setting the video standard to PAL or
 *  NTSC will limit the available resolutions and frame rates to those compatible
 *  with the chosen video standard.
 *  
 *  @param videoStandard Video standard value to be set for the camera.
 *  @param completion Remote execution result error block.
 */
- (void)setVideoStandard:(DJICameraVideoStandard)videoStandard withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's video standard value.
 *  
 *  @param videoStandard The value of the `DJICameraVideoStandard` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Remote execution result error block.
 */
- (void)getVideoStandardWithCompletion:(void (^_Nonnull)(DJICameraVideoStandard videoStandard, NSError *_Nullable error))completion;


/**
 *  Enables recording position, time and camera information into a video caption
 *  file (.srt) saved on the SD card. The information is updated at 1Hz. Currently
 *  the .srt file can only be downloaded directly from the SD card.
 *  
 *  @param enabled `YES` to enable video caption.
 *  @param completion The execution callback with the returned value.
 */
- (void)setVideoCaptionEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets whether the video caption is enabled.
 *  
 *  @param enabled The enabled value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getVideoCaptionEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Sets the video file compression standard. It is only supported X4S camera, X5S
 *  camera and Phantom 4 Pro. For all other products, H.264 is used.
 *  
 *  @param standard The compression standard to use.
 *  @param completion Completion block that receives the setter result.
 */
- (void)setVideoFileCompressionStandard:(DJIVideoFileCompressionStandard)standard withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the video file compression standard. It is only supported X4S camera, X5S
 *  camera and Phantom 4 Pro.
 *  
 *  @param standard The value of the `DJIVideoFileCompressionStandard` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getVideoFileCompressionStandardWithCompletion:(void (^_Nonnull)(DJIVideoFileCompressionStandard standard, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Photo related
/*********************************************************************************/


/**
 *  Sets the camera's aspect ratio for photos. See `DJICameraPhotoAspectRatio` to
 *  view all possible ratios. Not supported by Z30 camera as the aspect ratio of Z30
 *  is always `DJICameraPhotoAspectRatio16_9`.
 *  
 *  @param aspectRatio Aspect ratio for photos to be taken by camera.
 *  @param completion Remote execution result error block.
 */
- (void)setPhotoAspectRatio:(DJICameraPhotoAspectRatio)aspectRatio withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's aspect ratio for photos.
 *  
 *  @param aspectRatio The value of the `DJICameraPhotoAspectRatio` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Remote execution result callback block.
 */
- (void)getPhotoAspectRatioWithCompletion:(void (^_Nonnull)(DJICameraPhotoAspectRatio aspectRatio, NSError *_Nullable error))completion;


/**
 *  Sets the camera's photo file format. See `DJICameraPhotoFileFormat` to view all
 *  possible photo formats to which the camera can be set. Also supported by thermal
 *  imaging camera. Not supported by Z30 camera as the photo file format for Z30 is
 *  always `DJICameraPhotoFileFormatJPEG`.
 *  
 *  @param format Photo file format used when the camera takes a photo.
 *  @param completion Completion block.
 */
- (void)setPhotoFileFormat:(DJICameraPhotoFileFormat)format withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's photo file format.
 *  
 *  @param format The value of the `DJICameraPhotoFileFormat` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getPhotoFileFormatWithCompletion:(void (^_Nonnull)(DJICameraPhotoFileFormat format, NSError *_Nullable error))completion;


/**
 *  Sets the burst shoot count for the camera when the user wants to use that
 *  feature. Check `DJICameraPhotoBurstCount` to view all possible burst count
 *  values to which the camera can be set.
 *  
 *  @param count The number of photos to take in one burst shoot.
 *  @param completion Completion block.
 */
- (void)setPhotoBurstCount:(DJICameraPhotoBurstCount)count withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the burst count type.
 *  
 *  @param count The value of the `DJICameraPhotoBurstCount` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getPhotoBurstCountWithCompletion:(void (^_Nonnull)(DJICameraPhotoBurstCount count, NSError *_Nullable error))completion;


/**
 *  Sets the RAW image burst shoot count for the camera when the user wants to use
 *  that feature. See `DJICameraPhotoBurstCount` to view all possible burst count
 *  values to which the camera can be set. It is only supported Inspire 2.
 *  
 *  @param count The number of photos to take in one RAW burst shoot.
 *  @param completion Completion block.
 */
- (void)setPhotoRAWBurstCount:(DJICameraPhotoBurstCount)count withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the RAW image burst count. It is only supported Inspire 2.
 *  
 *  @param count The value of the `DJICameraPhotoBurstCount` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getPhotoRAWBurstCountWithCompletion:(void (^_Nonnull)(DJICameraPhotoBurstCount count, NSError *_Nullable error))completion;


/**
 *  Sets the camera's auto exposure bracketing (AEB) capture parameters.
 *  
 *  @param count AEB capture count to be set for the camera.
 *  @param completion Remote execution result error block.
 */
- (void)setPhotoAEBCount:(DJICameraPhotoAEBCount)count withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's AEB capture parameters.
 *  
 *  @param count The value of the `DJICameraPhotoAEBCount` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getPhotoAEBCountWithCompletion:(void (^_Nonnull)(DJICameraPhotoAEBCount count, NSError *_Nullable error))completion;


/**
 *  Sets the interval shoot parameters. The camera will capture a photo, wait a
 *  specified interval of time, take another photo, and continue in this manner
 *  until it has taken the required number of photos. Also supported by thermal
 *  imaging camera.
 *  
 *  @param settings An instance of `DJICameraPhotoTimeIntervalSettings`.
 *  @param completion Remote execution result error block.
 */
- (void)setPhotoTimeIntervalSettings:(DJICameraPhotoTimeIntervalSettings)settings withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's interval shoot parameters. </br></br>Also supported by thermal
 *  imaging camera.
 *  
 *  @param settings The value of the `DJICameraPhotoTimeIntervalSettings` Struct.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getPhotoTimeIntervalSettingsWithCompletion:(void (^_Nonnull)(DJICameraPhotoTimeIntervalSettings settings, NSError *_Nullable error))completion;


/**
 *  Sets the TimeLapse parameters, including interval, duration and file format when
 *  saving. Precondition: Camera should be in `DJICameraShootPhotoModeTimeLapse`
 *  mode of `DJICameraShootPhotoMode`.
 *  
 *  @param settings The interval, duration and file format to set for time-lapse mode.
 *  @param completion The execution block with the returned execution result.
 */
- (void)setPhotoTimeLapseSettings:(DJICameraPhotoTimeLapseSettings)settings withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the TimeLapse parameters including interval, duration and file format when
 *  saving. Precondition: The camera must be in `DJICameraShootPhotoModeTimeLapse`
 *  mode of `DJICameraShootPhotoMode`.
 *  
 *  @param settings The value of the `DJICameraPhotoTimeLapseSettings` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getPhotoTimeLapseSettingsWithCompletion:(void (^_Nonnull)(DJICameraPhotoTimeLapseSettings settings, NSError *_Nullable error))completion;


/**
 *  Sets the panorama mode. It is used when `setShootPhotoMode:withCompletion` is
 *  called with `DJICameraShootPhotoModePanorama`.  It is only supported by Spark.
 *  
 *  @param mode The panorama mode to set.
 *  @param completion `completion block` to receive the result.
 */
- (void)setPhotoPanoramaMode:(DJICameraPhotoPanoramaMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the panorama mode. It is only supported by Spark.
 *  
 *  @param mode The current panorama mode.
 *  @param error Error retrieving the value.
 *  @param completion `completion block` to receive the result.
 */
- (void)getPhotoPanoramaModeWithCompletion:(void (^_Nonnull)(DJICameraPhotoPanoramaMode mode, NSError *_Nullable error))completion;


/**
 *  Change the original image configuration when shooting panorama photos. CAUTION:
 *  enabling this may consume 500 MB in the SD card or the internal storage for each
 *  panorama. It is supported by Mavic Air and Mavic 2. For Mavic Air, `format` is
 *  not used and it will ignore the value.
 *  
 *  @param settings An object of `DJICameraOriginalPhotoSettings`.
 *  @param completion Completion block that receives the setter result.
 */
- (void)setPanoOriginalPhotoSettings:(DJICameraOriginalPhotoSettings *)settings withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the configuration, which determines the behavior for the original images
 *  when shooting panorama photos. CAUTION: If this is enabled, it may consume 500
 *  MB in the SD card or the internal storage for each panorama. It is supported by
 *  Mavic Air and Mavic 2. However, Mavic Air cannot change the format to save the
 *  original images. `format` will be  ignored by Mavic Air.
 *  
 *  @param setting An object of `DJICameraOriginalPhotoSettings`.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getPanoOriginalPhotoSettingsWithCompletion:(void (^_Nonnull)(DJICameraOriginalPhotoSettings *setting, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Exposure Settings
/*********************************************************************************/


/**
 *  Sets the camera's exposure mode. Check `DJICameraExposureMode` to view all
 *  possible camera exposure modes. Please note that in different exposure mode, it
 *  will have different values for the same setting.
 *  
 *  @param mode Camera exposure mode to set.
 *  @param completion Remote execution result error block.
 */
- (void)setExposureMode:(DJICameraExposureMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's exposure mode.
 *  
 *  @param mode The value of the `DJICameraExposureMode` of the Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getExposureModeWithCompletion:(void (^_Nonnull)(DJICameraExposureMode mode, NSError *_Nullable error))completion;


/**
 *  Sets the camera's ISO value. See `DJICameraISO` to view all possible ISO
 *  settings for the camera. For the X5, X5R, Phantom 4 Pro camera, X4S and X5S, the
 *  ISO value can be set for all modes. For the other cameras, the ISO value can
 *  only be set when the camera exposure mode is in Manual mode. See the
 *  `setExposureMode:withCompletion` method for how to set exposure mode.
 *  
 *  @param iso ISO value to be set.
 *  @param completion Completion block.
 */
- (void)setISO:(DJICameraISO)iso withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's ISO value.
 *  
 *  @param iso The value of the `DJICameraISO` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getISOWithCompletion:(void (^_Nonnull)(DJICameraISO iso, NSError *_Nullable error))completion;


/**
 *  Sets the camera shutter speed. To see all available <code>shutterSpeed</code>
 *  value settings, see `DJICameraShutterSpeed`. The shutter speed should not be set
 *  slower than the video frame rate when the camera's mode is
 *  `DJICameraModeRecordVideo`. For example, if the video frame rate is 30fps, the
 *  <code>shutterSpeed</code> must be <= 1/30. Precondition: The shutter speed can
 *  be set only when the camera exposure mode is Shutter mode or Manual mode.
 *  
 *  @param shutterSpeed Shutter speed value to be set for the camera. For all available values shutterSpeed can be set to, please check `DJICameraShutterSpeed`. <br> The shutter speed should not be set slower than the video frame rate when the camera's mode is `DJICameraModeRecordVideo`. For example, if the video frame rate = 30fps, then the shutterSpeed must be <= 1/30.
 *  @param completion Remote execution result error block.
 */
- (void)setShutterSpeed:(DJICameraShutterSpeed)shutterSpeed withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's shutter speed.
 *  
 *  @param shutterSpeed The value of the `DJICameraShutterSpeed` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getShutterSpeedWithCompletion:(void (^_Nonnull)(DJICameraShutterSpeed shutterSpeed, NSError *_Nullable error))completion;


/**
 *  Sets the camera's exposure metering. See `DJICameraMeteringMode` to view all
 *  possible exposure metering settings for the camera.
 *  
 *  @param mode Exposure metering to be set. Check the enum `DJICameraMeteringMode` to find all possible exposure metering the camera can be set to.
 *  @param completion Completion block.
 */
- (void)setMeteringMode:(DJICameraMeteringMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's exposure metering.
 *  
 *  @param mode The value of the `DJICameraMeteringMode` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getMeteringModeWithCompletion:(void (^_Nonnull)(DJICameraMeteringMode mode, NSError *_Nullable error))completion;


/**
 *  Sets the spot metering area index. The camera image is divided into 96 spots
 *  defined by 12 columns and 8 rows. The row index range is [0,7], where the values
 *  increase top to bottom across the image. The column index range is [0, 11],
 *  where the values increase left to right. In order to make the method work, The
 *  camera exposure mode should be <code>Program</code>, <code>Shutter</code> or
 *  <code>Aperture</code>, the exposure metering mode must be
 *  `DJICameraMeteringModeSpot`, and `setAELock:withCompletion` must be `NO`.
 *  
 *  @param rowIndex Spot metering row index to be set. The value should falls in [0, 7], where the values increase top to bottom across the image.
 *  @param columnIndex Spot metering column index to be set. The value should falls in [0, 11], where the values increase left to right.
 *  @param completion Remote execution result error block.
 */
- (void)setSpotMeteringTargetRowIndex:(uint8_t)rowIndex columnIndex:(uint8_t)columnIndex withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the spot metering area row index and column index. In order to make the
 *  method work, The camera exposure mode should be `DJICameraExposureModeProgram`,
 *  `DJICameraExposureModeShutterPriority` or
 *  `DJICameraExposureModeAperturePriority`, the exposure metering mode must be
 *  `DJICameraMeteringModeSpot`, and `getAELockWithCompletion` must be `NO`.
 *  
 *  @param rowIndex The rowIndex value.
 *  @param columnIndex The colIndex value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSpotMeteringTargetWithCompletion:(void (^_Nonnull)(uint8_t rowIndex, uint8_t columnIndex, NSError *_Nullable error))completion;


/**
 *  Sets the camera's exposure compensation. See `DJICameraExposureCompensation` to
 *  view all possible exposure compensations to which the camera can be set. In
 *  order to use this function, set the camera exposure mode to
 *  <code>shutter</code>, <code>program</code> or <code>aperture</code>.
 *  
 *  @param compensation Exposure compensation value to be set for the camera.
 *  @param completion Completion block.
 */
- (void)setExposureCompensation:(DJICameraExposureCompensation)compensation withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's exposure compensation.
 *  
 *  @param compensation The value of the `DJICameraExposureCompensation` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getExposureCompensationWithCompletion:(void (^_Nonnull)(DJICameraExposureCompensation compensation, NSError *_Nullable error))completion;


/**
 *  Locks or unlocks the camera's AE (auto exposure).
 *   Post condition:
 *   If the AE lock is enabled, the spot metering area cannot be set.
 *  
 *  @param isLocked `YES` if the camera AE is locked, `NO` if it is unlocked.
 *  @param completion The execution callback with the returned execution result.
 */
- (void)setAELock:(BOOL)isLocked withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines if the camera's AE (auto exposure) is locked.
 *  
 *  @param isLocked The isLocked value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getAELockWithCompletion:(void (^_Nonnull)(BOOL isLocked, NSError *_Nullable error))completion;


/**
 *  Enables/disables auto-unlocking of AE lock after shooting a photo. If it is
 *  enabled, the Auto Exposure will unlock after each shot. If disabled, Auto
 *  Exposure will change when calling `setAELock:withCompletion`. It is only
 *  supported X4S, X5S and Phantom 4 Pro cameras. For the other products, auto-
 *  unlocking is always enabled.
 *  
 *  @param enabled `YES` if the camera AE will automatically unlock.
 *  @param completion Completion block that receives the setter result.
 */
- (void)setAutoAEUnlockEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether auto-unlocking of AE lock is enabled. It is only supported by
 *  X4S, X5S and Phantom 4 Pro cameras.
 *  
 *  @param enabled The enabled value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getAutoAEUnlockEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark White Balance
/*********************************************************************************/


/**
 *  Sets the camera's white balance. When the white balance is a preset value
 *  (values except `DJICameraWhiteBalancePresetCustom`), the
 *  <code>colorTemperature</code> argument does not take effect. When the white
 *  balance is `DJICameraWhiteBalancePresetCustom`, the `colorTemperature` value is
 *  used instead.
 *  
 *  @param whiteBalance White balance value to be set.
 *  @param completion Completion block.
 *  
 *  See Also: `DJICameraWhiteBalancePreset` to view all possible white balance setting options for the camera.
 */
- (void)setWhiteBalance:(DJICameraWhiteBalance *)whiteBalance withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's white balance and color temperature.
 *  
 *  @param whiteBalance The `DJICameraWhiteBalance` object.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getWhiteBalanceWithCompletion:(void (^_Nonnull)(DJICameraWhiteBalance *_Nullable whiteBalance, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Other settings
/*********************************************************************************/


/**
 *  Sets the camera's anti-flicker frequency for video recording. Precondition: The
 *  exposure mode must be Program. Note: for the Z30 camera, changing anti-flicker
 *  will reboot the camera before the setting takes effect.
 *  
 *  @param antiFlickerFrequency Anti-flicker value to set for the camera. See `DJICameraAntiFlickerFrequency` to view all the possible anti-flicker type settings for the camera.
 *  @param completion Completion block.
 */
- (void)setAntiFlickerFrequency:(DJICameraAntiFlickerFrequency)antiFlickerFrequency withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's anti-flicker.
 *  
 *  @param antiFlickerFrequency The value of the `DJICameraAntiFlickerFrequency` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getAntiFlickerFrequencyWithCompletion:(void (^_Nonnull)(DJICameraAntiFlickerFrequency antiFlickerFrequency, NSError *_Nullable error))completion;


/**
 *  Sets the camera's sharpness. The default value is 0.
 *  
 *  @param sharpness Sharpness value to be set in the range of [-3, 3].
 *  @param completion Asynchronous execution result.
 */
- (void)setSharpness:(int8_t)sharpness withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's sharpness.
 *  
 *  @param sharpness The value of the sharpness with range [-3, 3].
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSharpnessWithCompletion:(void (^_Nonnull)(int8_t sharpness, NSError *_Nullable error))completion;


/**
 *  Sets the camera's contrast. The default saturation value is 0.
 *  
 *  @param contrast Contrast value to be set in the range of [-3, 3].
 *  @param completion Completion block.
 */
- (void)setContrast:(int8_t)contrast withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's contrast.
 *  
 *  @param contrast The value of the contrast with range [-3, 3].
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getContrastWithCompletion:(void (^_Nonnull)(int8_t contrast, NSError *_Nullable error))completion;


/**
 *  Sets the camera's saturation. The default saturation value is 0.
 *  
 *  @param saturation Saturation value to be set in the range of [-3, 3]. The default value of the saturation value is 0.
 *  @param completion Remote execution result error block.
 */
- (void)setSaturation:(int8_t)saturation withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's saturation.
 *  
 *  @param saturation The saturation value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSaturationWithCompletion:(void (^_Nonnull)(int8_t saturation, NSError *_Nullable error))completion;


/**
 *  Sets the camera's color. The default value is `DJICameraColorNone`. For a list
 *  of all possible camera colors, see `DJICameraColor`.
 *  
 *  @param color Camera color to be applied to the camera.
 *  @param completion Remote execution result error block.
 */
- (void)setColor:(DJICameraColor)color withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's color.
 *  
 *  @param color The current camera's color.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getColorWithCompletion:(void (^_Nonnull)(DJICameraColor color, NSError *_Nullable error))completion;


/**
 *  Determines whether the device supports the quick view. Quick view is the period
 *  of time a photo is shown as a preview after it is taken and before the camera
 *  returns to the live camera view.
 *  
 *  @return A boolean value.
 */
- (BOOL)isPhotoQuickViewSupported;


/**
 *  Sets the camera's quick view duration. The valid range is [0, 10] seconds. When
 *  duration is 0, it means that the quick view is disabled. The default value is 0
 *  second. Call `isPhotoQuickViewSupported` before using this method.
 *  
 *  @param duration Quick view duration to be set for the camera.
 *  @param completion Remote execution result error block.
 */
- (void)setPhotoQuickViewDuration:(NSUInteger)duration withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's quick view duration.
 *  
 *  @param duration The duration value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getPhotoQuickViewDurationWithCompletion:(void (^_Nonnull)(NSUInteger duration, NSError *_Nullable error))completion;


/**
 *  Enable/disable defog feature. When defog feature is enabled, the contrast will
 *  be enhanced extraordinarily. It is only supported Z30.
 *  
 *  @param enabled `YES` to enable defog feature.
 *  @param completion Completion block that receives the setter result.
 */
- (void)setDefogEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether defog feature is enabled. It is only supported by Z30 camera.
 *  
 *  @param enabled The enabled value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getDefogEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Enables/disables the IR filter (infared filter). Disabling the IR filter can
 *  enhance the image in low light environments. Enabling the IR filter can reduce
 *  the color distortion caused by the infared light. It is only supported by Z30
 *  camera.
 *  
 *  @param enabled `YES` to enable IR-Cut filter.
 *  @param completion Completion block that receives the setter result.
 */
- (void)setIRFilterEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether IR filter (infared filter) is enabled. Disabling the IR
 *  filter can enhance the image in low light environments. Enabling the IR filter
 *  can reduce the color distortion caused by the infared light. It is only
 *  supported by Z30 camera.
 *  
 *  @param enabled `YES` if IR-Cut filter is enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getIRFilterEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Digital Zoom
/*********************************************************************************/


/**
 *  Check if the current device supports digital zoom scale. It is supported by Osmo
 *  with X3 camera, Phantom 4 camera, Z3 camera, Mavic Pro camera and Z30 camera.
 *  
 *  @return A boolean value.
 */
- (BOOL)isDigitalZoomSupported;


/**
 *  Adjusts the digital zoom. It is supported by Osmo with X3 camera, Phantom 4
 *  camera, Z3 camera and Mavic Pro camera.
 *  
 *  @param factor The valid range is from 1.0 to 2.0.
 *  @param completion The completion block with the returned execution result.
 */
- (void)setDigitalZoomFactor:(float)factor withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets current digital zoom. It is supported by Osmo with X3 camera, Phantom 4
 *  camera, Z3 camera, Mavic Pro camera and Z30 camera. Note Z30 cannot set the
 *  digital zoom scale, but will use digital zoom when using
 *  `startContinuousOpticalZoomInDirection:withSpeed:withCompletion` and the optical
 *  zoom has reached its limit.
 *  
 *  @param factor The scale value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getDigitalZoomFactorWithCompletion:(void (^_Nonnull)(float factor, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Optical Zoom
/*********************************************************************************/


/**
 *  Check if camera supports optical zoom. It is only supported by X5, X5R and X5S
 *  camera with the Olympus M.Zuiko ED 14-42mm f/3.5-5.6 EZ lens, Z3 camera and Z30
 *  camera. @return `YES` if camera supports optical zoom.
 *  
 *  @return A boolean value.
 */
-(BOOL)isOpticalZoomSupported;


/**
 *  Gets the specification of the zoom lens. It is only supported by X5, X5R and X5S
 *  camera with lens Olympus M.Zuiko ED 14-42mm f/3.5-5.6 EZ, Z3 camera and Z30
 *  camera.
 *  
 *  @param spec The value of the `DJICameraOpticalZoomSpec` Struct.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
-(void)getOpticalZoomSpecWithCompletion:(void(^_Nonnull)(DJICameraOpticalZoomSpec spec, NSError *_Nullable error))completion;


/**
 *  Sets focal length of the zoom lens. It is only supported by X5, X5R and X5S
 *  camera with lens Olympus M.Zuiko ED 14-42mm f/3.5-5.6 EZ, Z3 camera and Z30
 *  camera.
 *  
 *  @param focalLength Focal length of zoom lens. Valid range is [`minFocalLength`, `maxFocalLength`] and must be a multiple of `focalLengthStep`.
 *  @param completion The completion block with the returned execution result.
 */
-(void)setOpticalZoomFocalLength:(NSUInteger)focalLength withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets zoom lens focal length in units of 0.1mm. It is only supported by X5, X5R
 *  and X5S camera with lens Olympus M.Zuiko ED 14-42mm f/3.5-5.6 EZ, Z3 camera and
 *  Z30 camera.
 *  
 *  @param focalLength The focalLength value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
-(void)getOpticalZoomFocalLengthWithCompletion:(void (^_Nonnull)(NSUInteger focalLength, NSError *_Nullable error))completion;


/**
 *  Gets current optical zoom factor with range [1, 30]. It is only supported Z30
 *  camera. The Z30 zoom factor can be changed with
 *  `setOpticalZoomFocalLength:withCompletion` and
 *  `startContinuousOpticalZoomInDirection:withSpeed:withCompletion`. The zoom
 *  factor is then calculated and given through this method.
 *  
 *  @param factor The zoom factor value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
-(void)getOpticalZoomFactorWithCompletion:(void (^_Nonnull)(float factor, NSError *_Nullable error))completion;


/**
 *  Start changing the focal length of the lens in specified direction with
 *  specified speed. Focal length change (zooming) will halt when maximum or minimum
 *  focal lengths are reached, or `stopContinuousOpticalZoomWithCompletion` is
 *  called. It is only supported by X5, X5R and X5S camera on Osmo with lens Olympus
 *  M.Zuiko ED 14-42mm f/3.5-5.6 EZ, Z3 camera and Z30 camera.
 *  
 *  @param direction Direction to zoom.
 *  @param speed Zoom speed.
 *  @param completion The execution callback with the returned execution result.
 */
-(void)startContinuousOpticalZoomInDirection:(DJICameraZoomDirection)direction
                                   withSpeed:(DJICameraZoomSpeed)speed
                              withCompletion:(DJICompletionBlock)completion;


/**
 *  Called to stop focal length changing, when it currently is from calling
 *  `startContinuousOpticalZoomInDirection:withSpeed:withCompletion`. It is only
 *  supported by X5, X5R and X5S camera on Osmo with lens Olympus M.Zuiko ED 14-42mm
 *  f/3.5-5.6 EZ, Z3 camera and Z30 camera.
 *  
 *  @param completion The execution callback with the returned execution result.
 */
-(void)stopContinuousOpticalZoomWithCompletion:(DJICompletionBlock)completion;

/*********************************************************************************/
#pragma mark - TapZoom
/*********************************************************************************/


/**
 *  Determines whether the current camera supports TapZoom feature. TapZoom is only
 *  supported by Z30 camera. @return `YES` if the camera supports TapZoom.
 *  
 *  @return A boolean value.
 */
-(BOOL)isTapZoomSupported;


/**
 *  Enable/disable TapZoom. `tapZoomAtTarget:withCompletion` can only be called when
 *  TapZoom is enabled. It is only supported Z30 camera.
 *  
 *  @param enabled `YES` to enable TapZoom feature.
 *  @param completion Completion block that receives the setter result.
 */
-(void)setTapZoomEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether TapZoom is enabled. It is only supported by Z30 camera.
 *  
 *  @param enabled The enabled value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
-(void)getTapZoomEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  TapZoom uses a multiplier to change the zoom scale when called. The final zoom
 *  scale for a TapZoom will be: Current Zoom Scale x Multiplier. The multiplier
 *  range is [1,5]. A multiplier of 1 will not change the zoom. When the multiplier
 *  is 1, the zoom scale will not change during TapZoom. It is only supported by Z30
 *  camera.
 *  
 *  @param multiplier Multiplier of TapZoom.
 *  @param completion Completion block that receives the setter result.
 */
-(void)setTapZoomMultiplier:(uint8_t)multiplier withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the multiplier for TapZoom. It is only supported by Z30 camera.
 *  
 *  @param step The step value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
-(void)getTapZoomMultiplierWithCompletion:(void (^_Nonnull)(uint8_t step, NSError *_Nullable error))completion;


/**
 *  TapZoom at the target. It can be called only when TapZoom is enabled.  When a
 *  new target is set, the gimbal will rotate and locate the target in the center of
 *  the screen. At the same time, the camera will zoom by multiplying the TapZoom
 *  multiplier. It is only supported Z30 camera.
 *  
 *  @param target The target to zoom. The range for x and y is from 0.0 to 1.0. The point [0.0, 0.0] represents the top-left corner of the screen.
 *  @param completion Completion block that receives the execution result.
 */
-(void)tapZoomAtTarget:(CGPoint)target withCompletion:(DJICompletionBlock)completion;

/*********************************************************************************/
#pragma mark Audio Settings
/*********************************************************************************/


/**
 *  Determines whether the current device supports audio recording. Currently audio
 *  recording is supported only by the Osmo camera.
 *  
 *  @return The boolean value.
 */
- (BOOL)isAudioRecordingSupported;


/**
 *  Enables audio recording when capturing video. Supported only by Osmo camera.
 *  
 *  @param enabled Enable or disable audio recording.
 *  @param completion The execution callback with the returned execution result.
 */
- (void)setAudioRecordingEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether the audio record is enabled.
 *  
 *  @param enabled The enabled value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getAudioRecordingEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Sets the microphone recording gain.
 *  
 *  @param value Recording gain with range [0, 100].
 *  @param completion The completion block with the returned value(s).
 */
- (void)setAudioGain:(uint8_t)value withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the microphone recording gain.
 *  
 *  @param value The value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getAudioGainWithCompletion:(void (^_Nonnull)(uint8_t value, NSError *_Nullable error))completion;


/**
 *  This method will turn off the camera's cooling fan whenever the camera is cool
 *  enough to do so. This allows better audio recording from the internal microphone
 *  in the camera.
 *  
 *  @param turnOffWhenPossible `YES` to turn fan off whenever possible.
 *  @param completion The execution block with the returned execution result.
 */
- (void)setTurnOffFanWhenPossible:(BOOL)turnOffWhenPossible withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether the fan will turn off whenever it is cool enough to do so to
 *  enable better audio recordings from the camera's internal microphone.
 *  
 *  @param turnOffWhenPossible The turnOffWhenPossible value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getTurnOffFanWhenPossibleWithCompletion:(void (^_Nonnull)(BOOL turnOffWhenPossible, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Advanced Camera Settings
/*********************************************************************************/


/**
 *  `YES` if the changeable lens is supported by the camera. Currently a changeable
 *  lens is supported only by the X5, X5R and X5S cameras.
 *  
 *  @return A boolean value.
 */
- (BOOL)isInterchangeableLensSupported;


/**
 *  Gets details of the installed lens. Supported only by the X5, X5R, X5S and X7
 *  cameras. This is available only when  `isInterchangeableLensSupported` returns
 *  `YES`.
 *  
 *  @param info The info string value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getLensInformationWithCompletion:(void (^_Nonnull)(NSString *_Nullable info, NSError *_Nullable error))completion;


/**
 *  Determines whether the camera supports an adjustable aperture. Currently
 *  adjustable aperture is supported only by the X5, X5R, X4S, X5S cameras and Mavic
 *  2 Pro.
 *  
 *  @return A boolean value.
 */
- (BOOL)isAdjustableApertureSupported;


/**
 *  Sets the aperture value. This feature is available only when
 *  `isAdjustableApertureSupported` returns `YES`.
 *   Precondition:
 *   The exposure mode `DJICameraExposureMode` must be in
 *  `DJICameraExposureModeManual` or `DJICameraExposureModeAperturePriority`. </br>
 *  Supported only by the X5, X5R, X4S, X5S camera and Mavic 2 Pro.
 *  
 *  @param aperture The aperture to set. See DJICameraLensFocusMode.
 *  @param completion The execution callback with the returned execution result.
 */
- (void)setAperture:(DJICameraAperture)aperture withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the lens aperture. This feature is available only when
 *  `isAdjustableApertureSupported` returns `YES`.
 *  
 *  @param aperture The value of the `DJICameraAperture` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getApertureWithCompletion:(void (^_Nonnull)(DJICameraAperture aperture, NSError *_Nullable error))completion;


/**
 *  Determines whether the camera supports an adjustable focal point. Currently, the
 *  adjustable focal point is supported by the X5, X5R, Z3, Mavic Pro camera, Z30,
 *  Phantom 4 Pro camera, X4S, X5S, Mavic 2 Pro, Mavic 2 Zoom Camera and and Mavic 2
 *  Enterprise Camera.
 *  
 *  @return A boolean value.
 */
- (BOOL)isAdjustableFocalPointSupported;


/**
 *  Sets the lens focus mode. See `DJICameraFocusMode`. It is available only when
 *  `isAdjustableFocalPointSupported` returns `YES`. Supported by the X5, X5R, Z3
 *  cameras (Z3 camera can only support `DJICameraFocusModeAuto`), the Mavic Pro
 *  camera, Z30, Phantom 4 Pro camera, X4S, X5S, Mavic 2 Pro, Mavic 2 Zoom Camera
 *  and Mavic 2 Enterprise Camera.
 *  
 *  @param focusMode Focus mode to set. Check `DJICameraFocusMode` for more detail.
 *  @param completion The execution callback with the returned execution result.
 */
- (void)setFocusMode:(DJICameraFocusMode)focusMode withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the lens focus mode. Please check `DJICameraFocusMode`. It is available
 *  only when `isAdjustableFocalPointSupported` returns `YES`. Supported only by the
 *  X5, X5R, Z3 cameras, Mavic Pro camera, Z30, Phantom 4 Pro camera, X4S, X5S,
 *  Mavic 2 Pro,  Mavic 2 Zoom Camera and Mavic 2 Enterprise Camera.
 *  
 *  @param focusMode The value of the `DJICameraFocusMode` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getFocusModeWithCompletion:(void (^_Nonnull)(DJICameraFocusMode focusMode, NSError *_Nullable error))completion;


/**
 *  Sets the lens focus target point. When the focus mode is auto, the target point
 *  is the focal point. When the focus mode is manual, the target point is the zoom
 *  out area if the focus assistant is enabled for the manual mode. It is available
 *  only when `isAdjustableFocalPointSupported` returns `YES`. Supported only by the
 *  X5, X5R, Z3 cameras, Mavic Pro camera, Phantom 4 Pro camera, Mavic 2 Pro, Mavic
 *  2 Zoom Camera, Mavic 2 Enterprise Camera, X4S and X5S. camera, X4S and X5S.
 *  
 *  @param focusTarget The focus target to set. The range for x and y is from 0.0 to 1.0. The point [0.0, 0.0] represents the top-left angle of the screen.
 *  @param completion The execution callback with the returned execution result.
 */
- (void)setFocusTarget:(CGPoint)focusTarget withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the lens focus target point. It is available only when
 *  `isAdjustableFocalPointSupported` returns `YES`. Supported only by the X5, X5R,
 *  Z3 cameras, Mavic Pro camera and Phantom 4 Pro camera, X4S, X5S, Mavic 2 Pro,
 *  Mavic 2 Zoom Camera and Mavic 2 Enterprise Camera.
 *  
 *  @param focusTarget The CGPoint struct.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getFocusTargetWithCompletion:(void (^_Nonnull)(CGPoint focusTarget, NSError *_Nullable error))completion;


/**
 *  Used to enable/disable the lens focus assistant. When the focus assistant is
 *  enabled, the camera live view will digitally zoom into the focus target area so
 *  the user can see the quality of focus. Focus assistant can be used for both
 *  manual focus (MF) and auto focus (AF). It is available only when
 *  `isAdjustableFocalPointSupported` returns `YES`. Supported only by the X5, X5R,
 *  Z3, Phantom 4 Pro camera, X4S and X5S. Because Z3 only supports AF mode,
 *  `isEnabledMF` will be ignored.
 *  
 *  @param settings Sets whether the lens focus assistant for AF and MF mode is enabled.
 *  @param completion The execution callback with the returned execution result.
 */
- (void)setFocusAssistantSettings:(DJICameraFocusAssistantSettings)settings
                   withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether the lens focus assistant is enabled. When the focus assistant
 *  is enabled, the camera live view will digitally zoom into the focus target area
 *  so the user can see the quality of focus. Focus assistant can be used for both
 *  manual focus (MF) and auto focus (AF). It is available only when
 *  `isAdjustableFocalPointSupported` returns `YES`. Supported only by the X5, X5R,
 *  Z3 cameras, Phantom 4 Pro, X4s and X5S.
 *  
 *  @param settings Sets whether the lens focus assistant under AF and MF mode is enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getFocusAssistantSettingsWithCompletion:(void (^_Nonnull)(DJICameraFocusAssistantSettings settings,
                                                                  NSError *_Nullable error))completion;


/**
 *  Gets the lens focusing ring value's max value. It is available only when
 *  `isAdjustableFocalPointSupported` returns `YES`. Supported only by the X5, X5R,
 *  Z3 cameras, Phantom 4 Pro camera, X4S, X5S, Mavic 2 Pro, Mavic 2 Zoom Camera and
 *  Mavic 2 Enterprise Camera.
 *  
 *  @param upperBound The upperBound value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getFocusRingValueUpperBoundWithCompletion:(void (^_Nonnull)(NSUInteger upperBound, NSError *_Nullable error))completion;


/**
 *  Set the focal distance by simulating the focus ring adjustment. Value can have a
 *  range of 0, `getFocusRingValueUpperBoundWithCompletion`], which represents
 *  infinity and the closest possible focal distance. It is available only when
 *  `isAdjustableFocalPointSupported` returns `YES`. For some lenses, the minimum
 *  focus ring value is larger than 0. For example the minimum of DJI MFT 15mm f/1.7
 *  ASPH is 270. To retrieve the minimum value, perform the following steps: - Call
 *  `setFocusMode:withCompletion` with `DJICameraFocusModeAuto`. - Call
 *  `setFocusTarget:withCompletion` with the furthest target (>30m). - Call
 *  `getFocusRingValueWithCompletion` to get the current focus ring value. This is
 *  the minimum value. The maximum value can be retrieved using
 *  `getFocusRingValueUpperBoundWithCompletion`. Supported only by X5, X5R, Z3
 *  cameras, Phantom 4 Pro, X4S, X5S, Mavic 2 Pro, Mavic 2 Zoom Camera  and Mavic 2
 *  Enterprise Camera.
 *  
 *  @param value Value to adjust focus ring to. The minimum value is 0, the maximum value depends on the installed lens. Please use method `getFocusRingValueUpperBoundWithCompletion` to ensure the input argument is valid.
 *  @param completion The execution callback with the returned execution result.
 */
- (void)setFocusRingValue:(NSUInteger)value withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the lens focus ring value. It is available only when
 *  `isAdjustableFocalPointSupported` returns `YES`. Supported only by the X5, X5R,
 *  Z3 cameras, Phantom 4 Pro, X4S, X5S, Mavic 2 Pro, Mavic 2 Zoom Camera, Mavic 2
 *  Enterprise Camera.
 *  
 *  @param distance The distance value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getFocusRingValueWithCompletion:(void (^_Nonnull)(NSUInteger distance, NSError *_Nullable error))completion;


/**
 *  Enables HD (high-definition) live view. When it is enabled, the live view
 *  resolution is 1080p with frame rate 30 fps. The settings will only take effect
 *  when the camera is in record-video mode and the video resolution is either 1080p
 *  or 2.7k without slow-motion enabled. If recording video in 4k, then the live
 *  stream will be limited to 720p. Supported by Mavic Pro, Mavic 2 Pro, Mavic 2
 *  Zoom and Phantom 4 Pro v2.0.
 *  
 *  @param enabled Enable or disable HD live view.
 *  @param completion The execution callback with the returned execution result.
 */
-(void)setHDLiveViewEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  `YES` if 1080p live view is enabled. This will return the value of the setter,
 *  and not necessarily the actual live view resolution. For example, if recording
 *  in 4K and HD live view has previously been set, then this will return `YES` but
 *  the actual live view resolution will be 720p. Supported only by Mavic Pro.
 *  
 *  @param enabled The enabled value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
-(void)getHDLiveViewEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Enables the automatic control of the front-arm LEDs. The camera can turn off the
 *  front-arm LEDs automatically when it shoots photos or records videos. The LEDs
 *  will be turned on after the shooting or recording is finished. Supported only by
 *  Mavic Pro.
 *  
 *  @param enabled Enable the automatic control of the front-arm LEDs.
 *  @param completion The completion block with the returned execution result.
 */
-(void)setLEDAutoTurnOffEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether the automatic control of the front-arm LEDs is Enabled.
 *  Supported only by Mavic Pro.
 *  
 *  @param enabled The enabled value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
-(void)getLEDAutoTurnOffEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Sets the camera's orientation. The gimbal will rotate the roll axis based on the
 *  orientation. Supported only by Mavic Pro.
 *  
 *  @param orientation Camera's orientation.
 *  @param completion The execution callback with the returned execution result.
 */
-(void)setOrientation:(DJICameraOrientation)orientation withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera's orientation. Supported only by Mavic Pro.
 *  
 *  @param orientation The value of the `DJICameraOrientation` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
-(void)getOrientationWithCompletion:(void (^_Nonnull)(DJICameraOrientation orientation, NSError *_Nullable error))completion;


/**
 *  Enables vision stabilization for Z30 camera on M200 series. The vision system in
 *  the M200 series of aircraft can be used to compensate for any drift in the
 *  gimbal by analyzing the live view when there is no gimbal movement. Drift in the
 *  gimbal will be most noticeable at higher zoom factors. It is only supported Z30
 *  on M200 series.
 *  
 *  @param enabled `YES` to enable the vision stabilization.
 *  @param completion `completion block` to receive the result.
 */
- (void)setVisionStabilizationEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether vision stabilization is enabled. It is only supported Z30 on
 *  M200 series.
 *  
 *  @param enabled `YES` if the vision stabilization is enabled.
 *  @param error Error if there is any.
 *  @param completion Completion block to receive the result.
 */
- (void)getVisionStabilizationEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Custom information can be stored in media file's XMP meta data. The custom
 *  information is written to the media file automatically after the media file is
 *  created. This method defines the information to write. The same information will
 *  be written to all media files until the information is changed again by this
 *  method. Custom information written to each file can be retrieved through
 *  `fetchCustomInformationWithCompletion`  or from the image itself when processed
 *  on a separate system. It is only supported Phantom 4 Pro, Phantom 4  Advanced,
 *  Phantom 4 Pro V2.0, Zenmuse X4S, Zenmuse X5S, Zenmuse X7 and Mavic 2 Enterprise
 *  camera.
 *  
 *  @param information Custom information to set. Use UTF-8 encoding with a length equal to or less than 31 characters.
 *  @param completion Completion block to receive the result.
 */
- (void)setMediaFileCustomInformation:(NSString *)information withCompletion:(DJICompletionBlock)completion;


/**
 *  Custom information can be stored in media file's XMP meta data. This method
 *  retrieves the information that will be written to future media files. The
 *  information written to individual files can be retrieved through
 *  `fetchCustomInformationWithCompletion`. It is only supported Phantom 4 Pro,
 *  Phantom 4 Advanced, Phantom 4 Pro V2.0, Zenmuse X4S, Zenmuse X5S, Zenmuse X7 and
 *  Mavic 2 Enterprise camera.
 *  
 *  @param information The custom information to write.
 *  @param error The encountered error if any.
 *  @param completion Completion block to receive the result.
 */
- (void)getMediaFileCustomInformationWithCompletion:(void (^_Nonnull)(NSString *_Nullable information, NSError *_Nullable error))completion;


/**
 *  Enables/disables dewarping (lens distortion correction) for video recorded to SD
 *  card. Supported by Phantom 4 Pro camera, X4S, X5S and X7.
 *  
 *  @param enabled `YES` to enable video dewarping.
 *  @param completion Completion block to receive the setter result.
 */
- (void)setVideoDewarpingEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether dewarping (lens distortion correction) is enabled. Supported
 *  by Phantom 4 Pro camera, X4S, X5S and X7.
 *  
 *  @param enabled `YES` if the video dewarping is enabled.
 *  @param error The encountered error if any.
 *  @param completion Completion block to receive the getter result.
 */
- (void)getVideoDewarpingEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Sensor Dedusting
/*********************************************************************************/


/**
 *  Initiates the sensor cleaning mode. Calling this will change
 *  `sensorCleaningState` from `DJICameraSensorCleaningStateIdle` to
 *  `DJICameraSensorCleaningStateInitiating`. To start the sensor dedusting
 *  operation, the workflow should be:
 *   1. Call `initSensorCleaningModeWithCompletion`.
 *   2. Remove the lens from the camera.
 *   3. Call `startSensorCleaningWithCompletion`.
 *   4. When `sensorCleaningState` becomes
 *  `DJICameraSensorCleaningStateWaitingForLensRemount`, mount the lens back to the
 *  camera.
 *   It is only supported Zenmuse X7.
 *  
 *  @param completion Completion block to receive the result.
 */
- (void)initSensorCleaningModeWithCompletion:(DJICompletionBlock)completion;


/**
 *  Starts cleaning the sensor. The sensor cleaning should only be started when the
 *  lens is removed from the camera. It is only supported Zenmuse X7.
 *  
 *  @param completion Completion block to receive the result.
 */
- (void)startSensorCleaningWithCompletion:(DJICompletionBlock)completion;


/**
 *  Exits sensor cleaning mode. Calling this will stop the current executing
 *  operation and change `sensorCleaningState` to
 *  `DJICameraSensorCleaningStateIdle`.
 *  
 *  @param completion Completion block to receive the result.
 */
- (void)exitSensorCleaningModeWithCompletion:(DJICompletionBlock)completion;

/*********************************************************************************/
#pragma mark EI Mode
/*********************************************************************************/

/**
 *  Determines whether the EI (exposure index) mode is supported by the camera. In
 *  this mode, the camera mimics the way a film camera works to help
 *  cinematographers capture as much information as possible while balancing the
 *  dynamic range and noise with different log curves. This mode only takes effect
 *  when the camera mode is in `DJICameraModeRecordVideo`. The EI mode is supported
 *  by X4S, X5S and X7.
 *  
 *  @return `YES` if the EI mode is supported, otherwise `NO`.
 */
- (BOOL)isEIModeSupported;


/**
 *  Sets the exposure sensitivity mode. It is only supported when
 *  `isEIModeSupported` returns `YES`. It is supported by X4S, X5S and X7. For other
 *  cameras, only ISO mode is supported.
 *  
 *  @param mode The exposure sensitivity mode to set.
 *  @param completion Completion block to receive the setter result.
 */
- (void)setExposureSensitivityMode:(DJICameraExposureSensitivityMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the exposure sensitivity mode. It is only supported when
 *  `isEIModeSupported` returns `YES`. It is supported by X4S, X5S and X7. For other
 *  cameras, only ISO mode is supported.
 *  
 *  @param mode The exposure sensitivity mode has been set.
 *  @param error Error if there is any.
 *  @param completion Completion block to receive the getter result.
 */
- (void)getExposureSensitivityModeWithCompletion:(void (^_Nonnull)(DJICameraExposureSensitivityMode mode, NSError *_Nullable error))completion;


/**
 *  Sets EI value. The valid range can be fetched from `getEIRangeWithCompletion`.
 *  It is only valid when exposure sensitivity mode is
 *  `DJICameraExposureSensitivityModeEI`. It is only supported by X4S, X5S and X7.
 *  
 *  @param ei The EI value to set.
 *  @param completion Completion block to receive the setter result.
 */
- (void)setEI:(NSUInteger)ei withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets EI value. It is only valid when exposure sensitivity mode is
 *  `DJICameraExposureSensitivityModeEI`. It is only supported by X4S, X5S and X7.
 *  
 *  @param ei The EI value to set.
 *  @param error Error if there is any.
 *  @param completion Completion block to receive the getter result.
 */
- (void)getEIWithCompletion:(void (^_Nonnull)(NSUInteger ei, NSError *_Nullable error))completion;


/**
 *  Gets the EI value recommended by the camera. It is only valid when exposure
 *  sensitivity mode is `DJICameraExposureSensitivityModeEI`. It is only supported
 *  by X4S, X5S and X7.
 *  
 *  @param recommendedEI The EI value recommended by the camera.
 *  @param error Error if there is any.
 *  @param completion Completion block to receive the getter result.
 */
- (void)getRecommendedEIWithCompletion:(void (^_Nonnull)(NSUInteger recommendedEI, NSError *_Nullable error))completion;


/**
 *  Gets the valid range of EI values. It is only valid when exposure sensitivity
 *  mode is `DJICameraExposureSensitivityModeEI`. It is only supported by X4S, X5S
 *  and X7.
 *  
 *  @param range The valid range of EI values. Each element is an integer.
 *  @param error Error if there is any.
 *  @param completion Completion block to receive the getter result.
 */
- (void)getEIRangeWithCompletion:(void (^_Nonnull)(NSArray<NSNumber *> *_Nullable range, NSError *_Nullable error))completion;


/**
 *  Sets the camera color for EI mode. It is only valid when exposure sensitivity
 *  mode is `DJICameraExposureSensitivityModeEI`. It is only supported by X4S, X5S
 *  and X7.
 *  
 *  @param color The camera color to set.
 *  @param completion Completion block to receive the setter result.
 */
- (void)setEIColor:(DJICameraEIColor)color withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera color for EI mode. It is only valid when exposure sensitivity
 *  mode is `DJICameraExposureSensitivityModeEI`. It is only supported by X4S, X5S
 *  and X7.
 *  
 *  @param color The current camera color.
 *  @param error Error if there is any.
 *  @param completion Completion block to receive the getter result.
 */
- (void)getEIColorWithCompletion:(void (^_Nonnull)(DJICameraEIColor color, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Mechanical Shutter Speed
/*********************************************************************************/

/**
 *  Determines whether the mechanical shutter speed is supported by the camera or
 *  the lens (for X7). The mechanical shutter is supported by Phantom 4 Pro camera,
 *  X4S and X7 with DL lenses.
 *  
 *  @return `YES` if the mechanical shutter is supported, otherwise `NO`.
 */
- (BOOL)isMechanicalShutterSupported;


/**
 *  Enables the mechanical shutter. It is only valid when
 *  `isMechanicalShutterSupported` returns `YES`.
 *  
 *  @param enabled `YES` to enable the mechanical shutter.
 *  @param completion Completion block to receive the setter result.
 */
- (void)setMechanicalShutterEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether the mechanical shutter is enabled. It is only valid when
 *  `isMechanicalShutterSupported` returns `YES`.
 *  
 *  @param enabled `YES` if the mechanical shutter is enabled.
 *  @param error Error if there is any.
 *  @param completion Completion block to receive the getter result.
 */
- (void)getMechanicalShutterEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark ND Filter
/*********************************************************************************/

/**
 *  Determines whether the ND filter mode is supported by the camera and the lens.
 *  Only the DL-S 16mm F2.8 ND ASPH lens for X7 has a built-in ND4 filter and
 *  supports changing the modes through an application.
 *  
 *  @return `YES` if the ND filter mode is supported, otherwise `NO`.
 */
- (BOOL)isNDFilterModeSupported;


/**
 *  Sets the mode of ND filter. It is only valid when `isNDFilterModeSupported`
 *  returns `YES`.
 *  
 *  @param mode The ND filter mode to set.
 *  @param completion Completion block to receive the setter result.
 */
- (void)setNDFilterMode:(DJICameraNDFilterMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the ND filter mode. It is only valid when `isNDFilterModeSupported` returns
 *  `YES`.
 *  
 *  @param mode The ND filter mode.
 *  @param error Error if there is any.
 *  @param completion Completion block to receive the getter result.
 */
- (void)getNDFilterModeWithCompletion:(void (^_Nonnull)(DJICameraNDFilterMode mode, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Clip Name
/*********************************************************************************/

/**
 *  Sets the clip name for the video to be stored in SSD. The clip name will be
 *  applied to the next video file stored in SSD. After saving a video file,
 *  `clipID` will increase by 1 automatically.  It is only supported by Inspire 2.
 *  
 *  @param name The clip name to set.
 *  @param completion Completion block to receive the setter result.
 */
- (void)setSSDClipFileName:(DJICameraSSDClipFileName *)name withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the clip name for video to be stored in SSD. It is only supported by
 *  Inspire 2.
 *  
 *  @param name The clip name that will be applied to the next video file stored in SSD.
 *  @param error Error if there is any.
 *  @param completion Completion block to receive the getter result.
 */
- (void)getSSDClipFileNameWithCompletion:(void (^_Nonnull)(DJICameraSSDClipFileName *_Nullable name, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Storage Location
/*********************************************************************************/

/**
 *  Determines if the camera supports the internal storage or not. When it is
 *  supported, the camera shoot photos or record videos without SD card. The newly
 *  generated photos or videos will be stored in the internal storage.
 *  
 *  @return `YES` if internal storage is supported.
 */
- (BOOL)isInternalStorageSupported;


/**
 *  Sets the storage location for the newly generated photos or videos. It is only
 *  supported when `isInternalStorageSupported` returns `YES`.
 *  
 *  @param location The storage location to set.
 *  @param completion Completion block to receive the setter result.
 */
- (void)setStorageLocation:(DJICameraStorageLocation)location withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the storage location for the newly generated photos or videos. When
 *  `isInternalStorageSupported` returns `NO`, this setting is always
 *  `DJICameraStorageLocationSDCard`.
 *  
 *  @param location The location to store photos and videos.
 *  @param error Error if there is any.
 *  @param completion Completion block to receive the getter result.
 */
- (void)getStorageLocationWithCompletion:(void (^_Nonnull)(DJICameraStorageLocation location, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Save/load camera settings
/*********************************************************************************/


/**
 *  Load the camera's factory settings.
 *   Post condition: The camera will reboot itself.
 *  
 *  @param completion The execution callback with the returned value(s).
 */
- (void)restoreFactorySettings:(DJICompletionBlock)completion;


/**
 *  Saves the current camera settings permanently to the specified profile. See
 *  `DJICameraCustomSettingsProfile` to view all possible camera users.
 *  
 *  @param profile Camera profile for which to store camera settings.
 *  @param completion The execution callback with the returned execution result.
 */
- (void)saveSettingsToProfile:(DJICameraCustomSettingsProfile)profile withCompletion:(DJICompletionBlock)completion;


/**
 *  Load camera settings from the specified user.
 *   Post condition:
 *   The camera will reboot itself.
 *  
 *  @param profile Camera profile to load camera settings from.
 *  @param completion The execution callback with the returned execution result.
 */
- (void)loadSettingsFromProfile:(DJICameraCustomSettingsProfile)profile withCompletion:(DJICompletionBlock)completion;

/*********************************************************************************/
#pragma mark - Storage Operation
/*********************************************************************************/


/**
 *  Formats the SD card by deleting all the data on the SD card. This does not
 *  change any settings the user may have set on the SD card.
 *  
 *  @param completion Remote execution result callback block.
 */
- (void)formatSDCardWithCompletion:(DJICompletionBlock)completion;


/**
 *  Formats the storage by deleting all the data on it.
 *  
 *  @param storage The storage (either SD card or the internal storage) to format. When it is `DJICameraStorageLocationSDCard`, this interface has the same effect as `formatSDCardWithCompletion`.
 *  @param completion Remote execution result callback block.
 */
- (void)formatStorage:(DJICameraStorageLocation)storage withCompletion:(DJICompletionBlock)completion;

@end

/*********************************************************************************/
#pragma mark - DJISSDOperations
/*********************************************************************************/

/**
 *   X5, X5R and X5S cameras are DSLR quality cameras that can save JPEG,
 *  lossless raw images, MP4 videos, and raw videos requiring very high amounts
 *  of storage in the range of 500 Gb or more. A Solid State Drive (SSD)
 *  provides such storage. Note that JPEG is a compressed format, and raw images
 *  store much more information and allow for a full range of postprocessing
 *  features.
 */
@interface DJICamera (SSDOperations)


/**
 *  Determines whether the SSD is supported by the camera. Currently, the SSD is
 *  supported only by X5R, X4S and X5S camera. @return `YES` if SSD is supported,
 *  otherwise `NO`.
 *  
 *  @return A boolean value.
 */
- (BOOL)isSSDSupported;


/**
 *  Formats the SSD by deleting all the data on the SSD. This does not change any
 *  settings the user may have set on the SSD.
 *  
 *  @param completion The execution callback with the returned execution result.
 */
- (void)formatSSDWithCompletion:(DJICompletionBlock)completion;


/**
 *  Set Raw Video Resolution and Frame Rate of the SSD. Note, only raw video is
 *  saved to the SSD. Compressed video, compressed pictures and raw pictures are all
 *  saved to the SD Card. During video capture, Raw video and compressed video are
 *  saved simultaneously to the SSD and SD Card respectively. @warning The supported
 *  resolutions and frame rates for SSD Raw Videos are shown below:
 *   <b>NTSC:</b>
 *   Resolution_4096x2160, FrameRate_24fps
 *   Resolution_3840x2160, FrameRate_24fps
 *   Resolution_3840x2160, FrameRate_30fps
 *   Resolution_2704X1520, FrameRate_24fps
 *   Resolution_2704X1520, FrameRate_30fps
 *   Resolution_1920x1080, FrameRate_60fps
 *   Resolution_1920x1080, FrameRate_48fps
 *   Resolution_1920x1080, FrameRate_30fps
 *   Resolution_1920x1080, FrameRate_24fps
 *   <b>PAL:</b>
 *   Resolution_4096x2160, FrameRate_25fps
 *   Resolution_4096x2160, FrameRate_24fps
 *   Resolution_3840x2160, FrameRate_25fps
 *   Resolution_3840x2160, FrameRate_24fps
 *   Resolution_2704X1520, FrameRate_25fps
 *   Resolution_2704X1520, FrameRate_24fps
 *   Resolution_1920x1080, FrameRate_50fps
 *   Resolution_1920x1080, FrameRate_48fps
 *   Resolution_1920x1080, FrameRate_25fps
 *   Resolution_1920x1080, FrameRate_24fps
 *   For X5S, the frame rate of SSD has to be the same as the video to be stored in
 *  SD card, so <code>frameRate</code> is ignored. The possible resolutions are
 *  determined by SD card video's frame rate and the SSD video license
 *  (`DJICameraSSDVideoLicense`) being used. The supported resolutions in the
 *  current configuration can be queried by using `SSDVideoResolutionRange` in
 *  `DJICameraCapabilities`.
 *  
 *  @param resolutionAndFrameRate Resolution and frame rate to be set for the video.
 *  @param completion Remote execution result error block.
 */
- (void)setSSDVideoResolutionAndFrameRate:(DJICameraVideoResolutionAndFrameRate *)resolutionAndFrameRate
                           withCompletion:(DJICompletionBlock)completion;


/**
 *  Get Raw Video Format and Frame Rate of the SSD.
 *  
 *  @param resolutionAndframeRate The `DJICameraVideoResolutionAndFrameRate` object.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSSDVideoResolutionAndFrameRateWithCompletion:(void (^_Nonnull)(DJICameraVideoResolutionAndFrameRate *_Nullable resolutionAndframeRate,
                                                                          NSError *_Nullable error))completion;


/**
 *  Sets the camera color for video that will be stored in SSD. It is only applied
 *  when the selected license key is either `DJICameraSSDVideoLicenseProRes422HQ` or
 *  `DJICameraSSDVideoLicenseProRes4444XQ`. This is the legacy version of SSD Color
 *  and it is only supported by Inspire 2 with firmware package versions
 *  (`getFirmwarePackageVersionWithCompletion`) lower than 01.0.0240. For newer
 *  firmware package versions, use `setSSDColor:withCompletion` instead.
 *  
 *  @param color SSD legacy color to set.
 *  @param completion Completion block that receives the setter result.
 */
- (void)setSSDLegacyColor:(DJICameraSSDLegacyColor)color withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the camera color for video that will store in SSD. This is the legacy
 *  version of SSD Color and it is only supported by Inspire 2 with firmware package
 *  versions (`getFirmwarePackageVersionWithCompletion`) lower than 01.0.0240. For
 *  newer firmware package versions, use `getSSDColorWithCompletion` instead.
 *  
 *  @param color The value of the `DJICameraSSDLegacyColor` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSSDLegacyColorWithCompletion:(void (^_Nonnull)(DJICameraSSDLegacyColor color, NSError *_Nullable error))completion;


/**
 *  Sets the color for videos that will be stored in SSD. It is only applied when
 *  the selected license key is either `DJICameraSSDVideoLicenseProRes422HQ` or
 *  `DJICameraSSDVideoLicenseProRes4444XQ`. For `DJICameraSSDVideoLicenseCinemaDNG`,
 *  the color is always `DJICameraSSDColorRawColor`. It is only supported Inspire 2
 *  with the firmware package version (`getFirmwarePackageVersionWithCompletion`)
 *  01.0.0240 or later. For older firmware package versions, use
 *  `setSSDLegacyColor:withCompletion` instead.
 *  
 *  @param color Video color to set.
 *  @param completion Completion block to receive the result.
 */
- (void)setSSDColor:(DJICameraSSDColor)color withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the color for videos that will be stored in SSD. It is only supported
 *  Inspire 2 with the firmware package version
 *  (`getFirmwarePackageVersionWithCompletion`) 01.0.0240 or later. For older
 *  firmware package versions, use `getSSDLegacyColorWithCompletion` instead.
 *  
 *  @param color Color that has been set.
 *  @param error Error if there is any.
 *  @param completion Completion block to receive the result.
 */
- (void)getSSDColorWithCompletion:(void (^_Nonnull)(DJICameraSSDColor color, NSError *_Nullable error))completion;


/**
 *  Gets purchased license key(s). An Inspire 2 License Key activates the usage
 *  permission of CinemaDNG or Apple ProRes inside CineCore 2.0. User can purchase a
 *  license key on DJI's website. It is supported by Inspire 2. the digital filter
 *  for video that will store in SSD. It is only supported Inspire 2.
 *  
 *  @param licenses The array of licenses number.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSSDVideoLicensesWithCompletion:(void (^_Nonnull)(NSArray<NSNumber *> *licenses , NSError *_Nullable error))completion;


/**
 *  Sets the SSD video license to be used. If an unpurchased license is selected
 *  then only SD video will be recorded.
 *  
 *  @param license License to used.
 *  @param completion Completion block to receive the result.
 */
- (void)activateSSDVideoLicense:(DJICameraSSDVideoLicense)license withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the license key being used. It is supported by Inspire 2.
 *  
 *  @param license The value of the `DJICameraSSDVideoLicense` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSSDVideoLicenseWithCompletion:(void (^_Nonnull)(DJICameraSSDVideoLicense license, NSError *_Nullable error))completion;


/**
 *  Enables/disables the recording of RAW video. It is supported by X5S. User can
 *  use the other SSD interfaces only when it is enabled. For X5R, RAW recording is
 *  always enabled if there is SSD inserted.
 *  
 *  @param enabled `YES` to enable the RAW video recording.
 *  @param completion Completion block that receives the setter result.
 */
- (void)setSSDVideoRecordingEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether the recording of RAW video is enabled. It is supported by
 *  X5S.
 *  
 *  @param enabled The enabled value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSSDVideoRecordingEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Enables this to lock the gimbal when the camera is shooting a photo. The gimbal
 *  will  keep the attitude when starting to shoot the photo.
 *  
 *  @param enabled `YES` to enable the feature.
 *  @param completion Completion block that receives the setter result.
 */
- (void)setAutoLockGimbalEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether the gimbal will be locked automatically during shooting
 *  photos.
 *  
 *  @param enabled `YES` if it is enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getAutoLockGimbalEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark - Watermark
/*********************************************************************************/


/**
 *  Sets the watermark configuration. Enables this to add timestamp and location
 *  stamp to  the newly generated photos or videos. It is only supported by Mavic 2
 *  Enterprise.
 *  
 *  @param config The watermark configuration to set.
 *  @param completion Completion block to receive the result.
 */
- (void)setWatermarkSettings:(DJICameraWatermarkSettings *)config withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the watermark settings. If it is enabled, timestamp and location stamp will
 *  be  added to the newly generated photos or videos. It is only supported by Mavic
 *  2 Enterprise.
 *  
 *  @param settings The watermark settings to set.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getWatermarkSettingsWithCompletion:(void (^_Nonnull)(DJICameraWatermarkSettings *settings, NSError *_Nullable error))completion;

@end

/*********************************************************************************/
#pragma mark - Thermal Imaging Camera
/*********************************************************************************/

@interface DJICamera (ThermalCamera)


/**
 *  `YES` if the current connected device is a thermal imaging camera. @return BOOL
 *  `YES` if current connected device is thermal imaging camera.
 *  
 *  @return A boolean value.
 */
- (BOOL)isThermalCamera;


/**
 *  Sets the Region of Interest (ROI). Used to manage color range distribution
 *  across the screen to maximize contrast for regions of highest interest.
 *  Supported only by thermal imaging cameras.
 *  
 *  @param roi An enum type of the Region of Interest to be used. Please refer to `DJICameraThermalROI`.
 *  @param completion Completion block that receives the getter execution result.
 */
- (void)setThermalROI:(DJICameraThermalROI)roi withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the Region of Interest.
 *  
 *  @param roi The value of the `DJICameraThermalROI` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalROIWithCompletion:(void (^_Nonnull)(DJICameraThermalROI roi, NSError *_Nullable error))completion;


/**
 *  Sets the Palette. Each palette is a unique look-up table that maps 8-bit
 *  temperature values to different colors. Different palettes can be used to help
 *  the user better visualize temperature contrast or specific temperature bands.
 *  Supported only by thermal imaging cameras.
 *  
 *  @param palette An enum type of the CameraThermalPalette to be used. Please refer to DJICameraThermalPalette.
 *  @param completion Completion block that receives the getter execution result.
 */
- (void)setThermalPalette:(DJICameraThermalPalette)palette withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the Palette.
 *  
 *  @param palette The value of the `DJICameraThermalPalette` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalPaletteWithCompletion:(void (^_Nonnull)(DJICameraThermalPalette palette, NSError *_Nullable error))completion;


/**
 *  Sets the scene to instantly enhance your image. In all modes except Manual and
 *  User modes, the DDE, ACE, SSO,  brightness and contrast are set automatically to
 *  obtain the best result. In User modes, the contrast and brightness are set
 *  automatically to obtain the best results. Any settings that are made in these
 *  modes are retained if the scene is changed. In Manual mode, DDE, contrast and
 *  brightness are set manually. Supported only by thermal imaging cameras.
 *  
 *  @param scene An enum type for the `DJICameraThermalScene` to be used.
 *  @param completion Completion block that receives the getter execution result.
 */
- (void)setThermalScene:(DJICameraThermalScene)scene withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets current scene.
 *  
 *  @param scene The value of the `DJICameraThermalScene` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalSceneWithCompletion:(void (^_Nonnull)(DJICameraThermalScene scene, NSError *_Nullable error))completion;


/**
 *  Sets the Digital Data Enhancement index (for DDE dynamic mode). DDE can be used
 *  to enhance image details (sharpen, higher index) and/or suppress fixed pattern
 *  noise (soften, lower index). It can be set manually only when the Scene mode is
 *  Manual, User1, User2 or User3. Supported only by thermal imaging cameras.
 *  
 *  @param value Integer in range [-20, 100]. Values less than 0 soften the image and filter fixed pattern noise. Values greater than 0 sharpen the details in the image. Value of 0 results in no enhancement.
 *  @param completion Completion block that receives the getter execution result.
 */
- (void)setThermalDDE:(NSInteger)value withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the value of Digital Data Enhancement. The value is available only when the
 *  Scene mode is Manual, User1, User2 or User3. Supported only by thermal imaging
 *  cameras.
 *  
 *  @param value The value of Digital Data Enhancement.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalDDEWithCompletion:(void (^_Nonnull)(NSInteger value, NSError *_Nullable error))completion;


/**
 *  Set the value of Active Contrast Enhancement. Active contrast enhancement allows
 *  for a contrast trade-off between hotter and colder scenes when using 8-bit pixel
 *  data. It can be set manually only when the Scene mode is User1, User2 or User3.
 *  Supported only by thermal imaging cameras.
 *  
 *  @param value Integer in range [-8, 8]. <br> value > 0: more contrast in hotter scene content and less contrast in colder scene content (sky, ocean etc.). <br> value < 0: more contrast in colder scene content and less contrast in hotter scene content. <br> value = 0: neutral <br> value = 3: recommended for generic use
 *  @param completion Completion block that receives the getter execution result.
 */
- (void)setThermalACE:(NSInteger)value withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the value of Active Contrast Enhancement. The value is available only when
 *  the Scene mode is Manual, User1, User2 or User3. Supported only by thermal
 *  imaging cameras.
 *  
 *  @param value The value of Active Contrast Enhancement.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalACEWithCompletion:(void (^_Nonnull)(NSInteger value, NSError *_Nullable error))completion;


/**
 *  Sets the value of Smart Scene Optimization. When using non-linear histogram
 *  equalization to map the 14-bit sensor pixel values to 8-bit pixel values, it can
 *  become difficult to determine the difference in temperature of two objects from
 *  their different shades of gray. SSO allows a percentage of the 14-bit histogram
 *  to be mapped linearly to the 8-bit histogram, which will compromise local
 *  contrast, but allow for more accurate visual radiometric measurements. This is
 *  particularly useful for bi-modal scenes. It can be set manually only when the
 *  Scene mode is User1, User2 or User3. Supported only by thermal imaging cameras.
 *  
 *  @param value Percentage of histogram to map linearly [0, 100].
 *  @param completion Completion block that receives the getter execution result.
 */
- (void)setThermalSSO:(NSInteger)value withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the value of Smart Scene Optimization. The value is available only when the
 *  Scene mode is Manual, User1, User2 or User3. Supported only by thermal imaging
 *  cameras.
 *  
 *  @param value The value of Smart Scene Optimization.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalSSOWithCompletion:(void (^_Nonnull)(NSInteger value, NSError *_Nullable error))completion;


/**
 *  Sets the brightness of the image. It can be set manually only when the Scene
 *  mode is Manual. Supported only by thermal imaging cameras.
 *  
 *  @param brightness The integer value falls in [0, 16383].
 *  @param completion Completion block that receives the getter execution result.
 */
- (void)setThermalBrightness:(NSUInteger)brightness withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the value of brightness. The value is available only when the Scene mode is
 *  Manual, User1, User2 or User3. Supported only by thermal imaging cameras.
 *  
 *  @param brightness The value of brightness.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalBrightnessWithCompletion:(void (^_Nonnull)(NSUInteger brightness, NSError *_Nullable error))completion;


/**
 *  Sets the value of contrast, with larger values having higher contrast. It can be
 *  set manually only when the Scene mode is Manual. Supported only by thermal
 *  imaging cameras.
 *  
 *  @param contrast Contrast value as an integer with range [0, 255].
 *  @param completion Completion block that receives the getter execution result.
 */
- (void)setThermalContrast:(NSUInteger)contrast withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets contrast value. The value is available only when the Scene mode is Manual,
 *  User1, User2 or User3. Supported only by thermal imaging cameras.
 *  
 *  @param Contrast The contrast value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalContrastWithCompletion:(void (^_Nonnull)(NSUInteger Contrast, NSError *_Nullable error))completion;


/**
 *  Enable or disable Isotherms. Isotherms can be used to highlight specific
 *  temperature ranges: When disabled, all 256 values (8-bits) are dedicated to the
 *  temperature histogram of the scene. When enabled, only 128 values (0-127) are
 *  mapped linearly to temperature. Then three bands 128-175, 176-223 and 224-255
 *  can be mapped to the user defined temperatures to highlight them to the user.
 *  Using some of the false color palettes (like RainbowIso) results in a thermal
 *  image that is grey scale except for three specific bands highlighted by either
 *  reds, blues or greens. Supported only by thermal imaging cameras.
 *  
 *  @param enabled `YES` if isotherms are enabled.
 *  @param completion Completion block that receives the getter execution result.
 */
- (void)setThermalIsothermEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether Isotherms are enabled. `YES` if Isotherms are enabled.
 *  Supported only by thermal imaging cameras.
 *  
 *  @param enabled `YES` if Isotherms are enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalIsothermEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;


/**
 *  Sets the unit of the Isotherm ranges to either Celsius or percent. Different
 *  units results in different value ranges for Isotherms. Supported only by thermal
 *  imaging cameras.
 *  
 *  @param unit An enum type of the CameraThermalIsothermUnit to be used. Please refer to DJICameraThermalIsothermUnit.
 *  @param completion Completion block that receives the getter execution result.
 */
- (void)setThermalIsothermUnit:(DJICameraThermalIsothermUnit)unit withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the units for Isotherm ranges. Supported only by thermal imaging cameras.
 *  
 *  @param unit The value of the `DJICameraThermalIsothermUnit` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalIsothermUnitWithCompletion:(void (^_Nonnull)(DJICameraThermalIsothermUnit unit, NSError *_Nullable error))completion;


/**
 *  Sets the upper threshold value for Isotherm. All temperature values above this
 *  will use colors 224-255 from the palette. Supported only by thermal imaging
 *  cameras.
 *  
 *  @param value If the unit is percentage, the allowed range is [0,100]. If the unit is Celsius, the allowed range is [-40, 550]. The value can only be equal or larger than middle Isotherm threshold.
 *  @param completion Completion block that receives the getter execution result.
 */
- (void)setThermalIsothermUpperValue:(NSInteger)value withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the upper threshold value for Isotherm. Supported only by thermal imaging
 *  cameras.
 *  
 *  @param value The upper threshold value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalIsothermUpperValueWithCompletion:(void (^_Nonnull)(NSInteger value, NSError *_Nullable error))completion;


/**
 *  Sets the middle threshold value for Isotherm. Temperature values between the
 *  middle and upper Isotherm threshold will be displayed with colors 176-223 from
 *  the palette. Supported only by thermal imaging cameras.
 *  
 *  @param value If the unit is percentage, the value falls in [0,100]. If the unit is Celsius, the value range is [-40, 550]. The value can only be equal or larger than lower threshold and equal or smaller than upper threshold.
 *  @param completion Completion block that receives the getter execution result.
 */
- (void)setThermalIsothermMiddleValue:(NSInteger)value withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the middle threshold value for Isotherm. Supported only by thermal imaging
 *  cameras.
 *  
 *  @param value The middle threshold value for Isotherm.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalIsothermMiddleValueWithCompletion:(void (^_Nonnull)(NSInteger value, NSError *_Nullable error))completion;


/**
 *  Sets the lower threshold value for Isotherm. Temperature values between the
 *  lower and middle Isotherm threshold will be displayed with colors 128-175 from
 *  the palette. Supported only by thermal imaging cameras.
 *  
 *  @param value If the unit is percentage, the value falls in [0,100]. If the unit is Celsius, the value range is [-40, 550]. The value can only be equal or smaller than upper threshold.
 *  @param completion Completion block that receives the getter execution result.
 */
- (void)setThermalIsothermLowerValue:(NSInteger)value withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the lower threshold value for Isotherm. Supported only by thermal imaging
 *  cameras.
 *  
 *  @param value The lower threshold value for Isotherm.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalIsothermLowerValueWithCompletion:(void (^_Nonnull)(NSInteger value, NSError *_Nullable error))completion;


/**
 *  Sets the gain mode. Low gain mode can be used for scenes with temperatures
 *  ranging from -40 to 550 degrees Celsius. For higher contrast, the high gain mode
 *  can be used by for temperatures between -25 to 135 degrees Celsius for the
 *  640x512 camera and -25 to 100 degrees Celsius for 324 x 256 camera. Supported
 *  only by thermal imaging cameras.
 *  
 *  @param mode An enum type of the CameraThermalGainMode to be used. Please refer to DJICameraThermalGainMode.
 *  @param completion Completion block that receives the getter execution result.
 */
- (void)setThermalGainMode:(DJICameraThermalGainMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the gain mode. Supported only by thermal imaging cameras.
 *  
 *  @param mode The value of the `DJICameraThermalGainMode` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalGainModeWithCompletion:(void (^_Nonnull)(DJICameraThermalGainMode mode, NSError *_Nullable error))completion;


/**
 *  Sets the mode for thermal measurement. Use delegate method
 *  `camera:didUpdateTemperatureData` or
 *  `camera:didUpdateAreaTemperatureAggregations` to receive the measurement result.
 *  Supported only by thermal imaging cameras.
 *  
 *  @param mode The desired measurement mode.
 *  @param completion Completion block that receives the getter execution result.
 */
- (void)setThermalMeasurementMode:(DJICameraThermalMeasurementMode)mode
                   withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the mode for thermal measurement. Supported only by thermal imaging
 *  cameras.
 *  
 *  @param mode The value of the `DJICameraThermalMeasurementMode` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalMeasurementModeWithCompletion:(void (^_Nonnull)(DJICameraThermalMeasurementMode mode,
                                                                  NSError *_Nullable error))completion;


/**
 *  Adjusts the digital zoom. Supported only by thermal imaging cameras.
 *  
 *  @param factor For resolution 640 x 512, x1,x2,x4,x8 can be set. For resolution 336 x 256, only x1,x2,x4 can be set. Please refer to DJICameraThermalDigitalZoomScale in DJICameraSettingsDef.
 *  @param completion The execution callback with the returned execution result.
 */
- (void)setThermalDigitalZoomFactor:(DJICameraThermalDigitalZoomFactor)factor withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets current digital zoom. Supported only by thermal imaging cameras.
 *  
 *  @param factor The value of the `DJICameraThermalDigitalZoomFactor` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalDigitalZoomFactorWithCompletion:(void (^_Nonnull)(DJICameraThermalDigitalZoomFactor factor, NSError *_Nullable error))completion;


/**
 *  Gets the thermal imaging camera profile. The profile includes information about
 *  resolution, frame rate and focal length. Supported only by thermal imaging
 *  cameras.
 *  
 *  @param profile The value of the `DJICameraThermalProfile` Struct.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalProfileWithCompletion:(void (^_Nonnull)(DJICameraThermalProfile profile, NSError *_Nullable error))completion;


/**
 *  Gets the spot metering target point if one is set, if not then returns
 *  CGPointZero. Supported only by Zenmuse XT containing Advanced Radiometry
 *  capabilities.
 *  
 *  @param targetPoint The CGPoint struct.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalSpotMeteringTargetPointWithCompletion:(void (^_Nonnull)(CGPoint targetPoint, NSError *_Nullable error))completion;


/**
 *  Sets the spot metering target point which then changes the
 *  `camera:didUpdateTemperatureData` delegate call to return. This method requires
 *  a relative point that is proportional to the dimension of the camera video
 *  dimension, the x, and y values must all be between 0 and 1.0. Supported only by
 *  Zenmuse XT containing Advanced Radiometry capabilities.
 *  
 *  @param targetPoint The desired target point.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setThermalSpotMeteringTargetPoint:(CGPoint)targetPoint withCompletion:(DJICompletionBlock)completion;


/**
 *  Get a rect representing the currently set metering area for the thermal scene.
 *  Supported only by Zenmuse XT containing Advanced Radiometry capabilities.
 *  
 *  @param area The CGRect struct.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalMeteringAreaWithCompletion:(void (^_Nonnull)(CGRect area, NSError *_Nullable error))completion;


/**
 *  Set the metering area for a rectangle inside the thermal image scene, which
 *  allows the camera to transmit aggregate temperature computations via the
 *  `camera:didUpdateAreaTemperatureAggregations` delegate method. See
 *  `DJICameraThermalAreaTemperatureAggregations` for the statistical values that
 *  are available. This method requires a relative rect that is proportional to the
 *  rect of the thermal scene, the x, y, width, and height values must all be
 *  between 0 and 1.0. Supported only by Zenmuse XT containing Advanced Radiometry
 *  capabilities.
 *  
 *  @param area The desired thermal metering area.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setThermalMeteringArea:(CGRect)area withCompletion:(DJICompletionBlock)completion;


/**
 *  Get the currently set flat-field correction (FFC) mode. Supported only by
 *  thermal imaging cameras with installed firmware version of 1.15.1.60 or higher.
 *  
 *  @param mode The value of the `DJICameraThermalFFCMode` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalFFCModeWithCompletion:(void (^_Nonnull)(DJICameraThermalFFCMode mode, NSError *_Nullable error))completion;


/**
 *  Set the flat-field correction (FFC) mode. Supported only by thermal imaging
 *  cameras.
 *  
 *  @param mode The desired FFC mode.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setThermalFFCMode:(DJICameraThermalFFCMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Trigger flat-field correction. Supported only by thermal imaging cameras.
 *  
 *  @param completion Completion block that receives the execution result of the trigger action.
 */
- (void)triggerThermalFFCWithCompletion:(DJICompletionBlock)completion;


/**
 *  Get the currently set custom user profile. This profile represents user-set
 *  external scene parameters for the thermal scene. Supported only by thermal
 *  imaging cameras.
 *  
 *  @param profile The value of the `DJICameraThermalCustomExternalSceneSettingsProfile` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalCustomExternalSceneSettingsProfileWithCompletion:(void (^_Nonnull)(DJICameraThermalCustomExternalSceneSettingsProfile profile, NSError *_Nullable error))completion;


/**
 *  Set the custom user profile. This profile represents user-set external scene
 *  parameters for the thermal scene. Supported only by thermal imaging cameras.
 *  
 *  @param profile The desired user profile setting.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setThermalCustomExternalSceneSettingsProfile:(DJICameraThermalCustomExternalSceneSettingsProfile)profile withCompletion:(DJICompletionBlock)completion;


/**
 *  Set the temperature of the atmosphere between the scene and the camera.
 *  Supported only by Zenmuse XT containing Advanced Radiometry capabilities.
 *  
 *  @param temperature The assumed temperature of the atmosphere between the camera and the scene, can be between -50 and 327.67 degrees Celsius.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setThermalAtmosphericTemperature:(float)temperature withCompletion:(DJICompletionBlock)completion;


/**
 *  Set the transmission coefficient of the atmosphere between the scene and the
 *  camera. Supported only by Zenmuse XT containing Advanced Radiometry
 *  capabilities.
 *  
 *  @param coefficient The desired atmospheric temperature, can be between 50 and 100.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setThermalAtmosphericTransmissionCoefficient:(float)coefficient withCompletion:(DJICompletionBlock)completion;


/**
 *  Set the assumed temperature reflected by the background of the scene, can be
 *  between -50 and 327.67 degrees Celsius. Supported only by Zenmuse XT containing
 *  Advanced Radiometry capabilities.
 *  
 *  @param temperature The desired background reflected temperature.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setThermalBackgroundTemperature:(float)temperature withCompletion:(DJICompletionBlock)completion;


/**
 *  Set the emissivity of the thermal scene, can be between 50 and 100. Supported
 *  only by Zenmuse XT containing Advanced Radiometry capabilities.
 *  
 *  @param emissivity The desired scene emissivity.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setThermalSceneEmissivity:(float)emissivity withCompletion:(DJICompletionBlock)completion;


/**
 *  Set assumed window reflection coefficient, can be between 0 and X where X is the
 *  window transmission coefficient parameter. Supported only by Zenmuse XT
 *  containing Advanced Radiometry capabilities.
 *  
 *  @param reflection The desired window reflection coefficient.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setThermalWindowReflection:(float)reflection withCompletion:(DJICompletionBlock)completion;


/**
 *  Set the temperature reflected in the window, can be between -50 and 327.67
 *  degrees Celsius. Supported only by Zenmuse XT containing Advanced Radiometry
 *  capabilities.
 *  
 *  @param temperature The desired window reflected temperature.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setThermalWindowReflectedTemperature:(float)temperature withCompletion:(DJICompletionBlock)completion;


/**
 *  Set the window temperature, can be between -50 and 327.67 degrees Celsius.
 *  Supported only by Zenmuse XT containing Advanced Radiometry capabilities.
 *  
 *  @param temperature The desired window temperature.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setThermalWindowTemperature:(float)temperature withCompletion:(DJICompletionBlock)completion;


/**
 *  Set the window transmission coefficient, can be between 50 and 100-X where X is
 *  the window reflection. Supported only by Zenmuse XT containing Advanced
 *  Radiometry capabilities.
 *  
 *  @param coefficient The desired window transmission coefficient.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setThermalWindowTransmissionCoefficient:(float)coefficient withCompletion:(DJICompletionBlock)completion;


/**
 *  Sets the temperature unit. Only supported by XT2.
 *  
 *  @param temperatureUnit Temperature unit to set.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setThermalTemperatureUnit:(DJICameraTemperatureUnit)temperatureUnit withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the temperature unit. Only supported by XT2.
 *  
 *  @param temperatureUnit The current temperature unit.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getThermalTemperatureUnitWithCompletion:(void (^_Nonnull)(DJICameraTemperatureUnit temperatureUnit, NSError *_Nullable error))completion;


/**
 *  Sets the display mode to coordinate the video feeds from both the  visual camera
 *  and the thermal camera. Only supported by XT2 camera.
 *  
 *  @param mode The display mode to set.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setDisplayMode:(DJICameraDisplayMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the display mode. The display mode determine the way to coordinate  the
 *  video feeds from both the visual camera and the thermal camera. Only  supported
 *  by XT2 camera.
 *  
 *  @param mode The current display mode.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getDisplayModeWithCompletion:(void (^_Nonnull)(DJICameraDisplayMode mode, NSError *_Nullable error))completion;


/**
 *  Sets the thermal window's position relative to the visual window. The setting is
 *  valid when  the display mode is `DJICameraDisplayModePIP`. Refer to
 *  `setDisplayMode:withCompletion`  and `getDisplayModeWithCompletion`. Only
 *  supported by XT2 camera.
 *  
 *  @param position The position to set.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setPIPPosition:(DJICameraPIPPosition)position withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the PIP position which determines the thermal window's position relative to
 *  the visual window. The setting  is valid when the display mode is
 *  `DJICameraDisplayModePIP`. Refer to `setDisplayMode:withCompletion`  and
 *  `getDisplayModeWithCompletion`. Only supported by XT2 camera.
 *  
 *  @param position The current position.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getPIPPositionWithCompletion:(void (^_Nonnull)(DJICameraPIPPosition position, NSError *_Nullable error))completion;


/**
 *  Sets the level for MSX display mode. The range for level is [0, 100]. When it is
 *  0, the visible spectrum definition is invisible.  When it is 100, the visual
 *  spectrum definition is the most obvious. Only supported by XT2 camera.
 *  
 *  @param level The MSX level to set with range [0, 100].
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setMSXLevel:(uint8_t)level withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the level for MSX display mode. The range for level is [0, 100]. When it is
 *  0, the visible spectrum definition is invisible. When  it is 100, the visual
 *  spectrum definition is the most obvious. Only supported by XT2 camera.
 *  
 *  @param level The current MSX level.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getMSXLevelWithCompletion:(void (^_Nonnull)(uint8_t level, NSError *_Nullable error))completion;


/**
 *  Sets the vertical alignment offset between the video feeds from both the visual
 *  camera and the thermal camera. The alignment is applied to  the MSX display
 *  mode. The valid range is [-8, 8]. Positive value will move the thermal window
 *  up. Use this setting to fine-tune the performance  of MSX display mode and the
 *  align PIP mode. Only supported by XT2 camera.
 *  
 *  @param offset The vertical offset to set.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setDualFeedVerticalAlignmentOffset:(int8_t)offset withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the vertical alignment offset between the video feeds from both the visual
 *  camera and the thermal camera. The alignment is applied to the  MSX display
 *  mode. The valid range is [-8, 8]. Positive value will move the thermal window
 *  up. Only supported by XT2 camera.
 *  
 *  @param offset The current vertical offset.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getDualFeedVerticalAlignmentOffsetWithCompletion:(void (^_Nonnull)(int8_t offset, NSError *_Nullable error))completion;


/**
 *  Sets the horizontal alignment offset between the video feeds from both the
 *  visual camera and the thermal camera. The alignment is applied to the MSX
 *  display mode. The valid range is [-100, 100]. Positive value will move the
 *  thermal window to the right. Use this setting to fine-tune the performance  of
 *  MSX display mode and the align PIP mode. Only supported by XT2 camera.
 *  
 *  @param offset The horizontal offset to set.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setDualFeedHorizontalAlignmentOffset:(int8_t)offset withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the horizontal alignment offset between the video feeds from both the
 *  visual camera and the thermal camera. The alignment is applied to the MSX
 *  display mode. The valid range is [-100, 100]. Positive value will move the
 *  thermal window to the right. Only supported by XT2 camera.
 *  
 *  @param offset The current vertical offset.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getDualFeedHorizontalAlignmentOffsetWithCompletion:(void (^_Nonnull)(int8_t offset, NSError *_Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
