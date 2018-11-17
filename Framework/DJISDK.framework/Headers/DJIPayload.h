//
//  DJIPayload.h
//  DJISDK
//
//  Copyright © 2018 DJI. All rights reserved.
//

#import <DJISDK/DJISDK.h>
#import <DJISDK/DJIPayloadWidget.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIPayloadWidget;
@class DJIPayload;


/**
 *  Delegate class to receive updated state related to Payload.
 */
@protocol DJIPayloadDelegate <NSObject>

@optional


/**
 *  Receives the command data sent from the payload device. The command data is sent
 *  from the UART/CAN channel of the payload device and the bandwidth of this
 *  channel  is 3K bytes/s on M200 series.
 *  
 *  @param payload The payload instance received the command data from the payload device.
 *  @param data The data that received by the payload instance.
 */
- (void)payload:(DJIPayload *)payload didReceiveCommandData:(NSData *)data;


/**
 *  Receives the stream data sent from the payload device. The stream data is sent
 *  from  the UDP channel of the payload device. This channel has wider bandwidth
 *  than the channel  for command data but data might get lost without re-
 *  transmission.
 *  
 *  @param payload The payload instance received the stream data from the payload device.
 *  @param data The data that received by the payload instance.
 */
- (void)payload:(DJIPayload *)payload didReceiveStreamData:(NSData *)data;


/**
 *  Receives a text message sent from the payload device.
 *  
 *  @param payload The payload instance received the text message from the payload device.
 *  @param message The message that received by the payload instance.
 */
- (void)payload:(DJIPayload *)payload didReceiveMessage:(NSString *)message;


/**
 *  The payload device updates the value for the widgets.
 *  
 *  @param payload The payload instance received the updated widget values.
 *  @param widgets The updated value for widgets.
 */
- (void)payload:(DJIPayload *)payload didUpdateWidgets:(NSArray<DJIPayloadWidget*> *)widgets;

@end


/**
 *  Class used to interact with the payload device mounted on DJI aircraft.
 */
@interface DJIPayload : DJIBaseComponent


/**
 *  Delegate to receive the update information.
 */
@property(nonatomic, weak) id<DJIPayloadDelegate> delegate;


/**
 *  Gets the bandwidth of the upstream (from Mobile SDK to Payload). The unit is
 *  bytes/s.  The bandwidth is determined by the firmware and currently it is not
 *  larger than 500 bytes/s.
 *  
 *  @param upstreamBandwidth The upstream bandwidth determined by the firmware.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getUpstreamBandwidthWithCompletion:(void (^)(NSUInteger upstreamBandwidth, NSError * _Nullable error))completion;


/**
 *  Gets the product name defined by the manufacturer of the payload device.
 *  
 *  @return The product name of the payload device.
 */
- (NSString * _Nullable)getPayloadProductName;


/**
 *  Set the value for a widget of the payload device. Different widget types
 *  requires different  value:
 *   - for `DJIPayloadWidgetTypeInput`, the input should be an unsigned 32-bit
 *  integer
 *   - for `DJIPayloadWidgetTypeSwitch`, the input should be value  of
 *  `DJIPayloadSwitchState`
 *   - for `DJIPayloadWidgetTypeRange`, the input should  be a integer from value 0
 *  to 100
 *   - for `DJIPayloadWidgetTypeList`, the input should  be a integer not larger
 *  than list size minus one.
 *   Widget with  type `DJIPayloadWidgetTypeButton` is not configurable.
 *  
 *  @param value The value to configure.
 *  @param type Type of the widget to configure.
 *  @param index Index of the widget to configure.
 *  @param completion Completion block to receive the execution result.
 */
- (void)configureWidgetValue:(NSUInteger)value type:(DJIPayloadWidgetType)type index:(NSUInteger)index withCompletion:(DJICompletionBlock)completion;


/**
 *  Sets the switch state for the switch widget with the specific index. It has the
 *  same effect  as `configureWidgetValue:type:index:withCompletion` with
 *  `DJIPayloadWidgetTypeSwitch` as the argument.
 *  
 *  @param state Switch state to set.
 *  @param index Widget index to set.
 *  @param completion Completion block to receive the execution result.
 */
- (void)setSwitchState:(DJIPayloadSwitchState)state index:(NSUInteger)index withCompletion:(DJICompletionBlock)completion;


/**
 *  Sets the range value for the range widget with the specific index. It has the
 *  same effect as `configureWidgetValue:type:index:withCompletion`  with
 *  `DJIPayloadWidgetTypeRange` as the argument.
 *  
 *  @param rangeValue Range value to set. The valid range is [0, 100].
 *  @param index Widget index to set.
 *  @param completion Completion block to receive the execution result.
 */
- (void)setRangeValue:(NSUInteger)rangeValue index:(NSUInteger)index withCompletion:(DJICompletionBlock)completion;


/**
 *  Sets the selected item index for the list widget with the specific index. It has
 *  the same effect as `configureWidgetValue:type:index:withCompletion`  with
 *  `DJIPayloadWidgetTypeList` as the argument.
 *  
 *  @param selectedItemIndex Index of the selected item. The valid range is from 0 to list size - 1.
 *  @param index Widget index to set.
 *  @param completion Completion block to receive the execution result.
 */
- (void)setSelectedItem:(NSUInteger)selectedItemIndex index:(NSUInteger)index withCompletion:(DJICompletionBlock)completion;


/**
 *  Sets the input value for the input widget with the specific index. It has the
 *  same effect as `configureWidgetValue:type:index:withCompletion`  with
 *  `DJIPayloadWidgetTypeList` as the argument.
 *  
 *  @param inputValue Input value to set. The valid value is an unsigned 32-bit integer.
 *  @param index Widget index to set.
 *  @param completion Completion block to receive the execution result.
 */
- (void)setInputValue:(NSUInteger)inputValue index:(NSUInteger)index withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets a widget by specifying the widget type and the index.
 *  
 *  @param widgetType Widget type to get.
 *  @param widgetIndex Widget index to get.
 *  
 *  @return The widget corresponding to the widget type and the index. `nil` if the widgets are not ready or there is no widget corresponding  to the widget type and the index.
 */
- (DJIPayloadWidget * _Nullable)getWidget:(DJIPayloadWidgetType)widgetType index:(NSInteger)widgetIndex;


/**
 *  Gets the full list of widgets on the payload device. A new instance of "NSArray"
 *  is returned when one of the widget is updated.
 *  
 *  @return The full list of widgets. `nil` if the widgets are not fetched yet.
 */
- (NSArray<DJIPayloadWidget*> * _Nullable)getWidgets;


/**
 *  Sends data to payload. The length of the data to send cannot exceed 32 bytes.
 *  The throughput cannot exceed the bandwidth  returned by
 *  `getUpstreamBandwidthWithCompletion`.
 *  
 *  @param data Data that will be sent to the payload device.
 *  @param completion Completion block to receive the execution result.
 */
- (void)sendDataToPayload:(NSData *)data withCompletion:(DJICompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END
