//
//  DJIAirLinkKey.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import "DJIKey.h"

NS_ASSUME_NONNULL_BEGIN

EXTERN_KEY NSString *const DJIAirLinkComponent;

EXTERN_KEY NSString *const DJIAirLinkWiFiLinkSubComponent;
EXTERN_KEY NSString *const DJIAirLinkLightbridgeLinkSubComponent;
EXTERN_KEY NSString *const DJIAirLinkOcuSyncLinkSubComponent;

EXTERN_KEY NSString *const DJIAirLinkParamIsWiFiLinkSupported;
EXTERN_KEY NSString *const DJIAirLinkParamIsLightbridgeLinkSupported;
EXTERN_KEY NSString *const DJIAirLinkParamIsOcuSyncLinkSupported;

EXTERN_KEY NSString *const DJIAirLinkParamUplinkSignalQuality;
EXTERN_KEY NSString *const DJIAirLinkParamDownlinkSignalQuality;

//LightBridge
EXTERN_KEY NSString *const DJILightbridgeLinkParamChannelInterference;
EXTERN_KEY NSString *const DJILightbridgeLinkParamChannelSelectionMode;
EXTERN_KEY NSString *const DJILightbridgeLinkParamChannelRange;
EXTERN_KEY NSString *const DJILightbridgeLinkParamChannelNumber;
EXTERN_KEY NSString *const DJILightbridgeLinkParamDataRate;
EXTERN_KEY NSString *const DJILightbridgeLinkParamTransmissionMode;
EXTERN_KEY NSString *const DJILightbridgeLinkParamBandwidthAllocationForLBVideoInputPort;
EXTERN_KEY NSString *const DJILightbridgeLinkParamBandwidthAllocationForHDMIVideoInputPort;
EXTERN_KEY NSString *const DJILightbridgeLinkParamBandwidthAllocationForMainCamera;
EXTERN_KEY NSString *const DJILightbridgeLinkParamBandwidthAllocationForLeftCamera;
EXTERN_KEY NSString *const DJILightbridgeLinkParamIsSecondaryVideoOutputSupported;
EXTERN_KEY NSString *const DJILightbridgeLinkParamSecondaryVideoOutputEnabled;
EXTERN_KEY NSString *const DJILightbridgeLinkParamLiveViewSimultaneousOutputEnabled;
EXTERN_KEY NSString *const DJILightbridgeLinkParamSecondaryVideoOutputPort;
EXTERN_KEY NSString *const DJILightbridgeLinkParamSecondaryVideoDisplayMode;
EXTERN_KEY NSString *const DJILightbridgeLinkParamSecondaryVideoOSDEnabled;
EXTERN_KEY NSString *const DJILightbridgeLinkParamSecondaryVideoOSDTopMargin;
EXTERN_KEY NSString *const DJILightbridgeLinkParamSecondaryVideoOSDLeftMargin;
EXTERN_KEY NSString *const DJILightbridgeLinkParamSecondaryVideoOSDBottomMargin;
EXTERN_KEY NSString *const DJILightbridgeLinkParamSecondaryVideoOSDRightMargin;
EXTERN_KEY NSString *const DJILightbridgeLinkParamSecondaryVideoOSDUnit;
EXTERN_KEY NSString *const DJILightbridgeLinkParamSecondaryVideoOutputFormatForHDMI;
EXTERN_KEY NSString *const DJILightbridgeLinkParamSecondaryVideoOutputFormatForSDI;
EXTERN_KEY NSString *const DJILightbridgeLinkParamSecondaryVideoPIPPosition;
EXTERN_KEY NSString *const DJILightbridgeLinkParamIsDualEncodeModeSupported;
EXTERN_KEY NSString *const DJILightbridgeLinkParamEXTVideoInputPortEnabled;
EXTERN_KEY NSString *const DJILightbridgeLinkParamFrequencyBand;
EXTERN_KEY NSString *const DJILightbridgeLinkParamSupportedFrequencyBands;
EXTERN_KEY NSString *const DJILightbridgeLinkParamRemoteControllerAntennaRSSI;
EXTERN_KEY NSString *const DJILightbridgeLinkParamAircraftAntennaRSSI;

//WiFi
EXTERN_KEY NSString *const DJIWiFiLinkParamChannelInterference;
EXTERN_KEY NSString *const DJIWiFiLinkParamRebootWiFi;
EXTERN_KEY NSString *const DJIWiFiLinkParamSSID;
EXTERN_KEY NSString *const DJIWiFiLinkParamPassword;
EXTERN_KEY NSString *const DJIWiFiLinkParamFrequencyBand;
EXTERN_KEY NSString *const DJIWiFiLinkParamChannelNumber;
EXTERN_KEY NSString *const DJIWiFiLinkParamAvailableChannelNumbers;
EXTERN_KEY NSString *const DJIWiFiLinkParamDataRate;
EXTERN_KEY NSString *const DJIWiFiLinkParamMagneticInterferenceLevel;
EXTERN_KEY NSString *const DJIWiFiLinkParamIsChannelSelectionModeSupported;
EXTERN_KEY NSString *const DJIWiFiLinkParamChannelSelectionMode;


//OcuSync
EXTERN_KEY NSString *const DJIOcuSyncLinkParamChannelInterference;
EXTERN_KEY NSString *const DJIOcuSyncLinkParamChannelSelectionMode;
EXTERN_KEY NSString *const DJIOcuSyncLinkParamChannelBandwidth;
EXTERN_KEY NSString *const DJIOcuSyncLinkParamChannelNumber;
EXTERN_KEY NSString *const DJIOcuSyncLinkParamChannelNumberValidRange;
EXTERN_KEY NSString *const DJIOcuSyncLinkParamVideoDataRate;
EXTERN_KEY NSString *const DJIOcuSyncLinkParamWarningMessages;
EXTERN_KEY NSString *const DJIOcuSyncLinkParamSupportedFrequencyBands;
EXTERN_KEY NSString *const DJIOcuSyncLinkParamFrequencyBand;


/**
 *  `DJIAirLinkKey` provides dedicated access to all communication  to the product
 *  attributes.
 */
@interface DJIAirLinkKey : DJIKey

@end

NS_ASSUME_NONNULL_END
