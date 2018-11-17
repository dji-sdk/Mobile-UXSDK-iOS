//
//  DJIKeyManager.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIKey;
@class DJIKeyedValue;


/**
 *  The completion block called when performing a get on a key.
 *  
 *  @param value An optional value returned as a result of the get. Nil if no value exists yet or if an error is returned.
 *  @param error An optional error object in case the call failed.
 */
typedef void (^DJIKeyedGetCompletionBlock)(DJIKeyedValue * _Nullable value, NSError * _Nullable error);


/**
 *  The completion block called when performing a set on a key.
 *  
 *  @param error An optional error in case the call failed.
 */
typedef void (^DJIKeyedSetCompletionBlock)(NSError * _Nullable error);


/**
 *  The completion block called when performing an action on a key.
 *  
 *  @param finished Whether or not the action finished.
 *  @param response The optional response value of the action.
 *  @param error The option error in case the call failed.
 */
typedef void (^DJIKeyedActionCompletionBlock)(BOOL finished, DJIKeyedValue * _Nullable response, NSError * _Nullable error);


/**
 *  The completion block, called every time the value behind a key is updated.
 *  
 *  @param oldValue The old value. `nil` if no value was present before.
 *  @param newValue The new value. `nil` if the stored values are being flushed.
 */
typedef void (^DJIKeyedListenerUpdateBlock)(DJIKeyedValue * _Nullable oldValue, DJIKeyedValue * _Nullable newValue);


/**
 *  `DJIKeyManager` provides access to the keyed interface using `DJIKey` and
 *  corresponding subclass objects. `DJIKeyManager` is accessed from `keyManager` in
 *  `DJISDKManager`.
 */
@interface DJIKeyManager : NSObject

- (instancetype)init OBJC_UNAVAILABLE("You must use the singleton");

+ (instancetype)new OBJC_UNAVAILABLE("You must use the singleton");


/**
 *  Returns the latest known value if available for the key.  Does not pull it from
 *  the product if unavailable.
 *  
 *  @param key A valid gettable key
 *  
 *  @return A value object or `nil` if no previous value was stored.
 */
- (nullable DJIKeyedValue *)getValueForKey:(DJIKey *)key;


/**
 *  Performs a get on a gettable key, pulling the information from the product if
 *  necessary.
 *  
 *  @param key A valid gettable key
 *  @param completion A valid get completion block.
 */
- (void)getValueForKey:(DJIKey *)key
        withCompletion:(DJIKeyedGetCompletionBlock)completion;


/**
 *  Performs a set on a settable key, changing attributes on the  connected product.
 *  
 *  @param value A value object relevant to the given key
 *  @param key A valid settable key
 *  @param completion A set completion block.
 */
- (void)setValue:(id)value
          forKey:(DJIKey *)key
        withCompletion:(DJIKeyedSetCompletionBlock)completion;


/**
 *  Performs an action on an actionable key.
 *  
 *  @param key A valid actionable key
 *  @param arguments Optional arguments relevant to the specific key
 *  @param completion An action completion block.
 */
- (void)performActionForKey:(DJIKey *)key
              withArguments:(nullable NSArray *)arguments
              andCompletion:(DJIKeyedActionCompletionBlock)completion;


/**
 *  Subscribes the listener object to all changes of value on the given  key.
 *  
 *  @param key A valid value-based key (get, set and/or action)
 *  @param listener A valid object to hold the subscription
 *  @param updateBlock A valid update block
 */
- (void)startListeningForChangesOnKey:(DJIKey *)key
                         withListener:(id)listener
                       andUpdateBlock:(DJIKeyedListenerUpdateBlock)updateBlock;


/**
 *  Stops the subscription to updates of a specific key value for a  specific
 *  listener. Does not affect other listeners subscribing to  this key or other
 *  subscriptions of the `listener`.
 *  
 *  @param key A valid value-based key
 *  @param listener A listener object that is subscribed to the `key` that was setup with `startListeningForChangesOnKey:withListener:andUpdateBlock`.
 */
- (void)stopListeningOnKey:(DJIKey *)key
               ofListener:(id)listener;


/**
 *  Stops all subscriptions on all key value updates for the given listener.
 *  
 *  @param listener The listener object passed to `startListeningForChangesOnKey:withListener:andUpdateBlock`.
 */
- (void)stopAllListeningOfListeners:(id)listener;


/**
 *  Determines if a key is supported by the connected product.
 *  
 *  @param key Key to be check on current product.
 *  
 *  @return `YES` if the key is supported.
 */
- (BOOL)isKeySupported:(DJIKey *)key;

@end

NS_ASSUME_NONNULL_END
