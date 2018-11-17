//
//  DJIParamCapabilityMinMax.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#import "DJIParamCapability.h"


/**
 *  Adds the maximum and minimum possible values of the parameter to  the
 *  `DJIParamCapability` base class.
 */
@interface DJIParamCapabilityMinMax : DJIParamCapability


/**
 *  The valid minimum value of the  parameter for the product. If `isSupported`
 *  returns `NO`, the value is undefined.
 */
@property(nonatomic, readonly) NSNumber *min;


/**
 *  The valid maximum value of the  parameter for the product. If `isSupported`
 *  returns `NO`, the value is undefined.
 */
@property(nonatomic, readonly) NSNumber *max;

@end
