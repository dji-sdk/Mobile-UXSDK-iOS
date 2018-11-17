//
//  DJIBluetoothProductConnector.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DJISDKFoundation.h"
@class CBPeripheral;


/**
 *  This protocol provides the delegate method that receives the list of DJI
 *  products that can be controlled by the Mobile SDK using a Bluetooth connection
 *  from the mobile device.
 */
@protocol DJIBluetoothProductConnectorDelegate <NSObject>


/**
 *  Provides the list of DJI products that can be connected with the mobile device
 *  over Bluetooth. Delegate will  continue to receive an updated list after
 *  `searchBluetoothProductsWithCompletion` is called  until the searching is
 *  finished (either product is connected or after 10s).
 *  
 *  @param peripherals A list of DJI products found by the connector.
 */
- (void)connectorDidFindProducts:(NSArray<CBPeripheral *>* _Nullable)peripherals;

@end


/**
 *  Some DJI products can be controlled using the Mobile SDK over a Bluetooth
 *  wireless  connection. This class contains methods to search for, connect to, and
 *  disconnect from such products.
 */
@interface DJIBluetoothProductConnector : NSObject


/**
 *  Delegate that receives the product list found by the connector.
 */
@property(nonatomic, weak) id<DJIBluetoothProductConnectorDelegate> _Nullable delegate;


/**
 *  Used to start searching for DJI Products that are near the mobile device and can
 *  be controlled with the Mobile  SDK using Bluetooth. Use
 *  `connectorDidFindProducts` to receive the product list.
 *  
 *  @param completion Completion block returns the command execution result. It is called once the searching is started.
 */
- (void)searchBluetoothProductsWithCompletion:(DJICompletionBlock)completion;


/**
 *  Connects to the DJI product using Bluetooth. Once it is connected,
 *  `DJISDKManager` can be used to access the product.
 *  
 *  @param product The Bluetooth product to connect to.
 *  @param completion The completion block returns the command execution result.
 */
- (void)connectProduct:(CBPeripheral *_Nullable)product
        withCompletion:(DJICompletionBlock)completion;


/**
 *  Disconnects connected Bluetooth product.
 *  
 *  @param completion The completion block returns the command execution result.
 */
- (void)disconnectProductWithCompletion:(DJICompletionBlock)completion;

@end
