//
//  DJIPlaybackManager.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DJICameraSettingsDef.h"
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIPlaybackManager;
@class DJICameraPlaybackState;


/**
 *  Block invoked when preparing a file for download.
 *  
 *  @param fileName File name.
 *  @param fileType Type of file.
 *  @param fileSize Size of file.
 *  @param skip Can be set to decide whether or not to skip the file.
 */
typedef void (^_Nullable DJIFileDownloadPreparingBlock)(NSString *_Nullable fileName, DJIDownloadFileType fileType, NSUInteger fileSize, BOOL *skip);


/**
 *  Block invoked when a file is downloading.
 *  
 *  @param data File data.
 *  @param error Error experienced during transfer.
 */
typedef void (^_Nullable DJIFileDownloadingBlock)(NSData *_Nullable data, NSError *_Nullable error);


/**
 *  Block invoked after a file has been downloaded.
 */
typedef void (^_Nullable DJIFileDownloadCompletionBlock)();

/*********************************************************************************/
#pragma mark - DJIPlaybackDelegate
/*********************************************************************************/


/**
 *  The protocol provides a delegate method to receive the updated state of the
 *  playback manager.
 */
@protocol DJIPlaybackDelegate <NSObject>

@required


/**
 *  Updates the playback state of the camera. This update method will only be called
 *  when the camera's work mode is  set to `DJICameraModePlayback`.
 *  
 *  @param playbackManager DJIPlaybackManager object.
 *  @param playbackState The camera's playback state.
 */
- (void)playbackManager:(DJIPlaybackManager *_Nonnull)playbackManager didUpdatePlaybackState:(DJICameraPlaybackState *_Nonnull)playbackState;

@end

/*********************************************************************************/
#pragma mark - DJIMediaManager
/*********************************************************************************/


/**
 *  The playback manager is used to interact with the playback system of the camera.
 *  By using the playback manager, the user can control the playback system.
 */
@interface DJIPlaybackManager : NSObject


/**
 *  Returns the delegate of DJIPlaybackManager
 */
@property(nonatomic, weak) id<DJIPlaybackDelegate> delegate;


/**
 *  This enables the user to select, download, or delete multiple media files when
 *  the camera is in Playback mode.
 *   Precondition:
 *   The camera work mode must be set to Camera Play back mode and then Multiple
 *  Preview Mode.
 *   Post condition:
 *   Multiple photos can be selected to be downloaded or deleted. @return
 *  DJICameraError Shows the  possible error during the execution. If there is no
 *  error, it returns <code>null</code>.
 */
- (void)enterMultipleEditMode;


/**
 *  Exits multiple edit mode.
 */
- (void)exitMultipleEditMode;


/**
 *  Selects or unselects a file at the specified index of the current page. This
 *  index is unrelated to the filename,  and is used in multiple edit mode.
 *   Precondition:
 *   The camera must enter Multiple Edit Mode.
 *  
 *  @param index Index at which to select a file.
 */
- (void)toggleFileSelectionAtIndex:(int)index;


/**
 *  Selects all the files on the SD card.
 *   Precondition:
 *   The camera must enter Multi Edit Mode.
 */
- (void)selectAllFiles;


/**
 *  Unselects all the files on the SD card.
 *   Precondition:
 *   The camera must enter Multiple Edit Mode.
 */
- (void)unselectAllFiles;


/**
 *  Selects all the file(s) on the current page.
 *   Precondition:
 *   The camera must enter Multiple Edit Mode.
 */
- (void)selectAllFilesInPage;


/**
 *  Unselects all the file(s) on the current page.
 *   Precondition:
 *   The camera must enter Multiple Edit  Mode.
 */
- (void)unselectAllFilesInPage;


/**
 *  Deletes all selected files from the SD card.
 *   Precondition:
 *   The camera must enter Multiple Edit Mode.
 *   Post condition:
 *   The images will be deleted from the SD card.
 */
- (void)deleteAllSelectedFiles;


/**
 *  Downloads the currently selected media files.
 *   Precondition:
 *   The camera must enter multiple preview mode.
 *  
 *  @param prepareBlock Callback to prepare each file for download.
 *  @param dataBlock Callback while a file is downloading. The dataBlock can be called multiple times for a file. The error  argument in <code>DJIFileDownloadingBlock</code> is not used and should be ignored.
 *  @param fileCompletionBlock Callback after each file have been downloaded.
 *  @param finishBlock Callback after the downloading is finished.
 */
- (void)downloadSelectedFilesWithPreparation:(nullable DJIFileDownloadPreparingBlock)prepareBlock
                                     process:(nullable DJIFileDownloadingBlock)dataBlock
                              fileCompletion:(nullable DJIFileDownloadCompletionBlock)fileCompletionBlock
                           overallCompletion:(nullable DJICompletionBlock)finishBlock;


/**
 *  Cancel current file download.
 *  
 *  @param block Callback after the operation finished.
 */
- (void)stopDownloadingFilesWithCompletion:(nullable DJICompletionBlock)block;


/**
 *  Enables the user to preview multiple files when the camera is in Playback mode.
 *   Precondition:
 *   The  camera work mode should be set to Playback mode.
 *   Post condition:
 *   There will be 8 images on one page.
 */
- (void)enterMultiplePreviewMode;


/**
 *  Goes to the next page when there are multiple pages.
 *   Precondition:
 *   The camera must enter Multiple  Preview Mode.
 *   Special case:
 *   If it is the last page, it will stay at the last page.
 */
- (void)goToNextMultiplePreviewPage;


/**
 *  Goes back to the previous page when there are multiple pages.
 *   Precondition:
 *    The camera must enter Multiple Preview Mode.
 *   Special case:
 *   If it is the first page, it will  stay at the first page.
 */
- (void)goToPreviousMultiplePreviewPage;


/**
 *  Enters single file preview mode for a file at the specified index. In order for
 *  this method to be called,  the camera work mode must be `DJICameraModePlayback`.
 *  
 *  @param index File to be previewed at the specified index. The value falls in [1,8].
 */
- (void)enterSinglePreviewModeWithIndex:(uint8_t)index;


/**
 *  Goes to the next page.
 *   Precondition:
 *   The camera must enter Single File Preview Mode.
 *    Special case:
 *   If it is the last image, it will go to the first image.
 */
- (void)goToNextSinglePreviewPage;


/**
 *  Goes back to the previous page.
 *   Precondition:
 *   The camera must enter Single File Preview Mode.
 *   Special case:
 *   If it is the first image, it will go to the last image.
 */
- (void)goToPreviousSinglePreviewPage;


/**
 *  Deletes the current file being previewed.
 *   Precondition:
 *   The camera must enter single file preview  mode.
 *   Post condition:
 *   The image will be deleted from the SD card.
 */
- (void)deleteCurrentPreviewFile;


/**
 *  Starts video playback. The selected file must be a video file.
 *   Precondition:
 *   The camera must enter  Single Preview Mode.
 *   Post condition:
 *   If the video finishes playing, it will stop and go back to the  beginning of
 *  the file.
 */
- (void)playVideo;


/**
 *  Pauses a video during playback.
 *   Precondition:
 *   The video is being played.
 */
- (void)pauseVideo;


/**
 *  Stops a video during playback.
 *   Precondition:
 *   The video is being played.
 *   Post condition:
 *    The file will stop and go back to the beginning of the file.
 */
- (void)stopVideo;


/**
 *  Plays a video from the specified location. The selected file must be a video
 *  file.
 *   Precondition:
 *    The camera must enter Single File Preview Mode.
 *   Post condition:
 *   The file will play from a specific location immediately. This command can only
 *  be called if the video is currently playing or is paused. If paused, the
 *  playback position will be updated and playing will resume.
 *  
 *  @param position Location from which to play the video must be in the range of [0, 100]. This value  represents at what percent of the entire video it should start playing.
 */
- (void)playVideoFromPositionInPercent:(uint8_t)position;

@end

NS_ASSUME_NONNULL_END
