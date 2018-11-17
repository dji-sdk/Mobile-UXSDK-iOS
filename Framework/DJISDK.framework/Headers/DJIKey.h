//
//  DJIKey.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#define EXTERN_KEY       extern __attribute__((visibility("default")))


/**
 *  Param to check product's and components' connection state. It can be used with
 *  `DJIProductKey` or other component key classes (e.g. `DJICameraKey`).
 */
EXTERN_KEY NSString *const DJIParamConnection;


/**
 *  Base class of all keys to be used with the keyed interface and the
 *  `DJIKeyManager`.
 */
@interface DJIKey : NSObject


/**
 *  Defines whether or not the key is to be used with components of the  product
 */
@property (nonatomic) BOOL isComponentKey;


/**
 *  Defines whether or not the key is to be used with missions. (Mission Control
 *  only)
 */
@property (nonatomic) BOOL isMissionKey;


/**
 *  The param part of the key.
 */
@property (readonly, nonatomic, nullable) NSString *param;


/**
 *  The component index of the key. Index is zero based. A component will have an
 *  index greater than  zero when there are multiple components of the same type on
 *  the DJI product, and one of the  components already has the index 0.
 */
@property (readonly, nonatomic) NSInteger index;


/**
 *  The sub-component index of the key. Index is zero based. Currently, no product
 *  supports multiple  sub-components of the same type, so it is always 0.
 */
@property (readonly, nonatomic) NSInteger subComponentIndex;


/**
 *  The subElement of the key if it exists.
 */
@property (readonly, nonatomic, nullable) NSString *subComponent;


/**
 *  Convenience creator of a key by only specifying the param to be used.
 *   This is mostly useful in DJIKey subclasses.
 *  
 *  @param param A valid String-formatted key as defined in DJIKey's subclasses headers
 *  
 *  @return A valid key object or `nil` if an error occurred.
 */
+ (nullable instancetype)keyWithParam:(nonnull NSString *)param;


/**
 *  Convenience creator of a key by specifying the index of the element and the
 *  parameter of the key
 *  
 *  @param index The index of the element. In the case of multiple components these would refer to their index.
 *  @param param A valid string-formatted key as defined in DJIKey's subclasses headers.
 *  
 *  @return A valid key object or nil if an error occurred.
 */
+ (nullable instancetype)keyWithIndex:(NSInteger)index
                             andParam:(nonnull NSString *)param;

/**
 *  Full creator of a key allowing to specify subelement, subindex and parameters.
 *  
 *  @param index The index of the element
 *  @param subComponent The sub element string-formatted key as defined in DJIKey's subclasses headers.
 *  @param subIndex The sub element index.
 *  @param param The string-formatted key as defined in DJIKey's subclasses headers.
 *  
 *  @return A valid key object or nil if an error occurred.
 */
+ (nullable instancetype)keyWithIndex:(NSInteger)index
                         subComponent:(nonnull NSString *)subComponent
                    subComponentIndex:(NSInteger)subIndex
                             andParam:(nonnull NSString *)param;

@end

NS_ASSUME_NONNULL_END
