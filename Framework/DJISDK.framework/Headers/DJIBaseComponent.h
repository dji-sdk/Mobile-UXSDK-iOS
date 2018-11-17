//
//  DJIBaseComponent.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <DJISDK/DJISDKFoundation.h>
#import <DJISDK/DJIBaseProduct.h>

NS_ASSUME_NONNULL_BEGIN
@class DJIBaseComponent;
@class DJIBaseProduct;


/**
 *  Abstract class for components in a DJI Product. A component can be a camera,
 *  gimbal, remote controller, etc. A DJI product consists of several components.
 *  All components of a product are subclasses of `DJIBaseComponent` and can be
 *  accessed directly from the product objects (`DJIAircraft` or `DJIHandheld`).
 */
@interface DJIBaseComponent : NSObject


/**
 *  Returns the component index. Index is zero based. A component will have an index
 *  greater than zero when there  are multiple components of the same type on the
 *  DJI product, and one of the components already has the index 0.  For instance,
 *  M210 can have two gimbal mounted cameras, and will therefore have two gimbal
 *  components with indices  0 and 1, and two camera components with indices 0 and
 *  1. For Matrice 600, there are printed numbers on the battery  boxes. The
 *  `DJIBattery` component instance with index 0 corresponds to battery compartment
 *  number 1. For Inspire 2  and M200 series, `DJIBattery` with index 0 corresponds
 *  to the battery on the port (left hand) side of the aircraft.  For M210 and M210
 *  RTK, `DJICamera` and `DJIGimbal` with index 0 corresponds to the camera and
 *  gimbal on the port  (left hand) side of the aircraft.
 */
@property (nonatomic, assign, readonly) NSUInteger index;


/**
 *  `YES` if the component is connected.
 */
@property (assign, nonatomic, readonly, getter = isConnected) BOOL connected;


/**
 *  Returns the firmware version of the component. Each component will  have a
 *  different firmware version, the combination of which will  form the package
 *  firmware version `getFirmwarePackageVersionWithCompletion` found in
 *  `DJIBaseProduct`.
 *  
 *  @param version The component's firmware version.
 *  @param error Error retrieving the value.
 *  @param block Completion block
 */
- (void)getFirmwareVersionWithCompletion:(void (^)(NSString *_Nullable version, NSError *_Nullable error))block;


/**
 *  Gets the serial number of the component. Depending on the component, this serial
 *  number might not match the serial number found  on the physical component.
 *  
 *  @param serialNumber The serial number of the component.
 *  @param error Error retrieving the value.
 *  @param block Completion block that receives the getter result.
 */
- (void)getSerialNumberWithCompletion:(void (^)(NSString *_Nullable serialNumber, NSError *_Nullable error))block;

@end

NS_ASSUME_NONNULL_END
