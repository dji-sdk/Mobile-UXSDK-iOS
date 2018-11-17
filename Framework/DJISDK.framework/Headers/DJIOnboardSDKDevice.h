//
//  DJIOnboardSDKDevice.h
//  DJISDK
//
//  Copyright © 2018 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIBaseComponent.h>

@class DJIOnboardSDKDevice;

NS_ASSUME_NONNULL_BEGIN


/**
 *  This protocol provides delegate methods to interative with Onboard SDK Devices.
 */
@protocol DJIOnboardSDKDeviceDelegate <NSObject>

@optional


/**
 *  Called when the Onboard SDK device sent a message to the mobile device through
 *  transparent transmission.
 *  
 *  @param osdkDevice The Onboard SDK device that update message data.
 *  @param data The binary message sent from the Onboard SDK device.
 */
- (void)onboardSDKDevice:(DJIOnboardSDKDevice *)osdkDevice
     didSendDataToMobile:(NSData *)data;


/**
 *  Called when the onboard device successfully connects and performs handshake.
 *  
 *  @param osdkDevice The Onboard SDK device updates the state.
 *  @param osdkVersion A string with the Onboard SDK version.
 */
- (void)onboardSDKDevice:(DJIOnboardSDKDevice *)osdkDevice didActivateWithOnboardSDKVersion:(NSString *)osdkVersion;


/**
 *  Called when the onboard device disconnects.
 *  
 *  @param osdkDevice The disconnected Onboard SDK device.
 */
- (void)onboardSDKDeviceDidDeactivate:(DJIOnboardSDKDevice *)osdkDevice;

@end


/**
 *  The `DJIOnboardSDKDevice` class abstracts the Onboard SDK device on the flight
 *  controller. It provides interfaces to interact with Onboard SDK and receive the
 *  updated state.
 */
@interface DJIOnboardSDKDevice : NSObject


/**
 *  Onboard SDK device delegate.
 */
@property(nonatomic, weak, nullable) id<DJIOnboardSDKDeviceDelegate> delegate;


/**
 *  Sends binary data from the mobile device to the Onboard device. The size of the
 *  data cannot  be greater than 100 bytes, and will be sent in 40 byte increments
 *  every 14ms. This method is  only supported on products that support the Onboard
 *  SDK (Matrice 100, Matrice 200 Series,  Matrice 600, Matrice 600 Pro, A3, A3 Pro,
 *  and N3).
 *  
 *  @param data Data to be sent to the external device. The size of the data should not be larger than 100 bytes.
 *  @param completion Completion block.
 */
- (void)sendDataFromMobileToOnboard:(NSData *)data withCompletion:(DJICompletionBlock)completion;


/**
 *  Whether an Onboard SDK device is currently active on the platform.
 */
@property (nonatomic, readonly) BOOL isActive;


/**
 *  The version of the Onboard SDK used by the currently active device on the
 *  platform. If Onboard  SDK version is not ready, an empty string (with zero
 *  length) will be returned.
 */
@property (nonatomic, readonly) NSString *onboardSDKVersion;

@end

NS_ASSUME_NONNULL_END
