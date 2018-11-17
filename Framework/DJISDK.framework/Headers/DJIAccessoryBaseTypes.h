//
//  DJIAccessoryBaseTypes.h
//
//  Copyright © 2018 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


/**
 *  Storage types of audio files. The storage types will determine the strategy of
 *  the aircraft to keep the file.
 */
typedef NS_ENUM(uint8_t, DJIAudioStorageLocation) {

    /**
     *  The audio file is stored to a temporary space. Files with temporary storage
     *  location will be automatically deleted when the aircraft reboots.
     */
    DJIAudioStorageLocationTemporary,

    /**
     *  The audio file is stored to a persistent space. Files with persistent storage
     *  location should be deleted manually by calling `deleteFiles:withCompletion`.
     */
    DJIAudioStorageLocationPersistent,

    /**
     *  Unknown.
     */
    DJIAudioStorageLocationUnknown = 0xFF,
};


/**
 *  The class contains the basic information of an audio file.
 */
@interface DJIAudioFileInfo : NSObject


/**
 *  The file name of the audio file. The aircraft will store the audio file with
 *  this file name.
 */
@property (nonatomic, copy) NSString *fileName;


/**
 *  The storage type of the audio file. The storage types will determine the
 *  strategy of  the aircraft to keep the file.
 */
@property (nonatomic) DJIAudioStorageLocation storageLocation;

@end


/**
 *  The speaker's play mode. It determines the behavior of the speaker when it
 *  finishes playing a file.
 */
typedef NS_ENUM(uint8_t, DJISpeakerPlayMode) {

    /**
     *  The speaker will play the selected file once. The speaker will stop playing
     *  after  finishing playing the file.
     */
    DJISpeakerPlayModeSingleOnce,

    /**
     *  The speaker will play the selected file repeatedly.
     */
    DJISpeakerPlayModeRepeatSingle,

    /**
     *  Unknown.
     */
    DJISpeakerPlayModeUnknown = 0xFF,
};


/**
 *  The speaker's Playing State.
 */
typedef NS_ENUM(uint8_t, DJISpeakerPlayingState) {

    /**
     *  The speaker is playing the voice.
     */
    DJISpeakerPlayingStatePlaying,

    /**
     *  The speaker is stopped and playing nothing.
     */
    DJISpeakerPlayingStateStopped,

    /**
     *  Unknown.
     */
    DJISpeakerPlayingStateUnknown = 0xFF,
};


/**
 *  Data transmission state of the speaker.
 */
typedef NS_ENUM(uint8_t, DJISpeakerDataTransmissionState) {

    /**
     *  The speaker is in idle state and is ready for receiving data from the mobile
     *  device.  Call `startTransmissionWithInfo:startBlock:onProgress:finish:failure`
     *  to start the data transmission.
     */
    DJISpeakerDataTransmissionStateIdle,

    /**
     *  The data transmission from the mobile device to the speaker is started.  Call
     *  `paceData` to transmit data.
     */
    DJISpeakerDataTransmissionStateReadyToTransmit,

    /**
     *  The mobile device is transmitting data to the speaker.
     */
    DJISpeakerDataTransmissionStateTransmitting,

    /**
     *  Unknown state, either the speaker is disconnected or not recognized.
     */
    DJISpeakerDataTransmissionStateUnknown = 0xFF,
};

NS_ASSUME_NONNULL_END
