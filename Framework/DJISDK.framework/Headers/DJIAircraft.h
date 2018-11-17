//
//  DJIAircraft.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIBaseProduct.h>

@class DJIFlightController;
@class DJIRemoteController;
@class DJIMobileRemoteController;
@class DJIAccessoryAggregation;

NS_ASSUME_NONNULL_BEGIN


/**
 *  The Aircraft's model name is unknown.
 */
extern NSString *const DJIAircraftModelNameUnknownAircraft;


/**
 *  The aircraft's model name is Inspire 1.
 */
extern NSString *const DJIAircraftModelNameInspire1;


/**
 *  The aircraft's model name is Inspire 1 Pro.
 */
extern NSString *const DJIAircraftModelNameInspire1Pro;


/**
 *  The aircraft's model name is Inspire 1 Raw.
 */
extern NSString *const DJIAircraftModelNameInspire1RAW;


/**
 *  The aircraft's model name is Phantom 3 Professional.
 */
extern NSString *const DJIAircraftModelNamePhantom3Professional;


/**
 *  The aircraft's model name is Phantom 3 Advanced.
 */
extern NSString *const DJIAircraftModelNamePhantom3Advanced;


/**
 *  The aircraft's model name is Phantom 3 Standard.
 */
extern NSString *const DJIAircraftModelNamePhantom3Standard;


/**
 *  The aircraft's model name is Phantom 3 4K.
 */
extern NSString *const DJIAircraftModelNamePhantom34K;


/**
 *  The aircraft's model name is Matrice 100.
 */
extern NSString *const DJIAircraftModelNameMatrice100;


/**
 *  The aircraft's model name is Phantom 4.
 */
extern NSString *const DJIAircraftModelNamePhantom4;


/**
 *  The aircraft's model name is Matrice 600.
 */
extern NSString *const DJIAircraftModelNameMatrice600;


/**
 *  The aircraft's model name is Matrice 600 Pro.
 */
extern NSString *const DJIAircraftModelNameMatrice600Pro;


/**
 *  The aircraft flight controller's model name is A3.
 */
extern NSString *const DJIAircraftModelNameA3;


/**
 *  The aircraft flight controller's model name is N3.
 */
extern NSString *const DJIAircraftModelNameN3;


/**
 *  The aircraft's model name is Mavic Pro.
 */
extern NSString *const DJIAircraftModelNameMavicPro;


/**
 *  The aircraft's model name is Phantom 4 Pro.
 */
extern NSString *const DJIAircraftModelNamePhantom4Pro;


/**
 *  The aircraft's model name is Phantom 4 Pro V2.
 */
extern NSString *const DJIAircraftModelNamePhantom4ProV2;


/**
 *  The aircraft's model name is Inspire 2.
 */
extern NSString *const DJIAircraftModelNameInspire2;


/**
 *  The aircraft's model name is Matrice 200.
 */
extern NSString *const DJIAircraftModelNameMatrice200;


/**
 *  The aircraft's model name is Phantom 4 Advanced.
 */
extern NSString *const DJIAircraftModelNamePhantom4Advanced;


/**
 *  The aircraft's model name is Spark.
 */
extern NSString *const DJIAircraftModelNameSpark;


/**
 *  The aircraft's model name is Matrice 210.
 */
extern NSString *const DJIAircraftModelNameMatrice210;


/**
 *  The aircraft's model name is Matrice 210 RTK.
 */
extern NSString *const DJIAircraftModelNameMatrice210RTK;


/**
 *  The aircraft's model name is Mavic Air.
 */
extern NSString *const DJIAircraftModelNameMavicAir;


/**
 *  The aircraft's model name is Mavic 2 Pro.
 */
extern NSString *const DJIAircraftModelNameMavic2Pro;


/**
 *  The aircraft's model name is Mavic 2 Zoom.
 */
extern NSString *const DJIAircraftModelNameMavic2Zoom;


/**
 *  The aircraft's model name is either Mavic 2 Pro or Mavic 2 Zoom.  The camera is
 *  not recognized yet.
 */
extern NSString *const DJIAircraftModelNameMavic2;


/**
 *  The aircraft's model name is Mavic 2 Enterprise.
 */
extern NSString *const DJIAircraftModelNameMavic2Enterprise;


/**
 *  The display name when only the remote controller is connected.
 */
extern NSString *const DJIAircraftModeNameOnlyRemoteController;


/**
 *  Aircraft product class, which includes basic product information and access to
 *  all components (such as flight controller, battery etc.). This object is
 *  accessed from `product` in `DJISDKManager`. Aircraft components are defined in
 *  both `DJIAircraft` and its parent `DJIBaseProduct`.
 */
@interface DJIAircraft : DJIBaseProduct



/**
 *  Returns an instance of the aircraft's flight controller.
 */
@property(nonatomic, readonly) DJIFlightController *_Nullable flightController;


/**
 *  Returns an array of the aircraft's batteries. It is used when the aircraft has
 *  multiple batteries, e.g. Matrice 600.
 */
@property(nonatomic, readonly) NSArray<DJIBattery *> *_Nullable batteries;


/**
 *  Retrieves instances of the product's cameras. This is used when the aircraft has
 *  multiple DJI cameras, e.g. M210 and  M210 RTK. Note, when two cameras do exist,
 *  camera order within the array will not always the same. For example: On the
 *  M210, the port side (left) camera will have property `index` to be 0 and the
 *  starboard side (right)  camera will have `index` to be 1. However, the first
 *  object of `cameras` will not  necessarily always be the camera with `index` of
 *  0.
 */
@property(nonatomic, readonly) NSArray<DJICamera *> *_Nullable cameras;


/**
 *  Retrieves instances of the product's gimbals. This is used when the aircraft has
 *  multiple DJI gimbals, e.g. M210  and M210 RTK. Note, when two gimbals do exist,
 *  gimbal order within the array will not always the same. For example:  On the
 *  M210, the port side (left) gimbal will have property `index` to be 0 and the
 *  starboard  side (right) gimbal will have `index` to be 1. However, the first
 *  object of `gimbals`  will not necessarily always be the gimbal with `index` of
 *  0.
 */
@property(nonatomic, readonly) NSArray<DJIGimbal *> *_Nullable gimbals;


/**
 *  Returns an instance of the aircraft's remote controller.
 */
@property(nonatomic, readonly) DJIRemoteController *_Nullable remoteController;


/**
 *  A simulated remote controller on the mobile device. It is supported by Mavic Pro
 *  and Spark using WiFi.
 */
@property(nonatomic, readonly) DJIMobileRemoteController *_Nullable mobileRemoteController;


/**
 *  The connected payload instance.
 */
@property(nonatomic, readonly) DJIPayload *_Nullable payload;


/**
 *  The container of accessories on the aircraft. It is accessible when the
 *  connected  aircraft supports extra accessories.
 */
@property(nonatomic, readonly) DJIAccessoryAggregation *_Nullable accessoryAggregation;


/**
 *  Retrieves instances of the product's payloads. This is used when the aircraft
 *  has multiple gimbal slots,  e.g. M210 and  M210 RTK. Note, when two payload
 *  instances do exist, the order within the array will not  always be the same. For
 *  example: On the M210, the port side (left) payload will have property index to
 *  be  0 and the starboard side (right) payload will have index to be 1. However,
 *  the first object of `cameras`  will not necessarily always be the payload with
 *  index of 0.
 */
@property(nonatomic, readonly) NSArray<DJIPayload *> *_Nullable payloads;

@end
NS_ASSUME_NONNULL_END
