//
//  DJIMediaManager.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <DJISDK/DJISDKFoundation.h>
#import <DJISDK/DJICameraSettingsDef.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIMediaFile;
@class DJIMediaManager;
@class DJIMediaVideoPlaybackState;
@class DJIFetchMediaTaskScheduler;


/**
 *  States of the file list in `DJIMediaManager`.
 */
typedef NS_ENUM(NSUInteger, DJIMediaFileListState) {

    /**
     *  The file list is up-to-date: it is synchronized with the SD card in the
     *  aircraft.
     */
    DJIMediaFileListStateUpToDate,

    /**
     *  New files have been generated since the last call of
     *  `refreshFileListOfStorageLocation:withCompletion`. Calling
     *  `refreshFileListOfStorageLocation:withCompletion` can synchronize the newly
     *  generated files and append them to the end of the file list.
     */
    DJIMediaFileListStateIncomplete,

    /**
     *  The file list is reset. The file list will be reset in one of the following
     *  cases:
     *   - Camera is disconnected.
     *   - SD card is formatted.
     *   - SD card is not inserted.
     *   - Error occurs when deleting files from SD card.
     *   In this state, `sdCardFileListSnapshot` will return `nil`.
     */
    DJIMediaFileListStateReset,

    /**
     *  `deleteFiles:withCompletion` has been called and the operation is still in
     *  progress.
     */
    DJIMediaFileListStateDeleting,

    /**
     *  A renaming operation is in progress.
     */
    DJIMediaFileListStateRenaming,

    /**
     *  The media manager is synchronizing the file list from the SD card.
     */
    DJIMediaFileListStateSyncing,

    /**
     *  Unknown.
     */
    DJIMediaFileListStateUnknown = 0xFF
};


/**
 *  This protocol provides a delegate method to receive the updated video playback
 *  state of the media manager.
 */
@protocol DJIMediaManagerDelegate <NSObject>

@optional


/**
 *  Updates the video playback state of the media manager. This update method will
 *  only be called when the media manager is playing a video.
 *  
 *  @param manager The media manager updates the playback state.
 *  @param state The playback state.
 */
-(void)manager:(DJIMediaManager *)manager didUpdateVideoPlaybackState:(DJIMediaVideoPlaybackState *)state;


/**
 *  Updates the video playback data of the media manager. This update method will
 *  only be called when the media manager is playing a video.
 *  
 *  @param manager The media manager updates the playback state.
 *  @param data An uint8_t value of video playback data.
 *  @param length A size_t value of the data length.
 *  @param forRendering Check if it's for rendering.
 */
-(void)manager:(DJIMediaManager *)manager didUpdateVideoPlaybackData:(uint8_t *)data length:(size_t)length forRendering:(BOOL)forRendering;


/**
 *  Updates the file list state of the media manager.
 *  
 *  @param manager The media manager with updated file list state.
 *  @param fileListState The new file list state.
 */
-(void)manager:(DJIMediaManager *)manager didUpdateFileListState:(DJIMediaFileListState)fileListState;


/**
 *  Updates the file list state of the media manager.
 *  
 *  @param manager The media manager with updated file list state.
 *  @param location The storage location of the file list.
 *  @param fileListState The latest state of the file list.
 */
-(void)manager:(DJIMediaManager *)manager didUpdateStorageLocation:(DJICameraStorageLocation)location
                                                     fileListState:(DJIMediaFileListState)fileListState;

@end

/*********************************************************************************/
#pragma mark - DJIMediaManager
/*********************************************************************************/


/**
 *  The media manager is used to interact with the file system on the SD card or the
 *  internal storage. By using the media manager, the user can get the metadata for
 *  all the multimedia files, and has access to each individual multimedia file.
 */
@interface DJIMediaManager : NSObject


/**
 *  Delegate that receives media manager's status update.
 */
@property (nonatomic, nullable, weak) id<DJIMediaManagerDelegate> delegate;


/**
 *  Fetch media task scheduler. This can be used to queue the download of the
 *  previews, thumbnails and XML custom data from multiple media files.
 */
@property (nonatomic, readonly) DJIFetchMediaTaskScheduler *taskScheduler;


/**
 *  The file list state of the SD card.
 */
@property (nonatomic, readonly) DJIMediaFileListState sdCardFileListState;


/**
 *  Returns a copy of the current file list on the SD card. Returns `nil` if
 *  `sdCardFileListState` is reset.
 *  
 *  @return An array of `DJIMediaFile` objects.
 */
- (NSArray<DJIMediaFile *> *_Nullable)sdCardFileListSnapshot;


/**
 *  The file list state of the internal storage.
 *  
 *  @return .
 */
@property (nonatomic, readonly) DJIMediaFileListState internalStorageFileListState;


/**
 *  Returns a copy of the current file list on the internal storage. Returns `nil`
 *  if `internalStorageFileListState` is reset or unknown.
 *  
 *  @return An array of `DJIMediaFile` objects.
 */
- (NSArray<DJIMediaFile *> *_Nullable)internalStoragefileListSnapshot;


/**
 *  Refreshes the file list of the storage. If the current state is
 *  `DJIMediaFileListStateReset`, the media manager will try to fetch the complete
 *  file list. If the current state  is `DJIMediaFileListStateIncomplete`, the media
 *  manager will only fetch the missing list of files. If the file list is refreshed
 *  successfully, the corresponding file list state (either `sdCardFileListState` or
 *  `internalStorageFileListState`) will become `DJIMediaFileListStateUpToDate`.
 *  
 *  @param storageLocation The storage location of the file list to refresh.
 *  @param completion Completion block to receive the result.
 */
- (void)refreshFileListOfStorageLocation:(DJICameraStorageLocation)storageLocation withCompletion:(DJICompletionBlock)completion;


/**
 *  Delete media files from storages. If the operation is started successfully,
 *  `DJIMediaFileListState` will become  `DJIMediaFileListStateDeleting`. If there
 *  is error or  "failedFiles" is not empty, `DJIMediaFileListState` will become
 *  `DJIMediaFileListStateReset`.
 *  
 *  @param files Media files to delete.
 *  @param failedFiles Files that failed to delete.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)deleteFiles:(NSArray<DJIMediaFile *> *_Nonnull)files withCompletion:(void (^_Nullable)(NSArray<DJIMediaFile *> *_Nonnull failedFiles, NSError *_Nullable error))completion;

@end

/**
 *  Category of `DJIMediaManager` includes methods to control the video playback.
 */
@interface DJIMediaManager (VideoPlayback)


/**
 *  Checks if the media manager supports video playback or not. @return `YES` if the
 *  media manager supports video playback.
 *  
 *  @return `YES` if the media manager supports video playback.
 */
- (BOOL)isVideoPlaybackSupported;


/**
 *  Start video playback through `DJIMediaManager`. When the media manager is
 *  playing a video, video data can be received from
 *  `manager:didUpdateVideoPlaybackData:length:forRendering` and playback state
 *  received from `manager:didUpdateVideoPlaybackState`. Video playback through
 *  `DJIMediaManager` is fixed at 720p.
 *  
 *  @param videoMedia The video to play.
 *  @param completion The completion block to receive the command execution result.
 */
- (void)playVideo:(DJIMediaFile *)videoMedia withCompletion:(DJICompletionBlock)completion;


/**
 *  The media manager resumes the paused video.
 *  
 *  @param completion The completion block to receive the command execution result.
 */
- (void)resumeWithCompletion:(DJICompletionBlock)completion;


/**
 *  The media manager pauses the playing video.
 *  
 *  @param completion The completion block to receive the command execution result.
 */
- (void)pauseWithCompletion:(DJICompletionBlock)completion;


/**
 *  The media manager stops the playing video.
 *  
 *  @param completion The completion block to receive the command execution result.
 */
- (void)stopWithCompletion:(DJICompletionBlock)completion;


/**
 *  Video playback is skipped to the new position in seconds from the start of the
 *  video.
 *  
 *  @param position New position to play in seconds from start of video. Input with precision of greater than 3 decimal places, will be rounded to 3.
 *  @param completion The completion block to receive the command execution result.
 */
- (void)moveToPosition:(float)position withCompletion:(DJICompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END
