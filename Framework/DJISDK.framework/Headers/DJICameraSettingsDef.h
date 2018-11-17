//
//  DJICameraSettingsDef.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "DJISDKFoundation.h"

NS_ASSUME_NONNULL_BEGIN

/*********************************************************************************/
#pragma mark - Camera Modes
/*********************************************************************************/

/*********************************************************************************/
#pragma mark DJICameraMode
/*********************************************************************************/


/**
 *  Camera work modes.
 */
typedef NS_ENUM (NSUInteger, DJICameraMode){
 

    /**
     *  Capture mode. In this mode, the user can capture pictures.
     */
    DJICameraModeShootPhoto = 0x00,
    

    /**
     *  Record mode. In this mode, the user can record videos.
     */
    DJICameraModeRecordVideo = 0x01,


    /**
     *  Playback mode. In this mode, the user can preview photos and videos, and can
     *  delete files. It is supported by Phantom 3 Professional camera, X3, X5 and X5R
     *  cameras on aircraft and Phantom 4 camera. Playback mode is not supported by Z30,
     *  X5S, X4S, Phantom 4 Pro, Mavic Pro, Phantom 3 Standard, Phantom 3 Advanced,
     *  Phantom 3 4K and Osmo series.
     */
    DJICameraModePlayback = 0x02,
 

    /**
     *  In this mode, the user can download media to the Mobile Device. Not supported by
     *  X5 camera nor X5R camera while mounted on aircraft.
     */
    DJICameraModeMediaDownload = 0x03,
    

    /**
     *  In this mode, live stream resolution and frame rate will be 1080i50 (PAL) or
     *  720p60 (NTSC). In this mode videos can be recorded. Still photos can also be
     *  taken only when video is recording. The only way to exit broadcast mode is to
     *  change modes to `DJICameraModeRecordVideo`. Only supported by Inspire 2.
     */
    DJICameraModeBroadcast = 0x04,
 

    /**
     *  The camera work mode is unknown.
     */
    DJICameraModeUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraShootPhotoMode
/*********************************************************************************/


/**
 *  The ShootPhoto mode itself can have several modes. The default value is
 *  `DJICameraShootPhotoModeSingle`.
 */
typedef NS_ENUM (NSUInteger, DJICameraShootPhotoMode){
 

    /**
     *  Sets the camera to take a single photo.
     */
    DJICameraShootPhotoModeSingle,
 

    /**
     *  Sets the camera to take an HDR photo. X5 camera, X5R camera, XT camera, Z30
     *  camera, Phantom 4 Pro camera, X4S camera and X5S camera do not support HDR mode.
     */
    DJICameraShootPhotoModeHDR,
 

    /**
     *  Set the camera to take multiple photos at once. XT camera does not support Burst
     *  mode.
     */
    DJICameraShootPhotoModeBurst,
 

    /**
     *  Automatic Exposure Bracketing (AEB) capture. In this mode you can quickly take
     *  multiple shots (the default is 3) at different exposures without having to
     *  manually change any settings between frames. XT camera and Z30 camera does not
     *  support AEB mode.
     */
    DJICameraShootPhotoModeAEB,
 

    /**
     *  Sets the camera to take a picture (or multiple pictures) continuously at a set
     *  time interval. The minimum interval for JPEG format of any quality is 2s. For
     *  all cameras except X4S, X5S and Phantom 4 Pro camera: The minimum interval for
     *  RAW or RAW+JPEG format is 10s. For the X4S, X5S and Phantom 4 Pro cameras the
     *  minimum interval for RAW or RAW+JPEG dformat is 5s.
     */
    DJICameraShootPhotoModeInterval,
 

    /**
     *  Sets the camera to take a picture (or multiple pictures) continuously at a set
     *  time interval. The camera will merge the photo sequence and the output is a
     *  video. The minimum interval for Video only format is 1 s. The minimum interval
     *  for Video+Photo format is 2 s. For the new Osmo firmware version, no video feed
     *  will be received if the camera is shooting photos with Time-lapse mode. Instead,
     *  user can receive a sequence of preview images using the delegate method
     *  `camera:didGenerateTimeLapsePreview`. Supported only by Osmo camera (Z3 and X3).
     */
    DJICameraShootPhotoModeTimeLapse,


    /**
     *  Sets the camera to take a burst of RAW photos. Use `rawPhotoBurstCount` to check
     *  how many photos have been shot. Only supported by X5S.
     */
    DJICameraShootPhotoModeRAWBurst,
    

    /**
     *  Sets the camera to take a series of photos while the aircraft moves up and down
     *  automatically. The image's depth of field can be computed with a third-party
     *  library to produce a photo with the bokeh effect. Note:
     *   1. It is only suitable for shooting still scenes.
     *   2. The aircraft will ascend about 20cm before shooting. Ensure that there is no
     *  obstacle about the aircraft.
     *   3. The suitable range of shooting is within 30m.
     *   It is only supported by Spark.
     */
    DJICameraShootPhotoModeShallowFocus,
    

    /**
     *  In panorama mode, the aircraft takes a series of photos with different gimbal
     *  and aircraft heading positions. The photos can be stitched with a third-party
     *  library. It is supported by Spark and Mavic Air.
     */
    DJICameraShootPhotoModePanorama,
    

    /**
     *  Sets the camera to take an enhanced-HDR photo. It blends a sequence of photos
     *  for ghost-free high dynamic range photos. It is supported by Mavic 2 Zoom and
     *  Mavic 2 Pro.
     */
    DJICameraShootPhotoModeEHDR,
    

    /**
     *  Sets the camera to take photos in HyperLight mode. It is a setting for low-light
     *  environment to enhance the photo quality while reducing noise significantly.  It
     *  is supported by Mavic 2 Zoom and Mavic 2 Pro.
     */
    DJICameraShootPhotoModeHyperLight,
    

    /**
     *  The shoot photo mode is unknown.
     */
    DJICameraShootPhotoModeUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark DJICameraExposureMode
/*********************************************************************************/


/**
 *  Camera exposure modes. The default value is `DJICameraExposureModeProgram`. The
 *  different exposure modes define whether Aperture, Shutter Speed, ISO can be set
 *  automatically or manually. Exposure compensation can be changed in all modes
 *  except Manual mode where it is not settable.
 *  X5, X5R, Phantom 4 Pro camera, X4S and X5S:
 *   Program Mode:       Shutter: Auto     Aperture: Auto     ISO: Manual or Auto
 *   Shutter Priority: Shutter: Manual   Aperture: Auto     ISO: Manual or Auto
 *   Aperture Priority:  Shutter: Auto     Aperture: Manual ISO: Manual or Auto
 *   Manual Mode:        Shutter: Manual   Aperture: Manual   ISO: Manual
 *  All other cameras:</b>
 *   Program Mode:       Shutter: Auto     Aperture: Fixed    ISO: Auto
 *   Shutter Priority: Shutter: Manual   Aperture: Fixed    ISO: Auto
 *   Aperture Priority:  NA
 *   Manual Mode:        Shutter: Manual Aperture: Manual   ISO: Manual
 */
typedef NS_ENUM (NSUInteger, DJICameraExposureMode){
 

    /**
     *  Program mode.
     */
    DJICameraExposureModeProgram,
 

    /**
     *  Shutter priority mode.
     */
    DJICameraExposureModeShutterPriority,
 

    /**
     *  Aperture priority mode.
     */
    DJICameraExposureModeAperturePriority,
 

    /**
     *  Manual mode.
     */
    DJICameraExposureModeManual,
 

    /**
     *  The camera exposure mode is unknown.
     */
    DJICameraExposureModeUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark - Video Related
/*********************************************************************************/

/*********************************************************************************/
#pragma mark DJICameraVideoFileFormat
/*********************************************************************************/


/**
 *  Video storage formats.
 */
typedef NS_ENUM (NSUInteger, DJICameraVideoFileFormat){
 

    /**
     *  The video storage format is MOV.
     */
    DJICameraVideoFileFormatMOV,
 

    /**
     *  The video storage format is MP4.
     */
    DJICameraVideoFileFormatMP4,
	

	/**
	 *  The video storage format is TIFF Sequence.
	 */
	DJICameraVideoFileFormatTIFFSequence,
	

	/**
	 *  The video storage format is SEQ. The raw data from the infrared camera is
	 *  stored.
	 */
	DJICameraVideoFileFormatSEQ,
	

    /**
     *  The video storage format is unknown.
     */
    DJICameraVideoFileFormatUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraVideoResolution
/*********************************************************************************/


/**
 *  Camera video resolution values. The resolutions available for a product are in
 *  `videoResolutionAndFrameRateRange`.
 */
typedef NS_ENUM (NSUInteger, DJICameraVideoResolution){

    /**
     *  The camera's video resolution is 336x256.
     */
    DJICameraVideoResolution336x256,


    /**
     *  The camera's video resolution is 640x480.
     */
    DJICameraVideoResolution640x480,
 

    /**
     *  The camera's video resolution is 640x512.
     */
    DJICameraVideoResolution640x512,
 

    /**
     *  The camera's video resolution is 1280x720.
     */
    DJICameraVideoResolution1280x720,
 

    /**
     *  The camera's video resolution is 1920x1080.
     */
    DJICameraVideoResolution1920x1080,
    

    /**
     *  The camera's video resolution is 2048x1080.
     */
    DJICameraVideoResolution2048x1080,
    

    /**
     *  The camera's video resolution is 2688x1512.
     */
    DJICameraVideoResolution2688x1512,
    

    /**
     *  The camera's video resolution is 2704x1520.
     */
    DJICameraVideoResolution2704x1520,
 

    /**
     *  The camera's video resolution is 2720x1530.
     */
    DJICameraVideoResolution2720x1530,
    

    /**
     *  The camera's video resolution is 3712x2088. It's only used by X7 camera.
     */
    DJICameraVideoResolution3712x2088,
 

    /**
     *  The camera's video resolution is 3840x1572.
     */
    DJICameraVideoResolution3840x1572,
 

    /**
     *  The camera's video resolution is 3840x2160.
     */
    DJICameraVideoResolution3840x2160,
    

    /**
     *  The camera's video resolution is 3944x2088. It's only used by X7 camera.
     */
    DJICameraVideoResolution3944x2088,
 

    /**
     *  The camera's video resolution is 4096x2160.
     */
    DJICameraVideoResolution4096x2160,
 

    /**
     *  The camera's video resolution is 4608x2160.
     */
    DJICameraVideoResolution4608x2160,
    

    /**
     *  The camera's video resolution is 4608x2592.
     */
    DJICameraVideoResolution4608x2592,
    

    /**
     *  The camera's video resolution is 5280x2160.
     */
    DJICameraVideoResolution5280x2160,
    

    /**
     *  The camera's video resolution is 5280x2972.
     */
    DJICameraVideoResolution5280x2972,
	

	/**
	 *  The camera's video resolution is 5760x3240.
	 */
	DJICameraVideoResolution5760x3240,
	

	/**
	 *  The camera's video resolution is 6016x3200.
	 */
	DJICameraVideoResolution6016x3200,


    /**
     *  The camera's video resolution will be maximum resolution supported by the camera
     *  sensor. For X5S and X4S, the maximum resolution is 5280x2972.
     */
    DJICameraVideoResolutionMax,


    /**
     *  The camera's SSD video resolution is unset. When the SSD resolution is unset,
     *  camera will not store video to SSD. SSD's resolution is determined by both
     *  license key and SD card's video frame rate. If there is no supported resolution
     *  with the current configuration, <code>DJICameraVideoResolutionUnset</code> will
     *  be selected and user should adjust either the license or the frame rate.
     */
    DJICameraVideoResolutionNoSSDVideo,
	

    /**
     *  The camera's video resolution is unknown.
     */
    DJICameraVideoResolutionUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark DJICameraVideoFrameRate
/*********************************************************************************/


/**
 *  Camera video frame rate values. The frame rates available for a product are in
 *  `videoResolutionAndFrameRateRange`.
 */
typedef NS_ENUM (NSUInteger, DJICameraVideoFrameRate){
 

    /**
     *  The camera's video frame rate is 23.976fps (frames per second).
     */
    DJICameraVideoFrameRate23dot976FPS,
 

    /**
     *  The camera's video frame rate is 24fps (frames per second).
     */
    DJICameraVideoFrameRate24FPS,
 

    /**
     *  The camera's video frame rate is 25fps (frames per second).
     */
    DJICameraVideoFrameRate25FPS,
 

    /**
     *  The camera's video frame rate is 29.97fps (frames per second).
     */
    DJICameraVideoFrameRate29dot970FPS,
 

    /**
     *  The camera's video frame rate is 30fps (frames per second).
     */
    DJICameraVideoFrameRate30FPS,


    /**
     *  The camera's video frame rate is 47.95fps (frames per second).
     */
    DJICameraVideoFrameRate47dot950FPS,
 

    /**
     *  The camera's video frame rate is 48fps (frames per second).
     */
    DJICameraVideoFrameRate48FPS,
    

    /**
     *  The camera's video frame rate is 50fps (frames per second).
     */
    DJICameraVideoFrameRate50FPS,
 

    /**
     *  The camera's video frame rate is 59.94fps (frames per second).
     */
    DJICameraVideoFrameRate59dot940FPS,
 

    /**
     *  The camera's video frame rate is 60fps (frames per second).
     */
    DJICameraVideoFrameRate60FPS,


    /**
     *  The camera's video frame rate is 90fps (frames per second).
     */
    DJICameraVideoFrameRate90FPS,


    /**
     *  The camera's video frame rate is 96fps (frames per second).
     */
    DJICameraVideoFrameRate96FPS,
    

    /**
     *  The camera's video frame rate is 100fps (frames per second). This frame rate can
     *  only be used when `isSlowMotionSupported` returns `YES`.
     */
    DJICameraVideoFrameRate100FPS,
    

    /**
     *  The camera's video frame rate is 120fps (frames per second). This frame rate can
     *  only be used when `isSlowMotionSupported` returns `YES`.
     */
    DJICameraVideoFrameRate120FPS,
    

    /**
     *  The camera's video frame rate is unknown.
     */
    DJICameraVideoFrameRateUnknown = 0xFF
};


/*********************************************************************************/
#pragma mark DJICameraVideoFOV
/*********************************************************************************/


/**
 *  FOV (field-of-view) to use for recording a video.
 */
typedef NS_ENUM (NSUInteger, DJICameraVideoFOV){
    

    /**
     *  The default FOV. Use this value if the FOV is not configurable for the camera.
     */
    DJICameraVideoFOVDefault,
    

    /**
     *  Use a narrow FOV to record videos.
     */
    DJICameraVideoFOVNarrow,
    

    /**
     *  Use a wide FOV to record videos.
     */
    DJICameraVideoFOVWide,


    /**
     *  UNKNOWN
     */
    DJICameraVideoFOVUnknown = 0xFF, 
};

/*********************************************************************************/
#pragma mark DJICameraVideoResolutionAndFrameRate
/*********************************************************************************/

/**
 *  This class contains current values for camera parameters related to video
 *  resolution and video frame rate.
 */
@interface DJICameraVideoResolutionAndFrameRate : NSObject


/**
 *  Creates a `DJICameraVideoResolutionAndFrameRate` instance  with a preset camera
 *  video resolution and frame rate. The value  of `fov` is
 *  `DJICameraVideoFOVDefault`.
 *  
 *  @param resolution The specific resolution.
 *  @param frameRate The specific frame rate.
 */
-(instancetype)initWithResolution:(DJICameraVideoResolution)resolution
                        frameRate:(DJICameraVideoFrameRate)frameRate;


/**
 *  Creates a `DJICameraVideoResolutionAndFrameRate` instance with a preset camera
 *  video  resolution, frame rate and FOV. FOV is only configurable for Mavic 2 Pro
 *  and it is only  configurable when the resolution is
 *  `DJICameraVideoResolution3840x2160` (4K).  Use `DJICameraVideoFOVDefault` when
 *  FOV is not configurable.
 *  
 *  @param resolution The specific resolution.
 *  @param frameRate The specific frame rate.
 *  @param fov The specific FOV.
 */
-(instancetype)initWithResolution:(DJICameraVideoResolution)resolution
                        frameRate:(DJICameraVideoFrameRate)frameRate
                              fov:(DJICameraVideoFOV)fov;


/**
 *  Returns the camera's current video resolution.
 */
@property (nonatomic, readonly) DJICameraVideoResolution resolution;


/**
 *  Returns the camera's current video frame rate.
 */
@property (nonatomic, readonly) DJICameraVideoFrameRate frameRate;


/**
 *  The FOV for recording videos.
 */
@property (nonatomic, readonly) DJICameraVideoFOV fov;


@end

/*********************************************************************************/
#pragma mark DJICameraVideoStandard
/*********************************************************************************/


/**
 *  Video standard values. The default value is NTSC.
 */
typedef NS_ENUM (NSUInteger, DJICameraVideoStandard){
 

    /**
     *  The camera video standard value is set to PAL.
     */
    DJICameraVideoStandardPAL,
 

    /**
     *  The camera video standard value is set to NTSC.
     */
    DJICameraVideoStandardNTSC,
 

    /**
     *  The camera video standard value is unknown.
     */
    DJICameraVideoStandardUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark - Photo related
/*********************************************************************************/

/*********************************************************************************/
#pragma mark DJICameraPhotoFileFormat
/*********************************************************************************/


/**
 *  Camera photo file formats. The default value is `DJICameraPhotoFileFormatJPEG`.
 */
typedef NS_ENUM (NSUInteger, DJICameraPhotoFileFormat){
 

    /**
     *  The camera's photo storage format is RAW.
     */
    DJICameraPhotoFileFormatRAW,
 

    /**
     *  The camera's photo storage format is JPEG.
     */
    DJICameraPhotoFileFormatJPEG,
 

    /**
     *  The camera stores both the RAW and JPEG formats of the photo.
     */
    DJICameraPhotoFileFormatRAWAndJPEG,
 

    /**
     *  The camera's photo storage format is TIFF (14bit).
     */
    DJICameraPhotoFileFormatTIFF14Bit,
 

    /**
     *  The camera's photo storage format is Radiometric JPEG (a special JPEG format
     *  with temperature information). A radiometric JPEG has the .jpg suffix and can be
     *  viewed as a normal JPEG file would. At the same time, the temperature data is
     *  also stored in the file as meta data. PC software is required to analyze the
     *  file and it is accessible at FLIR's website
     *  http://www.flir.com/instruments/display/?id=54865. Only supported by XT camera
     *  with firmware version 1.16.1.70 or above.
     */
    DJICameraPhotoFileFormatRadiometricJPEG,
 

    /**
     *  The camera's photo storage format is TIFF Linear Low. In this mode each pixel is
     *  14 bits and linearly proportional with temperature, covering a high dynamic
     *  range of temperature which results in a lower temperature resolution. Supported
     *  only by Zenmuse XT containing Advanced Radiometry capabilities with firmware
     *  version 1.17.1.80 or lower. For newer firmwares, the temperature resolution
     *  preference is coupled with the thermal gain mode.
     */
    DJICameraPhotoFileFormatTIFF14BitLinearLowTempResolution,
 

    /**
     *  The camera's photo storage format is TIFF Linear High. In this mode each pixel
     *  is 14 bits and linearly proportional with temperature, covering a low dynamic
     *  range of temperature which results in a higher temperature resolution. Supported
     *  only by Zenmuse XT containing Advanced Radiometry capabilities with firmware
     *  version 1.17.1.80 or lower. For newer firmwares, the temperature resolution
     *  preference is coupled with the thermal gain mode.
     */
    DJICameraPhotoFileFormatTIFF14BitLinearHighTempResolution,
 

    /**
     *  The camera's photo storage format is unknown.
     */
    DJICameraPhotoFileFormatUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraPhotoTimeLapseFileFormat
/*********************************************************************************/


/**
 *  File format for camera when it is in time-lapse mode. The default file format is
 *  video. If video+JPEG is selected the minimum interval will be 2 seconds.
 */
typedef NS_ENUM (NSUInteger, DJICameraPhotoTimeLapseFileFormat) {
 

    /**
     *  The camera in time-lapse mode will generate video.
     */
    DJICameraPhotoTimeLapseFileFormatVideo = 0x00,
 

    /**
     *  The camera in time-lapse mode will generate video and JPEG.
     */
    DJICameraPhotoTimeLapseFileFormatJPEGAndVideo,
 

    /**
     *  The file format is unknown.
     */
    DJICameraPhotoTimeLapseFileFormatUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraPhotoAspectRatio
/*********************************************************************************/


/**
 *  Photo aspect ratio, where the first value is the width and the second value is
 *  the height. The default value is `DJICameraPhotoAspectRatio4_3`.
 */
typedef NS_ENUM (NSUInteger, DJICameraPhotoAspectRatio){
 

    /**
     *  The camera's photo ratio is 4 : 3.
     */
    DJICameraPhotoAspectRatio4_3 = 0x00,
 

    /**
     *  The camera's photo ratio is 16 : 9.
     */
    DJICameraPhotoAspectRatio16_9 = 0x01,
 

    /**
     *  The camera's photo ratio is 3:2. It is only supported by Phantom 4 Pro camera.
     */
    DJICameraPhotoAspectRatio3_2 = 0x02,
 

    /**
     *  The camera's photo ratio is unknown.
     */
    DJICameraPhotoAspectRatioUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraPhotoBurstCount
/*********************************************************************************/


/**
 *  The number of photos taken in one burst shot (shooting photo in burst mode).
 */
typedef NS_ENUM (NSUInteger, DJICameraPhotoBurstCount){
 

    /**
     *  The camera burst shoot count is set to capture 3 pictures at once when the
     *  camera shoots a photo.
     */
    DJICameraPhotoBurstCount3 = 3,


    /**
     *  The camera burst shoot count is set to capture 5 pictures at once when the
     *  camera takes a photo.
     */
    DJICameraPhotoBurstCount5 = 5,


    /**
     *  The camera burst shoot count is set to capture 7 pictures at once when the
     *  camera takes a photo. It is not supported by Z30 camera.
     */
    DJICameraPhotoBurstCount7 = 7,


    /**
     *  The camera burst shoot count is set to capture 10 pictures at once when the
     *  camera takes a photo. Only supported by X4S camera, X5S camera and Phantom 4 Pro
     *  camera.
     */
    DJICameraPhotoBurstCount10 = 10,


    /**
     *  The camera burst shoot count is set to capture 14 pictures at once when the
     *  camera takes a photo. Only supported by X4S camera, X5S camera and Phantom 4 Pro
     *  camera.
     */
    DJICameraPhotoBurstCount14 = 14,
    

    /**
     *  The camera burst shoot count is set to capture RAW pictures continuously until
     *  `stopShootPhotoWithCompletion` command is sent. It is only supported by Inspire
     *  2 when the photo shoot mode is RAW burst.
     */
    DJICameraPhotoBurstCountContinuous = 0xFF,


    /**
     *  The camera burst shoot count value is unknown.
     */
    DJICameraPhotoBurstCountUnknown = 0xFFFF,
};

/*********************************************************************************/
#pragma mark DJICameraPhotoAEBCount
/*********************************************************************************/


/**
 *  The number of pictures to continuously take at one time in AEB mode. Use with
 *  `DJICameraPhotoAEBParam`.
 */
typedef NS_ENUM (NSUInteger, DJICameraPhotoAEBCount){
    

    /**
     *  The number of pictures to continuously take at one time in AEB mode is 3.
     */
    DJICameraPhotoAEBCount3 = 0x03,
    

    /**
     *  The number of pictures to continuously take at one time in AEB mode is 5.
     */
    DJICameraPhotoAEBCount5 = 0x05,


    /**
     *  The number of pictures to continuously take at one time in AEB mode is 7.
     */
    DJICameraPhotoAEBCount7 = 0x07,
    

    /**
     *  The number of pictures to continuously take at one time in AEB mode is unknown.
     */
    DJICameraPhotoAEBCountUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraPhotoTimeIntervalSettings
/*********************************************************************************/


/**
 *  Sets the number of pictures, and sets the time interval between pictures for the
 *  Interval shoot photo mode.
 */
typedef struct
{
 

    /**
     *  The number of photos to capture. The value range is [2, 255]. If 255 is
     *  selected, then the camera will continue to take pictures until
     *  stopShootPhotoWithCompletion is called. For thermal imaging camera and Z30
     *  camera, it can only be set to 255.
     */
    uint8_t captureCount;
    

    /**
     *  The time interval between when two photos are taken. The range for this
     *  parameter depends the photo file format(DJICameraPhotoFileFormat). For XT
     *  camera, the range is [1, 60] seconds. For all other products, when the file
     *  format is JPEG, the range is [2, 2^16 - 1] seconds; when the file format is RAW
     *  or RAW+JPEG, the range is [10, 2^16 - 1] seconds.
     */
    uint16_t timeIntervalInSeconds;
} DJICameraPhotoTimeIntervalSettings;

/*********************************************************************************/
#pragma mark DJICameraPhotoTimeLapseSettings
/*********************************************************************************/


/**
 *  Stores the time lapse settings.
 */
typedef struct {

    /**
     *  The time interval between when two photos are taken.
     */
    NSUInteger interval;


    /**
     *  The total duration for which the camera will take pictures.
     */
    NSUInteger duration;


    /**
     *  The file format for captured photos during time lapse.
     */
    DJICameraPhotoTimeLapseFileFormat fileFormat;

} DJICameraPhotoTimeLapseSettings;

/*********************************************************************************/
#pragma mark DJICameraPhotoPanoramaMode
/*********************************************************************************/

/**
 *  Panorama photo modes.
 */
typedef NS_ENUM(NSUInteger, DJICameraPhotoPanoramaMode) {

    /**
     *  Camera will shoot 3 rows of 3 photos. Each photo in a row will be taken with a
     *  different aircraft heading. Each row of photos is taken with a different gimbal
     *  pitch.
     */
    DJICameraPhotoPanoramaMode3x3,

    /**
     *  Camera will shoot 3 photos with the same aircraft heading and different gimbal
     *  pitch.
     */
    DJICameraPhotoPanoramaMode3x1,
    

    /**
     *  Camera will shoot 8 rows of 3 photos and 1 extra photo (facing downward). Each
     *  photo in a row will be taken with a different aircraft heading. Each row of
     *  photos is taken with a different gimbal pitch.
     */
    DJICameraPhotoPanoramaModeSphere,
    

    /**
     *  Camera will shoot 3 photos with the same gimbal pitch (facing forward) and
     *  different aircraft headings.
     */
    DJICameraPhotoPanoramaMode180,
    

    /**
     *  The camera will capture and patch nine photos resulting in a 48-megapixel super
     *  resolution photo. It is only supported by Mavic 2 Zoom.
     */
    DJICameraPhotoPanoramaModeSuperResolution,
    

    /**
     *  Unknown.
     */
    DJICameraPhotoPanoramaModeUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark - Camera advanced settings
/*********************************************************************************/

/*********************************************************************************/
#pragma mark DJICameraShutterSpeed
/*********************************************************************************/


/**
 *  Camera's shutter speed options.
 */
typedef NS_ENUM (NSUInteger, DJICameraShutterSpeed) {
 

    /**
     *  Camera's shutter speed 1/8000 s.
     */
    DJICameraShutterSpeed1_8000,
 

    /**
     *  Camera's shutter speed 1/6400 s.
     */
    DJICameraShutterSpeed1_6400,
 

    /**
     *  Camera's shutter speed 1/6000 s.
     */
    DJICameraShutterSpeed1_6000,
 

    /**
     *  Camera's shutter speed 1/5000 s.
     */
    DJICameraShutterSpeed1_5000,
 

    /**
     *  Camera's shutter speed 1/4000 s.
     */
    DJICameraShutterSpeed1_4000,
 

    /**
     *  Camera's shutter speed 1/3200 s.
     */
    DJICameraShutterSpeed1_3200,
 

    /**
     *  Camera's shutter speed 1/3000 s.
     */
    DJICameraShutterSpeed1_3000,
 

    /**
     *  Camera's shutter speed 1/2500 s.
     */
    DJICameraShutterSpeed1_2500,
 

    /**
     *  Camera's shutter speed 1/2000 s.
     */
    DJICameraShutterSpeed1_2000,
 

    /**
     *  Camera's shutter speed 1/1500 s.
     */
    DJICameraShutterSpeed1_1500,
 

    /**
     *  Camera's shutter speed 1/1600 s.
     */
    DJICameraShutterSpeed1_1600,
 

    /**
     *  Camera's shutter speed 1/1250 s.
     */
    DJICameraShutterSpeed1_1250,
 

    /**
     *  Camera's shutter speed 1/1000 s.
     */
    DJICameraShutterSpeed1_1000,
 

    /**
     *  Camera's shutter speed 1/800 s.
     */
    DJICameraShutterSpeed1_800,
    

    /**
     *  Camera's shutter speed 1/750 s.
     */
    DJICameraShutterSpeed1_750,
 

    /**
     *  Camera's shutter speed 1/725 s.
     */
    DJICameraShutterSpeed1_725,
 

    /**
     *  Camera's shutter speed 1/640 s.
     */
    DJICameraShutterSpeed1_640,
 

    /**
     *  Camera's shutter speed 1/500 s.
     */
    DJICameraShutterSpeed1_500,
 

    /**
     *  Camera's shutter speed 1/400 s.
     */
    DJICameraShutterSpeed1_400,
 

    /**
     *  Camera's shutter speed 1/350 s.
     */
    DJICameraShutterSpeed1_350,
 

    /**
     *  Camera's shutter speed 1/320 s.
     */
    DJICameraShutterSpeed1_320,
 

    /**
     *  Camera's shutter speed 1/250 s.
     */
    DJICameraShutterSpeed1_250,
 

    /**
     *  Camera's shutter speed 1/240 s.
     */
    DJICameraShutterSpeed1_240,
 

    /**
     *  Camera's shutter speed 1/200 s.
     */
    DJICameraShutterSpeed1_200,
 

    /**
     *  Camera's shutter speed 1/180 s.
     */
    DJICameraShutterSpeed1_180,
 

    /**
     *  Camera's shutter speed 1/160 s.
     */
    DJICameraShutterSpeed1_160,
 

    /**
     *  Camera's shutter speed 1/125 s.
     */
    DJICameraShutterSpeed1_125,
 

    /**
     *  Camera's shutter speed 1/120 s.
     */
    DJICameraShutterSpeed1_120,
 

    /**
     *  Camera's shutter speed 1/100 s.
     */
    DJICameraShutterSpeed1_100,
 

    /**
     *  Camera's shutter speed 1/90 s.
     */
    DJICameraShutterSpeed1_90,
 

    /**
     *  Camera's shutter speed 1/80 s.
     */
    DJICameraShutterSpeed1_80,
 

    /**
     *  Camera's shutter speed 1/60 s.
     */
    DJICameraShutterSpeed1_60,
 

    /**
     *  Camera's shutter speed 1/50 s.
     */
    DJICameraShutterSpeed1_50,
    

    /**
     *  Camera's shutter speed 1/45 s.
     */
    DJICameraShutterSpeed1_45,
 

    /**
     *  Camera's shutter speed 1/40 s.
     */
    DJICameraShutterSpeed1_40,
 

    /**
     *  Camera's shutter speed 1/30 s.
     */
    DJICameraShutterSpeed1_30,
 

    /**
     *  Camera's shutter speed 1/25 s.
     */
    DJICameraShutterSpeed1_25,
 

    /**
     *  Camera's shutter speed 1/20 s.
     */
    DJICameraShutterSpeed1_20,
 

    /**
     *  Camera's shutter speed 1/15 s.
     */
    DJICameraShutterSpeed1_15,
 

    /**
     *  Camera's shutter speed 1/12.5 s.
     */
    DJICameraShutterSpeed1_12Dot5,
 

    /**
     *  Camera's shutter speed 1/10 s.
     */
    DJICameraShutterSpeed1_10,
 

    /**
     *  Camera's shutter speed 1/8 s.
     */
    DJICameraShutterSpeed1_8,
 

    /**
     *  Camera's shutter speed 1/6.25 s.
     */
    DJICameraShutterSpeed1_6Dot25,
    

    /**
     *  Camera's shutter speed 1/6 s.
     */
    DJICameraShutterSpeed1_6,
 

    /**
     *  Camera's shutter speed 1/5 s.
     */
    DJICameraShutterSpeed1_5,
 

    /**
     *  Camera's shutter speed 1/4 s.
     */
    DJICameraShutterSpeed1_4,
 

    /**
     *  Camera's shutter speed 1/3 s.
     */
    DJICameraShutterSpeed1_3,
 

    /**
     *  Camera's shutter speed 1/2.5 s.
     */
    DJICameraShutterSpeed1_2Dot5,
    

    /**
     *  Camera's shutter speed 0.3 s.
     */
    DJICameraShutterSpeed0Dot3,
 

    /**
     *  Camera's shutter speed 1/2 s.
     */
    DJICameraShutterSpeed1_2,
 

    /**
     *  Camera's shutter speed 1/1.67 s.
     */
    DJICameraShutterSpeed1_1Dot67,
 

    /**
     *  Camera's shutter speed 1/1.25 s.
     */
    DJICameraShutterSpeed1_1Dot25,
    

    /**
     *  Camera's shutter speed 0.7 s.
     */
    DJICameraShutterSpeed0Dot7,
 

    /**
     *  Camera's shutter speed 1.0 s.
     */
    DJICameraShutterSpeed1,
 

    /**
     *  Camera's shutter speed 1.3 s.
     */
    DJICameraShutterSpeed1Dot3,
    

    /**
     *  Camera's shutter speed 1.4 s.
     */
    DJICameraShutterSpeed1Dot4,
 

    /**
     *  Camera's shutter speed 1.6 s.
     */
    DJICameraShutterSpeed1Dot6,
 

    /**
     *  Camera's shutter speed 2.0 s.
     */
    DJICameraShutterSpeed2,
 

    /**
     *  Camera's shutter speed 2.5 s.
     */
    DJICameraShutterSpeed2Dot5,
 

    /**
     *  Camera's shutter speed 3.0 s.
     */
    DJICameraShutterSpeed3,
 

    /**
     *  Camera's shutter speed 3.2 s.
     */
    DJICameraShutterSpeed3Dot2,
 

    /**
     *  Camera's shutter speed 4.0 s.
     */
    DJICameraShutterSpeed4,
 

    /**
     *  Camera's shutter speed 5.0 s.
     */
    DJICameraShutterSpeed5,
 

    /**
     *  Camera's shutter speed 6.0 s.
     */
    DJICameraShutterSpeed6,
 

    /**
     *  Camera's shutter speed 7.0 s.
     */
    DJICameraShutterSpeed7,
 

    /**
     *  Camera's shutter speed 8.0 s.
     */
    DJICameraShutterSpeed8,
 

    /**
     *  Camera's shutter speed 9.0 s.
     */
    DJICameraShutterSpeed9,
 

    /**
     *  Camera's shutter speed 10.0 s.
     */
    DJICameraShutterSpeed10,
    

    /**
     *  Camera's shutter speed 11.0 s.
     */
    DJICameraShutterSpeed11,
 

    /**
     *  Camera's shutter speed 13.0 s.
     */
    DJICameraShutterSpeed13,
 

    /**
     *  Camera's shutter speed 15.0 s.
     */
    DJICameraShutterSpeed15,
    

	/**
	 *  Camera's shutter speed 16.0 s.
	 */
    DJICameraShutterSpeed16,
 

    /**
     *  Camera's shutter speed 20.0 s.
     */
    DJICameraShutterSpeed20,
    

    /**
     *  Camera's shutter speed 23.0 s.
     */
    DJICameraShutterSpeed23,
 

    /**
     *  Camera's shutter speed 25.0 s.
     */
    DJICameraShutterSpeed25,
 

    /**
     *  Camera's shutter speed 30.0 s.
     */
    DJICameraShutterSpeed30,
	

    /**
     *  Camera's shutter speed unknown.
     */
    DJICameraShutterSpeedUnknown = 0xFF
};


/*********************************************************************************/
#pragma mark DJICameraISO
/*********************************************************************************/


/**
 *  Camera ISO values.
 */
typedef NS_ENUM (NSUInteger, DJICameraISO){
 

    /**
     *  The ISO value is automatically set. This cannot be used for all cameras when in
     *  Manual mode.
     */
    DJICameraISOAuto = 0x00,
 

    /**
     *  The ISO value is set to 100.
     */
    DJICameraISO100 = 0x01,
 

    /**
     *  The ISO value is set to 200.
     */
    DJICameraISO200 = 0x02,
 

    /**
     *  The ISO value is set to 400.
     */
    DJICameraISO400 = 0x03,
 

    /**
     *  The ISO value is set to 800.
     */
    DJICameraISO800 = 0x04,
 

    /**
     *  The ISO value is set to 1600.
     */
    DJICameraISO1600 = 0x05,
 

    /**
     *  The ISO value is set to 3200.
     */
    DJICameraISO3200 = 0x06,
 

    /**
     *  The ISO value is set to 6400.
     */
    DJICameraISO6400 = 0x07,
 

    /**
     *  The ISO value is set to 12800.
     */
    DJICameraISO12800 = 0x08,
 

    /**
     *  The ISO value is set to 25600.
     */
    DJICameraISO25600 = 0x09,
    

    /**
     *  ISO value is fixed by the camera firmware. When the camera color is set to
     *  `DJICameraColorDLog`, camera will fix the ISO to a specific value in order to
     *  optimize the performance. The value set by camera can be accessed from `ISO`.
     */
    DJICameraISOFixed = 0xFF,
    

    /**
     *  The ISO value is set to Unknown value.
     */
    DJICameraISOUnknown = 0xFFFF,
};

/*********************************************************************************/
#pragma mark DJICameraAperture
/*********************************************************************************/


/**
 *  Camera aperture values. X5, X5R, Z30, Phantom 4 Pro camera, X4S and X5S support
 *  this setting.
 */
typedef NS_ENUM (NSUInteger, DJICameraAperture) {
 

    /**
     *  The Aperture value is f/1.6. It is only supported by Z30 camera.
     */
    DJICameraApertureF1Dot6,
 

    /**
     *  The Aperture value is f/1.7.
     */
    DJICameraApertureF1Dot7,
 

    /**
     *  The Aperture value is f/1.8.
     */
    DJICameraApertureF1Dot8,


    /**
     *  The Aperture value is f/2.
     */
    DJICameraApertureF2,
 

    /**
     *  The Aperture value is f/2.2.
     */
    DJICameraApertureF2Dot2,
 

    /**
     *  The Aperture value is f/2.4. It is only supported by Z30 camera.
     */
    DJICameraApertureF2Dot4,
 

    /**
     *  The Aperture value is f/2.5.
     */
    DJICameraApertureF2Dot5,
    

    /**
     *  The Aperture value is f/2.6.
     */
    DJICameraApertureF2Dot6,
 

    /**
     *  The Aperture value is f/2.8.
     */
    DJICameraApertureF2Dot8,
 

    /**
     *  The Aperture value is f/3.2.
     */
    DJICameraApertureF3Dot2,
 

    /**
     *  The Aperture value is f/3.4.
     */
    DJICameraApertureF3Dot4,
 

    /**
     *  The Aperture value is f/3.5.
     */
    DJICameraApertureF3Dot5,


    /**
     *  The Aperture value is f/4.
     */
    DJICameraApertureF4,
 

    /**
     *  The Aperture value is f/4.5.
     */
    DJICameraApertureF4Dot5,
 

    /**
     *  The Aperture value is f/4.8.
     */
    DJICameraApertureF4Dot8,


    /**
     *  The Aperture value is f/5.
     */
    DJICameraApertureF5,
 

    /**
     *  The Aperture value is f/5.6.
     */
    DJICameraApertureF5Dot6,
 

    /**
     *  The Aperture value is f/6.3.
     */
    DJICameraApertureF6Dot3,
 

    /**
     *  The Aperture value is f/6.8.
     */
    DJICameraApertureF6Dot8,
 

    /**
     *  The Aperture value is f/7.1.
     */
    DJICameraApertureF7Dot1,


    /**
     *  The Aperture value is f/8.
     */
    DJICameraApertureF8,


    /**
     *  The Aperture value is f/9.
     */
    DJICameraApertureF9,
    

    /**
     *  The Aperture value is f/9.
     */
    DJICameraApertureF9Dot5,
 

    /**
     *  The Aperture value is f/9.6.
     */
    DJICameraApertureF9Dot6,
 

    /**
     *  The Aperture value is f/10.
     */
    DJICameraApertureF10,
 

    /**
     *  The Aperture value is f/11.
     */
    DJICameraApertureF11,
 

    /**
     *  The Aperture value is f/13.
     */
    DJICameraApertureF13,
 

    /**
     *  The Aperture value is f/14.
     */
    DJICameraApertureF14,
 

    /**
     *  The Aperture value is f/16.
     */
    DJICameraApertureF16,
 

    /**
     *  The Aperture value is f/18.
     */
    DJICameraApertureF18,
 

    /**
     *  The Aperture value is f/19.
     */
    DJICameraApertureF19,
    

    /**
     *  The Aperture value is f/20.
     */
    DJICameraApertureF20,
 

    /**
     *  The Aperture value is f/22.
     */
    DJICameraApertureF22,
 

    /**
     *  The Aperture value is Unknown.
     */
    DJICameraApertureUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraWhiteBalancePreset
/*********************************************************************************/


/**
 *  Camera white balance. The default value is `DJICameraWhiteBalanceAuto`.
 */
typedef NS_ENUM (NSUInteger, DJICameraWhiteBalancePreset){
 

    /**
     *  The camera's white balance is automatically set.
     */
    DJICameraWhiteBalancePresetAuto = 0x00,
 

    /**
     *  The camera's white balance is set to sunny.
     */
    DJICameraWhiteBalancePresetSunny = 0x01,
 

    /**
     *  The camera's white balance is set to cloudy.
     */
    DJICameraWhiteBalancePresetCloudy = 0x02,
 

    /**
     *  The camera's white balance is set to water surface.
     */
    DJICameraWhiteBalancePresetWaterSurface = 0x03,
 

    /**
     *  The camera's white balance is set to indoors and incandescent light.
     */
    DJICameraWhiteBalancePresetIndoorIncandescent = 0x04,
 

    /**
     *  The camera's white balance is set to indoors and fluorescent light.
     */
    DJICameraWhiteBalancePresetIndoorFluorescent = 0x05,
 

    /**
     *  The camera's white balance is set to custom color temperature. By using this
     *  white balance value, user can set a specific value for the color temperature.
     */
    DJICameraWhiteBalancePresetCustom = 0x06,


	/**
	 *  The camera's white balance is set to neutral. It is only supported by the X7.
	 */
	DJICameraWhiteBalancePresetNeutral = 0x07,
	

    /**
     *  The camera's white balance is unknown.
     */
    DJICameraWhiteBalancePresetUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraWhiteBalance
/*********************************************************************************/


/**
 *  This class contains current values for some camera parameters related to white
 *  balance. Values for the camera's current white balance preset and color
 *  temperature can be obtained from this class.
 */
@interface DJICameraWhiteBalance : NSObject


/**
 *  The current preset for white balance.
 */
@property (nonatomic, readonly) DJICameraWhiteBalancePreset preset;


/**
 *  The current setting for color temperature. Real color temperature value (K) =
 *  value * 100. For example, 50 -> 5000K.
 */
@property (nonatomic, readonly) uint8_t colorTemperature;


/**
 *  Create a `DJICameraWhiteBalance` instance with a white balance preset.
 *  
 *  @param preset White balance preset that is not `DJICameraWhiteBalancePresetCustom`.
 *  
 *  @return A white balance instance. 'nil' if 'preset' is `DJICameraWhiteBalancePresetCustom`.
 */
-(nullable instancetype)initWithPreset:(DJICameraWhiteBalancePreset)preset;


/**
 *  Create a `DJICameraWhiteBalance` instance with a white balance preset.
 *  
 *  @param temperature Color temperature value to be set in the range of [20, 100]. Real color temperature value (K) = value * 100. For example, 50 -> 5000K.
 *  
 *  @return A white balance instance. 'nil' if 'temperature' is invalid.
 */
-(nullable instancetype)initWithCustomColorTemperature:(uint8_t)temperature;

@end

/*********************************************************************************/
#pragma mark DJICameraMeteringMode
/*********************************************************************************/


/**
 *  Camera exposure metering. The default value is `DJICameraMeteringModeCenter`.
 */
typedef NS_ENUM (NSUInteger, DJICameraMeteringMode){
 

    /**
     *  The camera's exposure metering is set to the center.
     */
    DJICameraMeteringModeCenter = 0x00,
 

    /**
     *  The camera's exposure metering is set to average.
     */
    DJICameraMeteringModeAverage = 0x01,
 

    /**
     *  The camera's exposure metering is set to a single spot.
     */
    DJICameraMeteringModeSpot = 0x02,
 

    /**
     *  The camera's exposure metering is unknown.
     */
    DJICameraMeteringModeUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraExposureCompensation
/*********************************************************************************/


/**
 *  Camera exposure compensation.
 */
typedef NS_ENUM (NSUInteger, DJICameraExposureCompensation){
 

    /**
     *  The camera's exposure compensation is -5.0ev.
     */
    DJICameraExposureCompensationN50 = 0x01,
 

    /**
     *  The camera's exposure compensation is -4.7ev.
     */
    DJICameraExposureCompensationN47,
 

    /**
     *  The camera's exposure compensation is -4.3ev.
     */
    DJICameraExposureCompensationN43,
 

    /**
     *  The camera's exposure compensation is -4.0ev.
     */
    DJICameraExposureCompensationN40,
 

    /**
     *  The camera's exposure compensation is -3.7ev.
     */
    DJICameraExposureCompensationN37,
 

    /**
     *  The camera's exposure compensation is -3.3ev.
     */
    DJICameraExposureCompensationN33,
 

    /**
     *  The camera's exposure compensation is -3.0ev.
     */
    DJICameraExposureCompensationN30,
 

    /**
     *  The camera's exposure compensation is -2.7ev.
     */
    DJICameraExposureCompensationN27,
 

    /**
     *  The camera's exposure compensation is -2.3ev.
     */
    DJICameraExposureCompensationN23,
 

    /**
     *  The camera's exposure compensation is -2.0ev.
     */
    DJICameraExposureCompensationN20,
 

    /**
     *  The camera's exposure compensation is -1.7ev.
     */
    DJICameraExposureCompensationN17,
 

    /**
     *  The camera's exposure compensation is -1.3ev.
     */
    DJICameraExposureCompensationN13,
 

    /**
     *  The camera's exposure compensation is -1.0ev.
     */
    DJICameraExposureCompensationN10,
 

    /**
     *  The camera's exposure compensation is -0.7ev.
     */
    DJICameraExposureCompensationN07,
 

    /**
     *  The camera's exposure compensation is -0.3ev.
     */
    DJICameraExposureCompensationN03,
 

    /**
     *  The camera's exposure compensation is 0.0ev.
     */
    DJICameraExposureCompensationN00,
 

    /**
     *  The camera's exposure compensation is +0.3ev.
     */
    DJICameraExposureCompensationP03,
 

    /**
     *  The camera's exposure compensation is +0.7ev.
     */
    DJICameraExposureCompensationP07,
 

    /**
     *  The camera's exposure compensation is +1.0ev.
     */
    DJICameraExposureCompensationP10,
 

    /**
     *  The camera's exposure compensation is +1.3ev.
     */
    DJICameraExposureCompensationP13,
 

    /**
     *  The camera's exposure compensation is +1.7ev.
     */
    DJICameraExposureCompensationP17,
 

    /**
     *  The camera's exposure compensation is +2.0ev.
     */
    DJICameraExposureCompensationP20,
 

    /**
     *  The camera's exposure compensation is +2.3ev.
     */
    DJICameraExposureCompensationP23,
 

    /**
     *  The camera's exposure compensation is +2.7ev.
     */
    DJICameraExposureCompensationP27,
 

    /**
     *  The camera's exposure compensation is +3.0ev.
     */
    DJICameraExposureCompensationP30,
 

    /**
     *  The camera's exposure compensation is +3.3ev.
     */
    DJICameraExposureCompensationP33,
 

    /**
     *  The camera's exposure compensation is +3.7ev.
     */
    DJICameraExposureCompensationP37,
 

    /**
     *  The camera's exposure compensation is +4.0ev.
     */
    DJICameraExposureCompensationP40,
 

    /**
     *  The camera's exposure compensation is +4.3ev.
     */
    DJICameraExposureCompensationP43,
 

    /**
     *  The camera's exposure compensation is +4.7ev.
     */
    DJICameraExposureCompensationP47,
 

    /**
     *  The camera's exposure compensation is +5.0ev.
     */
    DJICameraExposureCompensationP50,


    /**
     *  The camera's exposure compensation is fixed by the camera.
     */
    DJICameraExposureCompensationFixed = 0xFF,
    

    /**
     *  The camera's exposure compensation is unknown.
     */
    DJICameraExposureCompensationUnknown = 0xFFFF,
};

/*********************************************************************************/
#pragma mark DJICameraAntiFlicker
/*********************************************************************************/


/**
 *  Camera anti-flickers. The default value is `DJICameraAntiFlickerFrequency50Hz`.
 */
typedef NS_ENUM (NSUInteger, DJICameraAntiFlickerFrequency){
 

    /**
     *  The camera's anti-flicker is automatically set. It is not supported by Z30
     *  camera.
     */
    DJICameraAntiFlickerFrequencyAuto = 0x00,
 

    /**
     *  The camera's anti-flicker is 60 Hz.
     */
    DJICameraAntiFlickerFrequency60Hz = 0x01,
 

    /**
     *  The camera's anti-flicker is 50 Hz.
     */
    DJICameraAntiFlickerFrequency50Hz = 0x02,
 

    /**
     *  The anti-flicker is disabled. Only supported by Mavic Air.
     */
    DJICameraAntiFlickerFrequencyDisabled = 0x03,
    

    /**
     *  The camera's anti-flicker is unknown.
     */
    DJICameraAntiFlickerFrequencyUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark - Exposure Status
/*********************************************************************************/


/**
 *  Camera exposure state.
 */
typedef NS_ENUM(NSUInteger, DJICameraExposureState) {

    /**
     *  The camera exposure state is normal.
     */
    DJICameraExposureStateNormal,

    /**
     *  The camera exposure state is underexposed.
     */
    DJICameraExposureStateUnderexposed,

    /**
     *  The camera exposure state is overexposed.
     */
    DJICameraExposureStateOverexposed,

    /**
     *  The camera exposure state is unknown.
     */
    DJICameraExposureStateUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark - DJICameraExposureSettings
/*********************************************************************************/


/**
 *  This class contains current values for some camera parameters related to
 *  exposure, which determines how sensitive the picture is to light and depends on
 *  the balance of the ISO value, the shutter speed, and the aperture value. When
 *  the camera is in different exposure modes, different parameters are
 *  automatically changed by the camera to either get the correct exposure (in
 *  Program, Shutter Priority and Aperture Priority modes), or report back the
 *  current exposure (in Manual mode). The current values of these parameters used
 *  by the camera are contained in this class.
 */
typedef struct{
 

    /**
     *  The current aperture value being used by the camera. A larger aperture results
     *  in a higher exposure and shallower depth of field. For cameras that do not
     *  support adjustable aperture (e.g. Zenmuse X3), the real aperture value is fixed.
     */
    DJICameraAperture aperture;
    

    /**
     *  The current shutter speed being used by the camera. A slower shutter speed
     *  results in a higher exposure, but more blurring in areas of the scene that are
     *  moving.
     */
    DJICameraShutterSpeed shutterSpeed;
    

    /**
     *  The current ISO value being used by the camera. `DJICameraISO` defines the
     *  number of the ISO values separated by one exposure stop. However, when the ISO
     *  is in automatic mode, the camera can select ISO values less than one stop apart,
     *  and therefore this property is the actual ISO value being used by the camera. A
     *  higher ISO results in a higher exposure, and more noise in the resulting image.
     */
    NSUInteger ISO;


    /**
     *  Returns the camera's current exposure compensation. In Program, Aperture
     *  Priority and Shutter Priority modes, the exposure compensation value changes the
     *  exposure target the camera is using to calculate correct exposure and is set by
     *  the user. For example, Aperture Priority mode indicates that the priority is to
     *  maintain the aperture setting and adjusting the exposure by varying the ISO and
     *  shutter speed. In Manual mode, this value is reported from the camera and
     *  reports how much the  exposure needs to be compensated for to get to what the
     *  camera thinks is the correct exposure. In Manual mode, the range of exposure
     *  compensation reported by the camera is -2.0 EV to 2.0 EV. In Program, Aperture
     *  Priority and Shutter Priority modes, the range of exposure compensation is -3.0
     *  EV to + 3.0 EV. For the Z30 camera in manual mode, exposureCompensation is not
     *  used and the value is always 'DJICameraExposureCompensationN00'.
     */
    DJICameraExposureCompensation exposureCompensation;
	

	/**
	 *  The current EI (exposure index) value being used by the camera. The value is
	 *  only valid when the exposure sensitivity mode is
	 *  `DJICameraExposureSensitivityModeEI`.
	 */
	NSUInteger EI;
    

    /**
     *  The camera exposure state.
     */
    DJICameraExposureState exposureState;
}DJICameraExposureSettings;

/*********************************************************************************/
#pragma mark - Lens related
/*********************************************************************************/

/*********************************************************************************/
#pragma mark DJICameraFocusMode
/*********************************************************************************/


/**
 *  Camera focus mode. It is settable only when `isAdjustableFocalPointSupported`
 *  returns `YES` and the physical AF switch on the camera is set to auto.
 */
typedef NS_ENUM (NSUInteger, DJICameraFocusMode){
 

    /**
     *  The camera's focus mode is set to manual. In this mode, user sets the focus ring
     *  value to adjust the focal distance.
     */
    DJICameraFocusModeManual,
 

    /**
     *  The camera's focus mode is set to auto. For the Z30 camera, the focus is
     *  calculated completely automatically. For all other cameras, a focus target can
     *  be set by the user, which is used to calculate focus automatically.
     */
    DJICameraFocusModeAuto,
 

    /**
     *  The camera's focus mode is set to Continuous AF. It is only supported by Mavic
     *  Pro with firmware version V01.03.0000 or above, X4S camera, Mavic 2 Zoom camera
     *  and Mavic 2 Pro camera.
     */
    DJICameraFocusModeAFC,

    /**
     *  The camera's focus mode is unknown.
     */
    DJICameraFocusModeUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraFocusStatus
/*********************************************************************************/


/**
 *  The focusing status of the camera's lens.
 */
typedef NS_ENUM (NSUInteger, DJICameraFocusStatus) {
 

    /**
     *  The lens is idle. No focus target has been set.
     */
    DJICameraFocusStatusIdle = 0x00,
 

    /**
     *  The lens is focusing on the target.
     */
    DJICameraFocusStatusFocusing,
 

    /**
     *  The lens succeeded to focus on the target.
     */
    DJICameraFocusStatusSuccessful,
 

    /**
     *  The lens failed to focus on the target. This happens when the target is too
     *  close, or the camera cannot distinguish the object to focus (e.g. a white wall).
     */
    DJICameraFocusStatusFailed,
    

    /**
     *  The lens focus status is unknown.
     */
    DJICameraFocusStatusUnknown
};

/*********************************************************************************/
#pragma mark DJICameraSensorCleaningState
/*********************************************************************************/


/**
 *  The states of the sensor cleaning operation.
 */
typedef NS_ENUM (NSUInteger, DJICameraSensorCleaningState) {
	

	/**
	 *  Not in sensor cleaning mode.
	 */
	DJICameraSensorCleaningStateIdle,
	

	/**
	 *  The camera is initiating sensor cleaning mode.
	 */
	DJICameraSensorCleaningStateInitiating,
	

	/**
	 *  Remove the lens from the camera to continue cleaning operation.
	 */
	DJICameraSensorCleaningStateWaitingForLensRemoval,
	

	/**
	 *  The camera is ready to start the sensor cleaning. Call
	 *  `startSensorCleaningWithCompletion` to start the operation.
	 */
	DJICameraSensorCleaningStateReady,
	

	/**
	 *  The camera is executing sensor cleaning.
	 */
	DJICameraSensorCleaningStateCleaning,
	

	/**
	 *  The sensor cleaning process is finishing. No action is required in this state
	 *  and the state will change to `DJICameraSensorCleaningStateWaitingForLensRemount`
	 *  automatically.
	 */
	DJICameraSensorCleaningStateFinishing,
	

	/**
	 *  The sensor cleaning is finished and the camera is waiting for the lens to be
	 *  remounted. When the lens is mounted, the state will change to
	 *  `DJICameraSensorCleaningStateIdle`.
	 */
	DJICameraSensorCleaningStateWaitingForLensRemount,
	

	/**
	 *  Unknown.
	 */
	DJICameraSensorCleaningStateUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark DJICameraFocusAssistantSettings
/*********************************************************************************/


/**
 *  Stores the focus settings
 */
typedef struct {


    /**
     *  `YES` if the lens focus assistant is enabled for Manual Focusing.
     */
    BOOL isEnabledMF;
    

    /**
     *  `YES` if the lens focus assistant is enabled for Auto Focusing.
     */
    BOOL isEnabledAF;
    
} DJICameraFocusAssistantSettings;

/*********************************************************************************/
#pragma mark - SD card related
/*********************************************************************************/

/*********************************************************************************/
#pragma mark DJICameraSDCardOperationState
/*********************************************************************************/

/**
 *  Operation states of the camera's SD card.
 */
typedef NS_ENUM(NSUInteger, DJICameraSDCardOperationState) {


    /**
     *  The SD card is in the normal state.
     */
    DJICameraSDCardOperationStateNormal = 0,


    /**
     *  The SD card is not inserted.
     */
    DJICameraSDCardOperationStateNotInserted = 1,


    /**
     *  The SD card is in invalid state.
     */
    DJICameraSDCardOperationStateInvalid = 2,


    /**
     *  The SD card is in read-only state and write operation is not allowed.
     */
    DJICameraSDCardOperationStateReadOnly = 3,


    /**
     *  It is required to format the SD card before using it.
     */
    DJICameraSDCardOperationFormatNeeded = 4,


    /**
     *  The SD card is being formatted.
     */
    DJICameraSDCardOperationStateFormatting = 5,


    /**
     *  The SD card is using an invalid file system. Format the SD card before using it.
     */
    DJICameraSDCardOperationStateInvalidFileSystem = 6,


    /**
     *  The SD card is busy.
     */
    DJICameraSDCardOperationStateBusy = 7,


    /**
     *  The SD card is full.
     */
    DJICameraSDCardOperationStateFull = 8,


    /**
     *  The SD card is too slow.
     */
    DJICameraSDCardOperationStateSlow = 9,


    /**
     *  The SD card encounters an unknown error.
     */
    DJICameraSDCardOperationStateUnknownError = 10,


    /**
     *  No remaining file indices for any new photos or videos.
     */
    DJICameraSDCardOperationStateNoRemainFileIndices = 11,


    /**
     *  The SD card is in initializing state.
     */
    DJICameraSDCardOperationStateInitializing = 12,


    /**
     *  It is recommended to format the SD card before using it.
     */
    DJICameraSDCardOperationStateFormatRecommended = 13,


    /**
     *  The camera is recovering the damaged files on the SD card.
     */
    DJICameraSDCardOperationStateRecoveringFiles = 14,


    /**
     *  The SD card is being written in a slow speed.
     */
    DJICameraSDCardOperationStateWritingSlowly = 15,
};

/*********************************************************************************/
#pragma mark - SSD related
/*********************************************************************************/

/*********************************************************************************/
#pragma mark DJICameraSSDOperationState
/*********************************************************************************/


/**
 *  Solid State Drive (SSD) State.
 */
typedef NS_ENUM (NSUInteger, DJICameraSSDOperationState) {
    

    /**
     *  SSD is not found.
     */
    DJICameraSSDOperationStateNotFound,
 

    /**
     *  SSD is idle.
     */
    DJICameraSSDOperationStateIdle,
 

    /**
     *  SSD is Saving.
     */
    DJICameraSSDOperationStateSaving,
 

    /**
     *  SSD is formatting.
     */
    DJICameraSSDOperationStateFormatting,
 

    /**
     *  SSD is initializing.
     */
    DJICameraSSDOperationStateInitializing,
 

    /**
     *  SSD validation error.
     */
    DJICameraSSDOperationStateError,
 

    /**
     *  SSD is full.
     */
    DJICameraSSDOperationStateFull,


    /**
     *  Communication to SSD is not stable. User can re-plugin SSD. It is supported by
     *  X5S.
     */
    DJICameraSSDOperationStatePoorConnection,
    

    /**
     *  SSD is switching the license key. It is supported by X5S.
     */
    DJICameraSSDOperationStateSwitchingLicense,
    

    /**
     *  Formatting is required. It is supported by X5S.
     */
    DJICameraSSDOperationStateFormattingRequired,


    /**
     *  Not initialized yet. It is supported by X7.
     */
    DJICameraSSDOperationStateNotInitialized,
    

    /**
     *  The file system is not supported. It is supported by X7.
     */
    DJICameraSSDOperationStateInvalidFileSystem,
    

    /**
     *  SSD state is unknown. This happens in the first 2 seconds after turning the
     *  camera power on as during this time the camera cannot check the state of the
     *  SSD.
     */
    DJICameraSSDOperationStateUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark DJICameraSSDCapacity
/*********************************************************************************/


/**
 *  Solid State Drive (SSD) Capacity.
 */
typedef NS_ENUM (NSUInteger, DJICameraSSDCapacity) {
 

    /**
     *  SSD capacity is 256G.
     */
    DJICameraSSDCapacity256GB,
 

    /**
     *  SSD capacity is 512G.
     */
    DJICameraSSDCapacity512GB,
 

    /**
     *  SSD capacity is 1T.
     */
    DJICameraSSDCapacity1TB,
 

    /**
     *  SSD capacity is unknown.
     */
    DJICameraSSDCapacityUnknown = 0xFF,
};


/**
 *  DJI camera's license keys. An Inspire 2 License Key activates the usage
 *  permission of CinemaDNG or Apple ProRes inside CineCore 2.0. License keys are
 *  obtained by by purchase from the DJI store website using the Inspire 2 serial
 *  number. The Inspire 2 is then connected to DJI Assistant 2, and the license keys
 *  downloaded to it. It is only supported X5S and X7 cameras.
 */
typedef NS_ENUM (NSUInteger, DJICameraSSDVideoLicense) {


    /**
     *  CinemaDNG.
     */
    DJICameraSSDVideoLicenseCinemaDNG,


    /**
     *  Apple ProRes 422 HQ.
     */
    DJICameraSSDVideoLicenseProRes422HQ,


    /**
     *  Apple ProRes 4444 XQ(no alpha).
     */
    DJICameraSSDVideoLicenseProRes4444XQ,


    /**
     *  Unknown.
     */
    DJICameraSSDVideoLicenseUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark - Thermal Imaging Camera Related
/*********************************************************************************/

/*********************************************************************************/
#pragma mark DJICameraThermalROI (Region Of Interest)
/*********************************************************************************/


/**
 *  Region of interest. Use this feature to manage color range distribution across
 *  the screen to maximize contrast for regions of highest interest.
 */
typedef NS_ENUM(NSUInteger, DJICameraThermalROI) {
 

    /**
     *  Causes the color spectrum to be evenly distributed across the entire image
     *  depending the default settings.
     */
    DJICameraThermalROIFull,
 

    /**
     *  Ignores areas of the sky 33% so that most of the spectrum can be allocated to
     *  remaining areas, providing higher contrast and utility for analysis.
     */
    DJICameraThermalROISkyExcluded33,
 

    /**
     *  Ignores areas of the sky 50% so that most of the spectrum can be allocated to
     *  remaining areas, providing higher contrast and utility for analysis.
     */
    DJICameraThermalROISkyExcluded50,
 

    /**
     *  The ROI type is unknown.
     */
    DJICameraThermalROIUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraThermalPalette
/*********************************************************************************/


/**
 *  The different colors are used to show various temperatures in the thermal
 *  imagery image. The colors are not actually related to wavelengths of light, but
 *  rather the grayscale intensity.
 */
typedef NS_ENUM(NSUInteger, DJICameraThermalPalette) {
 

    /**
     *  Without Isotherm enabled, the Palette type is WhiteHot. With Isotherm enabled,
     *  the Palette type is WhiteHotIso.
     */
    DJICameraThermalPaletteWhiteHot,
 

    /**
     *  Without Isotherm enabled, the Palette type is BlackHot. With Isotherm enabled,
     *  the Palette type is BlackHotIso.
     */
    DJICameraThermalPaletteBlackHot,
	

	/**
	 *  Without Isotherm enabled, the Palette type is RedHot. With Isotherm enabled, the
	 *  Palette type is RedHotIso.
	 */
	DJICameraThermalPaletteRedHot,
	

	/**
	 *  Without Isotherm enabled, the Palette type is GreenHot. With Isotherm enabled,
	 *  the Palette type is GreenHotIso.
	 */
	DJICameraThermalPaletteGreenHot,
	

    /**
     *  Without Isotherm enabled, the Palette type is Fusion. With Isotherm enabled, the
     *  Palette type is FusionIso.
     */
    DJICameraThermalPaletteFusion,
 

    /**
     *  Without Isotherm enabled, the Palette type is Rainbow. With Isotherm enabled,
     *  the Palette type is RainbowIso.
     */
    DJICameraThermalPaletteRainbow,
 

    /**
     *  Without Isotherm enabled, the Palette type is Ironbow1. With Isotherm enabled,
     *  the Palette type is IronbowWHIso.
     */
    DJICameraThermalPaletteIronbow1,
 

    /**
     *  Without Isotherm enabled, the Palette type is Ironbow2. With Isotherm enabled,
     *  the Palette type is IronbowBHIso.
     */
    DJICameraThermalPaletteIronbow2,
 

    /**
     *  Without Isotherm enabled, the Palette type is IceFire. With Isotherm enabled,
     *  the Palette type is IceFireIso.
     */
    DJICameraThermalPaletteIceFire,
 

    /**
     *  Without Isotherm enabled, the Palette type is Sepia. With Isotherm enabled, the
     *  Palette type is SepiaIso.
     */
    DJICameraThermalPaletteSepia,
 

    /**
     *  Without Isotherm enabled, the Palette type is Glowbow. With Isotherm enabled,
     *  the Palette type is GlowbowIso.
     */
    DJICameraThermalPaletteGlowbow,
 

    /**
     *  Without Isotherm enabled, the Palette type is Color1. With Isotherm enabled, the
     *  Palette type is MidRangeWHIso.
     */
    DJICameraThermalPaletteColor1,
 

    /**
     *  Without Isotherm enabled, the Palette type is Color2. With Isotherm enabled, the
     *  Palette type is MidRangeBHIso.
     */
    DJICameraThermalPaletteColor2,
 

    /**
     *  Without Isotherm enabled, the Palette type is Rain. With Isotherm enabled, the
     *  Palette type is RainbowHCIso.
     */
    DJICameraThermalPaletteRain,
	

    /**
     *  The palette type is unknown.
     */
    DJICameraThermalPaletteUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraThermalScene
/*********************************************************************************/


/**
 *  Uses the Scene option to instantly enhance your image.
 */
typedef NS_ENUM(NSUInteger, DJICameraThermalScene) {
 

    /**
     *  Linearly transforms the 14-bit sensor pixel data to 8-bit JPEG/MP4 pixel data.
     */
    DJICameraThermalSceneLinear,
 

    /**
     *  Automatically adjusts DDE, ACE, SSO, brightness and contrast.
     */
    DJICameraThermalSceneDefault,
 

    /**
     *  Automatically adjusts DDE, ACE, SSO, brightness and contrast with presets
     *  optimized for scenes composed of the sea and the sky scenes.
     */
    DJICameraThermalSceneSeaSky,
 

    /**
     *  Automatically adjusts DDE, ACE, SSO, brightness and contrast with presets
     *  optimized for outdoor scenes.
     */
    DJICameraThermalSceneOutdoor,
 

    /**
     *  Automatically adjusts DDE, ACE, SSO, brightness and contrast with presets
     *  optimized for indoor scenes.
     */
    DJICameraThermalSceneIndoor,
 

    /**
     *  Allows manual setting of DDE, ACE, SSO, brightness and contrast.
     */
    DJICameraThermalSceneManual,
 

    /**
     *  First saved settings of DDE, ACE, SSO, brightness and contrast.
     */
    DJICameraThermalSceneProfile1,
 

    /**
     *  Second saved settings of DDE, ACE, SSO, brightness and contrast.
     */
    DJICameraThermalSceneProfile2,
 

    /**
     *  Third saved settings of DDE, ACE, SSO, brightness and contrast.
     */
    DJICameraThermalSceneProfile3,
 

    /**
     *  The Scene type is unknown.
     */
    DJICameraThermalSceneUnknown = 0xFF
};


/*********************************************************************************/
#pragma mark DJICameraThermalIsothermUnit
/*********************************************************************************/


/**
 *  The unit for Isotherm.
 */
typedef NS_ENUM(NSUInteger, DJICameraThermalIsothermUnit) {
 

    /**
     *  The unit type is percentage. The allowed range is [0, 100].
     */
    DJICameraThermalIsothermUnitPercentage,
 

    /**
     *  The unit type is degrees Celsius. The allowed range is [-40, 1000].
     */
    DJICameraThermalIsothermUnitCelsius,
 

    /**
     *  The unit type is unknown.
     */
    DJICameraThermalIsothermUnitUnknown = 0xFF
};



/*********************************************************************************/
#pragma mark DJICameraThermalGainMode
/*********************************************************************************/


/**
 *  The gain mode.
 */
typedef NS_ENUM(NSUInteger, DJICameraThermalGainMode) {
 

    /**
     *  The camera will automatically select the optimal gain mode according to the
     *  temperature range of the image.
     */
    DJICameraThermalGainModeAuto,
 

    /**
     *  The camera covers a wider temperature range but is less sensitive to temperature
     *  differences.
     */
    DJICameraThermalGainModeLow,
 

    /**
     *  The camera covers a smaller temperature range but is more sensitive to
     *  temperature differences.
     */
    DJICameraThermalGainModeHigh,
 

    /**
     *  The gain mode is unknown.
     */
    DJICameraThermalGainModeUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraThermalResolution
/*********************************************************************************/


/**
 *  The resolution of thermal imaging camera.
 */
typedef NS_ENUM(NSUInteger, DJICameraThermalResolution) {
 

    /**
     *  The thermal imaging camera resolution is 336x256.
     */
    DJICameraThermalResolution336x256,
 

    /**
     *  The thermal imaging camera resolution is 640x512.
     */
    DJICameraThermalResolution640x512,
 

    /**
     *  The thermal imaging camera resolution is unknown.
     */
    DJICameraThermalResolutionUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraThermalFrameRateUpperBound
/*********************************************************************************/


/**
 *  The frame rate upper bound supported by the thermal camera.
 */
typedef NS_ENUM(NSUInteger, DJICameraThermalFrameRateUpperBound) {
 

    /**
     *  The thermal imaging camera frame rate upper bound is 8.3Hz.
     */
    DJICameraThermalFrameRateUpperBound8Dot3Hz,
 

    /**
     *  The thermal imaging camera frame rate upper bound is 30Hz.
     */
    DJICameraThermalFrameRateUpperBound30Hz,
 

    /**
     *  The thermal imaging camera frame rate upper bound is unknown.
     */
    DJICameraThermalFrameRateUpperBoundUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraThermalLens
/*********************************************************************************/


/**
 *  The focal length of the thermal imaging camera.
 */
typedef NS_ENUM(NSUInteger, DJICameraThermalLensFocalLength) {
 

    /**
     *  The thermal imaging camera's lens focal length is 6.8 mm.
     */
    DJICameraThermalLensFocalLength6Dot8mm,
 

    /**
     *  The thermal imaging camera lens focal length is 7.5mm.
     */
    DJICameraThermalLensFocalLength7Dot5mm,
 

    /**
     *  The thermal imaging camera's lens focal length is 9 mm.
     */
    DJICameraThermalLensFocalLength9mm,
 

    /**
     *  The thermal imaging camera's lens focal length is 13 mm.
     */
    DJICameraThermalLensFocalLength13mm,
 

    /**
     *  The thermal imaging camera's lens focal length is 19 mm.
     */
    DJICameraThermalLensFocalLength19mm,
 

    /**
     *  The thermal imaging camera's lens focal length is unknown.
     */
    DJICameraThermalLensFocalLengthUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraThermalVersion
/*********************************************************************************/


/**
 *  There is a standard version and version with Advanced Radiometry capabilities of
 *  the Zenmuse XT thermal camera. This enum defines the versions.
 */
typedef NS_ENUM(NSUInteger, DJICameraThermalVersion) {
 

    /**
     *  The thermal camera is Zenmuse XT Standard version.
     */
    DJICameraThermalVersionXTStandard,
 

    /**
     *  The thermal camera is Zenmuse XT Advanced Radiometry version.
     */
    DJICameraThermalVersionXTAdvancedRadiometryEnabled,
};

/*********************************************************************************/
#pragma mark DJICameraThermalCustomSettings
/*********************************************************************************/


/**
 *  User defined parameters.
 */
typedef NS_ENUM(NSUInteger, DJICameraThermalCustomExternalSceneSettingsProfile) {
 

    /**
     *  Custom thermal external scene settings for user 1.
     */
    DJICameraThermalCustomExternalSceneSettingsProfile1,
 

    /**
     *  Custom thermal external scene settings for user 2.
     */
    DJICameraThermalCustomExternalSceneSettingsProfile2,
 

    /**
     *  Custom thermal external scene settings for user 3.
     */
    DJICameraThermalCustomExternalSceneSettingsProfile3,
 

    /**
     *  The user is unknown.
     */
    DJICameraThermalCustomExternalSceneSettingsProfileUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraThermalFFCMode
/*********************************************************************************/


/**
 *  Flat-field correction mods.
 */
typedef NS_ENUM(NSUInteger, DJICameraThermalFFCMode) {
 

    /**
     *  Automatic flat-field correction mode.
     */
    DJICameraThermalFFCModeAuto,
 

    /**
     *  Manual flat-field correction mode.
     */
    DJICameraThermalFFCModeManual,
 

    /**
     *  Unknown flat-field correction mode.
     */
    DJICameraThermalFFCModeUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraThermalProfile
/*********************************************************************************/


/**
 *  The profile of the thermal imaging camera, which includes information about
 *  resolution, frame rate and focal length.
 */
typedef struct {
 

    /**
     *  The supported resolution of the thermal imaging camera.
     */
    DJICameraThermalResolution resolution;
 

    /**
     *  The supported frame rate upper bound of the thermal imaging camera.
     */
    DJICameraThermalFrameRateUpperBound frameRateUpperBound;
 

    /**
     *  The lens model of the thermal imaging camera.
     */
    DJICameraThermalLensFocalLength focalLength;
 

    /**
     *  The version of the thermal imaging camera.
     */
    DJICameraThermalVersion version;
} DJICameraThermalProfile;

/*********************************************************************************/
#pragma mark DJICameraThermalDigitalZoomFactor
/*********************************************************************************/


/**
 *  Thermal camera digital zoom scale. The default value is
 *  `DJICameraThermalDigitalZoomScalex1`.
 */
typedef NS_ENUM(NSUInteger, DJICameraThermalDigitalZoomFactor) {
 

    /**
     *  Digital zoom factor x1.
     */
    DJICameraThermalDigitalZoomFactorx1,
 

    /**
     *  Digital Zoom factor is x2.
     */
    DJICameraThermalDigitalZoomFactorx2,
 

    /**
     *  Digital Zoom factor is x4.
     */
    DJICameraThermalDigitalZoomFactorx4,
 

    /**
     *  Digital Zoom factor is x8.
     */
    DJICameraThermalDigitalZoomFactorx8,
 

    /**
     *  Digital Zoom factor is unknown.
     */
    DJICameraThermalDigitalZoomFactorUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraThermalMeasurementMode
/*********************************************************************************/


/**
 *  Thermal camera temperature measurement mode. The default value is
 *  `DJICameraThermalMeasurementModeDisabled` .
 */
typedef NS_ENUM(NSUInteger, DJICameraThermalMeasurementMode) {
 

    /**
     *  Disable temperature measuring.
     */
    DJICameraThermalMeasurementModeDisabled,
 

    /**
     *  Enable temperature measurement and set mode to spot metering. Use
     *  `camera:didUpdateTemperatureData` to receive the updated temperature data. In
     *  this mode, the advanced radiometry version XT camera can change the metering
     *  point using `setThermalSpotMeteringTargetPoint:withCompletion`.
     */
    DJICameraThermalMeasurementModeSpotMetering,
 

    /**
     *  Enable temperature measurement and set mode to area metering. Use
     *  `camera:didUpdateAreaTemperatureAggregations` to receive the updated temperature
     *  data. Only supported by the advanced radiometry version XT camera.
     */
    DJICameraThermalMeasurementModeAreaMetering,
 

    /**
     *  Thermal camera's temperature measurement mode is unknown.
     */
    DJICameraThermalMeasurementModeUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraThermalAreaTemperatureAggregations
/*********************************************************************************/


 /**
  *  The aggregate temperature measurements for a selected metering area.
  */
typedef struct {
 

    /**
     *  The average temperature of the selected metering area.
     */
    float averageAreaTemperature;
 

    /**
     *  The minimum temperature of the selected metering area.
     */
    float minAreaTemperature;
 

    /**
     *  The minimum temperature coordinate of the selected metering area.
     */
    CGPoint minTemperaturePoint;
 

    /**
     *  The maximum temperature of the selected metering area.
     */
    float maxAreaTemperature;
 

    /**
     *  The maximum temperature coordinate of the selected metering area.
     */
    CGPoint maxTemperaturePoint;
} DJICameraThermalAreaTemperatureAggregations;

/*********************************************************************************/
#pragma mark DJICameraThermalExternalSceneSettings
/*********************************************************************************/


 /**
  *  Thermal cameras measure the apparent surface temperature of a given object. This
  *  is done by taking the amount of infrared radiation an object emits and
  *  calculating the surface temperature by applying a formula that adjusts for
  *  external factors. This struct includes all of the external scene parameters that
  *  the thermal camera firmware allows  to be customized. There are two types of
  *  parameters, optical parameters which specify how much infrared  radiation is
  *  transmitted from the surface to the thermal sensor, as well as parameters that
  *  specify sources of thermal radiance other than the object. For a more in-depth
  *  overview of the physics behind thermal imaging, see
  *  https://en.wikipedia.org/wiki/Thermography.
  */
typedef struct {
 

    /**
     *  Atmospheric temperature, can be between -50 and 327.67 degrees Celsius.
     */
    float atmosphericTemperature;
 

    /**
     *  Transmission coefficient of the atmosphere between the scene and the camera, can
     *  be between 50 and 100.
     */
    float atmosphericTransmissionCoefficient;
 

    /**
     *  Background temperature (reflected by the scene), can be between -50 and 327.67
     *  degrees Celsius.
     */
    float backgroundTemperature;
 

    /**
     *  Emissivity of the scene, can be between 50 and 100.
     */
    float sceneEmissivity;
 

    /**
     *  Window reflection, can be between 50 and 100-X where X is the window
     *  transmission coefficient parameter.
     */
    float windowReflection;
 

    /**
     *  Temperature reflected in the window, can be between -50 and 327.67 degrees
     *  Celsius.
     */
    float windowReflectedTemperature;
 

    /**
     *  Window temperature, can be between -50 and 327.67 degrees Celsius.
     */
    float windowTemperature;
 

    /**
     *  Transmission coefficient of the window, can be between 50 and 100-X where X is
     *  the window reflection.
     */
    float windowTransmissionCoefficient;
} DJICameraThermalExternalSceneSettings;

/*********************************************************************************/
#pragma mark DJICameraDisplayMode
/*********************************************************************************/


/**
 *  Display modes to coordinate the video feeds from both the visual camera and the
 *  thermal camera. Only supported  by XT2 camera.
 */
typedef NS_ENUM(NSUInteger, DJICameraDisplayMode) {

    /**
     *  Displays only the video feed from the visual camera.
     */
    DJICameraDisplayModeVisualOnly,
    

    /**
     *  Displays only the video feed from the thermal camera.
     */
    DJICameraDisplayModeThermalOnly,
    

    /**
     *  Displays the video feed from the visual camera as the main subject, and the
     *  video  from the thermal camera in a window not bigger than the main subject. The
     *  position  of the thermal camera window can be adjusted with
     *  `DJICameraPIPPosition`.
     */
    DJICameraDisplayModePIP,
    

    /**
     *  Multi-Spectral Dynamic Imaging. Fuse the video feeds from both the visual camera
     *  and the  thermal camera as one. Adds visible spectrum definition to IR images by
     *  detecting the edges  of objects and including that detail in the thermal image.
     */
    DJICameraDisplayModeMSX,
    

    /**
     *  The thermal video feed display mode is unknown.
     */
    DJICameraDisplayModeUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraPIPPosition
/*********************************************************************************/


/**
 *  Possible positions to place the window of the thermal camera video feed when the
 *  display mode  is `DJICameraDisplayModePIP`. Only supported by XT2 camera.
 */
typedef NS_ENUM(NSUInteger, DJICameraPIPPosition) {

    /**
     *  Position the window to the vertical center and the horizontal center.
     */
    DJICameraPIPPositionCenter,
    

    /**
     *  Position the window to be bottom right.
     */
    DJICameraPIPPositionBottomRight,
    

    /**
     *  Position the window to be centered on the right.
     */
    DJICameraPIPPositionCenterRight,
    

    /**
     *  Position the window to be top right.
     */
    DJICameraPIPPositionTopRight,
    

    /**
     *  Position the window to be centered at bottom.
     */
    DJICameraPIPPositionBottomCenter,
    

    /**
     *  Position the window to be centered at top.
     */
    DJICameraPIPPositionTopCenter,
    

    /**
     *  Position the window to be bottom left.
     */
    DJICameraPIPPositionBottomLeft,
    

    /**
     *  Position the window to be centered on the left.
     */
    DJICameraPIPPositionCenterLeft,
    

    /**
     *  Position the window to be top left.
     */
    DJICameraPIPPositionTopLeft,
    

    /**
     *  Position the thermal window on the right side of the main  window (the visual
     *  camera video feed). Scale both windows  with the same height.
     */
    DJICameraPIPPositionSideBySide,
    

    /**
     *  Position the thermal window on top of the main window (the  visual camera video
     *  feed). Then align the object in the thermal  window with the same object in the
     *  main window. The alignment  offset can be adjusted by
     *  `setDualFeedHorizontalAlignmentOffset:withCompletion`  and
     *  `setDualFeedVerticalAlignmentOffset:withCompletion`.
     */
    DJICameraPIPPositionAlign,


    /**
     *  Unknown.
     */
    DJICameraPIPPositionUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark - Optical Zoom
/*********************************************************************************/

/*********************************************************************************/
#pragma mark DJICameraOpticalZoomSpec
/*********************************************************************************/



/**
 *  Zoom lens profile. Includes focal length range and minimum focal length step.
 *  Supported by X5, X5R and X5S with zoom lens, Z3 camera and Z30 camera.
 */
typedef struct {
 

    /**
     *  The maximum focal length of the lens in units of 0.1mm.
     */
    NSUInteger maxFocalLength;
 

    /**
     *  The minimum focal length of the lens in units of 0.1mm.
     */
    NSUInteger minFocalLength;
 

    /**
     *  The minimum interval of focal length change in units of 0.1mm.
     */
    NSUInteger focalLengthStep;
}DJICameraOpticalZoomSpec;

/*********************************************************************************/
#pragma mark DJICameraZoomDirection
/*********************************************************************************/



/**
 *  The direction to adjust the camera zoom (camera focal length). Supported by X5,
 *  X5R and X5S with zoom lens, Z3 camera and Z30 camera.
 */
typedef NS_ENUM(uint8_t, DJICameraZoomDirection) {
 

    /**
     *  Lens will zoom in. The focal length increases, field of view becomes narrower
     *  and magnification is higher.
     */
    DJICameraZoomDirectionZoomIn,
 

    /**
     *  Lens will zoom out. The focal length decreases, field of view becomes wider and
     *  magnification is lower.
     */
    DJICameraZoomDirectionZoomOut
};

/*********************************************************************************/
#pragma mark DJICameraZoomSpeed
/*********************************************************************************/


/**
 *  The speed of lens to zoom. The speed of lens to zoom. Supported by X5, X5R and
 *  X5S with zoom lens, Z3 camera and Z30 camera.
 */
typedef NS_ENUM(uint8_t, DJICameraZoomSpeed) {
 

    /**
     *  Lens zooms very in slowest speed.
     */
    DJICameraZoomSpeedSlowest,
 

    /**
     *  Lens zooms in slow speed.
     */
    DJICameraZoomSpeedSlow,
 

    /**
     *  Lens zooms in speed slightly slower than normal speed.
     */
    DJICameraZoomSpeedModeratelySlow,
 

    /**
     *  Lens zooms in normal speed.
     */
    DJICameraZoomSpeedNormal,
 

    /**
     *  Lens zooms very in speed slightly faster than normal speed.
     */
    DJICameraZoomSpeedModeratelyFast,
 

    /**
     *  Lens zooms very in fast speed.
     */
    DJICameraZoomSpeedFast,
 

    /**
     *  Lens zooms very in fastest speed.
     */
    DJICameraZoomSpeedFastest
};

/*********************************************************************************/
#pragma mark - Others
/*********************************************************************************/

/*********************************************************************************/
#pragma mark DJICameraFileIndexMode
/*********************************************************************************/


/**
 *  File index modes.
 */
typedef NS_ENUM (NSUInteger, DJICameraFileIndexMode){
 

    /**
     *  Camera will reset the newest file's index to be one larger than the largest
     *  number of photos taken on the SD card.
     */
    DJICameraFileIndexModeReset,
 

    /**
     *  Camera will set the newest file's index to the larger of either the maximum
     *  number of photos taken on the SD card or the camera.
     */
    DJICameraFileIndexModeSequence,
 

    /**
     *  The mode is unknown.
     */
    DJICameraFileIndexModeUnknown = 0xFF
};


/**
 *  Modes of ND filter.
 */
typedef NS_ENUM (NSUInteger, DJICameraNDFilterMode){

	/**
	 *  Auto. ND filter will be enabled or disabled automatically by the camera.
	 */
	DJICameraNDFilterModeAuto,
	

	/**
	 *  The ND filter is on.
	 */
	DJICameraNDFilterModeOn,
	

	/**
	 *  The ND filter is off.
	 */
	DJICameraNDFilterModeOff,
	

	/**
	 *  Unknown.
	 */
	DJICameraNDFilterModeUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark DJICameraCustomSettingsProfile
/*********************************************************************************/


/**
 *  Camera user settings. A user can save or load camera settings to or from the
 *  specified user.
 */
typedef NS_ENUM (NSUInteger, DJICameraCustomSettingsProfile){
 

    /**
     *  Default user.
     */
    DJICameraCustomSettingsProfileDefault,
 

    /**
     *  Settings for user 1.
     */
    DJICameraCustomSettingsProfile1,
 

    /**
     *  Settings for user 2.
     */
    DJICameraCustomSettingsProfile2,
 

    /**
     *  Settings for user 3.
     */
    DJICameraCustomSettingsProfile3,
 

    /**
     *  Settings for user 4.
     */
    DJICameraCustomSettingsProfile4,
 

    /**
     *  The user is unknown.
     */
    DJICameraCustomSettingsProfileUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraColor
/*********************************************************************************/


/**
 *  Camera color. The default value is `DJICameraColorNone`. Z30 camera only
 *  supports `DJICameraColorNone`, `DJICameraColorBlackAndWhite` and
 *  `DJICameraColorInverse`.
 */
typedef NS_ENUM (NSUInteger, DJICameraColor){
 

    /**
     *  The camera color is set to none or no filter.
     */
    DJICameraColorNone,
 

    /**
     *  The camera color is set to art.
     */
    DJICameraColorArt,
 

    /**
     *  The camera color is set to black and white.
     */
    DJICameraColorBlackAndWhite,
 

    /**
     *  The camera color is set to bright.
     */
    DJICameraColorBright,
 

    /**
     *  The camera color is set to D-Cinelike (called movie before).
     */
    DJICameraColorDCinelike,
 

    /**
     *  The camera color is set to portrait. Only supported by Osmo with X3 camera.
     */
    DJICameraColorPortrait,
 

    /**
     *  The camera color is set to M31.
     */
    DJICameraColorM31,
 

    /**
     *  The camera color is set to kDX.
     */
    DJICameraColorkDX,
 

    /**
     *  The camera color is set to prismo.
     */
    DJICameraColorPrismo,
 

    /**
     *  The camera color is set to jugo.
     */
    DJICameraColorJugo,
 

    /**
     *  The camera color is set to D-Log (called neutral before). For Mavic 2 Pro,
     *  setting to this color can enable 10-bit DLog-M color profile.
     */
    DJICameraColorDLog,
 

    /**
     *  The camera color is set to true color. It is only supported by Phantom 4 with
     *  firmware v1.2.503 or above.
     */
    DJICameraColorTrueColor,
 

    /**
     *  The camera color is set to inverse.
     */
    DJICameraColorInverse,


    /**
     *  The camera color is set to reminiscence.
     */
    DJICameraColorReminiscence,


    /**
     *  The camera color is set to solarize.
     */
    DJICameraColorSolarize,


    /**
     *  The camera color is set to posterize.
     */
    DJICameraColorPosterize,


    /**
     *  The camera color is set to whiteboard.
     */
    DJICameraColorWhiteboard,
    

    /**
     *  The camera color is set to blackboard.
     */
    DJICameraColorBlackboard,
    

    /**
     *  The camera color is set to aqua.
     */
    DJICameraColorAqua,


    /**
     *  The camera color is set to delta.
     */
    DJICameraColorDelta,
    

    /**
     *  The camera color is set to dk79.
     */
    DJICameraColorDK79,
    

    /**
     *  The camera color is set to vision4.
     */
    DJICameraColorVision4,
    

    /**
     *  The camera color is set to vision6.
     */
    DJICameraColorVision6,
    

    /**
     *  The camera color is set to true color extend.
     */
    DJICameraColorTrueColorExt,
    

    /**
     *  The camera color is set to Film A.
     */
    DJICameraColorFilmA,
    

    /**
     *  The camera color is set to Film B.
     */
    DJICameraColorFilmB,
    

    /**
     *  The camera color is set to Film C.
     */
    DJICameraColorFilmC,
    

    /**
     *  The camera color is set to Film D.
     */
    DJICameraColorFilmD,
    

    /**
     *  The camera color is set to Film E.
     */
    DJICameraColorFilmE,
    

    /**
     *  The camera color is set to Film F.
     */
    DJICameraColorFilmF,
    

    /**
     *  The camera color is set to Film G.
     */
    DJICameraColorFilmG,
    

    /**
     *  The camera color is set to Film H.
     */
    DJICameraColorFilmH,
    

    /**
     *  The camera color is set to Film I.
     */
    DJICameraColorFilmI,
    

    /**
     *  The camera color is set to HLG (Hybrid Log-Gamma).
     */
    DJICameraColorHLG,
    

    /**
     *  The camera color is unknown.
     */
    DJICameraColorUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraEIColor
/*********************************************************************************/

/**
 *  Camera colors for EI mode.
 */
typedef NS_ENUM (NSUInteger, DJICameraEIColor){

    /**
     *  The EI color is set to D-Log.
     */
    DJICameraEIColorDLog,

    /**
     *  The EI color is set to Rec.709.
     */
    DJICameraEIColorRec709,

    /**
     *  Unknown.
     */
    DJICameraEIColorUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraSSDLegacyColor
/*********************************************************************************/


/**
 *  The legacy camera color for videos that will be stored in SSD. The default value
 *  is `DJICameraSSDLegacyColorNone`. It is only supported Inspire 2 with firmware
 *  package versions lower than 01.0.0240.
 */
typedef NS_ENUM (NSUInteger, DJICameraSSDLegacyColor){


    /**
     *  The camera color is set to none. It is only supported by X5S on Inspire 2.
     */
    DJICameraSSDLegacyColorNone,


    /**
     *  The camera color is set to DCinelike. It is only supported by X5S on Inspire 2.
     */
    DJICameraSSDLegacyColorDCinelike,


    /**
     *  The camera color is set to DLog. It is only supported by X5S on Inspire 2.
     */
    DJICameraSSDLegacyColorDLog,


    /**
     *  The camera color is set to DColor1. It is only supported by X5S on Inspire 2.
     */
    DJICameraSSDLegacyColorDColor1,


    /**
     *  The camera color is set to DColor2. It is only supported by X5S on Inspire 2.
     */
    DJICameraSSDLegacyColorDColor2,
    

    /**
     *  The camera color is set to DColor3. It is only supported by X5S on Inspire 2.
     */
    DJICameraSSDLegacyColorDColor3,


    /**
     *  The camera color is unknown.
     */
    DJICameraSSDLegacyColorUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraSSDColor
/*********************************************************************************/

/**
 *  Camera colors for videos that will be stored in SSD. It is only supported
 *  Inspire 2 with the firmware package version 01.0.0240 or later.
 */
typedef NS_ENUM (NSUInteger, DJICameraSSDColor) {


	/**
	 *  Standard. It is available when the camera is in ISO mode and the SSD license is
	 *  `DJICameraSSDVideoLicenseProRes422HQ` or `DJICameraSSDVideoLicenseProRes4444XQ`.
	 */
	DJICameraSSDColorStandard,


	/**
	 *  D-Log. It is available when the camera is in EI mode and the SSD license is
	 *  `DJICameraSSDVideoLicenseProRes422HQ` or `DJICameraSSDVideoLicenseProRes4444XQ`.
	 */
	DJICameraSSDColorDLog,
	

	/**
	 *  Rec.709. It is available when the camera is in EI mode and the SSD license is
	 *  `DJICameraSSDVideoLicenseProRes422HQ` or `DJICameraSSDVideoLicenseProRes4444XQ`.
	 */
	DJICameraSSDColorRec709,
	

	/**
	 *  Cine-like. It is available when the camera is in ISO mode and the SSD license is
	 *  `DJICameraSSDVideoLicenseProRes422HQ` or `DJICameraSSDVideoLicenseProRes4444XQ`.
	 */
	DJICameraSSDColorCineLike,
	

	/**
	 *  Raw color. This is the only for `DJICameraSSDVideoLicenseCinemaDNG`.
	 */
	DJICameraSSDColorRawColor,
	

	/**
	 *  Unknown.
	 */
	DJICameraSSDColorUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraExposureSensitivityMode
/*********************************************************************************/

/**
 *  The exposure sensitivity modes.
 */
typedef NS_ENUM (NSUInteger, DJICameraExposureSensitivityMode) {
	

	/**
	 *  ISO mode.
	 */
	DJICameraExposureSensitivityModeISO,
	

	/**
	 *  EI (exposure index) mode. In this mode, the camera mimics the way a film camera
	 *  works to help cinematographers capture as much information as possible while
	 *  balancing the dynamic range and noise with different log curves. This mode only
	 *  takes effect when the camera mode is in `DJICameraModeRecordVideo`.
	 */
	DJICameraExposureSensitivityModeEI,
	

	/**
	 *  Unknown.
	 */
	DJICameraExposureSensitivityModeUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJIDownloadFileType
/*********************************************************************************/


/**
 *  Download file types. This typedef is supported by Phantom 3 Professional camera,
 *  X3, X5 and X5R cameras on aircraft and Phantom 4 camera.
 */
typedef NS_ENUM (NSUInteger, DJIDownloadFileType){
 

    /**
     *  The file to be download is a photo file type.
     */
    DJIDownloadFileTypePhoto,
 

    /**
     *  The file to be downloaded is a RAW type in DNG format.
     */
    DJIDownloadFileTypeRAWDNG,
 

    /**
     *  The file to be downloaded is a video file in 720P.
     */
    DJIDownloadFileTypeVideo720P,
 

    /**
     *  The file to be downloaded is a video file in 1080P.
     */
    DJIDownloadFileTypeVideo1080P,
 

    /**
     *  The file to be downloaded is a video file in 4K.
     */
    DJIDownloadFileTypeVideo4K,
 

    /**
     *  The file to be downloaded is unknown.
     */
    DJIDownloadFileTypeUnknown
};

/*********************************************************************************/
#pragma mark DJICameraOrientation
/*********************************************************************************/


/**
 *  Physical orientation of the camera.
 */
typedef NS_ENUM(NSUInteger, DJICameraOrientation) {
 

    /**
     *  By default, the camera is in landscape orientation.
     */
    DJICameraOrientationLandscape,
 

    /**
     *  The camera is in the portrait orientation, which is rotated 90 degrees in the
     *  clockwise direction from the default landscape orientation.
     */
    DJICameraOrientationPortrait,
 

    /**
     *  Unknown.
     */
    DJICameraOrientationUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark DJIVideoFileCompressionStandard
/*********************************************************************************/


/**
 *  The compression standard used to store the video files. It is only supported
 *  X4S, X5S and Phantom 4 Pro cameras.
 */
typedef NS_ENUM(NSUInteger, DJIVideoFileCompressionStandard){
 

    /**
     *  H.264 compression standard.
     */
    DJIVideoFileCompressionStandardH264,
 

    /**
     *  H.265 compression standard.
     */
    DJIVideoFileCompressionStandardH265,
 

    /**
     *  Unknown.
     */
    DJIVideoFileCompressionStandardUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark - DJICameraPictureStylePreset
/*********************************************************************************/


/**
 *  Camera preset type, a combine of Saturation, Contrast, Sharpness.
 */
typedef NS_ENUM(NSUInteger, DJICameraPictureStylePresetType) {
    

    /**
     *  Saturation 0, Contrast 0, Sharpness 0.
     */
    DJICameraPictureStylePresetTypeStandard = 0x00,
    

    /**
     *  Saturation 0, Contrast 1, Sharpness 1.
     */
    DJICameraPictureStylePresetTypeLandscape,
    

    /**
     *  Saturation 0, Contrast 0, Sharpness -1.
     */
    DJICameraPictureStylePresetTypeSoft,
    

    /**
     *  Custom preset type
     */
    DJICameraPictureStylePresetTypeCustom,


    /**
     *  Unknown preset type
     */
    DJICameraPictureStylePresetTypeUnknown,

};


/**
 *  The temperature units.
 */
typedef NS_ENUM(NSUInteger, DJICameraTemperatureUnit) {

	/**
	 *  Use degree Fahrenheit as the unit.
	 */
	DJICameraTemperatureUnitFahrenheit,

	/**
	 *  Use degree Celsius as the unit.
	 */
	DJICameraTemperatureUnitCelsius,

	/**
	 *  Unknown.
	 */
	DJICameraTemperatureUnitUnknown,
};


/**
 *  Camera preset type that stores saturation, contrast and sharpness
 */
typedef struct{
    

    /**
     *  An NSInteger value of saturation.
     */
    NSInteger saturation;
    

    /**
     *  An NSInteger value of contrast.
     */
    NSInteger contrast;
    

    /**
     *  An NSInteger value of sharpness.
     */
    NSInteger sharpness;
    

    /**
     *  An enum value of `DJICameraPictureStylePresetType`.
     */
    DJICameraPictureStylePresetType presetType;
}DJICameraPictureStylePreset;

/*********************************************************************************/
#pragma mark DJICameraSSDClipFileName
/*********************************************************************************/

/**
 *  The name of a video file stored in SSD.
 */
@interface DJICameraSSDClipFileName : NSObject


/**
 *  A single captical character represents the equipment. The possible value is from
 *  'A' to 'Z'.
 */
@property(nonatomic, readonly) char equipmentLabel;


/**
 *  The reel ID. The possible value is from 0 to 999.
 */
@property(nonatomic, readonly) uint16_t reelID;


/**
 *  The clip ID. The possible value is from 0 to 999.
 */
@property(nonatomic, readonly) uint16_t clipID;


/**
 *  Create a SSD clip name instance.
 *  
 *  @param label The equipment label of the clip. The valid input is from 'A' to 'Z'.
 *  @param reelID The reel ID. The valid input is from 0 to 999.
 *  @param clipID The clip ID. The valid input is from 0 to 999.
 *  
 *  @return A clip name instance. Return `nil` if the input is invalid.
 */
- (nullable instancetype)initWithEquipmentLabel:(char)label reelID:(uint16_t)reelID clipID:(uint16_t)clipID;

@end

/*********************************************************************************/
#pragma mark DJICameraStorageLocation
/*********************************************************************************/

/**
 *  Different storage locations supported by the camera.
 */
typedef NS_ENUM (NSUInteger, DJICameraStorageLocation){

    /**
     *  SD card.
     */
    DJICameraStorageLocationSDCard,

    /**
     *  The internal storage embedded in the aircraft. When it is available, the camera
     *  can shoot photos or record videos without SD card. It is only supported by Mavic
     *  Air.
     */
    DJICameraStorageLocationInternalStorage,

    /**
     *  Unknown.
     */
    DJICameraStorageLocationUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark DJICameraOriginalPhotoSettings
/*********************************************************************************/

/**
 *  Settings to determine the behavior for the original photos created when doing
 *  composite shooting (e.g. panorama).
 */
@interface DJICameraOriginalPhotoSettings : NSObject


/**
 *  `YES` if the camera should save the original photos.
 */
@property (nonatomic, readonly) BOOL shouldSaveOriginalPhotos;


/**
 *  The format for the original photos if the user decides to save them. Mavic Air
 *  cannot change this  setting and it will ignore this property.
 */
@property (nonatomic, readonly) DJICameraPhotoFileFormat format;


/**
 *  Creates an instance of the configuration to decide saving the original photos or
 *  not. `format` will  be `DJICameraPhotoFileFormatJPEG`. Use this constructor for
 *  Mavic Air.
 *  
 *  @param shouldSaveOriginalPhotos `YES` to save the original photos.
 */
- (instancetype)initWithSavingOriginalImagesEnabled:(BOOL)shouldSaveOriginalPhotos;


/**
 *  Creates an instance of the configuration to decide whether saving the original
 *  images and the format.
 *  
 *  @param shouldSaveOriginalPhotos `YES` to save the original images.
 *  @param format The format to save the original images.
 */
- (instancetype)initWithSavingOriginalImagesEnabled:(BOOL)shouldSaveOriginalPhotos andFormat:(DJICameraPhotoFileFormat)format;

@end

/*********************************************************************************/
#pragma mark DJICameraWatermarkSettings
/*********************************************************************************/

/**
 *  The watermark configuration to decide if timestamp and location stamp will be
 *  added to photos or videos.
 */
@interface DJICameraWatermarkSettings : NSObject


/**
 *  `YES` if the timestamp and the location stamp is added to photos.
 */
@property (nonatomic, readonly) BOOL enabledForPhotos;


/**
 *  `YES` if the timestamp and the location stamp is added to videos. The stamps are
 *  updated during the videos.
 *  
 *  @return `YES` if the watermark (timestamp and location stamp) is enabled for videos.
 */
@property (nonatomic, readonly) BOOL enabledForVideos;


/**
 *  Creates an instance of the settings to control the watermark on photos and
 *  videos.
 *  
 *  @param enabledForPhotos Enables the feature for photos.
 *  @param enabledForVideos Enables the feature for videos.
 */
- (instancetype)initWithForPhotos:(BOOL)enabledForPhotos andForVideos:(BOOL)enabledForVideos;

@end

NS_ASSUME_NONNULL_END
