//
//  DJIProductKey.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import "DJIKey.h"

NS_ASSUME_NONNULL_BEGIN

EXTERN_KEY NSString *const DJIDefaultProduct;
EXTERN_KEY NSString *const DJIProductParamModelName;

EXTERN_KEY NSString *const DJIParamFirmwareVersion;
EXTERN_KEY NSString *const DJIParamSerialNumber;


/**
 *  `DJIProductKey` represent keys which are global to the whole product.
 */
@interface DJIProductKey : DJIKey


/**
 *  Convenience key creator that give access to the product model name.
 *  
 *  @return A valid DJIProductKey object configured to access the product model name.
 */
+ (nullable instancetype)modelNameKey;

@end

NS_ASSUME_NONNULL_END
