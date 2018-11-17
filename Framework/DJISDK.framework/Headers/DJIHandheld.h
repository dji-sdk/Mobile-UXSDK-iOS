//
//  DJIHandheld.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIBaseProduct.h>

@class DJIFlightController;
@class DJIHandheldController;


NS_ASSUME_NONNULL_BEGIN


/**
 *  Handheld device model name unknown.
 */
extern NSString *const DJIHandheldModelNameUnknownHandheld;


/**
 *  Handheld device model name Osmo.
 */
extern NSString *const DJIHandheldModelNameOsmo;


/**
 *  Handheld device model name Osmo Pro.
 */
extern NSString *const DJIHandheldModelNameOsmoPro;


/**
 *  Handheld device model name Osmo RAW.
 */
extern NSString *const DJIHandheldModelNameOsmoRAW;


/**
 *  Handheld device model name Osmo Mobile.
 */
extern NSString *const DJIHandheldModelNameOsmoMobile;


/**
 *  Handheld device model name Osmo+.
 */
extern NSString *const DJIHandheldModelNameOsmoPlus;


/**
 *  Handheld device model name Osmo Mobile 2.
 */
extern NSString *const DJIHandheldModelNameOsmoMobile2;


/**
 *  Handheld product class, which includes basic product information and access to
 *  all components (such as camera, battery etc.). This object is accessed from
 *  `product` in `DJISDKManager`.
 */
@interface DJIHandheld : DJIBaseProduct


/**
 *  Returns an instance of the handheld device's handheld controller.
 */
@property(nonatomic, readonly) DJIHandheldController *_Nullable handheldController;

@end

NS_ASSUME_NONNULL_END
