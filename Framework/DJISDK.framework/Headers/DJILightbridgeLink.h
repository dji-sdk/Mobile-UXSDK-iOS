//
//  DJILightbridgeLink.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <DJISDK/DJIAirLinkBaseTypes.h>
#import <DJISDK/DJIBaseProduct.h>
#import <DJISDK/DJISDKFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@class DJILightbridgeLink;
@class DJILightbridgeAntennaRSSI;
@class DJILightbridgeChannelInterference;

/*********************************************************************************/
#pragma mark - DJILBAirLinkDelegate
/*********************************************************************************/


/**
 *  This protocol provides delegate methods to receive updated signal information
 *  for channels and updated video data  from Lightbridge 2.
 */
@protocol DJILightbridgeLinkDelegate <NSObject>

@optional


/**
 *  Signal quality and strength information for current uplink channel on each
 *  Remote Controller antenna.
 *  
 *  @param lightbridgeLink An `DJILightbridgeLink` instance.
 *  @param rssi An `DJILightbridgeAntennaRSSI` instance.
 */
- (void)lightbridgeLink:(DJILightbridgeLink *_Nonnull)lightbridgeLink didUpdateRemoteControllerAntennaRSSI:(DJILightbridgeAntennaRSSI * _Nonnull)rssi;


/**
 *  Signal quality and strength information for current downlink channel on each air
 *  link module antenna.
 *  
 *  @param lightbridgeLink An `DJILightbridgeLink` instance.
 *  @param rssi An `DJILightbridgeAntennaRSSI` instance.
 */
- (void)lightbridgeLink:(DJILightbridgeLink *_Nonnull)lightbridgeLink didUpdateAircraftAntennaRSSI:(DJILightbridgeAntennaRSSI * _Nonnull)rssi;


/**
 *  Signal strength of all signals present on all available downlink channels.
 *  Signals  that are not the communication signal are considered interference.
 *  
 *  @param lightbridgeLink `DJILightbridgeLink` instance.
 *  @param interference The updated interference information. The elements in the array  of 'DJILBAirLinkChannelInterference' objects each hold the interference signal  strength of a channel. Elements are sorted by increasing channel number.
 */
-(void) lightbridgeLink:(DJILightbridgeLink *)lightbridgeLink didUpdateChannelInterference:(NSArray <DJILightbridgeChannelInterference *> *)interference;

@end

/*********************************************************************************/
#pragma mark - DJILightbridgeLink
/*********************************************************************************/


/**
 *  This class contains methods to change settings of the Lightbridge Air Link.
 */
@interface DJILightbridgeLink : NSObject


/**
 *  Returns the DJILBAirLink delegate.
 */
@property(nonatomic, weak) id<DJILightbridgeLinkDelegate> delegate;


/**
 *  Sets the downlink channel selection mode (automatic or manual).
 *  
 *  @param mode Channel selection mode for the air link.
 *  @param completion Completion block.
 */
- (void)setChannelSelectionMode:(DJILightbridgeChannelSelectionMode)mode
                 withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the downlink channel selection mode.
 *  
 *  @param mode The DJILBAirLinkChannelSelectionMode object.
 *  @param error Error retrieving the value.
 *  @param completion Completion block.
 */
- (void)getChannelSelectionModeWithCompletion:(void (^_Nonnull)(DJILightbridgeChannelSelectionMode mode,
                                                                NSError *_Nullable error))completion;


/**
 *  Gets the channels available for the current frequency band.
 *  
 *  @param channelRange The channel range.
 *  @param error Error retrieving the value.
 *  @param completion Completion block.
 */
- (void)getChannelRangeWithCompletion:(void (^_Nonnull)(NSRange channelRange,
                                                        NSError *_Nullable error))completion;


/**
 *  Sets the fixed downlink channel. Channel selection mode should be set  to
 *  `DJILightbridgeChannelSelectionModeManual`. The valid range  of channel can be
 *  obtained from `getChannelRangeWithCompletion`.
 *  
 *  @param channelNumber Specific channel for the air link.
 *  @param completion Completion block.
 */
- (void)setChannelNumber:(int)channelNumber withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets current downlink channel of air link.
 *  
 *  @param channelNumber The channel number.
 *  @param error Error retrieving the value.
 *  @param completion Completion block.
 */
- (void)getChannelNumberWithCompletion:(void (^_Nonnull)(int channelNumber,
                                                         NSError *_Nullable error))completion;


/**
 *  Sets the downlink data rate (throughput). Higher data rates increase the quality
 *  of video transmission, but can  only be used at shorter ranges.
 *  
 *  @param rate Fixed rate (throughput).
 *  @param completion Completion block.
 */
- (void)setDataRate:(DJILightbridgeDataRate)rate
     withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the current downlink data rate (throughput).
 *  
 *  @param rate The DJILBAirLinkDataRate object.
 *  @param error Error retrieving the value.
 *  @param completion Completion block.
 */
- (void)getDataRateWithCompletion:(void (^_Nonnull)(DJILightbridgeDataRate rate,
                                                    NSError *_Nullable error))completion;


/**
 *  Sets FPV video quality vs latency preference. This mode only affects the FPV
 *  camera and not the camera on the HD Gimbal.
 *  
 *  @param mode Quality vs Latency tradeoff for the FPV video
 *  @param completion Completion block.
 */
- (void)setTransmissionMode:(DJILightbridgeTransmissionMode)mode
             withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets FPV video quality vs latency preference. This mode only affects the FPV
 *  camera and not the camera on the HD Gimbal.
 *  
 *  @param transmissionMode The DJILBAirLinkFPVVideoQualityLatency object.
 *  @param error Error retrieving the value.
 *  @param completion Completion block.
 */
- (void)getTransmissionModeWithCompletion:(void (^_Nonnull)(DJILightbridgeTransmissionMode transmissionMode,
                                                            NSError *_Nullable error))completion;


/**
 *  Sets the percentage downlink video bandwidth dedicated to the video  feed from
 *  one of the LB input ports. The remaining percentage is dedicated  to the video
 *  feed from EXT input port. Setting 100% dedicates all the video bandwidth to LB.
 *  
 *  @param percent Percentage downlink bandwidth for video feed from LB port.
 *  @param completion Completion block.
 */
- (void)setBandwidthAllocationForLBVideoInputPort:(float)percent
                                   withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the percentage downlink video bandwidth dedicated to the video feed from
 *  one of  the LB input ports. The remaining percentage is dedicated to the video
 *  feed from EXT input port.
 *  
 *  @param percent Percentage downlink bandwidth for video feed from LB port.
 *  @param error Error encountered during the request. If the request is successful, it will be `nil`.
 *  @param completion Completion block.
 */
- (void)getBandwidthAllocationForLBVideoInputPortWithCompletion:(void (^_Nonnull)(float percent,
                                                                                  NSError *_Nullable error))completion;


/**
 *  Sets the percentage downlink video bandwidth dedicated to the main camera or
 *  main cameras (for  M210 and M210 RTK). The remaining percentage is dedicated to
 *  the FPV camera. For M210 and M210  RTK, the bandwidth for main cameras can be
 *  further divided by calling
 *  `setBandwidthAllocationForLeftCamera:withCompletion`. It is only supported by
 *  Inspire 2  and M200 series.
 *  
 *  @param percent Percentage downlink bandwidth for main camera(s).
 *  @param completion Completion block.
 */
- (void)setBandwidthAllocationForMainCamera:(float)percent
                             withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the percentage downlink video bandwidth dedicated to the main camera or
 *  main cameras  (for M210 and M210 RTK). The remaining percentage is dedicated to
 *  the FPV camera. It is  only supported by Inspire 2 and M200 series.
 *  
 *  @param percent Percentage downlink bandwidth for main camera(s).
 *  @param error Error encountered during the request. If the request is successful, it will be `nil`.
 *  @param completion Completion block.
 */
- (void)getBandwidthAllocationForMainCameraWithCompletion:(void (^_Nonnull)(float percent,
                                                                            NSError *_Nullable error))completion;


/**
 *  Sets the percentage of the main cameras' bandwidth dedicated to the left camera.
 *  The remaining percentage  is dedicated to the right camera. The main cameras'
 *  bandwidth is determined by
 *  `setBandwidthAllocationForMainCamera:withCompletion`.
 *   This setting will influence the physical sources  of video feeds
 *  (`primaryVideoFeed` and `secondaryVideoFeed`):
 *   - When  bandwidth is 100% on the left camera, the primary source is
 *  `DJIVideoFeedPhysicalSourceLeftCamera`  and the secondary source is
 *  `DJIVideoFeedPhysicalSourceFPVCamera`.
 *   - When bandwidth 0% on  the left camera, the primary source is
 *  `DJIVideoFeedPhysicalSourceRightCamera` and the secondary  source is
 *  `DJIVideoFeedPhysicalSourceFPVCamera`.
 *   - When bandwidth is neither 0% nor 100% on  the left camera, the primary source
 *  is `DJIVideoFeedPhysicalSourceLeftCamera` and the secondary  source is
 *  `DJIVideoFeedPhysicalSourceRightCamera`. It is only supported by M210 and M210
 *  RTK.
 *  
 *  @param percent Percentage downlink bandwidth for FPV camera.
 *  @param completion Completion block.
 */
- (void)setBandwidthAllocationForLeftCamera:(float)percent withCompletion:(DJICompletionBlock)completion;


/**
 *  When a product has multiple main cameras, this method gets the percentage
 *  bandwidth allocation  dedicated to the port (left) camera. The remaining
 *  percentage is dedicated to the starboard  (right) camera. The total bandwidth
 *  allocated to both main cameras (vs the FPV camera) is  determined by
 *  `setBandwidthAllocationForMainCamera:withCompletion`.
 *   This setting will  influence the physical sources of video feeds
 *  (`primaryVideoFeed`  and `secondaryVideoFeed`):
 *   - When bandwidth is 100% on the left camera,  the primary source is
 *  `DJIVideoFeedPhysicalSourceLeftCamera`  and the secondary source is
 *  `DJIVideoFeedPhysicalSourceFPVCamera`.
 *   - When bandwidth is 0% on the left camera, the primary source is
 *  `DJIVideoFeedPhysicalSourceRightCamera` and the secondary source  is
 *  `DJIVideoFeedPhysicalSourceFPVCamera`.
 *   - When bandwidth is  neither 0% nor 100% on the left camera, the primary source
 *  is  `DJIVideoFeedPhysicalSourceLeftCamera` and the secondary source is
 *  `DJIVideoFeedPhysicalSourceRightCamera`.
 *   It is only supported  by M210 and M210 RTK.
 *  
 *  @param percent Percentage downlink bandwidth for FPV camera.
 *  @param error Error encountered during the request. If the request is successful, it will be `nil`.
 *  @param completion Completion block.
 */
- (void)getBandwidthAllocationForLeftCameraWithCompletion:(void (^_Nonnull)(float percent, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark - Secondary Video Output
/*********************************************************************************/


/**
 *  Return whether secondary video output supported.
 *  
 *  @return A boolean value.
 */
- (BOOL)isSecondaryVideoOutputSupported;


/**
 *  Enable secondary video output on Remote Controller. The remote controller
 *  outputs video to the Mobile Device by  default. This will enable a secondary
 *  video stream to one of the Remote Controller's physical HDMI and SDI ports.
 *  
 *  @param enabled Enables secondary video output.
 *  @param completion Completion block.
 */
- (void)setSecondaryVideoOutputEnabled:(BOOL)enabled
                        withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets whether secondary video output on Remote Controller is enabled. The Remote
 *  Controller outputs video to the  Mobile Device by default, but a secondary video
 *  can be routed to its HDMI or SDI port.  Use
 *  `setSecondaryVideoOutputEnabled:withCompletion` to enable or disable,  and
 *  `setSecondaryVideoOutputPort:withCompletion` to choose the port.
 *  
 *  @param enabled The enabled value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block.
 */
- (void)getSecondaryVideoOutputEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled,
                                                                       NSError *_Nullable error))completion;


/**
 *  Sets secondary video output port on Remote Controller. HDMI or SDI are possible.
 *  Only one port can be active at once.
 *  
 *  @param port Secondary video output port.
 *  @param completion Completion block.
 */
- (void)setSecondaryVideoOutputPort:(DJILightbridgeSecondaryVideoOutputPort)port
                     withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the secondary video output port on Remote Controller. HDMI or SDI are
 *  possible. Only one port can be active at once.
 *  
 *  @param port The value the `DJILightbridgeSecondaryVideoOutputPort` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block.
 */
- (void)getSecondaryVideoOutputPortWithCompletion:(void (^_Nonnull)(DJILightbridgeSecondaryVideoOutputPort port,
                                                                    NSError *_Nullable error))completion;


/**
 *  Sets the secondary video output Picture in Picture (PIP) display mode. The air
 *  link module can connect to both  an FPV camera (through the HDMI and AV ports)
 *  and a camera mounted on the HD Gimbal (through the Gimbal port).  The output
 *  video can then be a combination of the two video sources. Either a single video
 *  source can be  displayed, or one can be displayed within the other (as a Picture
 *  in Picture, or PIP). If the mode is set  incorrectly,  then no output video will
 *  be displayed.
 *  
 *  @param mode Picture in Picture (PIP) display mode.
 *  @param completion Completion block.
 */
- (void)setSecondaryVideoDisplayMode:(DJILightbridgeSecondaryVideoDisplayMode)mode
                      withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the secondary video output Picture in Picture (PIP) display mode. The air
 *  link module can connect to both an  FPV camera (through the HDMI and AV ports)
 *  and a camera mounted on the HD Gimbal (through the Gimbal port). The  output
 *  video can then be a combination of the two video sources. Either a single video
 *  source can be displayed, or  one can be displayed within the other (as a Picture
 *  in Picture, or PIP).
 *  
 *  @param videoDisplayMode The value of the `DJILightbridgeSecondaryVideoDisplayMode` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSecondaryVideoDisplayModeWithCompletion:(void (^_Nonnull)(DJILightbridgeSecondaryVideoDisplayMode videoDisplayMode,
                                                                     NSError *_Nullable error))completion;


/**
 *  Enables and disables On Screen Display (OSD) overlay on the secondary video. OSD
 *  is flight data like altitude,  attitude etc. and can be overlayed on the PIP
 *  video.
 *  
 *  @param enabled Determines whether to display OSD on screen.
 *  @param completion Completion block.
 */
- (void)setSecondaryVideoOSDEnabled:(BOOL)enabled
                     withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether On Screen Display (OSD) is overlayed on the video feed.
 *  
 *  @param enabled The enabled value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSecondaryVideoOSDEnabled:(void (^_Nonnull)(BOOL enabled,
                                                      NSError *_Nullable error))completion;


/**
 *  Sets the OSD top margin in video pixels.
 *  
 *  @param margin Top margin of OSD. The range is [0, 50].
 *  @param completion Completion block.
 */
- (void)setSecondaryVideoOSDTopMargin:(NSUInteger)margin
                       withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the OSD top margin in video pixels.
 *  
 *  @param margin The OSD top margin value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSecondaryVideoOSDTopMarginWithCompletion:(void (^_Nonnull)(NSUInteger margin,
                                                                      NSError *_Nullable error))completion;


/**
 *  Sets the OSD left margin in video pixels.
 *  
 *  @param margin Left margin of OSD. The range is [0, 50].
 *  @param completion Completion block.
 */
- (void)setSecondaryVideoOSDLeftMargin:(NSUInteger)margin
                        withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the OSD left margin in video pixels.
 *  
 *  @param margin The OSD left margin value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSecondaryVideoOSDLeftMarginWithCompletion:(void (^_Nonnull)(NSUInteger margin,
                                                                       NSError *_Nullable error))completion;


/**
 *  Sets the OSD bottom margin in video pixels.
 *  
 *  @param margin Bottom margin of OSD. The range is [0, 50].
 *  @param completion Completion block.
 */
- (void)setSecondaryVideoOSDBottomMargin:(NSUInteger)margin
                          withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the OSD bottom margin in video pixels.
 *  
 *  @param margin The OSD bottom margin value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSecondaryVideoOSDBottomMarginWithCompletion:(void (^_Nonnull)(NSUInteger margin,
                                                                         NSError *_Nullable error))completion;


/**
 *  Sets the OSD right margin in video pixels.
 *  
 *  @param margin Right margin of OSD. The range is [0, 50].
 *  @param completion Completion block.
 */
- (void)setSecondaryVideoOSDRightMargin:(NSUInteger)margin
                         withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the OSD right margin in video pixels.
 *  
 *  @param margin The OSD right margin value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSecondaryVideoOSDRightMarginWithCompletion:(void (^_Nonnull)(NSUInteger margin,
                                                                        NSError *_Nullable error))completion;


/**
 *  Sets the OSD units to either metric or imperial.
 *  
 *  @param unit OSD units.
 *  @param completion Completion block.
 */
- (void)setSecondaryVideoOSDUnit:(DJILightbridgeSecondaryVideoOSDUnit)unit
                  withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the OSD units (metric or imperial).
 *  
 *  @param unit The value of the `DJILightbridgeSecondaryVideoOSDUnit` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSecondaryVideoOSDUnitWithCompletion:(void (^_Nonnull)(DJILightbridgeSecondaryVideoOSDUnit unit,
                                                                 NSError *_Nullable error))completion;


/**
 *  Sets the Remote Controller HDMI video port output video format.
 *  
 *  @param port The value of the `DJILightbridgeSecondaryVideoOutputPort` Enum.
 *  @param format The value of the `DJILightbridgeSecondaryVideoFormat` Enum.
 *  @param completion Completion block to receive the result.
 */
- (void)setSecondaryVideoOutputFormat:(DJILightbridgeSecondaryVideoFormat)format
                              forPort:(DJILightbridgeSecondaryVideoOutputPort)port
                       withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the Remote Controller HDMI video port output video format.
 *  
 *  @param port The value of the `DJILightbridgeSecondaryVideoOutputPort` Enum.
 *  @param format The value of the `DJILightbridgeSecondaryVideoFormat` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSecondaryVideoOutputFormatForPort:(DJILightbridgeSecondaryVideoOutputPort)port
                              withCompletion:(void (^_Nonnull)(DJILightbridgeSecondaryVideoFormat format,
                                                               NSError *_Nullable error))completion;


/**
 *  Sets the PIP (Picture In Picture) position relative to the top left corner of
 *  the main subject video feed.
 *  
 *  @param position Position of the PIP on the screen.
 *  @param completion Completion block.
 */
- (void)setSecondaryVideoPIPPosition:(DJILightbridgePIPPosition)position
                      withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the PIP (Picture In Picture) position relative to the top left corner of
 *  the main subject video feed.
 *  
 *  @param position The value of the `DJILightbridgePIPPosition` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSecondaryVideoPIPPositionWithCompletion:(void (^_Nonnull)(DJILightbridgePIPPosition position,
                                                                     NSError *_Nullable error))completion;


/**
 *  `YES` if Lightbridge 2 device supports dual encode mode. Dual encode mode allows
 *  the  Lightbridge module to encode and transmit both it's AV and HDMI inputs
 *  simultaneously.
 *  
 *  @return A boolean value.
 */
-(BOOL) canEXTVideoInputPortBeDisabled;


/**
 *  Sets Lightbridge 2 encode mode. It is only available when  `
 *  canEXTVideoInputPortBeDisabled` returns  `YES`. For Lightbridge 2 modules that
 *  don't support dual encode mode, the encode mode is  always single.
 *  
 *  @param enabled The encode mode to set.
 *  @param completion Completion block.
 */
- (void)setEXTVideoInputPortEnabled:(BOOL)enabled
                     withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets Lightbridge 2 encode mode. It is only available when `
 *  canEXTVideoInputPortBeDisabled` returns  `YES`. For Lightbridge 2 modules that
 *  don't support dual encode mode, the encode mode is  always single.
 *  
 *  @param enabled `YES` if EXT video input port is enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getEXTVideoInputPortEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled,
                                                                    NSError *_Nullable error))completion;


/**
 *  Sets the computational power and bandwidth balance between AV and HDMI inputs on
 *  the Lightbridge 2 module when  dual encode mode is enabled. Balance is in
 *  percent [0.0,  1.0]. It is only available  when `
 *  canEXTVideoInputPortBeDisabled` returns `YES`. When <code>percent</code> is 0.0,
 *  all resources are allocated for video data from AV port. When
 *  <code>percent</code> is 1.0, all resources are  allocated for video data from
 *  HDMI port.
 *  
 *  @param percent Percentage resources dedicated to HDMI encoding and transmission.
 *  @param completion Completion block.
 */
- (void)setBandwidthAllocationForHDMIVideoInputPort:(float)percent
                                     withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the computational power and bandwidth balance between AV and HDMI inputs on
 *  the Lightbridge 2 module when  dual encode mode is enabled. It is only available
 *  when ` canEXTVideoInputPortBeDisabled` returns  `YES`. When <code>percent</code>
 *  is 0.0, all resources are allocated for video data from AV  port. When
 *  <code>percent</code> is 1.0, all resources are allocated for video data from
 *  HDMI port.
 *  
 *  @param percent The percent value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getBandwidthAllocationForHDMIVideoInputPortWithCompletion:(void (^_Nonnull)(float percent,
                                                                                    NSError *_Nullable error))completion;


/**
 *  Gets the frequency bands supported by the product in the current area. It is
 *  only supported by Inspire 2 and  Phantom 4 Pro. For the other products with LB
 *  air link, the frequency band is always 2.4 GHz.
 *  
 *  @param frequencyBands The array of the `DJILightbridgeFrequencyBand` values.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSupportedFrequencyBandsWithCompletion:(void (^_Nonnull)(NSArray<NSNumber *> *_Nullable frequencyBands,
                                                                   NSError *_Nullable error))completion;


/**
 *  Sets the LB air link frequency band. It is only supported by Inspire 2 and
 *  Phantom 4 Pro. For the other products
 *   with LB air link, the frequency band is always 2.4 GHz.
 *  
 *  @param frequencyBand LBAirLink frequency band to change to.
 *  @param completion Remote execution result error block.
 */
- (void)setFrequencyBand:(DJILightbridgeFrequencyBand)frequencyBand
          withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the LB air link frequency band. It is only supported by Inspire 2 and
 *  Phantom 4 Pro. For the other products  with LB air link, the frequency band is
 *  always 2.4 GHz.
 *  
 *  @param frequencyBand The current frequency band.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getFrequencyBandWithCompletion:(void (^_Nonnull)(DJILightbridgeFrequencyBand frequencyBand,
                                                         NSError *_Nullable error))completion;


/**
 *  Enables the setting to output video to both the mobile device and the HDMI port
 *  on the remote controller  simultaneously. When it is disabled and the remote
 *  controller is connected to a HDMI display, the mobile  device will not receive
 *  the live view. It is only supported by Inspire 1 and M100.
 *  
 *  @param enabled `YES` to enable live view simultaneous output.
 *  @param completion Completion block to receive the result.
 */
-(void) setLiveViewSimultaneousOutputEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Determines whether the setting to output video to both the mobile device and the
 *  HDMI port on the remote  controller simultaneously is enabled or not. When it is
 *  disabled and the remote controller is connected  to a HDMI display, the mobile
 *  device will not receive the live view. It is only supported by Inspire 1 and
 *  M100.
 *  
 *  @param enabled `YES` if enabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
-(void) getLiveViewSimultaneousOutputEnabledWithCompletion:(void(^_Nonnull)(BOOL enabled, NSError* _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
