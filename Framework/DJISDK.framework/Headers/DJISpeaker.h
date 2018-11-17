//
//  DJISpeaker.h
//  DJISDK
//
//  Copyright © 2018 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJISDK.h>
#import <DJISDK/DJIMediaManager.h>
#import <DJISDK/DJIAccessoryBaseTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIAudioFileInfo;
@class DJISpeaker;
@class DJIAudioMediaFile;
@class DJISpeakerState;


/**
 *  Block to receive the speaker's file list.
 *  
 *  @param state An enum value of `DJIMediaFileListState`.
 */
typedef void (^DJISpeakerFileListStateBlock) (DJIMediaFileListState state);


/**
 *  Block to receive the speaker's state.
 *  
 *  @param state An object of `DJISpeakerState`.
 */
typedef void (^DJISpeakerStateBlock) (DJISpeakerState* state);


/**
 *  State of the speaker accessory.
 */
@interface DJISpeakerState : NSObject


/**
 *  The volume of the speaker to play audio.
 */
@property (nonatomic, readonly) NSUInteger volume;


/**
 *  The audio playing state.
 */
@property (nonatomic, readonly) DJISpeakerPlayingState playingState;


/**
 *  The playing mode of the speaker.
 */
@property (nonatomic, readonly) DJISpeakerPlayMode playingMode;


/**
 *  The index of the audio media file being played. If the speaker is not  playing
 *  any files, -1 will be returned.
 */
@property (nonatomic, readonly) NSInteger playingIndex;


/**
 *  The storage location of the file that is being played by the speaker.
 */
@property (nonatomic, readonly) DJIAudioStorageLocation audioStorageLocation;

@end


/**
 *  The class represents the speaker accessory on the aircraft. Used transmit audio
 *  files and control the speaker.
 */
@interface DJISpeaker : DJIBaseComponent


/**
 *  Current file list state of the speaker.
 */
@property (nonatomic, readonly) DJIMediaFileListState fileListState;


/**
 *  The data transmission state of the speaker.
 */
@property (nonatomic, readonly) DJISpeakerDataTransmissionState dataTransmissionState;


/**
 *  Sets the volume to play audio. The valid range is [0, 100]. 100 means loudest.
 *  
 *  @param volume Volume value to set.
 *  @param completion Completion block to receive the result.
 */
- (void)setVolume:(NSUInteger)volume withCompletion:(DJICompletionBlock)completion;


/**
 *  Sets the play mode of the speaker to control the behavior after finishing
 *  playing a file.
 *  
 *  @param playMode The play mode to set.
 *  @param completion Completion block to receive the result.
 */
- (void)setPlayMode:(DJISpeakerPlayMode)playMode withCompletion:(DJICompletionBlock)completion;


/**
 *  Called when the transmission starts and the aircraft is ready to receive data of
 *  the audio  file from the mobile device.
 */
typedef void (^DJISpeakerTransmissionStartBlock) ();


/**
 *  Called to update the transmission progress. The progress is updated when a chunk
 *  of data is  received successfully by the aircraft.
 *  
 *  @param dataSize The accumulated data size of the audio file received by the aircraft.
 */
typedef void (^DJISpeakerTransmissionOnProgressBlock) (NSInteger dataSize);


/**
 *  Called when the transmission finishes successfully.
 *  
 *  @param index The index assigned by the aircraft for the new audio file.
 */
typedef void (^DJISpeakerTransmissionFinishBlock) (NSInteger index);


/**
 *  Called when the transmission is interrupted by an error.
 *  
 *  @param error The possible error during the transmission.
 */
typedef void (^DJISpeakerTransmissionFailureBlock) (NSError *error);


/**
 *  Starts to send a complete audio file to the aircraft, which can be played by the
 *  speaker.  A transmission session can only be started when the transmission state
 *  is in `DJISpeakerDataTransmissionStateIdle`.  If the transmission is started
 *  successfully, the state will change  to
 *  `DJISpeakerDataTransmissionStateReadyToTransmit`. Then  call `paceData` to send
 *  data to SDK.  Call `markEOF` when all data has been sent to SDK. SDK will
 *  maintain a  buffer to hold all the data and transmit it to the aircraft. For M2E
 *  Speaker, the audio file to transmit  should fulfill the following
 *  configurations:
 *   - The speaker only receives raw PCM(Pulse-code modulation) data of an audio
 *  file,  if the audio file is compressed, PCM extraction is needed before the
 *  transmission.
 *   - The audio channel is mono.
 *   -  The audio sample rate is 44,100 Hz.
 *   - The PCM (Pulse-code modulation) sample  depth is 16 bit per sample.
 *   - The audio file is stored in the aircraft instead  of the speaker.
 *  
 *  @param info The information of the file to transmit. It is also used to determine the  location the file will be stored in the aircraft.
 *  @param startBlock Called when the transmission starts and the aircraft is ready to receive  data of the audio file from the mobile device.
 *  @param progressBlock Called to update the transmission progress. The progress is updated when a  chunk of data is received successfully by the aircraft.
 *  @param finishBlock Called when the transmission finishes successfully.
 *  @param failureBlock Called when the transmission is interrupted by an error.
 */
- (void)startTransmissionWithInfo:(DJIAudioFileInfo *)info
                       startBlock:(DJISpeakerTransmissionStartBlock)startBlock
                       onProgress:(DJISpeakerTransmissionOnProgressBlock)progressBlock
                           finish:(DJISpeakerTransmissionFinishBlock)finishBlock
                          failure:(DJISpeakerTransmissionFailureBlock)failureBlock;


/**
 *  Sends raw PCM data of the audio file to SDK internal logic. The raw PCM data is
 *  the AudioBufferList that will be used to  contain the rendered or provided audio
 *  data. For Mavic 2 Enterprise, the transmission rate is limited to 80kB/s by sdk.
 *  Therefore, SDK will cache the paced data to a local file when the rate of pacing
 *  data is over 80kB/s. The paced data will be appended  to the local file. Call
 *  `markEOF` when all data of the data has been paced to SDK.
 *  
 *  @param data Raw PCM data stream in bytes.
 *  
 *  @return `YES` if data is paced successfully. Otherwise, pacing data is not in the current state or the data size is illegal.
 */
- (BOOL)paceData:(NSData *)data;


/**
 *  Marks EOF (end-of-file). It is used to inform SDK that all data of the file has
 *  been paced. SDK will continue  to transmit data to the aircraft. The state will
 *  change to `DJISpeakerDataTransmissionStateIdle` when all data is transmitted.
 *  After calling this method, `paceData` is invalid until a new transmission
 *  session starts. If no  data is paced before calling this method, the
 *  transmission session will end immediately.
 *  
 *  @return The occurred error if any.
 */
- (NSError *)markEOF;


/**
 *  This will entirely stop the data transfer process and of course clean the
 *  transfer thread pool.
 */
- (void)cancelTransmission;


/**
 *  Starts to play the audio file with the specific index.
 *  
 *  @param fileIndex The file index of the `AudioMediaFile` to play.
 *  @param completion Completion block to receive the result.
 */
- (void)play:(NSUInteger)fileIndex withCompletion:(DJICompletionBlock)completion;


/**
 *  Stops the speaker from playing audio. The method is only valid when  the playing
 *  state is `DJISpeakerPlayingStatePlaying`.
 *  
 *  @param completion Completion block to receive the result.
 */
- (void)stopAudioPlayWithCompletion:(DJICompletionBlock)completion;


/**
 *  Renames the audio file with the specific index. If the operation is started
 *  successfully, FileListState will become `DJIMediaFileListStateRenaming`.
 *  
 *  @param index The index of the audio file to rename.
 *  @param fileName The new file name of the audio file. The file name should not exceed 128 characters.
 *  @param completion Completion block to receive the result.
 */
- (void)rename:(NSString *)fileName index:(NSUInteger)index withCompletion:(DJICompletionBlock)completion;


/**
 *  Returns a copy of the current audio file list from the storage. Returns `null`
 *  if `fileListState` is reset.
 *  
 *  @return An array of `DJIAudioMediaFile` objects.
 */
- (NSArray<DJIAudioMediaFile*> *)fileListSnapshot;


/**
 *  Refresh the audio file list in the aircraft.
 *   - If the current state  is `DJIMediaFileListStateReset`, SDK  will try to fetch
 *  the complete file list.
 *   - If the current state is `DJIMediaFileListStateIncomplete`, SDK  will only
 *  fetch the missing list of files.
 *   - If the operation is started successfully,  the `DJIMediaFileListState`  will
 *  become  `DJIMediaFileListStateSyncing`.
 *   - When the  file list is refreshed successfully, the `DJIMediaFileListState`
 *  will become `DJIMediaFileListStateUpToDate`.
 *  
 *  @param completion Completion block to receive the result.
 */
- (void)refreshFileListWithCompletion:(DJICompletionBlock)completion;


/**
 *  Deletes audio files in the aircraft. If the operation is started successfully,
 *  `fileListState` will  become `DJIMediaFileListStateDeleting`. If there is error
 *  or  "failedFiles" is not empty, `fileListState`  will become
 *  `DJIMediaFileListStateReset`.
 *  
 *  @param fileIndices A list of AudioMediaFile's index.
 *  @param failedFiles Delete failed files.
 *  @param error Error deleting the files.
 *  @param completion Completion block to receive the result.
 */
- (void)deleteFiles:(NSArray<NSNumber*> *)fileIndices withCompletion:(void (^_Nullable)(NSArray<NSNumber*> *_Nonnull failedFiles, NSError *_Nullable error))completion;

#pragma mark - Listener


/**
 *  Adds listener to receive the latest state of the speaker.
 *  
 *  @param listener The listener to receive the state. SDK will add reference count of the listener.  Call `removeSpeakerStateListener` to release the resource.
 *  @param queue The queue to execute the block. Pass NULL to use the default queue.
 *  @param block Block that will be executed when the state is updated.
 */
- (void)addSpeakerStateListener:(id)listener
                      withQueue:(nullable dispatch_queue_t)queue
                       andBlock:(DJISpeakerStateBlock)block;


/**
 *  Removes the listener of the speaker state.
 *  
 *  @param listener The listener to remove.
 */
- (void)removeSpeakerStateListener:(id)listener;


/**
 *  Adds listener to receive the latest file list state of the speaker.
 *  
 *  @param listener The listener to receive the state. SDK will add reference count of the listener.  Call `removeFileListStateListener` to release the resource.
 *  @param queue The queue to execute the block. Pass 'NULL' to use the default queue.
 *  @param block Block that will be executed when the state is updated.
 */
- (void)addFileListStateListener:(id)listener
                       withQueue:(nullable dispatch_queue_t)queue
                        andBlock:(DJISpeakerFileListStateBlock)block;


/**
 *  Removes the listener of the speaker file list state.
 *  
 *  @param listener Listener to be removed.
 */
- (void)removeFileListStateListener:(id)listener;

@end

NS_ASSUME_NONNULL_END
