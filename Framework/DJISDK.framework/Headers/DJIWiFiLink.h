//
//  DJIWiFiLink.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <DJISDK/DJISDK.h>
#import <DJISDK/DJIBaseComponent.h>
#import <DJISDK/DJIAirLinkBaseTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIWiFiLink;


/**
 *  This protocol provides a delegate method to receive the updated WiFi signal
 *  quality.
 */
@protocol DJIWiFiLinkDelegate <NSObject>

@optional


/**
 *  Updates the WiFi Signal Quality.
 *  
 *  @param link DJIWiFiLink object.
 *  @param level An enum value of `DJIWiFiMagneticInterferenceLevel`.
 */
- (void)wifiLink:(DJIWiFiLink *_Nonnull)link didUpdateMagneticInterferenceLevel:(DJIWiFiMagneticInterferenceLevel)level;


/**
 *  This will be invoked when there is a change in RSSI. Interference power of the
 *  available channels.
 *  
 *  @param link DJIWiFiLink object.
 *  @param interferences The interference power of available channels.
 */
- (void)wifiLink:(DJIWiFiLink *_Nonnull)link didUpdateChannelInterference:(NSArray<DJIWiFiChannelInterference *> *)interferences;

@end

/*********************************************************************************/
#pragma mark WiFi Component
/*********************************************************************************/


/**
 *  This class provides methods to change the setting of the product's WiFi.
 *  Rebooting WiFi is required in order to make new settings take effect.
 */
@interface DJIWiFiLink : NSObject


/**
 *  Returns the `DJIWiFiLink` delegate.
 */
@property (nonatomic, weak) id <DJIWiFiLinkDelegate> delegate;


/**
 *  Returns `YES` if the firmware of the connect product supports channel selection
 *  mode. This feature is only supported by Mavic Air and Spark.
 */
@property (nonatomic, readonly) BOOL isChannelSelectionModeSupported;


/**
 *  Reboot WiFi to enable new settings to take effect.
 *  
 *  @param completion Remote execution result error block.
 */
- (void)rebootWithCompletion:(DJICompletionBlock)completion;

/*********************************************************************************/
#pragma mark SSID and Password
/*********************************************************************************/


/**
 *  Gets the WiFi SSID.
 *  
 *  @param ssid The SSID string.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getSSIDWithCompletion:(void (^_Nonnull)(NSString *_Nullable ssid,
                                                    NSError *_Nullable error))completion;


/**
 *  Sets the WiFi SSID. The setting will take effect only after the product reboots.
 *  
 *  @param ssid The WiFi SSID to change. It should only include alphabetic characters, numbers, spaces, '-' and should not be  more than 30 characters.
 *  @param completion Remote execution result error block.
 */
- (void)setSSID:(NSString *_Nonnull)ssid
 withCompletion:(DJICompletionBlock)completion;


/**
 *  Get the WiFi Password.
 *  
 *  @param password The password string.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getPasswordWithCompletion:(void (^_Nonnull)(NSString *_Nullable password,
                                                        NSError *_Nullable error))completion;


/**
 *  Sets the WiFi Password.
 *  
 *  @param password The new WiFi password. It must be at least 8 characters and can only includes alphabetic characters and numbers.
 *  @param completion Remote execution result error block.
 */
- (void)setPassword:(NSString *_Nullable)password
     withCompletion:(DJICompletionBlock)completion;

/*********************************************************************************/
#pragma mark Frequency Band Selection
/*********************************************************************************/


/**
 *  It is not supported by Spark or Mavic Air. For these products, set different
 *  channel  numbers to select the frequency band.
 *  
 *  @param frequencyBand WiFi frequency band to change to.
 *  @param completion Remote execution result error block.
 */
- (void)setFrequencyBand:(DJIWiFiFrequencyBand)frequencyBand
          withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the current WiFi frequency band. It is not supported by Spark or Mavic Air.
 *  
 *  @param frequencyBand The value of `DJIWiFiFrequencyBand` Enum.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getFrequencyBandWithCompletion:(void (^_Nonnull)(DJIWiFiFrequencyBand frequencyBand,
                                                         NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Channels
/*********************************************************************************/


/**
 *  Sets the channel selection mode. Both channel number and bandwidth can be
 *  changed.  If the 5 GHz band is available,  then channels from that band can also
 *  be used. It is  supported when `isChannelSelectionModeSupported` returns `YES`.
 *  
 *  @param mode Selection mode to set.
 *  @param completion Completion block that receives the setter result.
 */
-(void)setChannelSelectionMode:(DJIWiFiChannelSelectionMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the channel selection mode. It is supported when
 *  `isChannelSelectionModeSupported` returns `YES`.
 *  
 *  @param mode The current selection mode. It returns `DJIWiFiChannelSelectionModeUnknown` when error is encountered.
 *  @param error The encountered error if any.
 *  @param completion Completion block to receive the result.
 */
-(void)getChannelSelectionModeWithCompletion:(void (^_Nonnull)(DJIWiFiChannelSelectionMode mode, NSError *_Nullable error))completion;


/**
 *  Sets the WiFi channel. `getAvailableChannelNumbersWithCompletion` must be used
 *  to determine which channels are possible  to set. When a new channel is set, the
 *  WiFi on the product will reboot. The channel can only be changed when the
 *  product is not flying. Supported only by Mavic Pro.
 *  
 *  @param channelNumber Index of the channel to select.
 *  @param completion The completion block with the returned execution result.
 */
-(void)setChannelNumber:(NSUInteger)channelNumber withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the WiFi channel. Channels 1-13 are in the 2.4 GHz band. Other channels are
 *  in the 5 GHz band.
 *  
 *  @param channelNumber The channelIndex value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
-(void)getChannelNumberWithCompletion:(void (^)(NSUInteger channelNumber,
                                                NSError *_Nullable error))completion;


/**
 *  Gets the channels available for the current frequency band. When
 *  `DJIWiFiFrequencyBandDual` is  selected, channels for both 2.4GHz and 5GHz are
 *  available. Supported only by Mavic Pro.
 *  
 *  @param channelNumbers The array of the channel value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
-(void)getAvailableChannelNumbersWithCompletion:(void (^)(NSArray<NSNumber *> *_Nullable channelNumbers,
                                                          NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Data Rate
/*********************************************************************************/


/**
 *  Sets the WiFi data rate (throughput). Higher data rates increase the quality of
 *  video transmission, but can only be  used at shorter ranges. It is not supported
 *  by Spark or Mavic Air.
 *  
 *  @param rate Data rate (throughput).
 *  @param completion The completion block with the returned execution result.
 */
-(void)setDataRate:(DJIWiFiDataRate)rate withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the current data rate (throughput). It is not supported by Spark or Mavic
 *  Air.
 *  
 *  @param rate The `DJIWiFiDataRate` object.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
-(void)getDataRateWithCompletion:(void (^)(DJIWiFiDataRate rate,
                                           NSError *_Nullable error))completion;


@end

NS_ASSUME_NONNULL_END
