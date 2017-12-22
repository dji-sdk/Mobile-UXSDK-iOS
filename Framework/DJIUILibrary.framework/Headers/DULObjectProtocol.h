//
//  DULObjectProtocol.h
//  DJIUILibrary
//
//  Created by RussFenenga on 11/3/17.
//  Copyright © 2017 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJISDK.h>

#import <DJIUILibrary/DULSDKModel.h>
#import <DJIUILibrary/DULSDKModelValue.h>


/**
 *  Protocol that provides interfaces for getting updates on keys.
 */
@protocol DULObjectProtocol <NSObject>

@required


/**
 *  An array of DJIKey to be used by the UILibrary CoreModel in order to retrieve
 *  data from the SDK automatically.
 *  
 *  @return the list of dependent keys
 */
- (nonnull NSArray <__kindof DJIKey *> *)dependentKeys;


/**
 *  This method is called by the UILibrary CoreModel when a value has been received
 *  from the aircraft. It is the entry point in the object for aircraft data.
 *  
 *  @param value the value associated with the key.
 *  @param key the SDK key as registered in the dependentKey
 */
- (void)transformValue:(nonnull DULSDKModelValue *)value forKey:(nonnull __kindof DJIKey *)key;


/**
 *  Method that is automatically called once the data has been used by transform.
 */
- (void)update;

@end
