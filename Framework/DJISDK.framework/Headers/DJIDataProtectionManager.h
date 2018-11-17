//
//  DJIDataProtectionManager.h
//  DJISDK
//
//  Copyright © 2018 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 *  Data Protection Manager. DJI SDK will data to DJI servers in the background in
 *  order to complete  logics, including data related to user's information. Data
 *  Protection Manager can be used to authorize  DJI server to access the user-
 *  related data. SDK will NOT send the data to DJI server in the background  before
 *  the authorization. Internet requests triggered by the user manually are not
 *  managed by `DJIDataProtectionManager`.  Involved user-related data is listed in
 *  the documentation of the interfaces. The authorization is not persistent and
 *  each  authorization setting will be reset to the default value for each APP's
 *  life cycle. This class is accessible before  calling `registerAppWithDelegate`.
 */
@interface DJIDataProtectionManager : NSObject

- (instancetype)init OBJC_UNAVAILABLE("You must use the singleton");

+ (instancetype)new OBJC_UNAVAILABLE("You must use the singleton");


/**
 *  Authorizes DJI server to access DJI device's hardware information (serial
 *  numbers of the aircraft and the remote  controller). The serial number will be
 *  sent to DJI server for two purposes:
 *   - DJI SDK analytics: the hashed  serial number is used to distinguish
 *  statistics from different DJI devices.
 *   - App Activation: the serial number  is used to request the app activation
 *  state from the server. When the user is located in China, the serial number is
 *  still sent to DJI server for policy reason even it is not authorized by the
 *  user. DJI server is NOT authorized by  default. However, it is highly
 *  recommended to ask the user to authorize it, which can help DJI keep improving
 *  SDK.
 *  
 *  @param authorized `YES` to authorize DJI server to access the data.
 *  
 *  @return The encountered error if there is any.
 */
-(NSError *)authorizeAccessToDJIDeviceHardwareInfo:(BOOL)authorized;


/**
 *  Determines if DJI device's hardware information is accessible by DJI server.
 *  
 *  @return `YES` if it is authorized.
 */
-(BOOL)isAccessToDJIDeviceHardwareInfoAuthorized;


/**
 *  Determines if the obfuscated location of either the mobile device or the DJI
 *  device is accessible by DJI server. The  precise location is obfuscated with a
 *  random offset from range (5km - 10km) before sending to DJI server. Because of
 *  policy reasons, this is authorized by default and it cannot be turned off. The
 *  obfuscated location is used to update  the fly zones around the user.
 *  
 *  @return `YES` if it is authorized.
 */
-(BOOL)isAccessToObfuscatedLocationAuthorized;

@end
