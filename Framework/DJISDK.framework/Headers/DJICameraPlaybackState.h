//
//  DJICameraPlaybackState.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>


/**
 *  Showing media file types when the camera is in Playback mode.
 */
typedef NS_ENUM (uint8_t, DJICameraPlaybackFileType){


    /**
     *  The JPEG media file type.
     */
    DJICameraPlaybackFileTypeJPEG,


    /**
     *  The DNG media file type.
     */
    DJICameraPlaybackFileTypeRAWDNG,


    /**
     *  The Video media file type.
     */
    DJICameraPlaybackFileTypeVIDEO,


    /**
     *  The playback file format is unknown.
     */
    DJICameraPlaybackFileTypeUnknown = 0xFF
};


/**
 *  A playback mode represents a task that the Playback manager is executing.
 */
typedef NS_ENUM (uint8_t, DJICameraPlaybackMode){


    /**
     *  Single file preview mode.
     */
    DJICameraPlaybackModeSingleFilePreview = 0,


    /**
     *  Single video playback start.
     */
    DJICameraPlaybackModeSingleVideoPlaybackStart = 2,


    /**
     *  Single video playback pause.
     */
    DJICameraPlaybackModeSingleVideoPlaybackPause = 3,


    /**
     *  Multiple file edit.
     */
    DJICameraPlaybackModeMultipleFilesEdit = 4,


    /**
     *  Multiple media file preview.
     */
    DJICameraPlaybackModeMultipleFilesPreview = 5,


    /**
     *  Download media files.
     */
    DJICameraPlaybackModeDownload = 6,


    /**
     *  Unknown playback mode.
     */
    DJICameraPlaybackModeUnknown = 0xFF,
};


/**
 *  The file deletion status when deleting a file as the camera is in playback mode.
 */
typedef NS_ENUM (uint8_t, DJICameraPlaybackDeletionState){
    

    /**
     *  Camera is not deleting files.
     */
    DJICameraPlaybackDeletionStateNone,


    /**
     *  Media file delete failed.
     */
    DJICameraPlaybackDeletionStateFailed,


    /**
     *  Media file is deleting.
     */
    DJICameraPlaybackDeletionStateDeleting,


    /**
     *  Delete Media file successfully.
     */
    DJICameraPlaybackDeletionStateSuccessful,
    

    /**
     *  Media file unknown delete status.
     */
    DJICameraPlaybackDeletionStateUnknown,
};


/**
 *  This class provides the current state of the Playback manager, which includes
 *  the numbers of thumbnail and media files, video duration, video play progress,
 *  and file download state.
 */
@interface DJICameraPlaybackState : NSObject


/**
 *  The current mode of the Playback manager.
 */
@property(nonatomic, readonly) DJICameraPlaybackMode playbackMode;


/**
 *  The type of the current file. The DJICameraPlaybackFileFormat includes  types of
 *  JPEG, DNG and Video.
 *   The value of this property is valid when the playbackMode  is
 *  `DJICameraPlaybackModeSingleFilePreview`,
 *  `DJICameraPlaybackModeSingleVideoPlaybackStart`  or
 *  `DJICameraPlaybackModeSingleVideoPlaybackPause`.
 */
@property(nonatomic, readonly) DJICameraPlaybackFileType fileType;


/**
 *  The total number of thumbnails for both the photos and videos being viewed on
 *  the page. The value of the property  is valid when the `DJICameraPlaybackMode`
 *  is `DJICameraPlaybackModeMultipleFilesPreview`   or
 *  `DJICameraPlaybackModeMultipleFilesEdit`.
 */
@property(nonatomic, readonly) int numberOfThumbnails;


/**
 *  The total number of media files on the SD card, including photos and videos.
 */
@property(nonatomic, readonly) int numberOfMediaFiles;


/**
 *  The index of the current selected file.
 */
@property(nonatomic, readonly) int currentSelectedFileIndex;


/**
 *  The duration in second of the playing video. The value of the property is valid
 *  only when `DJICameraPlaybackMode`  is
 *  `DJICameraPlaybackModeSingleVideoPlaybackStart`  or
 *  `DJICameraPlaybackModeSingleVideoPlaybackPause`.
 */
@property(nonatomic, readonly) int videoDuration;


/**
 *  The progress, in percentage, of the playing video. The valid range is [0, 100].
 *  The value the property is valid  only when `DJICameraPlaybackMode`  is
 *  `DJICameraPlaybackModeSingleVideoPlaybackStart`  or
 *  `DJICameraPlaybackModeSingleVideoPlaybackPause`.
 */
@property(nonatomic, readonly) int videoPlayProgress;


/**
 *  The played duration, in seconds, of the playing video. The value the property is
 *  valid only when `DJICameraPlaybackMode`  is
 *  `DJICameraPlaybackModeSingleVideoPlaybackStart` or
 *  `DJICameraPlaybackModeSingleVideoPlaybackPause`.
 */
@property(nonatomic, readonly) int videoPlayPosition;


/**
 *  The total number of the selected files. The value is valid while
 *  `DJICameraPlaybackMode` is in `DJICameraPlaybackModeMultipleFilesEdit`>.
 */
@property(nonatomic, readonly) int selectedFileCount;


/**
 *  The total number of photos on the SD card.
 */
@property(nonatomic, readonly) int photoCount;


/**
 *  The total number of videos on the SD card.
 */
@property(nonatomic, readonly) int videoCount;


/**
 *  The dimension of the previewing photo. The value of the property is valid only
 *  when `DJICameraPlaybackMode`  is `DJICameraPlaybackModeSingleFilePreview`  and
 *  `fileType`  is `DJICameraPlaybackFileTypeJPEG`.
 */
@property(nonatomic, readonly) CGSize photoSize;


/**
 *  The current status of a file when the user tries to delete it.
 */
@property(nonatomic, readonly) DJICameraPlaybackDeletionState deletionState;


/**
 *  `YES` if all the files on the current page are selected.
 *  
 *  @return Response of all files being selected on page.
 */
@property(nonatomic, readonly) BOOL isAllFilesInPageSelected;


/**
 *  `YES` if the previewing file is a valid photo or video. The value of the
 *  property is valid  only when `DJICameraPlaybackMode`  is
 *  `DJICameraPlaybackModeSingleFilePreview`.
 */
@property(nonatomic, readonly) BOOL isSelectedFileValid;


/**
 *  `YES` if the previewing file has been downloaded. The value of the property is
 *  valid only when `DJICameraPlaybackMode`  is
 *  `DJICameraPlaybackModeSingleFilePreview`.
 */
@property(nonatomic, readonly) BOOL isFileDownloaded;

@end
