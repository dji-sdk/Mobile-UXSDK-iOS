//
//  DJIBaseProduct.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN



/**
 *  Completion block for asynchronous operations. This completion block is used for
 *  methods that return at an unknown future time.
 *  
 *  @param error An error object if an error occurred during async operation, or `nil` if no error occurred.
 */
typedef void (^_Nullable DJICompletionBlock)(NSError *_Nullable error);

@class DJIBaseComponent;
@class DJIBaseProduct;
@class DJIDiagnostics;
@class DJIVideoFeeder;
@class DJIGimbal;
@class DJIBattery;
@class DJICamera;
@class DJIAirLink;
@class DJIPayload;


/**
 *  This protocol provides delegate methods that notify user of changes in
 *  connectivity between the DJI product and the mobile device, changes in
 *  components that are part of the product, and diagnostic information from the
 *  product.
 */
@protocol DJIBaseProductDelegate <NSObject>

@optional


/**
 *  Called when the product's diagnostic information is updated.
 *  
 *  @param product An instance of `DJIBaseProduct`.
 *  @param info An NSArray of product's current diagnostics information.
 */
- (void)product:(DJIBaseProduct *_Nonnull)product didUpdateDiagnosticsInformation:(NSArray *_Nonnull)info;

@end


/**
 *  Abstract class for all DJI Products. `DJIAircraft` and `DJIHandheld` objects are
 *  subclasses of `DJIBaseProduct` and can be accessed from `product` in
 *  `DJISDKManager`. Additional components can be found in `DJIAircraft` and
 *  `DJIHandheld` that are unique to those products only.
 */
@interface DJIBaseProduct : NSObject


/**
 *  Used to notify user of changes in connectivity between the DJI product and the
 *  mobile device, changes in components that are part of the product, and
 *  diagnostic information from the product.
 */
@property (nonatomic, weak) id<DJIBaseProductDelegate> delegate;


/**
 *  Retrieves an instance of the device's camera.
 */
@property(nonatomic, readonly) DJICamera *_Nullable camera;


/**
 *  Retrieves an instance of the device's gimbal.
 */
@property(nonatomic, readonly) DJIGimbal *_Nullable gimbal;


/**
 *  Retrieves an instance of the product's smart battery. When using products with
 *  multiple batteries, such as the M600 or Inspire 2, use `batteries`, as this
 *  method will only return a single battery.
 */
@property(nonatomic, readonly) DJIBattery *_Nullable battery;


/**
 *  Retrieves an instance of the device's AirLink.
 */
@property(nonatomic, readonly) DJIAirLink *_Nullable airLink;


/**
 *  The videoFeeder.
 */
@property (nonatomic, readonly, nullable) DJIVideoFeeder *videoFeeder;


/**
 *  Gets the product's firmware package version. Products other than Phantom 4,
 *  Phantom 4 Pro, Mavic Pro, and Inspire 2, require internet connection. The
 *  execution time for this method depends on the speed of internet connectivity.
 *  
 *  @param version The product's firmware package version.
 *  @param error Error retrieving the value.
 *  @param block Completion block to receive the asynchronous result.
 */
- (void)getFirmwarePackageVersionWithCompletion:(void (^)(NSString *_Nullable version, NSError *_Nullable error))block;


/**
 *  Retrieves the model of the product.
 *  
 *  @param name Name to be set to the aircraft.
 *  @param completion Asynchronous execution result.
 */
- (void)setName:(NSString *)name withCompletion:(DJICompletionBlock)completion;


/**
 *  Retrieves the model of the product.
 *  
 *  @param name The device's name.
 *  @param error Error retrieving the value.
 *  @param completion Asynchronous execution result with name.
 */
- (void)getNameWithCompletion:(void (^)(NSString *_Nullable name, NSError *_Nullable error))completion;


/**
 *  Utility method to compare a version to the other.
 *  
 *  @param versionToTest Version string to compare.
 *  @param otherVersion Version string to compare.
 *  
 *  @return A boolean value.
 */
- (BOOL)isFirmwareVersion:(NSString *)versionToTest newerThanVersion:(NSString *)otherVersion;


/**
 *  Retrieves the model of the product. See `DJIAircraft` and `DJIHandheld` for the
 *  possible strings that can be returned.
 */
@property (nonatomic, strong, readonly) NSString *_Nullable model;

@end
NS_ASSUME_NONNULL_END
