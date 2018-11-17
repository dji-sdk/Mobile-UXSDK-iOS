//
//  DJIAirLinkBaseTypes.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#ifndef DJIAirLinkBaseTypes_h
#define DJIAirLinkBaseTypes_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  Define the air link maximum supported channel count.
 *  @deprecated See `DJILightbridgeChannelInterference`.
 */
#define DJI_LBAIRLINK_SUPPORTED_CHANNEL_COUNT (8)

/*********************************************************************************/
#pragma mark - WiFiLink
/*********************************************************************************/


/**
 *  WiFi frequency band.
 */
typedef NS_ENUM (uint8_t, DJIWiFiFrequencyBand){


    /**
     *  The WiFi Frequency band is 2.4 GHz.
     */
    DJIWiFiFrequencyBand2Dot4GHz,


    /**
     *  The WiFi Frequency band is 5 GHz.
     */
    DJIWiFiFrequencyBand5GHz,


    /**
     *  Dual frequency band mode. The WiFi frequency band can be either 2.4 GHz or 5
     *  GHz.
     */
    DJIWiFiFrequencyBandDual,


    /**
     *  The WiFi Frequency is unknown.
     */
    DJIWiFiFrequencyBandUnknown = 0xFF,
    
};


/**
 *  WiFi magnetic interference - as measured by Osmo, Phantom 3 4K and Phantom 3
 *  Standard.
 */
typedef NS_ENUM (uint8_t, DJIWiFiMagneticInterferenceLevel) {


    /**
     *  WiFi magnetic interference is low.
     */
    DJIWiFiMagneticInterferenceLevelLow,


    /**
     *  WiFi magnetic interference is medium. At this level, the video quality will be
     *  degraded compared to when the signal quality is low.
     */
    DJIWiFiMagneticInterferenceLevelMedium,


    /**
     *  WiFi magnetic interference is high. At this level, the video quality will be
     *  degraded compared to when the signal quality is medium.
     */
    DJIWiFiMagneticInterferenceLevelHigh,


    /**
     *  WiFi magnetic interference is Unknown.
     */
    DJIWiFiMagneticInterferenceLevelUnknown = 0xFF,
};


/**
 *  WiFi data rate. Lower rates are used for longer ranges, but will have lower
 *  video quality.
 */
typedef NS_ENUM (uint8_t, DJIWiFiDataRate) {


    /**
     *  1 Mbps.
     */
    DJIWiFiDataRate1Mbps = 1,

    /**
     *  2 Mbps.
     */
    DJIWiFiDataRate2Mbps = 2,

    /**
     *  4 Mbps.
     */
    DJIWiFiDataRate4Mbps = 4,

    /**
     *  Unknown.
     */
    DJIWiFiDataRateUnknown = 0xFF,
};


/**
 *  Channel selection mode for WiFi Link.
 */
typedef NS_ENUM (uint8_t, DJIWiFiChannelSelectionMode) {
	

	/**
	 *  WiFi link will automatically select the best physical channel based on the
	 *  signal environment.
	 */
	DJIWiFiChannelSelectionModeAuto,
	

	/**
	 *  Manually select the physical channel.
	 */
	DJIWiFiChannelSelectionModeManual,
	

	/**
	 *  Unknown.
	 */
	DJIWiFiChannelSelectionModeUnknown,
};


/**
 *  The interference power of a WiFi channel.
 */
@interface DJIWiFiChannelInterference : NSObject


/**
 *  The interference power with range from [-60, -100] dBm. A smaller, more negative
 *  value represents less interference and better communication quality.
 */
@property (nonatomic, readonly) NSInteger power;


/**
 *  The channel index.
 */
@property (nonatomic, readonly) NSUInteger channel;


/**
 *  The frequency band that the channel belongs to.
 */
@property (nonatomic, readonly) DJIWiFiFrequencyBand band;

@end

/*********************************************************************************/
#pragma mark - LightbridgeLink
/*********************************************************************************/


/**
 *  The interference power of a LBAirLink channel.
 */
@interface DJILightbridgeChannelInterference : NSObject


/**
 *  The interference power with range from [-60, -100] dBm. A smaller, more negative
 *  value represents less  interference and better communication quality.
 */
@property (nonatomic, readonly) NSInteger power;


/**
 *  The channel number. Different frequency bands have different channel index
 *  ranges.
 */
@property (nonatomic, readonly) NSUInteger channel;

@end


/**
 *  LBAirLink frequency band. Supported only by Phantom 4 Professional.
 */
typedef NS_ENUM (uint8_t, DJILightbridgeFrequencyBand){


    /**
     *  The LBAirLink Frequency band is 2.4 GHz.
     */
    DJILightbridgeFrequencyBand2Dot4GHz,
    

    /**
     *  The LBAirLink Frequency band is 5.7 GHz.
     */
    DJILightbridgeFrequencyBand5Dot7GHz,
    

    /**
     *  The LBAirLink Frequency band is 5.8 GHz.
     */
    DJILightbridgeFrequencyBand5Dot8GHz,
    

    /**
     *  The LBAirLink Frequency is unknown.
     */
    DJILightbridgeFrequencyBandUnknown = 0xFF,
    
};


/*********************************************************************************/
#pragma mark - Data Struct
/*********************************************************************************/


/**
 *  Downlink channel selection mode (manual or automatic) for the wireless link.
 */
typedef NS_ENUM (uint8_t, DJILightbridgeChannelSelectionMode) {


    /**
     *  Air link will automatically select the best physical channel based on the signal
     *  environment.
     */
    DJILightbridgeChannelSelectionModeAuto,


    /**
     *  Manually select the physical channel.
     */
    DJILightbridgeChannelSelectionModeManual,


    /**
     *  Unknown physical channel selection mode.
     */
    DJILightbridgeChannelSelectionModeUnknown,
};


/**
 *  OSD data units.
 */
typedef NS_ENUM (uint8_t, DJILightbridgeSecondaryVideoOSDUnit) {


    /**
     *  Imperial.
     */
    DJILightbridgeSecondaryVideoOSDUnitImperial,


    /**
     *  Metric.
     */
    DJILightbridgeSecondaryVideoOSDUnitMetric,


    /**
     *  Unknown.
     */
    DJILightbridgeSecondaryVideoOSDUnitUnknown,
};


/**
 *  Remote Controller port to which to send secondary video (in addition to USB
 *  video sent to the Mobile Device).
 */
typedef NS_ENUM (uint8_t, DJILightbridgeSecondaryVideoOutputPort) {


    /**
     *  HDMI port.
     */
    DJILightbridgeSecondaryVideoOutputPortHDMI,


    /**
     *  SDI port.
     */
    DJILightbridgeSecondaryVideoOutputPortSDI,


    /**
     *  Unknown.
     */
    DJILightbridgeSecondaryVideoOutputPortUnknown,
};


/**
 *  Defines the combination of video sources to form the secondary output video. The
 *  secondary output can display  video streams from one or two input sources. When
 *  the encode mode is single:</br> Source 1 represents video from  one of the
 *  Source1Only input ports (HDMI or AV).</br> Source 2 represents video from EXT
 *  input port  (HD Gimbal Camera).</br> When the encode mode is dual:</br> Source 1
 *  represents video from HDMI input port.</br>  Source 2 represents video from AV
 *  input port.
 */
typedef NS_ENUM (uint8_t, DJILightbridgeSecondaryVideoDisplayMode) {


    /**
     *  Displays video from Source 1 only. When the current encode mode is single, the
     *  secondary output will display  video from HDMI or AV input. When the current
     *  encode mode is dual, the secondary output will display video from  HDMI input.
     */
    DJILightbridgeSecondaryVideoDisplayModeSource1Only,


    /**
     *  Displays video from Source 2 only. When the current encode mode is single, the
     *  secondary output will display  video from HD Gimbal camera. When the current
     *  encode mode is dual, the secondary output will display video from  AV input.
     */
    DJILightbridgeSecondaryVideoDisplayModeSource2Only,


    /**
     *  Displays the video from Source 1 as the main subject, and the video from Source
     *  2 in a mini window (Picture in  Picture, or PIP).
     */
    DJILightbridgeSecondaryVideoDisplayModePIPSource1Main,


    /**
     *  Displays the video from Source 2 as the main subject, and the video from Source
     *  1 in a mini window (Picture in  Picture, or PIP).
     */
    DJILightbridgeSecondaryVideoDisplayModePIPSource2Main,


    /**
     *  Unknown output mode.
     */
    DJILightbridgeSecondaryVideoDisplayModeUnknown,
};


/**
 *  Secondary output video resolution and frame rate.
 */
typedef NS_ENUM (uint8_t, DJILightbridgeSecondaryVideoFormat) {


    /**
     *  1080I 60FPS.
     */
    DJILightbridgeSecondaryVideoFormat1080I60FPS,


    /**
     *  1080I 50FPS.
     */
    DJILightbridgeSecondaryVideoFormat1080I50FPS,


    /**
     *  1080P 60FPS.
     */
    DJILightbridgeSecondaryVideoFormat1080P60FPS,


    /**
     *  1080P 50FPS.
     */
    DJILightbridgeSecondaryVideoFormat1080P50FPS,


    /**
     *  1080P 30FPS.
     */
    DJILightbridgeSecondaryVideoFormat1080P30FPS,


    /**
     *  1080P 25FPS.
     */
    DJILightbridgeSecondaryVideoFormat1080P25FPS,


    /**
     *  1080P 24FPS.
     */
    DJILightbridgeSecondaryVideoFormat1080P24FPS,


    /**
     *  720P 60FPS.
     */
    DJILightbridgeSecondaryVideoFormat720P60FPS,


    /**
     *  720P 50FPS.
     */
    DJILightbridgeSecondaryVideoFormat720P50FPS,


    /**
     *  720P 30FPS.
     */
    DJILightbridgeSecondaryVideoFormat720P30FPS,


    /**
     *  720P 25FPS.
     */
    DJILightbridgeSecondaryVideoFormat720P25FPS,


    /**
     *  720P 24FPS.
     */
    DJILightbridgeSecondaryVideoFormat720P24FPS,


    /**
     *  Unknown.
     */
    DJILightbridgeSecondaryVideoFormatUnknown,
};


/**
 *  PIP (Picture In Picture) position on the screen relative to the main subject
 *  video.
 */
typedef NS_ENUM (uint8_t, DJILightbridgePIPPosition) {


    /**
     *  PIP is on the screen's top left.
     */
    DJILightbridgePIPPositionTopLeft,


    /**
     *  PIP is on the screen's top right.
     */
    DJILightbridgePIPPositionTopRight,


    /**
     *  PIP is on the screen's bottom left.
     */
    DJILightbridgePIPPositionBottomLeft,


    /**
     *  PIP is on the screen's bottom right.
     */
    DJILightbridgePIPPositionBottomRight,


    /**
     *  Unknown PIP position.
     */
    DJILightbridgePIPPositionUnknown,
};


/**
 *  FPV(First-person view) Video can prioritize either quality or latency.
 */
typedef NS_ENUM (uint8_t, DJILightbridgeTransmissionMode) {


    /**
     *  High quality priority.
     */
    DJILightbridgeTransmissionModeHighQuality,


    /**
     *  Low latency priority.
     */
    DJILightbridgeTransmissionModeLowLatency,


    /**
     *  Unknown.
     */
    DJILightbridgeTransmissionModeUnknown,
};


/**
 *  Wireless downlink data rate. Lower rates are used for longer ranges, but will
 *  have lower video quality.
 */
typedef NS_ENUM (uint8_t, DJILightbridgeDataRate) {


    /**
     *  4 Mbps (Potential range up to 3 km)
     */
    DJILightbridgeDataRate4Mbps,


    /**
     *  6 Mbps (Potential range up to 2 km)
     */
    DJILightbridgeDataRate6Mbps,


    /**
     *  8 Mbps (Potential range up to 1.5 km)
     */
    DJILightbridgeDataRate8Mbps,


    /**
     *  10 Mbps (Potential range up to 0.7 km)
     */
    DJILightbridgeDataRate10Mbps,


    /**
     *  Unknown.
     */
    DJILightbridgeDataRateUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark - OcuSyncLink
/*********************************************************************************/


/**
 *  This class represents the power spectral density of a frequency slice. Only
 *  supported by Mavic Pro.
 */
typedef NS_ENUM (uint8_t, DJIOcuSyncChannelSelectionMode) {


    /**
     *  OcuSync will automatically select the best channel number and bandwidth adapting
     *  to the signal environment.
     */
    DJIOcuSyncChannelSelectionModeAuto,


    /**
     *  Both channel number and bandwidth can be selected manually.
     */
    DJIOcuSyncChannelSelectionModeManual,
    

    /**
     *  Unknown physical channel selection mode.
     */
    DJIOcuSyncChannelSelectionModeUnknown = 0xFF
};



/**
 *  The frequency bands for OcuSync.
 */
typedef NS_ENUM (uint8_t, DJIOcuSyncFrequencyBand){


    /**
     *  The Frequency band is 2.4 GHz.
     */
    DJIOcuSyncFrequencyBand2Dot4GHz,
	

    /**
     *  The Frequency band is 5.8 GHz.
     */
    DJIOcuSyncFrequencyBand5Dot8GHz,
    

    /**
     *  Dual frequency band mode. The frequency band can be either 2.4 GHz or 5 GHz.
     */
    DJIOcuSyncFrequencyBandDual,


    /**
     *  Unknown.
     */
    DJIOcuSyncFrequencyBandUnknown = 0xFF,
    
};


/**
 *  The channel bandwidth for the OcuSync downlink (from the aircraft to the remote
 *  controller). Setting a smaller  bandwidth will reduce the data rate, but make
 *  the connection more robust.
 */
typedef NS_ENUM (uint8_t, DJIOcuSyncBandwidth) {


    /**
     *  The frequency band of the OcuSync link is 20 MHz (up to 46 Mbps).
     */
    DJIOcuSyncBandwidth20MHz,


    /**
     *  The frequency band of the OcuSync link is 10 MHz (up to 23 Mbps).
     */
    DJIOcuSyncBandwidth10MHz,


    /**
     *  Unknown frequency band.
     */
    DJIOcuSyncBandwidthUnknown = 0xFF
};


/**
 *  This class represents the power spectral density of a frequency slice. Only
 *  supported by Mavic Pro.
 */
@interface DJIOcuSyncFrequencyInterference : NSObject


/**
 *  The average interference spectral density of the frequency range. The valid
 *  range is from [-60, -110] dBm/MHz.  A smaller (more negative) value represents
 *  less interference and better communication quality.
 */
@property(nonatomic, readonly) NSInteger powerPerMHz;


/**
 *  The start point of the frequency range in MHz.
 */
@property(nonatomic, readonly) float frequencyStart;


/**
 *  The width of the frequency range in MHz.
 */
@property(nonatomic, readonly) float frequencyWidth;

@end


/**
 *  OcuSync link warning messages.
 */
typedef NS_ENUM (uint8_t, DJIOcuSyncWarningMessage) {


    /**
     *  Warning that interference is high for take-off. When the signal gets weaker as
     *  separation between remote  controller and aircraft get larger, there is a change
     *  the link will fail.
     */
    DJIOcuSyncWarningMessageStrongTakeoffInterference,


    /**
     *  There is strong interference on the downlink signal incident on the remote
     *  controller. If the channel selection  mode
     *  `DJIOcuSyncChannelSelectionModeManual`  is being used, consider changing to
     *  `DJIOcuSyncChannelSelectionModeAuto`  as the OcuSync link can automatically
     *  select  Channel Numbers and bandwidth to mitigate interference on the fly.
     */
    DJIOcuSyncWarningMessageStrongDownlinkInterference,


    /**
     *  There is strong interference on the uplink signal incident on the aircraft.
     */
    DJIOcuSyncWarningMessageStrongUplinkInterference,


    /**
     *  Weak OcuSync signal strength. Be aware of anything blocking the signal between
     *  the remote controller and aircraft,  adjust the orientation of the antennas on
     *  the remote controller, or reduce the distance between remote controller  and
     *  aircraft to increase signal strength.
     */
    DJIOcuSyncWarningMessageWeakSignal,


    /**
     *  The OcuSync link on the aircraft is rebooting.
     */
    DJIOcuSyncWarningMessageAircraftLinkReboot,


    /**
     *  The uplink from the remote controller to the aircraft is broken. Usually if only
     *  the uplink disconnects, it is due  to interference on the aircraft's OcuSync
     *  antennas. Try changing the channel number if the interference source  cannot be
     *  removed.
     */
    DJIOcuSyncWarningMessageUplinkBroken,


    /**
     *  The downlink from the aircraft to the remote controller is broken. Usually if
     *  only the downlink disconnects, it is  due to interference on the remote
     *  controller's OcuSync antennas. Try changing channel number, or reducing the
     *  bandwidth of the channel to make it more robust.
     */
    DJIOcuSyncWarningMessageDownlinkBroken,


    /**
     *  The link between the remote controller and the aircraft is unusable. It is
     *  determined to be unusable if signal is  too weak. Check to see if the antennas
     *  are setup correctly and the path from remote controller to aircraft is
     *  unobstructed.
     */
    DJIOcuSyncWarningMessageLinkUnusable,
};

NS_ASSUME_NONNULL_END

#endif /* DJIAirLinkBaseTypes_h */
