//
//  DUXObjectProtocol.h
//  DJIUXSDK
//
//  Created by RussFenenga on 11/3/17.
//  Copyright © 2017 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJISDK.h>

#import <DJIUXSDK/DUXSDKModel.h>
#import <DJIUXSDK/DUXSDKModelValue.h>


/**
 *  Protocol that provides interfaces for getting updates on keys.
 */
@protocol DUXObjectProtocol <NSObject>

@required


/**
 *  An array of DJIKey to be used by the UXSDK CoreModel in order to retrieve data
 *  from the SDK automatically.
 *  
 *  @return the list of dependent keys
 */
- (nonnull NSArray <__kindof DJIKey *> *)dependentKeys;


/**
 *  This method is called by the UXSDK CoreModel when a value has been received from
 *  the aircraft. It is the entry point in the object for aircraft data.
 *  
 *  @param value the value associated with the key.
 *  @param key the SDK key as registered in the dependentKey
 */
- (void)transformValue:(nonnull DUXSDKModelValue *)value forKey:(nonnull __kindof DJIKey *)key;

@optional

/**
 *  Method that is automatically called once the data has been used by transform.
 */
- (void)update;

@end
