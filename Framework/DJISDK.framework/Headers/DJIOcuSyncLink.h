//
//  DJIOcuSyncLink.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#import <DJISDK/DJIAirLinkBaseTypes.h>
#import <DJISDK/DJIBaseProduct.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIOcuSyncLink;

/*********************************************************************************/
#pragma mark - DJIOcuSyncLinkDelegate
/*********************************************************************************/


/**
 *  This protocol provides delegate methods to receive updated states of OcuSync.
 */
@protocol DJIOcuSyncLinkDelegate <NSObject>

@optional


/**
 *  Updated data rate in Mbps for the wireless downlink (from aircraft to remote
 *  controller). This link transfers  all information from aircraft to remote
 *  controller, which is predominantly video information.
 *  
 *  @param ocuSyncLink The OcuSync link from aircraft to remote controller.
 *  @param rate The data rate of the downlink in Mbps.
 */
-(void)ocuSyncLink:(DJIOcuSyncLink *)ocuSyncLink didUpdateVideoDownlinkRate:(float)rate;


/**
 *  Updated OcuSync link warning messages. This delegate method is called only when
 *  there are new warning messages  on the OcuSync link (either uplink or downlink).
 *  If the array has no elements, then all previous warning  messages are no longer
 *  in effect.
 *  
 *  @param ocuSyncLink The OcuSync link.
 *  @param messages An array of warning messages. Each element is an NSNumber with value defined in `DJIOcuSyncWarningMessage`.
 */
-(void)ocuSyncLink:(DJIOcuSyncLink *)ocuSyncLink didReceiveWarningMessages:(NSArray<NSNumber *> *)messages;



/**
 *  Updated power for interference signals with frequencies in the 2.4 GHz (2400MHz
 *  to 2482 MHz) frequency band  incident on the remote controller. Note, measuring
 *  the interference reduces effective data rate as the radio  is spending time
 *  listening to frequencies outside of the communication channel. Interference
 *  measurements will  only be made if the `delegate` property in OcuSyncLink is
 *  assigned to a class that implements this delegate method.
 *  
 *  @param ocuSyncLink The OcuSync link.
 *  @param interference The updated interference information. The elements in the array  of `DJIOcuSyncFrequencyInterference` objects each hold interference information about a small  part of the frequency band. Elements are sorted by increasing frequency.
 */
-(void)ocuSyncLink:(DJIOcuSyncLink *)ocuSyncLink didUpdateChannelInterference:(NSArray<DJIOcuSyncFrequencyInterference *> *)interference;

@end

/*********************************************************************************/
#pragma mark - DJIOcuSyncLink
/*********************************************************************************/


/**
 *  This class contains methods to change OcuSync link settings.
 */
@interface DJIOcuSyncLink : NSObject


/**
 *  Returns the DJIOcuSyncLink delegate.
 */
@property(nonatomic, weak) id<DJIOcuSyncLinkDelegate> delegate;


/**
 *  Sets the channel selection mode. Both channel number and bandwidth can be
 *  changed. If the 5 GHz band is available,  then channels from that band can also
 *  be used.
 *  
 *  @param mode Selection mode to set.
 *  @param completion Completion block that receives the setter result.
 */
-(void)setChannelSelectionMode:(DJIOcuSyncChannelSelectionMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the channel selection mode.
 *  
 *  @param mode The value of the `DJIOcuSyncChannelSelectionMode` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
-(void)getChannelSelectionModeWithCompletion:(void (^_Nonnull)(DJIOcuSyncChannelSelectionMode mode, NSError *_Nullable error))completion;


/**
 *  Sets the channel bandwidth of the OcuSync link. It can be set only when the
 *  selection mode is  `DJIOcuSyncChannelSelectionModeManual`.
 *  
 *  @param bandwidth Bandwidth to set.
 *  @param completion Completion block that receives the setter result.
 */
-(void)setChannelBandwidth:(DJIOcuSyncBandwidth)bandwidth withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the channel bandwidth of the OcuSync link.
 *  
 *  @param bandwidth The value of the `DJIOcuSyncBandwidth` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
-(void)getChannelBandwidthWithCompletion:(void (^_Nonnull)(DJIOcuSyncBandwidth bandwidth, NSError *_Nullable error))completion;


/**
 *  Selects the channel number. The OcuSync link operates on a  10 MHz or 20 MHz
 *  channel between 2400.5 MHz and 2482.5 MHz. The channel can be centered at 1 MHz
 *  steps within the  band. Therefore for a 10 MHz bandwidth, the OcuSync channel
 *  can be centered at 2405.5 MHz, 2406.5 MHz and every 1  MHz to 2477.5 MHz. For a
 *  20 MHz bandwidth, channel center can be at 2410.5 MHz to 2472.5 MHz in 1 MHz
 *  steps. The  channel location within the band is specified using the Channel
 *  Number. Channel Number is defined as the integer  of 0.5 MHz less than the
 *  channel center frequency. E.g. Channel Number 2406 represents the 10 MHz channel
 *  centered  at 2406.5 MHz (this is only for the 10 MHz bandwidth as 20 MHz
 *  bandwidth channels start at 2410.5 MHz). Channel  Number 2450 represents the
 *  channel centered at 2450.5 MHz (of any bandwidth).  Use
 *  `getChannelNumberValidRangeWithCompletion` to check the valid Channel Numbers
 *  for a given bandwidth. Channel  Number can only be set when the channel
 *  selection mode is `DJIOcuSyncChannelSelectionModeManual`.
 *  
 *  @param channelNumber Channel number to set OcuSync channel to.
 *  @param completion Completion block that receives the setter result.
 */
-(void)setChannelNumber:(NSUInteger)channelNumber withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the current OcuSync Link Channel Number. The OcuSync link operates on a 10
 *  MHz or 20 MHz channel between  2400.5 MHz and 2482.5 MHz. The channel can be
 *  centered at 1 MHz steps within the band. Therefore for a 10 MHz  bandwidth, the
 *  OcuSync channel can be centered at 2405.5 MHz, 2406.5 MHz and every 1 MHz to
 *  2477.5 MHz. For a  20 MHz bandwidth, channel center can be at 2410.5 MHz to
 *  2472.5 MHz in 1 MHz steps. The channel location within  the band is specified
 *  using the Channel Number. Channel Number is defined as the integer of 0.5 MHz
 *  less than the  channel center frequency. E.g. Channel Number 2406 represents the
 *  10 MHz channel centered at 2406.5 MHz (this is  only for the 10 MHz bandwidth as
 *  20 MHz bandwidth channels start at 2410.5 MHz). Channel Number 2450 represents
 *  the channel centered at 2450.5 MHz (of any bandwidth).
 *  
 *  @param channelNumber The channelNumber value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
-(void)getChannelNumberWithCompletion:(void (^_Nonnull)(NSUInteger channelNumber,
                                                        NSError *_Nullable error))completion;


/**
 *  Gets the valid range of Channel Numbers. The OcuSync link operates on a 10 MHz
 *  or 20 MHz channel between  2400.5 MHz and 2482.5 MHz. The channel can be
 *  centered at 1 MHz steps within the band. Therefore for a 10 MHz  bandwidth, the
 *  OcuSync channel can be centered at 2405.5 MHz, 2406.5 MHz and every 1 MHz to
 *  2477.5 MHz. For a  20 MHz bandwidth, channel center can be at 2410.5 MHz to
 *  2472.5 MHz in 1 MHz steps. The channel location within  the band is specified
 *  using the Channel Number. Channel Number is defined as the integer of 0.5 MHz
 *  less than the  channel center frequency. E.g. Channel Number 2406 represents the
 *  10 MHz channel centered at 2406.5 MHz (this is  only for the 10 MHz bandwidth as
 *  20 MHz bandwidth channels start at 2410.5 MHz). Channel Number 2450 represents
 *  the channel centered at 2450.5 MHz (of any bandwidth). This method should be
 *  used to confirm the Channel Number  to be set with
 *  `setChannelNumber:withCompletion` is valid.
 *  
 *  @param range The valid range of Channel Numbers.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
-(void)getChannelNumberValidRangeWithCompletion:(void (^_Nonnull)(NSRange range,
                                                                  NSError *_Nullable error))completion;


/**
 *  Gets the frequency bands supported by the product in the current area. It is
 *  supported by P4P V2 and Mavic 2 Series. For  Mavic Pro, only 2.4GHz is
 *  supported.
 *  
 *  @param frequencyBands The array of the `DJIOcuSyncFrequencyBand` values.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSupportedFrequencyBandsWithCompletion:(void (^_Nonnull)(NSArray<NSNumber *> *_Nullable frequencyBands,
                                                                   NSError *_Nullable error))completion;


/**
 *  Sets the OcuSync air link frequency band. It is only supported by Phantom 4 Pro
 *  V2 and Mavic 2 Series. For Mavic Pro,  the frequency band is always 2.4 GHz.
 *  
 *  @param frequencyBand Frequency band to change to.
 *  @param completion Completion block to receive the result.
 */
- (void)setFrequencyBand:(DJIOcuSyncFrequencyBand)frequencyBand
          withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the OcuSync air link frequency band. It is only supported by Phantom 4 Pro
 *  V2 and Mavic 2 Series. For Mavic Pro, the frequency band is always 2.4 GHz.
 *  
 *  @param frequencyBand The current frequency band.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getFrequencyBandWithCompletion:(void (^_Nonnull)(DJIOcuSyncFrequencyBand frequencyBand,
                                                         NSError *_Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
