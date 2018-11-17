//
//  DJIKeyedValue.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIParamCapabilityMinMax;


/**
 *  `DJIKeyedValue` is a container object for values associated with  `DJIKey`
 *  objects. The raw value is held inside `value` and  convenience methods are
 *  offers for quicker access.
 */
@interface DJIKeyedValue : NSObject


/**
 *  The raw value object. For struct, the value is held in an NSValue.
 */
@property (readonly, nonatomic, nullable) id value;


/**
 *  Convenience accessor to char value.
 */
@property (readonly, nonatomic) char charValue;


/**
 *  Convenience accessor to unsigned char value.
 */
@property (readonly, nonatomic) unsigned char unsignedCharValue;


/**
 *  Convenience accessor to short value.
 */
@property (readonly, nonatomic) short shortValue;


/**
 *  Convenience accessor to unsigned short value.
 */
@property (readonly, nonatomic) unsigned short unsignedShortValue;


/**
 *  Convenience accessor to int value.
 */
@property (readonly, nonatomic) int intValue;


/**
 *  Convenience accessor to unsigned int value.
 */
@property (readonly, nonatomic) unsigned int unsignedIntValue;


/**
 *  Convenience accessor to long value.
 */
@property (readonly, nonatomic) long longValue;


/**
 *  Convenience accessor to unsigned long value.
 */
@property (readonly, nonatomic) unsigned long unsignedLongValue;


/**
 *  Convenience accessor to long long value.
 */
@property (readonly, nonatomic) long long longLongValue;


/**
 *  Convenience accessor to unsigned long long value.
 */
@property (readonly, nonatomic) unsigned long long unsignedLongLongValue;


/**
 *  Convenience accessor to float value.
 */
@property (readonly, nonatomic) float floatValue;


/**
 *  Convenience accessor to double value.
 */
@property (readonly, nonatomic) double doubleValue;


/**
 *  Convenience accessor to bool value.
 */
@property (readonly, nonatomic) BOOL boolValue;


/**
 *  Convenience accessor to NSInteger value.
 */
@property (readonly, nonatomic) NSInteger integerValue;


/**
 *  Convenience accessor to NSUInteger value.
 */
@property (readonly, nonatomic) NSUInteger unsignedIntegerValue;


/**
 *  Convenience accessor to string value.
 */
@property (readonly, nonatomic, nullable, copy) NSString *stringValue;


/**
 *  Convenient accessor to the parameter range. `nil` if `value` is not in a  type
 *  of `DJIParamCapabilityMinMax`.
 */
@property (readonly, nonatomic, nullable) DJIParamCapabilityMinMax *paramRange;

@end

NS_ASSUME_NONNULL_END
