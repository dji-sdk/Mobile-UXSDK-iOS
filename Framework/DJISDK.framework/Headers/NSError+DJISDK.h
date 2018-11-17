//
//  NSError+DJISDK.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*********************************************************************************/
#pragma mark - Error Domains
/*********************************************************************************/


/**
 *  SDK common error domain.
 */
FOUNDATION_EXPORT NSString * _Nonnull const DJISDKErrorDomain;


/**
 *  SDK camera error domain.
 */
FOUNDATION_EXPORT NSString *_Nonnull const DJISDKCameraErrorDomain;


/**
 *  SDK mission error domain.
 */
FOUNDATION_EXPORT NSString *_Nonnull const DJISDKMissionErrorDomain;


/**
 *  SDK battery error domain.
 */
FOUNDATION_EXPORT NSString *_Nonnull const DJISDKBatteryErrorDomain;


/**
 *  SDK gimbal error domain.
 */
FOUNDATION_EXPORT NSString *_Nonnull const DJISDKGimbalErrorDomain;


/**
 *  SDK flight controller domain.
 */
FOUNDATION_EXPORT NSString *_Nonnull const DJISDKFlightControllerErrorDomain;


/**
 *  SDK remote controller domain.
 */
FOUNDATION_EXPORT NSString *_Nonnull const DJISDKRemoteControllerErrorDomain;


/**
 *  SDK registration error domain.
 */
FOUNDATION_EXPORT NSString *_Nonnull const DJISDKRegistrationErrorDomain;


/**
 *  SDK GEO error domain.
 */
FOUNDATION_EXPORT NSString *_Nonnull const DJISDKFlySafeErrorDomain;


/**
 *  SDK FlightHub error domain.
 */
FOUNDATION_EXPORT NSString *_Nonnull const DJISDKFlightHubErrorDomain;


/**
 *  The error domain used to describe errors produced by the `DJITakeOffAction`
 *  object.
 */
FOUNDATION_EXPORT NSString *_Nonnull const DJITakeOffActionErrorDomain;


/**
 *  The error domain used to describe errors produced by the
 *  `DJIAccessoryAggregation` object.
 */
FOUNDATION_EXPORT NSString *_Nonnull const DJIAccessoryAggregationErrorDomain;


/**
 *  The error domain used to describe errors produced by the `DJIAccessLocker`
 *  object.
 */
FOUNDATION_EXPORT NSString *_Nonnull const DJIAccessLockerErrorDomain;

/*********************************************************************************/
#pragma mark DJISDKRegistrationError
/*********************************************************************************/


/**
 *  The Error of SDK Registration.
 */
typedef NS_ENUM (NSInteger, DJISDKRegistrationError){
 

    /**
     *  The application is not able to connect to the Internet the first time it tries
     *  to register the API Key.
     */
    DJISDKRegistrationErrorCouldNotConnectToInternet = -1L,


    /**
     *  The application key you provided is incorrect.
     */
    DJISDKRegistrationErrorInvalidAppKey = -2L,


    /**
     *  The network you are trying to reach is busy, or the server is unreachable.
     */
    DJISDKRegistrationErrorHTTPTimeout = -3L,


    /**
     *  The attempt to copy metadata from another registered device to a device that is
     *  currently connected is not permitted. For example, if a developer has two
     *  devices and the application is activated with the app key on one of the devices
     *  and if the other device is plugged in and tries to register the application,
     *  this error will occur.
     */
    DJISDKRegistrationErrorDeviceDoesNotMatch = -4L,


    /**
     *  The bundle identifier of your application does not match the bundle identifier
     *  you registered on the developer website when you applied to obtain an
     *  application key.
     */
    DJISDKRegistrationErrorBundleIdDoesNotMatch = -5L,


    /**
     *  The application key is prohibited. This occurs when an application key that has
     *  already been released by DJI is revoked. Please contact DJI for assistance.
     */
    DJISDKRegistrationErrorAppKeyProhibited = -6L,


    /**
     *  There is a maximum number of devices one application key can be used to
     *  activate. The maximum number of devices is given when an application is
     *  registered on the DJI developer website. This error will occur if the maximum
     *  number of activations has been reached.
     */
    DJISDKRegistrationErrorMaxActivationCountReached = -7L,


    /**
     *  This error occurs when an application key was given for a specific platform and
     *  is trying to be used to activate an application for another platform. For
     *  instance, if an application key was given for an iOS application and is used to
     *  activate an Android application, this error will occur.
     */
    DJISDKRegistrationErrorAppKeyInvalidPlatformError = -8L,


    /**
     *  The application key does not exist. Please make sure the application key you are
     *  entering is correct.
     */
    DJISDKRegistrationErrorAppKeyDoesNotExist = -9L,


    /**
     *  There are two levels for the SDK framework, level 1 and level 2. If an
     *  application key was given under one level and is trying to be used to active an
     *  application using another level SDK framework, this error will occur.
     */
    DJISDKRegistrationErrorAppKeyLevelNotPermitted = -10L,


    /**
     *  There is a server error. Please contact DJI for assistance.
     */
    DJISDKRegistrationErrorServerParseFailure = -11L,


    /**
     *  There is a server error. Please contact DJI for assistance.
     */
    DJISDKRegistrationErrorServerWriteError = -12L,


    /**
     *  There is a server error. Please contact DJI for assistance.
     */
    DJISDKRegistrationErrorServerDataAbnormal = -13L,


    /**
     *  The activation data received from server is invalid. Please reconnect to the
     *  internet and try again.
     */
    DJISDKRegistrationErrorInvalidMetaData = -14L,


    /**
     *  No application key was provided.
     */
    DJISDKRegistrationErrorEmptyAppKey = -15L,


    /**
     *  Applications under basic develop account could only have the maximum of 20
     *  unique activations.  Visit DJI developer center
     *  <https://developer.dji.com/user/membership/> to upgrade the membership.
     */
	DJISDKRegistrationErrorOverMaxActivationsCount = -16L,


    /**
     *  An unknown error occurred when the application was trying to register. Please
     *  contact DJI for assistance.
     */
    DJISDKRegistrationErrorUnknown = -999L
};

/*********************************************************************************/
#pragma mark DJISDKError
/*********************************************************************************/


/**
 *  DJI SDK Error.
 */
typedef NS_ENUM (NSInteger, DJISDKError){
 

    /**
     *  Feature not supported error.
     */
    DJISDKErrorSDKFeatureNotSupported = -1000L,
 

    /**
     *  Application not activated error.
     */
    DJISDKErrorApplicationNotActivated = -1001L,
 

    /**
     *  SDKLevel not permitted error.
     */
    DJISDKErrorSDKLevelNotPermitted = -1002L,
 

    /**
     *  Timeout error.
     */
    DJISDKErrorTimeout = -1003L,
 

    /**
     *  System busy error.
     */
    DJISDKErrorSystemBusy = -1004L,
 

    /**
     *  Parameters invalid error.
     */
    DJISDKErrorInvalidParameters = -1005L,
 

    /**
     *  Get parameter failed error.
     */
    DJISDKErrorParameterGetFailed = -1006L,
 

    /**
     *  Setting parameters operation failed.
     */
    DJISDKErrorParameterSetFailed = -1007L,
 

    /**
     *  Command execute failed error.
     */
    DJISDKErrorCommandExecutionFailed = -1008L,
 

    /**
     *  Send data failed error.
     */
    DJISDKErrorSendDataFailed = -1009L,
 

    /**
     *  Connection to SDK failed error.
     */
    DJISDKErrorConnectionToSDKFailed = -1010L,
 

    /**
     *  Server data not ready.
     */
    DJISDKErrorServerDataNotReady = -1011L,
 

    /**
     *  Product unknown.
     */
    DJISDKErrorProductUnknown = -1012L,
 

    /**
     *  Product not support.
     */
    DJISDKErrorProductNotSupport = -1013L,
 

    /**
     *  Device not found.
     */
    DJISDKErrorDeviceNotFound = -1014L,
 

    /**
     *  The command is not supported by the current firmware version.
     */
    DJISDKErrorNotSupportedByFirmware = -1015L,
 

    /**
     *  The received data is invalid.
     */
    DJISDKErrorReceivedDataInvalid = -1016L,
 

    /**
     *  No data is received.
     */
    DJISDKErrorNoReceivedData = -1017L,
 

    /**
     *  The Bluetooth is off. Turn it on in iOS settings menu.
     */
    DJISDKErrorBluetoothOff = -1018L,


    /**
     *  Operation is cancelled.
     */
    DJISDKErrorOperationCancelled = -1019L,


    /**
     *  The Internet is not reachable.
     */
    DJISDKErrorInternetNetworkIsNotReachable = -1020L,
    

    /**
     *  Local Data Mode (LDM) is not supported in your context.
     */
    DJISDKErrorLDMIsNotSupported = -1021L,
    

    /**
     *  There are no existing archived logs.
     */
    DJISDKErrorNoExistingArchiveLogs = -1022L,
    

    /**
     *  The pack to send is more than the maximum allowed size.
     */
    DJISDKErrorBeyondMaximumAllowedSize = -1023L,
    

    /**
     *  The current transmission rate already reached the channel's bandwidth. Re-send
     *  data later.
     */
    DJISDKErrorReachChannelBandwidth = -1024L,


    /**
     *  Not defined error.
     */
    DJISDKErrorNotDefined = -1999L,
};

/*********************************************************************************/
#pragma mark DJISDKCameraError
/*********************************************************************************/


/**
 *  DJI SDK Camera Error.
 */
typedef NS_ENUM (NSInteger, DJISDKCameraError){
 

    /**
     *  Not supported command or command not support in this firmware.
     */
    DJISDKCameraErrorFirmwareDoesNotSupportCommand = -3000L,
 

    /**
     *  Camera memory allocation failed error.
     */
    DJISDKCameraErrorMemoryAllocationFailed = -3001L,
 

    /**
     *  Camera busy or command could not execute in current state.
     */
    DJISDKCameraErrorCommandCurrentlyNotEnabled = -3002L,
 

    /**
     *  Camera time not synced.
     */
    DJISDKCameraErrorTimeNotSynced = -3003L,
 

    /**
     *  No SD card.
     */
    DJISDKCameraErrorSDCardNotInserted = -3004L,
 

    /**
     *  SD card full.
     */
    DJISDKCameraErrorSDCardFull = -3005L,
 

    /**
     *  SD card error.
     */
    DJISDKCameraErrorSDCardError = -3006L,
 

    /**
     *  Camera sensor error.
     */
    DJISDKCameraErrorSensorError = -3007L,
 

    /**
     *  Camera system error.
     */
    DJISDKCameraErrorSystemError = -3008L,
 

    /**
     *  The command is not supported by the media file type.
     */
    DJISDKCameraErrorMediaTypeError = -3009L,
 

    /**
     *  The media file is not found in SD card.
     */
    DJISDKCameraErrorNoSuchMediaFile = -3010L,
 

    /**
     *  The command is aborted unexpectedly.
     */
    DJISDKCameraErrorMediaCommandAborted = -3011L,
 

    /**
     *  Data is corrupted during the file transmission.
     */
    DJISDKCameraErrorMediaFileDataCorrupted = -3012L,
 

    /**
     *  The media command is invalid.
     */
    DJISDKCameraErrorInvalidMediaCommand = -3013L,
 

    /**
     *  There is no permission to access the media file.
     */
    DJISDKCameraErrorNoPermission = -3014L,
 

    /**
     *  The download process of DJIPlaybackManager is interrupted.
     */
    DJISDKCameraErrorPlaybackDownloadInterruption = -3015L,
 

    /**
     *  There is no downloading files to stop.
     */
    DJISDKCameraErrorPlaybackNoDownloadingFiles = -3016L,
 

    /**
     *  Error accessing the SSD.
     */
    DJISDKCameraErrorSSDNotInserted = -3017L,

    /**
     *  The Camera's SSD is full.
     */
    DJISDKCameraErrorSSDFull = -3018L,

    /**
     *  Camera has no SSD.
     */
    DJISDKCameraErrorSSDError = -3019L,

    /**
     *  Media file is reset. The operation cannot be executed.
     */
    DJISDKCameraErrorMediaFileReset = -3020L,
};

/*********************************************************************************/
#pragma mark DJISDKFlightControllerError
/*********************************************************************************/


/**
 *  DJI SDK Flight Controller Error.
 */
typedef NS_ENUM (NSInteger, DJISDKFlightControllerError) {
 

    /**
     *  Mode error.
     */
    DJISDKFlightControllerErrorModeError = -4000L,
 

    /**
     *  Aircraft too close to the home point.
     */
    DJISDKFlightControllerErrorNearHomePoint = -4001L,
 

    /**
     *  Aircraft currently running a mission.
     */
    DJISDKFlightControllerErrorRunningMission = -4002L,
 

    /**
     *  Aircraft currently running virtual stick.
     */
    DJISDKFlightControllerErrorRunningVirtualStick = -4003L,
 

    /**
     *  Aircraft not in the air.
     */
    DJISDKFlightControllerErrorAircraftNotInTheAir = -4004L,
 

    /**
     *  Aircraft flight limited.
     */
    DJISDKFlightControllerErrorFlightLimited = -4005L,
 

    /**
     *  GPS level is not high enough to allow flight controller to obtain accurate
     *  location.
     */
    DJISDKFlightControllerErrorGPSSignalWeak = -4006L,
 

    /**
     *  Aircraft low battery.
     */
    DJISDKFlightControllerErrorLowBattery = -4007L,
 

    /**
     *  Aircraft home point not recorded.
     */
    DJISDKFlightControllerErrorHomePointNotRecorded = -4008L,
 

    /**
     *  Aircraft taking off.
     */
    DJISDKFlightControllerErrorTakingOff = -4009L,
 

    /**
     *  Aircraft landing.
     */
    DJISDKFlightControllerErrorLanding = -4010L,
 

    /**
     *  Aircraft going home.
     */
    DJISDKFlightControllerErrorGoingHome = -4011L,
 

    /**
     *  Aircraft starting engine.
     */
    DJISDKFlightControllerErrorStartingEngine = -4012L,
 

    /**
     *  Aircraft in a no fly zone.
     */
    DJISDKFlightControllerErrorInNoFlyZone = -4013L,
 

    /**
     *  Command can not be executed because the motors started.
     */
    DJISDKFlightControllerErrorMotorsStarted = -4013L,
 

    /**
     *  Aircraft could not enter transport mode, since the gimbal is still connected.
     */
    DJISDKFlightControllerErrorGimbalNotRemoved = -4014L,
 

    /**
     *  The aircraft is flying. For safety consideration, the motors could not be shut
     *  down.
     */
    DJISDKFlightControllerErrorCannotTurnOffMotorsWhileAircraftFlying = -4015L,
 

    /**
     *  The new home point is too far.
     */
    DJISDKFlightControllerErrorHomePointTooFar = -4016L,
 

    /**
     *  The new home altitude is too low. (Lower than 20m).
     */
    DJISDKFlightControllerErrorGoHomeAltitudeTooLow = -4017L,
 

    /**
     *  The new home altitude is too high. (higher than 500m).
     */
    DJISDKFlightControllerErrorGoHomeAltitudeTooHigh = -4018L,
 

    /**
     *  The remote controller's mode switch is not in correct mode.
     */
    DJISDKFlightControllerErrorRemoteControllerModeError = -4019L,
 

    /**
     *  The virtual stick control mode is not available.
     */
    DJISDKFlightControllerErrorVirtualStickControlModeError = -4020L,
 

    /**
     *  The aircraft is not at auto landing state.
     */
    DJISDKFlightControllerErrorAircraftNotAutoLanding = -4021L,
 

    /**
     *  The aircraft is not at go home state.
     */
    DJISDKFlightControllerErrorAircraftNotGoingHome = -4022L,
 

    /**
     *  RTK cannot start properly. Please reboot.
     */
    DJISDKFlightControllerErrorRTKCannotStart = -4023L,
 

    /**
     *  Connection between base station and mobile station is broken.
     */
    DJISDKFlightControllerErrorRTKConnectionBroken = -4024L,
 

    /**
     *  RTK base station antenna error. Check if the antenna is connected to the correct
     *  port.
     */
    DJISDKFlightControllerErrorRTKBSAntennaError = -4025L,
 

    /**
     *  RTK base station's coordinate resets.
     */
    DJISDKFlightControllerErrorRTKBSCoordinatesReset = -4026L,
 

    /**
     *  Illegal battery.
     */
    DJISDKFlightControllerErrorIllegalBattery = -4027L,
 

    /**
     *  Aircraft is in tripod mode.
     */
    DJISDKFlightControllerErrorInTripodMode = -4028L,
};

/*********************************************************************************/
#pragma mark DJISDKMissionError
/*********************************************************************************/


/**
 *  DJI SDK Mission Error.
 */
typedef NS_ENUM (NSInteger, DJISDKMissionError){


    /**
     *  Cannot execute in the current mode. For products and flight controller firmware
     *  versions that support 'F' mode (e.g. Phantom 3 Professional, Inspire 1, A3 with
     *  flight controller firmware version lower than 3.2.10.0, etc), please make sure
     *  the remote controller's mode switch is in 'F' mode. For the others, please make
     *  sure the remote controller's mode switch is in 'P' mode.
     */
    DJISDKMissionErrorModeError = -5000L,
 

    /**
     *  The GPS signal of the aircraft is weak.
     */
    DJISDKMissionErrorGPSSignalWeak = -5001L,
 

    /**
     *  Low battery level warning.
     */
    DJISDKMissionErrorAircraftLowBattery = -5002L,
 

    /**
     *  The aircraft is not in the air.
     */
    DJISDKMissionErrorAircraftNotInTheAir = -5003L,
 

    /**
     *  The aircraft's altitude is too high.
     */
    DJISDKMissionErrorAircraftAltitudeTooHigh = -5004L,
 

    /**
     *  The aircraft's altitude is too low.
     */
    DJISDKMissionErrorAircraftAltitudeTooLow = -5005L,
 

    /**
     *  Aircraft is taking off.
     */
    DJISDKMissionErrorAircraftTakingOff = -5006L,
 

    /**
     *  Aircraft is landing.
     */
    DJISDKMissionErrorAircraftLanding = -5007L,
 

    /**
     *  Aircraft is going home.
     */
    DJISDKMissionErrorAircraftGoingHome = -5008L,
 

    /**
     *  Aircraft is starting engine.
     */
    DJISDKMissionErrorAircraftStartingEngine = -5009L,
 

    /**
     *  The home point of the aircraft is not recorded.
     */
    DJISDKMissionErrorAircraftHomePointNotRecorded = -5010L,
 

    /**
     *  Aircraft lost the follow target.
     */
    DJISDKMissionErrorAircraftLostFollowMeTarget = -5011L,
 

    /**
     *  Aircraft is in novice mode.
     */
    DJISDKMissionErrorAircraftInNoviceMode = -5012L,
 

    /**
     *  Aircraft is in a no fly zone.
     */
    DJISDKMissionErrorAircraftInNoFlyZone = -5013L,
 

    /**
     *  The aircraft has reached the flight limitation.
     */
    DJISDKMissionErrorReachFlightLimitation = -5014L,
 

    /**
     *  The aircraft is running a mission.
     */
    DJISDKMissionErrorAircraftRunningMission = -5015L,
 

    /**
     *  Aircraft is not running a mission.
     */
    DJISDKMissionErrorAircraftNoRunningMission = -5016L,
 

    /**
     *  No aircraft mission.
     */
    DJISDKMissionErrorAircraftNoMission = -5017L,
 

    /**
     *  Aircraft is too close to the home point.
     */
    DJISDKMissionErrorAircraftNearHomePoint = -5018L,
 

    /**
     *  Aircraft is too far away from the mission.
     */
    DJISDKMissionErrorAircraftFarAwayMission = -5019L,
 

    /**
     *  The parameters of the mission are invalid.
     */
    DJISDKMissionErrorMissionParametersInvalid = -5020L,
 

    /**
     *  Mission's total distance is too large.
     */
    DJISDKMissionErrorMissionTotalDistanceTooLarge = -5021L,
 

    /**
     *  Mission needs too much time to execute.
     */
    DJISDKMissionErrorMissionNeedTooMuchTime = -5022L,
 

    /**
     *  Mission resume failed.
     */
    DJISDKMissionErrorMissionResumeFailed = -5023L,
 

    /**
     *  Command can not be executed. This is sometimes because commands are sent too
     *  frequently.
     */
    DJISDKMissionErrorCommandCanNotExecute = -5024L,
 

    /**
     *  Aircraft already in command state. Repeating the same command results in this
     *  error.
     */
    DJISDKMissionErrorAircraftAlreadyInCommandState = -5025L,
 

    /**
     *  Mission not prepared.
     */
    DJISDKMissionErrorMissionNotReady = -5026L,
 

    /**
     *  Custom mission step can not be paused.
     */
    DJISDKMissionErrorCustomMissionStepCannotPause = -5027L,
 

    /**
     *  Custom mission is not initialized with the mission steps.  The Steps array is
     *  empty.
     */
    DJISDKMissionErrorCustomMissionStepsNotInitialized = -5028L,
 

    /**
     *  Current mission step is initializing.
     */
    DJISDKMissionErrorCustomMissionStepInitializing = -5029L,
 

    /**
     *  The tracking target is lost.
     */
    DJISDKMissionErrorTrackingTargetLost = -5030L,
 

    /**
     *  No live video feed is captured for the ActiveTrack Mission.
     */
    DJISDKMissionErrorNoVideoFeed = -5031L,
 

    /**
     *  The frame rate of the live video feed is too low.
     */
    DJISDKMissionErrorVideoFrameRateTooLow = -5032L,
 

    /**
     *  The vision system cannot get the authorization to control the aircraft.
     */
    DJISDKMissionErrorVisionSystemNotAuthorized = -5033L,
 

    /**
     *  The vision system encounters system error.
     */
    DJISDKMissionErrorVisionSystemError = -5034L,
 

    /**
     *  The aircraft cannot bypass the obstacle.
     */
    DJISDKMissionErrorCannotBypassObstacle = -5035L,
 

    /**
     *  Mission was stopped by the user.
     */
    DJISDKMissionErrorStoppedByUser = -5036L,
 

    /**
     *  The vision system requires calibration.
     */
    DJISDKMissionErrorVisionSystemNeedsCalibration = -5037L,
 

    /**
     *  The vision sensors are overexposed.
     */
    DJISDKMissionErrorVisionSensorOverexposed = -5038L,
 

    /**
     *  The vision sensors are underexposed.
     */
    DJISDKMissionErrorVisionSensorUnderexposed = -5039L,
 

    /**
     *  The data from the vision system is abnormal.
     */
    DJISDKMissionErrorVisionDataAbnormal = -5040L,
 

    /**
     *  The feature points found by both vision sensors cannot match.
     */
    DJISDKMissionErrorFeaturePointCannotMatch = -5041L,
 

    /**
     *  The tracking rectangle is too small.
     */
    DJISDKMissionErrorTrackingRectTooSmall = -5042L,
 

    /**
     *  The tracking rectangle is too large.
     */
    DJISDKMissionErrorTrackingRectTooLarge = -5043L,
 

    /**
     *  The tracking target doesn't have enough features to lock onto.
     */
    DJISDKMissionErrorTrackingTargetNotEnoughFeatures = -5044L,
 

    /**
     *  The Tracking target is too close to the aircraft.
     */
    DJISDKMissionErrorTrackingTargetTooClose = -5045L,
 

    /**
     *  The tracking target is too far away from the aircraft.
     */
    DJISDKMissionErrorTrackingTargetTooFar = -5046L,
 

    /**
     *  The tracking target is too high.
     */
    DJISDKMissionErrorTrackingTargetTooHigh = -5047L,
 

    /**
     *  The tracking target is shaking too much.
     */
    DJISDKMissionErrorTrackingTargetShaking = -5048L,
 

    /**
     *  The ActiveTrack mission is too unsure the tracking object and confirmation is
     *  required.
     */
    DJISDKMissionErrorTrackingTargetLowConfidence = -5049L,
 

    /**
     *  Mission is paused by user.
     */
    DJISDKMissionErrorTrackingPausedByUser = -5050L,
 

    /**
     *  Gimbal pitch is too low.
     */
    DJISDKMissionErrorGimbalPitchTooLow = -5051L,
 

    /**
     *  Gimbal pitch is too large.
     */
    DJISDKMissionErrorGimbalPitchTooLarge = -5052L,
 

    /**
     *  Encounter an obstacle.
     */
    DJISDKMissionErrorTrackingObstacleDetected = -5053L,
 

    /**
     *  TapFly direction invalid.
     */
    DJISDKMissionErrorTapFlyDirectionInvalid = -5054L,
 

    /**
     *  The front vision system is not available.
     */
    DJISDKMissionErrorVisionSystemNotAvailable = -5055L,
 

    /**
     *  The initialization of the mission failed.
     */
    DJISDKMissionErrorInitializationFailed = -5056L,
 

    /**
     *  Mission can not pause or resume.
     */
    DJISDKMissionErrorCannotPauseOrResume = -5057L,
 

    /**
     *  The aircraft reaches the altitude lower bound of the TapFly Mission.
     */
    DJISDKMissionErrorReachAltitudeLowerBound = -5058L,
 

    /**
     *  RTK's signal is weak.
     */
    DJISDKMissionErrorRTKSignalWeak = -5059L,


    /**
     *  Aircraft's landing gear is deployed.
     */
    DJISDKMissionErrorLandingGearDeployed = -5060L,



    /**
     *  Max Flight speed value provided is invalid
     */
    DJISDKWaypointMissionParameterErrorMaxFlightSpeed = -5100L,


    /**
     *  Auto flight speed value provided is invalid
     */
    DJISDKWaypointMissionParameterErrorAutoFlightSpeed = -5101L,
    

    /**
     *  Repeat time value provided is invalid
     */
    DJISDKWaypointMissionParameterErrorRepeatTime = -5102L,
    

    /**
     *  Waypoint count is invalid
     */
    DJISDKWaypointMissionParameterErrorWaypointCount = -5102L,

    

    /**
     *  Waypoint mission is absent from the operator (upload failed somehow)
     */
    DJISDKWaypointMissionAbsentError = -5110L,
    

    /**
     *  Waypoint coordinate provided is invalid
     */
    DJISDKWaypointParameterErrorCoordinate = -5120L,
    

    /**
     *  Waypoint altitude provided is invalid
     */
    DJISDKWaypointParameterErrorAltitude = -5121L,
    

    /**
     *  Waypoint heading provided is invalid
     */
    DJISDKWaypointParameterErrorHeading = -5122L,
    

    /**
     *  Waypoint repeat time provided is invalid
     */
    DJISDKWaypointParameterErrorActionRepeatTime = -5123L,
    

    /**
     *  Waypoint action timeout provided is invalid
     */
    DJISDKWaypointParameterErrorActionTimeout = -5124L,
    

    /**
     *  Waypoint corner radius provided is invalid
     */
    DJISDKWaypointParameterErrorCornerRadius = -5125L,
    

    /**
     *  Waypoint gimbal pitch provided is invalid
     */
    DJISDKWaypointParameterErrorGimbalPitch = -5126L,
    

    /**
     *  Waypoint speed provided is invalid
     */
    DJISDKWaypointParameterErrorSpeed = -5127L,
    

    /**
     *  Waypoint shoot photo distance provided is invalid
     */
    DJISDKWaypointParameterErrorShootPhotoDistance = -5128L,
    

    /**
     *  Waypoint stay action param provided is invalid
     */
    DJISDKWaypointParameterErrorStayActionParam = -5129L,
    

    /**
     *  Waypoint rotate gimbal action param provided is invalid
     */
    DJISDKWaypointParameterErrorRotateGimbalActionParam = -5130L,
    

    /**
     *  Waypoint rotate aircraft action param provided is invalid
     */
    DJISDKWaypointParameterErrorRotateAircraftActionParam = -5131L,
    
    
};
/*********************************************************************************/
#pragma mark GEO Error
/*********************************************************************************/


/**
 *  DJI SDK GEO Error.
 */
typedef NS_ENUM(NSInteger, DJISDKFlySafeError){
 

    /**
     *  User is not logged in.
     */
    DJISDKFlySafeErrorNotLoggedIn = -6001L,
 

    /**
     *  The operation is cancelled.
     */
    DJISDKFlySafeErrorOperationCancelled = -6002L,
 

    /**
     *  Aircraft's location is not available.
     */
    DJISDKFlySafeErrorAircraftLocationNotAvailable = -6003L,
 

    /**
     *  Aircraft's serial number is not available.
     */
    DJISDKFlySafeErrorAircraftSerialNumberNotAvailable = -6004L,
 

    /**
     *  The token is invalid.
     */
    DJISDKFlySafeErrorInvalidToken = -6005L,
 

    /**
     *  User is not authorized.
     */
    DJISDKFlySafeErrorNotAuthorized = -6006L,
 

    /**
     *  Data returned by server is invalid.
     */
    DJISDKFlySafeErrorInvalidServerData = -6007L,
 

    /**
     *  The system is still initializing.
     */
    DJISDKFlySafeErrorInitializationNotFinished = -6008L,
 

    /**
     *  Aircraft's location does not support GEO.
     */
    DJISDKFlySafeErrorNotSupportGEO = -6009L,
 

    /**
     *  This area is not eligible for unlocking.
     */
    DJISDKFlySafeErrorAreaNotEligibleUnlock = -6010L,
 

    /**
     *  The simulated aircraft location is not valid. During the simulation, a location
     *  is valid if it is within 50km of (37.460484, -122.115312).
     */
    DJISDKFlySafeErrorInvalidSimulatedLocation = -6011L,
    

    /**
     *  The Account login is out of date, Need login again.
     */
    DJISDKFlySafeErrorTokenOutOfDate = -6012L,
};

/*********************************************************************************/
#pragma mark FlightHub Error
/*********************************************************************************/


/**
 *  DJI SDK FlightHub Error.
 */
typedef NS_ENUM(NSInteger, DJISDKFlightHubError){

	/**
	 *  Server rejected the request because the signature is invalid.
	 */
	DJISDKFlightHubErrorSignatureInvalid = -7001L,

	/**
	 *  Server rejected the request because the user does not have the permission.
	 */
	DJISDKFlightHubErrorNoRightToAccess = -7002L,

	/**
	 *  Invalid parameter(s).
	 */
	DJISDKFlightHubErrorParametersInvalid = -7003L,

	/**
	 *  No authorization information found.
	 */
	DJISDKFlightHubErrorNoAuthorizationInformationFound = -7004L,

	/**
	 *  The account information is not found.
	 */
	DJISDKFlightHubErrorUserNotFoundInUserCenter = -7005L,

	/**
	 *  Authorization information has expired. Please authorize again.
	 */
	DJISDKFlightHubErrorAuthorizationExpired = -7006L,

	/**
	 *  User not found in DJI FlightHub system.
	 */
	DJISDKFlightHubErrorUserNotFoundInFlightHub = -7007L,

	/**
	 *  The service package has been expired.
	 */
	DJISDKFlightHubErrorServicePackageExpired = -7008L,

	/**
	 *  The service package has reached the limit of device numbers.
	 */
	DJISDKFlightHubErrorServicePackageLimitationReached = -7009L,

	/**
	 *  The service package does not have permission to access SDK service.
	 */
	DJISDKFlightHubErrorUserHasNoSDKPermissionForServicePackage = -7010L,

	/**
	 *  No team found.
	 */
	DJISDKFlightHubErrorNoTeamFound = -7011L,

	/**
	 *  No aircraft found.
	 */
	DJISDKFlightHubErrorNoAircraftFound = -7012L,

	/**
	 *  The aircraft has already been bound in the chosen team.
	 */
	DJISDKFlightHubErrorAircraftAlreadyBoundInTeamChosen = -7013L,

	/**
	 *  No record found.
	 */
	DJISDKFlightHubErrorNoRecordFound = -7014L,

	/**
	 *  No user is logged in.
	 */
	DJISDKFlightHubErrorNotLoggedIn = -7015L,

	/**
	 *  Aircraft's serial number is not available.
	 */
	DJISDKFlightHubErrorAircraftSerialNumberNotAvailable = -7016L,

	/**
	 *  The aircraft has already been bound in the other team. Please unbind it first.
	 */
	DJISDKFlightHubErrorAircraftAlreadyBoundInTeamChosenInOtherTeam = -7017L,

	/**
	 *  Bound device number has reached the limit of your service package.
	 */
	DJISDKFlightHubErrorBoundDeviceLimitationReached = -7018L,
};

/*********************************************************************************/
#pragma mark Take-off Action Error
/*********************************************************************************/

/**
 *  Error codes for errors specific to `DJITakeOffActionErrorDomain`.
 */
typedef NS_ENUM(NSInteger, DJITakeOffActionError) {

    /**
     *  Motors should be off before Take-off action is executed.
     */
    DJITakeOffActionErrorMotorsAlreadyOn = 100,


    /**
     *  Unknown.
     */
    DJITakeOffActionErrorUnknown = -1,
};


/*********************************************************************************/
#pragma mark Upgrade Error
/*********************************************************************************/

//hidden-WM245
/**
 *  DJI SDK Upgrade Error.
 */
typedef NS_ENUM(NSInteger, DJISDKUpgradeError){
	//hidden-WM245
	/**
	 *	固件已经下载，不需要再重复下载
	 */
	DJISDKUpgradeErrorFirmwareAlreadyDownloaded = -10001L,

	//hidden-WM245
	/**
	 *	固件已经下载，不需要再重复下载
	 */
	DJISDKUpgradeErrorFirmwareDownloadFailed = -10002L,
	
	//hidden-WM245
	/**
	 *	固件传输失败。
	 */
	DJISDKUpgradeErrorFirmwareFirmwareTransferFailed = -10003L,
	
	//hidden-WM245
	/**
	 *	固件传入取消
	 */
	DJISDKUpgradeErrorFirmwareFirmwareTransferCanceled = -10004L,
	
	//hidden-WM245
	/**
	 *	固件版本号不一致
	 */
	DJISDKUpgradeErrorFirmwareFirmwareVersionNotSame = -10005L,
	
    //hidden-WM245
    /**
     *  需要直连飞机才允许升级
     */
    DJISDKUpgradeErrorAircraftNeedDirectConnected = -10006L,
    
    //hidden-WM245
    /**
     *  当前飞机电池电量过低
     */
    DJISDKUpgradeErrorAircraftLowElectricityNow = -10007L,
    
    //hidden-WM245
    /**
     * 当前遥控器电池电量过低
     */
    DJISDKUpgradeErrorRCLowElectricityNow = -10008L,
    
    //hidden-WM245
    /**
     *  电机处于起桨状态
     */
    DJISDKUpgradeErrorDeviceMotorOn = -10009L,
    
	//hidden-WM245
	/**
	 *	Unknown Error
	 */
	DJISDKUpgradeErrorUnknown = -11000L,
};

/*********************************************************************************/
#pragma mark Accessory Error
/*********************************************************************************/


/**
 *  Errors related to accessories on the aircraft (e.g. spotlights, speakers).
 */
typedef NS_ENUM(NSInteger, DJIAccessoryAggregationError) {

    /**
     *  The accessory is not connected. Also update the implementation.
     */
    DJIAccessoryAggregationErrorNotConnected = -8000L,

    /**
     *  The file name exceeds the maximum length (20 characters).
     */
    DJIAccessoryAggregationErrorFileNameLengthInvalid = -8001L,

    /**
     *  The file name is already taken in the aircraft. Choose a different file name.
     */
    DJIAccessoryAggregationErrorFileNameDuplicated = -8002L,

    /**
     *  A file name cannot be empty.
     */
    DJIAccessoryAggregationErrorFileNameEmpty = -8003L,

    /**
     *  The file does not exist in the aircraft.
     */
    DJIAccessoryAggregationErrorFileNotExist = -8004L,

    /**
     *  An error occurs when creating the file.
     */
    DJIAccessoryAggregationErrorFileCreated = -8005L,

    /**
     *  There is no more file index available for the file.
     */
    DJIAccessoryAggregationErrorFileIndexUnavailable = -8006L,

    /**
     *  Error occurs when renaming the file.
     */
    DJIAccessoryAggregationErrorRenameFile = -8007L,

    /**
     *  The connection of the speaker is broken and data transmission cannot start.
     */
    DJIAccessoryAggregationErrorDataTransmissionDisconnection = -8008L,

    /**
     *  The data transimission operation cannot be executed in the current state.
     */
    DJIAccessoryAggregationErrorWrongDataTransmissionState = -8009L,

    /**
     *  Data validation failed. Data is corrupted during the transmission.
     */
    DJIAccessoryAggregationErrorDataCorruption = -8010L,

    /**
     *  The ongoing data transmission is cancelled.
     */
    DJIAccessoryAggregationErrorCancelledByUser = -8011L,

    /**
     *  The ongoing data transmission is interrupted by timeout error.
     */
    DJIAccessoryAggregationErrorInterruptedByTimeout = -8012L,

    /**
     *  The storage is full.
     */
    DJIAccessoryAggregationErrorStorageFull = -8013L,
};

/*********************************************************************************/
#pragma mark AccessLocker Error
/*********************************************************************************/


/**
 *  Errors related to the access locker.
 */
typedef NS_ENUM(NSInteger, DJIAccessLockerError) {

    /**
     *  The command is not valid in current state.
     */
    DJIAccessLockerErrorInvalidState = -9000L,

    /**
     *  Write failure when updating data in the firmware.
     */
    DJIAccessLockerErrorFirmwareWrite = -9001L,

    /**
     *  Read failure when accessing data in the firmware.
     */
    DJIAccessLockerErrorFirmwareRead = -9002L,

    /**
     *  The Security Code is incorrect.
     */
    DJIAccessLockerErrorSecurityCodeIncorrect = -9003L,

    /**
     *  The user account is not set up for the security feature yet.
     */
    DJIAccessLockerErrorNotSetUp = -9004L,

    /**
     *  The aircraft is already unlocked.
     */
    DJIAccessLockerErrorAlreadyUnlocked = -9005L,

    /**
     *  Attempt with wrong Security Code more than 5 times. The aircraft is  disable and
     *  try again in 1 minute.
     */
    DJIAccessLockerErrorSecurityCodeIncorrectFiveTimes = -9006L,

    /**
     *  Attempt with wrong Security Code more than 20 times. The aircraft is disable and
     *  try again in 24 hours.
     */
    DJIAccessLockerErrorSecurityCodeIncorrectTwentyTimes = -9007L,

    /**
     *  The username does not exist.
     */
    DJIAccessLockerErrorUsernameNotExist = -9008L,

    /**
     *  The new security code is not valid. A valid security code should contain only
     *  numbers and letters and  its length is not less than 4 characters and not longer
     *  than 8 characters.
     */
    DJIAccessLockerErrorSecurityCodeFormatInvalid = -9009L,
};


/**
 *  NSError's DJISDK category. It contains methods to create custom NSErrors.
 */
@interface NSError (DJISDK)


/**
 *  Get DJISDKError.
 *  
 *  @param errorCode errorCode for `DJISDKError`.
 *  
 *  @return An NSError object initialized with errorCode. If the errorCode was 0, returns nil.
 */
+ (_Nullable instancetype)DJISDKErrorForCode:(NSInteger)errorCode;


/**
 *  Get DJISDKCameraError.
 *  
 *  @param errorCode errorCode for `DJISDKCameraError`.
 *  
 *  @return An NSError object initialized with errorCode. If the errorCode was 0, returns nil.
 */
+ (_Nullable instancetype)DJISDKCameraErrorForCode:(NSInteger)errorCode;


/**
 *  Get DJISDKFlightControllerError.
 *  
 *  @param errorCode errorCode for `DJISDKFlightControllerError`.
 *  
 *  @return An NSError object initialized with errorCode. If the errorCode was 0, returns nil.
 */
+ (_Nullable instancetype)DJISDKFlightControllerErrorForCode:(NSInteger)errorCode;


/**
 *  Get DJISDKMissionError.
 *  
 *  @param errorCode errorCode for `DJISDKMissionError`.
 *  
 *  @return An NSError object initialized with errorCode. If the errorCode was 0, returns nil.
 */
+ (_Nullable instancetype)DJISDKMissionErrorForCode:(NSInteger)errorCode;


/**
 *  Get DJISDKRegistrationError.
 *  
 *  @param errorCode errorCode for `DJISDKRegistrationError`.
 *  
 *  @return An NSError object initialized with errorCode. If the errorCode was 0, returns nil.
 */
+ (_Nullable instancetype)DJISDKRegistrationErrorForCode:(DJISDKRegistrationError)errorCode;


/**
 *  Get DJISDKFlySafeError.
 *  
 *  @param errorCode errorCode for `DJISDKFlySafeError`.
 *  
 *  @return An NSError object initialized with errorCode. If the errorCode was 0, returns nil.
 */
+ (_Nullable instancetype)DJISDKFlySafeErrorForCode:(DJISDKFlySafeError)errorCode;


/**
 *  Returns the specific error in the `DJISDKFlightHubError` according to the error
 *  code.
 *  
 *  @param errorCode errorCode for `DJISDKFlightHubError`.
 *  
 *  @return An NSError object initialized with errorCode. If the errorCode was 0, returns nil.
 */
+ (_Nullable instancetype)DJISDKFlightHubErrorForCode:(DJISDKFlightHubError)errorCode;


/**
 *  Get DJIAccessoryAggregationError.
 *  
 *  @param errorCode errorCode for `DJIAccessoryAggregationError`.
 *  
 *  @return An NSError object initialized with errorCode. If the errorCode was 0, returns nil.
 */
+ (_Nullable instancetype)DJIAccessoryAggregationErrorForCode:(DJIAccessoryAggregationError)errorCode;


/**
 *  Get DJIAccessoryAggregationError.
 *  
 *  @param errorCode errorCode for `DJIAccessoryAggregationError`.
 *  
 *  @return An NSError object initialized with errorCode. If the errorCode was 0, returns nil.
 */
+ (_Nullable instancetype)DJIAccessLockerErrorForCode:(DJIAccessLockerError)errorCode;


/**
 *  Get DJISDKError.
 *  
 *  @param errorCode Error code for `DJISDKError`.
 *  @param errorDomain Domain for `DJISDKError`.
 *  @param desc Description for `DJISDKError`.
 *  
 *  @return An NSError object initialized with errorCode, errorDomain and desc.
 */
+ (_Nullable instancetype)DJISDKErrorForCode:(NSInteger)errorCode domain:(NSString *_Nonnull)errorDomain desc:(const NSString *_Nonnull)desc;

@end

NS_ASSUME_NONNULL_END
