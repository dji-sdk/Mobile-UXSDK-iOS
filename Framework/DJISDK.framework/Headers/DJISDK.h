//
//  DJISDK.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <UIKit/UIKit.h>


/**
 *  Version number of DJI Mobile SDK.
 */
FOUNDATION_EXPORT double DJISDKVersionNumber;


/**
 *  Version string of DJI Mobile SDK.
 */
FOUNDATION_EXPORT const unsigned char DJISDKVersionString[];

/*********************************************************************************/
#pragma mark - SDK Manager
/*********************************************************************************/
#import <DJISDK/DJISDKManager.h>
#import <DJISDK/DJIBluetoothProductConnector.h>

/*********************************************************************************/
#pragma mark - App Activation
/*********************************************************************************/
#import <DJISDK/DJIAppActivationSystemTypes.h>
#import <DJISDK/DJIAppActivationManager.h>

/*********************************************************************************/
#pragma mark - User Account
/*********************************************************************************/
#import <DJISDK/DJIUserAccountManager.h>

/*********************************************************************************/
#pragma mark - Data Protection
/*********************************************************************************/
#import <DJISDK/DJIDataProtectionManager.h>

/*********************************************************************************/
#pragma mark - LDM
/*********************************************************************************/
#import <DJISDK/DJILDMManager.h>

/*********************************************************************************/
#pragma mark - FlightHub
/*********************************************************************************/
#import <DJISDK/DJIFlightHubManager.h>
#import <DJISDK/DJIFlightHubBaseTypes.h>

/*********************************************************************************/
#pragma mark - Products
/*********************************************************************************/
#import <DJISDK/DJIAircraft.h>
#import <DJISDK/DJIHandheld.h>
#import <DJISDK/DJIBaseProduct.h>



#import <DJISDK/DJIVideoFeeder.h>

/*********************************************************************************/
#pragma mark - Diagnostics
/*********************************************************************************/
#import <DJISDK/DJIDiagnostics.h>

/*********************************************************************************/
#pragma mark - Utility
/*********************************************************************************/
#import <DJISDK/DJIParamCapability.h>
#import <DJISDK/DJIParamCapabilityMinMax.h>

/*********************************************************************************/
#pragma mark - Components
/*********************************************************************************/
//-----------------------------------------------------------------
#pragma mark FlightController
//-----------------------------------------------------------------
#import <DJISDK/DJIFlightController.h>
#import <DJISDK/DJIFlightControllerState.h>
#import <DJISDK/DJILandingGear.h>
#import <DJISDK/DJICompass.h>
#import <DJISDK/DJIFlightAssistant.h>
#import <DJISDK/DJIVisionTypes.h>
#import <DJISDK/DJIIMUState.h>
#import <DJISDK/DJIRTK.h>
#import <DJISDK/DJISimulator.h>
#import <DJISDK/DJICompassCalibrationState.h>
#import <DJISDK/DJILandingGearStructs.h>
#import <DJISDK/DJIFlightControllerBaseTypes.h>
#import <DJISDK/DJISimulatorState.h>
#import <DJISDK/DJIAirSenseSystemInformation.h>
#import <DJISDK/DJIOnboardSDKDevice.h>

//-----------------------------------------------------------------
#pragma mark RemoteController
//-----------------------------------------------------------------
#import <DJISDK/DJIRemoteControllerBaseTypes.h>
#import <DJISDK/DJIRemoteController.h>
#import <DJISDK/DJIMobileRemoteController.h>
#import <DJISDK/DJIRemoteControllerDisplayNames.h>

//-----------------------------------------------------------------
#pragma mark Camera
//-----------------------------------------------------------------
#import <DJISDK/DJICamera.h>
#import <DJISDK/DJICameraSettingsDef.h>
#import <DJISDK/DJICameraPlaybackState.h>
#import <DJISDK/DJICameraSystemState.h>
#import <DJISDK/DJICameraFocusState.h>
#import <DJISDK/DJICameraStorageState.h>
#import <DJISDK/DJICameraSSDState.h>
#import <DJISDK/DJICameraDisplayNames.h>
#import <DJISDK/DJICameraCapabilities.h>
#import <DJISDK/DJIMediaManager.h>
#import <DJISDK/DJIMediaFile.h>
#import <DJISDK/DJIFetchMediaTaskScheduler.h>
#import <DJISDK/DJIPlaybackManager.h>
//-----------------------------------------------------------------
#pragma mark Gimbal
//-----------------------------------------------------------------
#import <DJISDK/DJIGimbalBaseTypes.h>
#import <DJISDK/DJIGimbal.h>
#import <DJISDK/DJIGimbalState.h>
#import <DJISDK/DJIGimbalMovementSettings.h>

//-----------------------------------------------------------------
#pragma mark Battery
//-----------------------------------------------------------------
#import <DJISDK/DJIBattery.h>
#import <DJISDK/DJIBatteryState.h>
//-----------------------------------------------------------------
#pragma mark AirLink
//-----------------------------------------------------------------
#import <DJISDK/DJIAirLink.h>
#import <DJISDK/DJILightbridgeLink.h>
#import <DJISDK/DJIWiFiLink.h>
#import <DJISDK/DJIOcuSyncLink.h>
#import <DJISDK/DJILightbridgeAntennaRSSI.h>
#import <DJISDK/DJIAirLinkBaseTypes.h>
//-----------------------------------------------------------------
#pragma mark Payload
//-----------------------------------------------------------------
#import <DJISDK/DJIPayload.h>
#import <DJISDK/DJIPayloadWidget.h>

//-----------------------------------------------------------------
#pragma mark Handheld Controller
//-----------------------------------------------------------------
#import <DJISDK/DJIHandheldControllerBaseTypes.h>
#import <DJISDK/DJIHandheldController.h>

//-----------------------------------------------------------------
#pragma mark Shared by Components
//-----------------------------------------------------------------
#import <DJISDK/DJIStick.h>

/*********************************************************************************/
#pragma mark - Abstract Classes
/*********************************************************************************/
#import <DJISDK/DJIBaseProduct.h>
#import <DJISDK/DJIBaseComponent.h>

/*********************************************************************************/
#pragma mark - Missions
/*********************************************************************************/
#import <DJISDK/DJIMissionControl.h>
#import <DJISDK/DJIMission.h>

//-----------------------------------------------------------------
#pragma mark Mission Triggers
//-----------------------------------------------------------------
#import <DJISDK/DJIMissionTrigger.h>
#import <DJISDK/DJIAircraftLandedMissionTrigger.h>
#import <DJISDK/DJIBatteryLevelMissionTrigger.h>
#import <DJISDK/DJIWaypointReachedMissionTrigger.h>

//-----------------------------------------------------------------
#pragma mark Mission Actions
//-----------------------------------------------------------------
#import <DJISDK/DJIMissionAction.h>
#import <DJISDK/DJIAircraftYawAction.h>
#import <DJISDK/DJIGimbalAttitudeAction.h>
#import <DJISDK/DJIGoHomeAction.h>
#import <DJISDK/DJIGoToAction.h>
#import <DJISDK/DJIRecordVideoAction.h>
#import <DJISDK/DJIShootPhotoAction.h>
#import <DJISDK/DJITakeOffAction.h>
#import <DJISDK/DJIHotpointAction.h>
#import <DJISDK/DJILandAction.h>

//-----------------------------------------------------------------
#pragma mark Waypoint
//-----------------------------------------------------------------
#import <DJISDK/DJIWaypoint.h>
#import <DJISDK/DJIWaypointMissionTypes.h>
#import <DJISDK/DJIWaypointMission.h>
#import <DJISDK/DJIWaypointMissionOperator.h>
#import <DJISDK/DJIWaypointMission+DJIMissionControlTimelineElement.h>

//-----------------------------------------------------------------
#pragma mark Hotpoint
//-----------------------------------------------------------------
#import <DJISDK/DJIHotpointMission.h>
#import <DJISDK/DJIHotpointMissionTypes.h>
#import <DJISDK/DJIHotpointMissionOperator.h>
#import <DJISDK/DJIHotpointMission+DJIMissionControlTimelineElement.h>

//-----------------------------------------------------------------
#pragma mark FollowMe
//-----------------------------------------------------------------
#import <DJISDK/DJIFollowMeMission.h>
#import <DJISDK/DJIFollowMeMissionOperator.h>
#import <DJISDK/DJIFollowMeMission+DJIMissionControlTimelineElement.h>

//-----------------------------------------------------------------
#pragma mark ActiveTrack
//-----------------------------------------------------------------
#import <DJISDK/DJIActiveTrackMission.h>
#import <DJISDK/DJIActiveTrackMissionOperator.h>

//-----------------------------------------------------------------
#pragma mark TapFly
//-----------------------------------------------------------------
#import <DJISDK/DJITapFlyMission.h>

//-----------------------------------------------------------------
#pragma mark TayFly
//-----------------------------------------------------------------
#import <DJISDK/DJITapFlyMission.h>
#import <DJISDK/DJITapFlyMissionOperator.h>

//-----------------------------------------------------------------
#pragma mark Panorama
//-----------------------------------------------------------------
#import <DJISDK/DJIPanoramaMissionTypes.h>
#import <DJISDK/DJIPanoramaMissionOperator.h>

/*********************************************************************************/
#pragma mark - GEO
/*********************************************************************************/
#import <DJISDK/DJIFlyZoneInformation.h>
#import <DJISDK/DJICustomUnlockZone.h>
#import <DJISDK/DJIUnlockedZoneGroup.h>
#import <DJISDK/DJIFlyZoneManager.h>
/*********************************************************************************/
#pragma mark - Categories
/*********************************************************************************/
#import <DJISDK/NSError+DJISDK.h>

/*********************************************************************************/
#pragma mark - Remote Logger
/*********************************************************************************/
#import <DJISDK/DJIRemoteLogger.h>

/*********************************************************************************/
#pragma mark - AccessLocker
/*********************************************************************************/

#import <DJISDK/DJIAccessLocker.h>
#import <DJISDK/DJIAccessLockerBaseTypes.h>

/*********************************************************************************/
#pragma mark - Accessory Aggregation
/*********************************************************************************/

#import <DJISDK/DJIAccessoryAggregation.h>
#import <DJISDK/DJIAccessoryAggregationState.h>
#import <DJISDK/DJISpotlight.h>
#import <DJISDK/DJIBeacon.h>
#import <DJISDK/DJISpeaker.h>
#import <DJISDK/DJIAudioMediaFile.h>
#import <DJISDK/DJIAccessoryBaseTypes.h>

/*********************************************************************************/
#pragma mark - Keyed Interface
/*********************************************************************************/
#import <DJISDK/DJIKeyManager.h>
#import <DJISDK/DJIKey.h>
#import <DJISDK/DJIKeyedValue.h>
#import <DJISDK/DJIMissionKey.h>
#import <DJISDK/DJIProductKey.h>
#import <DJISDK/DJIBatteryKey.h>
#import <DJISDK/DJICameraKey.h>
#import <DJISDK/DJIGimbalKey.h>
#import <DJISDK/DJIFlightControllerKey.h>
#import <DJISDK/DJIRemoteControllerKey.h>
#import <DJISDK/DJIAirLinkKey.h>
#import <DJISDK/DJIAccessoryKey.h>
#import <DJISDK/DJIPayloadKey.h>
#import <DJISDK/DJIHandheldControllerKey.h>
