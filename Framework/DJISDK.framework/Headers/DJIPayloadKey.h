//
//  DJIPayloadKey.h
//  DJISDK
//
//  Copyright © 2018, DJI. All rights reserved.
//

#import "DJIKey.h"

NS_ASSUME_NONNULL_BEGIN

EXTERN_KEY NSString *const DJIPayloadComponent;

EXTERN_KEY NSString *const DJIPayloadParamUpstreamBandwidth;
EXTERN_KEY NSString *const DJIPayloadParamMaximumContractedVolume;
EXTERN_KEY NSString *const DJIPayloadParamPayloadAllWidgets;
EXTERN_KEY NSString *const DJIPayloadParamConfigureWidgetValue;


/**
 *  `DJIPayloadKey` provides dedicated access to Flight  controller attributes.
 */
@interface DJIPayloadKey : DJIKey

@end

NS_ASSUME_NONNULL_END
