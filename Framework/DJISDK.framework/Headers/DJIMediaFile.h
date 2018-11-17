//
//  DJIMediaFile.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DJIBaseProduct.h"
#import "DJICameraSettingsDef.h"

NS_ASSUME_NONNULL_BEGIN

@class DJIMediaFile;

/*********************************************************************************/
#pragma mark - DJIMediaType
/*********************************************************************************/

@class UIImage;


/**
 *  Media types.
 */
typedef NS_ENUM (NSUInteger, DJIMediaType){


    /**
     *  Unknown file type.
     */
    DJIMediaTypeUnknown,


    /**
     *  Image of JPEG format.
     */
    DJIMediaTypeJPEG,


    /**
     *  Video of MP4 format.
     */
    DJIMediaTypeMP4,


    /**
     *  Video of MOV format.
     */
    DJIMediaTypeMOV,


    /**
     *  Image of DNG format.
     */
    DJIMediaTypeRAWDNG,


    /**
     *  Panorama file type.
     */
    DJIMediaTypePanorama,


    /**
     *  TIFF file type.
     */
    DJIMediaTypeTIFF,


    /**
     *  ShallowFocus file type. ShallowFocus files have a shallow depth of field.
     */
    DJIMediaTypeShallowFocus,
	

    /**
     *  TIFF Sequence file type. It is a video format for infrared cameras.
     */
    DJIMediaTypeTIFFSequence,


	/**
	 *  SEQ file type. It is a video format for infrared cameras.
	 */
    DJIMediaTypeSEQ,
    

    /**
     *  Audio file type. It is an audio format for the speaker.
     */
    DJIMediaTypeAudio,
};

/*********************************************************************************/
#pragma mark - DJIMediaVideoPlaybackStatus
/*********************************************************************************/


/**
 *  The playback status.
 */
typedef NS_ENUM(uint8_t, DJIMediaVideoPlaybackStatus) {


    /**
     *  The playback is stopped. No media is playing.
     */
    DJIMediaVideoPlaybackStatusStopped,


    /**
     *  The media manager is playing a video.
     */
    DJIMediaVideoPlaybackStatusPlaying,


    /**
     *  The playing video is paused.
     */
    DJIMediaVideoPlaybackStatusPaused,
};

/*********************************************************************************/
#pragma mark - DJIMediaVideoPlaybackState
/*********************************************************************************/


/**
 *  The playback state of the media manager.
 */
@interface DJIMediaVideoPlaybackState : NSObject


/**
 *  The video media file that is playing.
 *  
 *  @return An instance of `DJIMediaFile`.
 */
@property(nonatomic, readonly) DJIMediaFile *playingMedia;


/**
 *  The status of the playback (e.g. playing or paused).
 */
@property(nonatomic, readonly) DJIMediaVideoPlaybackStatus playbackStatus;


/**
 *  The playing position in seconds.
 */
@property(nonatomic, readonly) float playingPosition;

@end

/*********************************************************************************/
#pragma mark - DJIMediaFile
/*********************************************************************************/


/**
 *  This class contains information about a multi-media file on the SD card. It also
 *  provides methods to retrieve the data in the file.
 */
@interface DJIMediaFile : NSObject


@property (nonatomic, readonly) int guid;


/**
 *  `YES` if the media file is still valid. If a media file is from the file list of
 *  the media manager, the file will become invalid after the file list is reset.
 */
@property(nonatomic, readonly) BOOL valid; 


/**
 *  Get the file index used in the camera.
 */
@property(nonatomic, readonly) NSUInteger index;


/**
 *  Returns the name of the media file in the SD Card.
 */
@property(nonatomic, readonly) NSString *fileName;


/**
 *  Returns the size, in bytes, of the media file.
 */
@property(nonatomic, readonly) long long fileSizeInBytes;


/**
 *  Returns the time when the media file was created as a string in the format
 *  "yyyy-MM-dd kk:mm:ss".
 */
@property(nonatomic, readonly) NSString *timeCreated;


/**
 *  If the media file is a video, this property returns the duration of the video in
 *  seconds. Will be 0s if the media file is a photo.
 */
@property(nonatomic, readonly) float durationInSeconds;


/**
 *  Returns the type of media file.
 */
@property(nonatomic, readonly) DJIMediaType mediaType;


/**
 *  The orientation of the camera when the video file was first recorded. If the
 *  camera orientation changes during a video capture, this will report the initial
 *  orientation. Will be `DJICameraOrientationLandscape` if the media file is a
 *  photo. Only Mavic Pro supports this property. Will be
 *  `DJICameraOrientationLandscape` for other products.
 */
@property(nonatomic, readonly) DJICameraOrientation videoOrientation;


/**
 *  Camera resolution.
 */
@property(nonatomic, readonly) DJICameraVideoResolution resolution;


/**
 *  Frame rate when the media file is a video.
 *  
 *  @return An int value.
 */
@property(nonatomic, readonly) DJICameraVideoFrameRate frameRate;


/**
 *  Storage location of the media file.
 */
@property(nonatomic, readonly) DJICameraStorageLocation storageLocation;


/**
 *  Returns the thumbnail for this media. If this property returns nil, call
 *  `fetchThumbnailWithCompletion`.
 */
@property(nonatomic, nullable, readonly) UIImage *thumbnail;


/**
 *  Returns the preview image for this media. If this property returns `nil`, call
 *  `fetchPreviewWithCompletion`.
 */
@property(nonatomic, nullable, readonly) UIImage *preview;


/**
 *  Custom information can be stored in media file's XMP meta data using
 *  `setMediaFileCustomInformation:withCompletion` This property contains the
 *  information that was written to this media file. If this property returns `nil`,
 *  use `fetchCustomInformationWithCompletion` to populate it. Only supported by
 *  Phantom 4 Pro, Phantom 4 Advanced and Inspire 2 with firmware versions from
 *  after May 23 2017.
 */
@property(nonatomic, nullable, readonly) NSString *customInformation;


/**
 *  Fetches this media's thumbnail with a resolution (99 x 99) from the SD card.
 *  This method can be used to fetch either a photo or a video, where the first
 *  frame of the video is the thumbnail that is fetched. It is not available if the
 *  media type is Panorama.
 *   Precondition:
 *   The camera mode is MediaDownload mode.
 *   Post Condition:
 *   This method will start to download the media thumbnail in the SD card. The
 *  content can be videos or images.
 *  
 *  @param completion The `completion block` with the returned execution result.
 */
- (void)fetchThumbnailWithCompletion:(DJICompletionBlock)completion;


/**
 *  Free memory by setting cached thumbnail to `nil`. This does not need to be
 *  called before `fetchThumbnailWithCompletion` and is provided for convenience.
 */
- (void)resetThumbnail;


/**
 *  Fetch media's preview image. The preview image is a lower resolution (960 x 540)
 *  version of a photo. The `DJIMediaType` of this media object should be
 *  `DJIMediaTypeJPEG` or `DJIMediaTypeTIFF`. The preview will be stored in
 *  `preview`.
 *  
 *  @param completion The `completion block` with the returned execution result.
 */
- (void)fetchPreviewWithCompletion:(DJICompletionBlock)completion;


/**
 *  Free memory by setting cached preview image to `nil`. This does not need to be
 *  called before `fetchPreviewWithCompletion` and is provided  for convenience.
 */
- (void)resetPreview;


/**
 *  Custom information can be stored in media file's XMP meta data using
 *  `setMediaFileCustomInformation:withCompletion`. The information will be stored
 *  in `customInformation`. Only supported by Phantom 4 Pro, Phantom 4 Advanced,
 *  Phantom 4 Pro V2.0, Zenmuse X4S, Zenmuse X5S, Zenmuse X7 and Mavic 2 Enterprise
 *  camera.
 *  
 *  @param completion The `completion block` with the returned execution result.
 */
- (void)fetchCustomInformationWithCompletion:(DJICompletionBlock)completion;



/**
 *  Fetches this media file's full resolution data from the SD card. The difference
 *  between fetching the media data and fetching the thumbnail is that fetching the
 *  thumbnail will return a low-resolution image of the actual picture, while
 *  fetching the media data will return all data for a video or image. If last
 *  download action is aborted, it will continue to download the data from where the
 *  file download has been aborted.
 *  
 *  @param offset Offset in bytes. Pass 0 to fetch all data from the beginning. Pass the already fetched bytes to continue the previous download.
 *  @param queue Queue to call the update block on.
 *  @param data A chunk of binary data of the file.
 *  @param isComplete `YES` if the last byte of the file is returned and thus fetching is complete.
 *  @param error Error retrieving the value.
 *  @param updateBlock Block to receive file data. It will be called multiple times and each time will return the data received since the last call.
 */
- (void)fetchFileDataWithOffset:(NSUInteger)offset
                    updateQueue:(dispatch_queue_t)queue
                    updateBlock:(void (^_Nonnull)(NSData *_Nullable data, BOOL isComplete, NSError *_Nullable error))updateBlock;


/**
 *  Stops a currently executing call of
 *  `fetchFileDataWithOffset:updateQueue:updateBlock`.
 *  
 *  @param completion The `completion block` with the returned execution result.
 */
- (void)stopFetchingFileDataWithCompletion:(DJICompletionBlock)completion;


/**
 *  Fetches the file data of the sub media files. It is available only when
 *  `mediaType` is `DJIMediaTypePanorama` or `DJIMediaTypeShallowFocus`.
 *  
 *  @param dataList Sub media files' data. They are files are in JPEG format.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)fetchSubFileDataListWithCompletion:(void (^_Nonnull)(NSArray<NSData *> *_Nullable dataList, NSError *_Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
