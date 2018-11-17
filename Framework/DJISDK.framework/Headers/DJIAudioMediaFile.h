//
//  DJIAudioMediaFile.h
//  DJISDK
//
//  Copyright © 2018 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJISDK.h>
#import <DJISDK/DJIAccessoryBaseTypes.h>


/**
 *  This class represents the information of an audio file in the aircraft. The
 *  audio  file is not accessible if the aircraft is connected to a PC with the USB
 *  port.  For M2E Speaker, it only supports audio files with the following
 *  conditions:  The audio channel is mono. The audio sample rate is 44,100 Hz. The
 *  PCM (Pulse-code modulation)  sample depth is 16 bit per sample. The
 *  `DJIAudioMediaFile` contains  following properties:
 *   - `fileName`
 *   - `durationInSeconds`
 *  - `index`
 *   - `storageLocation`
 */
@interface DJIAudioMediaFile : DJIMediaFile


/**
 *  The storage location to store the file in the aircraft.
 */
@property (nonatomic, readonly) DJIAudioStorageLocation audioStorageLocation;

@end
