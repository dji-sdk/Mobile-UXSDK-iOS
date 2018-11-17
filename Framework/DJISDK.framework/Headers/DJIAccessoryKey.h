//
//  DJIAccessoryKey.h
//  DJISDK
//
//  Copyright © 2018 DJI. All rights reserved.
//

#import "DJIKey.h"

NS_ASSUME_NONNULL_BEGIN

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Component
////////////////////////////////////////////////////////////////////////////////

EXTERN_KEY NSString *const DJIAccessoryAggregationComponent;
EXTERN_KEY NSString *const DJIAccessoryParamBeaconSubComponent;
EXTERN_KEY NSString *const DJIAccessoryParamSpotlightSubComponent;
EXTERN_KEY NSString *const DJIAccessoryParamSpeakerSubComponent;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Spotlight
////////////////////////////////////////////////////////////////////////////////

EXTERN_KEY NSString *const DJIAccessoryParamBrightness;
EXTERN_KEY NSString *const DJIAccessoryParamBrightnessRange;
EXTERN_KEY NSString *const DJIAccessoryParamTemperature;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Beacon
////////////////////////////////////////////////////////////////////////////////

EXTERN_KEY NSString *const DJIAccessoryParamFlashingFrequency;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Speaker
////////////////////////////////////////////////////////////////////////////////

EXTERN_KEY NSString *const DJIAccessoryParamPlayingIndex;
EXTERN_KEY NSString *const DJIAccessoryParamVolume;
EXTERN_KEY NSString *const DJIAccessoryParamVolumeRange;
EXTERN_KEY NSString *const DJIAccessoryParamPlayMode;
EXTERN_KEY NSString *const DJIAccessoryParamPlayingAudioStorageType;
EXTERN_KEY NSString *const DJIAccessoryParamRename;
EXTERN_KEY NSString *const DJIAccessoryParamPlay;
EXTERN_KEY NSString *const DJIAccessoryParamStopAudioPlay;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Common
////////////////////////////////////////////////////////////////////////////////

EXTERN_KEY NSString *const DJIAccessoryParamEnabled;
EXTERN_KEY NSString *const DJIAccessoryParamIsConnected;


/**
 *  `DJIAccessoryKey` provides dedicated access to Accessories related attributes.
 */
@interface DJIAccessoryKey : DJIKey

@end

NS_ASSUME_NONNULL_END
