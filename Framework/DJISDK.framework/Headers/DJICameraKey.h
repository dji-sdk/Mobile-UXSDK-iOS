//
//  DJICameraKey.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import "DJIKey.h"

NS_ASSUME_NONNULL_BEGIN

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Common keys
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraComponent;
EXTERN_KEY NSString *const DJICameraParamDisplayName;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Camera Mode
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamMode;
EXTERN_KEY NSString *const DJICameraParamIsMediaDownloadModeSupported;
EXTERN_KEY NSString *const DJICameraParamIsPlaybackModeSupported;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Shoot Photo
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamShootPhotoMode;
EXTERN_KEY NSString *const DJICameraParamIsPhotoQuickViewSupported;
EXTERN_KEY NSString *const DJICameraParamIsTimeLapseSupported;
EXTERN_KEY NSString *const DJICameraParamStartShootPhoto;
EXTERN_KEY NSString *const DJICameraParamStartShootPhotoWithMode;
EXTERN_KEY NSString *const DJICameraParamStopShootPhoto;
EXTERN_KEY NSString *const DJICameraParamPhotoAspectRatio;
EXTERN_KEY NSString *const DJICameraParamPhotoFileFormat;
EXTERN_KEY NSString *const DJICameraParamPhotoBurstCount;
EXTERN_KEY NSString *const DJICameraParamPhotoRAWBurstCount;
EXTERN_KEY NSString *const DJICameraParamPhotoAEBCount;
EXTERN_KEY NSString *const DJICameraParamCurrentPanoramaPhotoCount;
EXTERN_KEY NSString *const DJICameraParamPhotoTimeIntervalSettings;
EXTERN_KEY NSString *const DJICameraParamPhotoTimeLapseSettings;
EXTERN_KEY NSString *const DJICameraParamPhotoPanoramaMode;
EXTERN_KEY NSString *const DJICameraParamPhotoQuickViewDuration;
EXTERN_KEY NSString *const DJICameraParamIsShootingSinglePhoto;
EXTERN_KEY NSString *const DJICameraParamIsShootingSinglePhotoInRAWFormat;
EXTERN_KEY NSString *const DJICameraParamIsShootingIntervalPhoto;
EXTERN_KEY NSString *const DJICameraParamIsShootingBurstPhoto;
EXTERN_KEY NSString *const DJICameraParamIsShootingRAWBurstPhoto;
EXTERN_KEY NSString *const DJICameraParamIsShootingPanoramaPhoto;
EXTERN_KEY NSString *const DJICameraParamIsStoringPhoto;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Record Video
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamStartRecordVideo;
EXTERN_KEY NSString *const DJICameraParamStopRecordVideo;
EXTERN_KEY NSString *const DJICameraParamVideoResolutionAndFrameRate;
EXTERN_KEY NSString *const DJICameraParamVideoFileFormat;
EXTERN_KEY NSString *const DJICameraParamVideoStandard;
EXTERN_KEY NSString *const DJICameraParamVideoCaptionEnabled;
EXTERN_KEY NSString *const DJICameraParamAntiFlickerFrequency;
EXTERN_KEY NSString *const DJICameraParamVideoFileCompressionStandard;
EXTERN_KEY NSString *const DJICameraParamIsRecording;
EXTERN_KEY NSString *const DJICameraParamCurrentRecordingTimeInSeconds;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Exposure Settings
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamExposureSettings;
EXTERN_KEY NSString *const DJICameraParamExposureMode;
EXTERN_KEY NSString *const DJICameraParamExposureState;
EXTERN_KEY NSString *const DJICameraParamISO;
EXTERN_KEY NSString *const DJICameraParamShutterSpeed;
EXTERN_KEY NSString *const DJICameraParamIsAdjustableApertureSupported;
EXTERN_KEY NSString *const DJICameraParamAperture;
EXTERN_KEY NSString *const DJICameraParamMeteringMode;
EXTERN_KEY NSString *const DJICameraParamSpotMeteringTarget;
EXTERN_KEY NSString *const DJICameraParamExposureCompensation;
EXTERN_KEY NSString *const DJICameraParamAELock;
EXTERN_KEY NSString *const DJICameraParamAutoAEUnlockEnabled;
EXTERN_KEY NSString *const DJICameraParamIsEIModeSupported;
EXTERN_KEY NSString *const DJICameraParamExposureSensitivityMode;
EXTERN_KEY NSString *const DJICameraParamEI;
EXTERN_KEY NSString *const DJICameraParamEIRange;
EXTERN_KEY NSString *const DJICameraParamRecommendedEI;
EXTERN_KEY NSString *const DJICameraParamVideoDewarpingEnabled;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Filters
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamSharpness;
EXTERN_KEY NSString *const DJICameraParamContrast;
EXTERN_KEY NSString *const DJICameraParamSaturation;
EXTERN_KEY NSString *const DJICameraParamColor;
EXTERN_KEY NSString *const DJICameraParamWhiteBalance;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Other settings
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamFileIndexMode;
EXTERN_KEY NSString *const DJICameraParamHDLiveViewEnabled;
EXTERN_KEY NSString *const DJICameraParamOrientation;
EXTERN_KEY NSString *const DJICameraParamDefogEnabled;
EXTERN_KEY NSString *const DJICameraParamVisionStabilizationEnabled;
EXTERN_KEY NSString *const DJICameraParamMediaFileCustomInformation;
EXTERN_KEY NSString *const DJICameraParamPanoOriginalPhotoSettings;
EXTERN_KEY NSString *const DJICameraParamAutoLockGimbalEnabled;
EXTERN_KEY NSString *const DJICameraParamIsLockGimbalDuringShootPhotoSupported;
EXTERN_KEY NSString *const DJICameraParamWatermarkSettings;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Digital zoom
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamIsDigitalZoomSupported;
EXTERN_KEY NSString *const DJICameraParamDigitalZoomFactor;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Optical zoom
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamIsOpticalZoomSupported;
EXTERN_KEY NSString *const DJICameraParamOpticalZoomSpec;
EXTERN_KEY NSString *const DJICameraParamOpticalZoomFocalLength;
EXTERN_KEY NSString *const DJICameraParamOpticalZoomFactor;
EXTERN_KEY NSString *const DJICameraParamStartContinuousOpticalZoom;
EXTERN_KEY NSString *const DJICameraParamStopContinuousOpticalZoom;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - TapZoom
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamTapZoomEnabled;
EXTERN_KEY NSString *const DJICameraParamTapZoomMultiplier;
EXTERN_KEY NSString *const DJICameraParamTapZoomTarget;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Audio
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamIsAudioRecordingSupported;
EXTERN_KEY NSString *const DJICameraParamAudioRecordingEnabled;
EXTERN_KEY NSString *const DJICameraParamAudioGain;
EXTERN_KEY NSString *const DJICameraParamTurnOffFanWhenPossible;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Lens
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamIsInterchangeableLensSupported;
EXTERN_KEY NSString *const DJICameraParamLensInformation;
EXTERN_KEY NSString *const DJICameraParamIsLensMounted;
EXTERN_KEY NSString *const DJICameraParamLensType;
EXTERN_KEY NSString *const DJICameraParamIsLensAFSwitchOn;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Sensor Cleaning
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamSensorCleaningState;
EXTERN_KEY NSString *const DJICameraParamInitSensorCleaningMode;
EXTERN_KEY NSString *const DJICameraParamStartSensorCleaning;
EXTERN_KEY NSString *const DJICameraParamExitSensorCleaningMode;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Focus
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamIsAdjustableFocalPointSupported;
EXTERN_KEY NSString *const DJICameraParamFocusMode;
EXTERN_KEY NSString *const DJICameraParamFocusTarget;
EXTERN_KEY NSString *const DJICameraParamFocusAssistantSettings;
EXTERN_KEY NSString *const DJICameraParamFocusRingValueUpperBound;
EXTERN_KEY NSString *const DJICameraParamFocusRingValue;
EXTERN_KEY NSString *const DJICameraParamLensFocusStatus;
EXTERN_KEY NSString *const DJICameraParamIsFocusAssistantWorking;
EXTERN_KEY NSString *const DJICameraParamIsAFCSupported;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Save/load settings
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamRestoreFactorySettings;
EXTERN_KEY NSString *const DJICameraParamSaveSettings;
EXTERN_KEY NSString *const DJICameraParamLoadSettings;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Thermal camera
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamIsThermalCamera;
EXTERN_KEY NSString *const DJICameraParamThermalROI;
EXTERN_KEY NSString *const DJICameraParamThermalPalette;
EXTERN_KEY NSString *const DJICameraParamThermalScene;
EXTERN_KEY NSString *const DJICameraParamThermalDDE;
EXTERN_KEY NSString *const DJICameraParamThermalACE;
EXTERN_KEY NSString *const DJICameraParamThermalSSO;
EXTERN_KEY NSString *const DJICameraParamThermalBrightness;
EXTERN_KEY NSString *const DJICameraParamThermalContrast;
EXTERN_KEY NSString *const DJICameraParamThermalIsothermEnabled;
EXTERN_KEY NSString *const DJICameraParamThermalIsothermUnit;
EXTERN_KEY NSString *const DJICameraParamThermalIsothermUpperValue;
EXTERN_KEY NSString *const DJICameraParamThermalIsothermMiddleValue;
EXTERN_KEY NSString *const DJICameraParamThermalIsothermLowerValue;
EXTERN_KEY NSString *const DJICameraParamThermalGainMode;
EXTERN_KEY NSString *const DJICameraParamThermalMeasurementMode;
EXTERN_KEY NSString *const DJICameraParamThermalDigitalZoomFactor;
EXTERN_KEY NSString *const DJICameraParamThermalProfile;
EXTERN_KEY NSString *const DJICameraParamThermalSpotMeteringTargetPoint;
EXTERN_KEY NSString *const DJICameraParamThermalSpotMeteringArea;
EXTERN_KEY NSString *const DJICameraParamThermalFFCMode;
EXTERN_KEY NSString *const DJICameraParamThermalTriggerFFC;
EXTERN_KEY NSString *const DJICameraParamThermalCustomExternalSceneSettingsProfile;
EXTERN_KEY NSString *const DJICameraParamThermalAtmosphericTemperature;
EXTERN_KEY NSString *const DJICameraParamThermalAtmosphericTransmissionCoefficient;
EXTERN_KEY NSString *const DJICameraParamThermalBackgroundTemperature;
EXTERN_KEY NSString *const DJICameraParamThermalSceneEmissivity;
EXTERN_KEY NSString *const DJICameraParamThermalWindowReflection;
EXTERN_KEY NSString *const DJICameraParamThermalWindowReflectedTemperature;
EXTERN_KEY NSString *const DJICameraParamThermalWindowTemperature;
EXTERN_KEY NSString *const DJICameraParamThermalWindowTransmissionCoefficient;
EXTERN_KEY NSString *const DJICameraParamThermalAreaTemperatureAggregations;
EXTERN_KEY NSString *const DJICameraParamThermalTemperatureData;
EXTERN_KEY NSString *const DJICameraParamThermalIsOverallTemperatureMeterSupported;
EXTERN_KEY NSString *const DJICameraParamDisplayMode;
EXTERN_KEY NSString *const DJICameraParamPIPPosition;
EXTERN_KEY NSString *const DJICameraParamMSXLevel;
EXTERN_KEY NSString *const DJICameraParamDualFeedVerticalAlignmentOffset;
EXTERN_KEY NSString *const DJICameraParamDualFeedHorizontalAlignmentOffset;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Camera system state
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamIsOverHeated;
EXTERN_KEY NSString *const DJICameraParamHasError;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - SD card
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamFormatSDCard;
EXTERN_KEY NSString *const DJICameraParamSDCardIsInitializing;
EXTERN_KEY NSString *const DJICameraParamSDCardHasError;
EXTERN_KEY NSString *const DJICameraParamSDCardIsReadOnly;
EXTERN_KEY NSString *const DJICameraParamSDCardIsFormatInvalid;
EXTERN_KEY NSString *const DJICameraParamSDCardIsFormatted;
EXTERN_KEY NSString *const DJICameraParamSDCardIsFormatting;
EXTERN_KEY NSString *const DJICameraParamSDCardIsFull;
EXTERN_KEY NSString *const DJICameraParamSDCardIsVerified;
EXTERN_KEY NSString *const DJICameraParamSDCardIsInserted;
EXTERN_KEY NSString *const DJICameraParamSDCardTotalSpaceInMB;
EXTERN_KEY NSString *const DJICameraParamSDCardRemainingSpaceInMB;
EXTERN_KEY NSString *const DJICameraParamSDCardAvailablePhotoCount;
EXTERN_KEY NSString *const DJICameraParamSDCardAvailableRecordingTimeInSeconds;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - SSD
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamIsSSDSupported;
EXTERN_KEY NSString *const DJICameraParamFormatSSD;
EXTERN_KEY NSString *const DJICameraParamSSDVideoResolutionAndFrameRate;
EXTERN_KEY NSString *const DJICameraParamSSDLegacyColor;
EXTERN_KEY NSString *const DJICameraParamSSDVideoLicenses;
EXTERN_KEY NSString *const DJICameraParamSSDRAWLicense;
EXTERN_KEY NSString *const DJICameraParamSSDVideoRecordingEnabled;
EXTERN_KEY NSString *const DJICameraParamSSDOperationState;
EXTERN_KEY NSString *const DJICameraParamSSDIsConnected;
EXTERN_KEY NSString *const DJICameraParamSSDTotalSpace;
EXTERN_KEY NSString *const DJICameraParamSSDAvailableRecordingTimeInSeconds;
EXTERN_KEY NSString *const DJICameraParamSSDRemainingSpaceInMB;
EXTERN_KEY NSString *const DJICameraParamSSDColor;
EXTERN_KEY NSString *const DJICameraParamSSDClipFileName;
EXTERN_KEY NSString *const DJICameraParamRAWPhotoBurstCount;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Storage Location
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamStorageLocation;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Internal Storage
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamIsInternalStorageSupported;
EXTERN_KEY NSString *const DJICameraParamFormatStorage;
EXTERN_KEY NSString *const DJICameraParamInternalStorageOperationState;
EXTERN_KEY NSString *const DJICameraParamInternalStorageRemainingSpaceInMB;
EXTERN_KEY NSString *const DJICameraParamInternalStorageAvailablePhotoCount;
EXTERN_KEY NSString *const DJICameraParamInternalStorageAvailableRecordingTimeInSeconds;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Used by UILib but no public interface
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamPictureStylePreset;
EXTERN_KEY NSString *const DJICameraParamIsVideoHistogramSupported;
EXTERN_KEY NSString *const DJICameraParamVideoHistogramEnabled;
EXTERN_KEY NSString *const DJICameraParamVideoHistogramGraph;
EXTERN_KEY NSString *const DJICameraParamShootPhotoForbiddenFlag;
EXTERN_KEY NSString *const DJICameraParamSDCardOperationState;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Misc
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamAutoTurnOffLEDMode;

////////////////////////////////////////////////////////////////////////////////
#pragma mark - Deprecated
////////////////////////////////////////////////////////////////////////////////
EXTERN_KEY NSString *const DJICameraParamThermalTemperatureDataEnabled; // Deprecated


/**
 *  `DJICameraKey` is an object dedicated to providing access to Camera  related
 *  attributes.
 */
@interface DJICameraKey : DJIKey

@end

NS_ASSUME_NONNULL_END
