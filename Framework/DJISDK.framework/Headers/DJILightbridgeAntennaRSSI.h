//
//  DJILightbridgeAntennaRSSI.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 *  RSSI object (received signal strength indicator).
 */
@interface DJILightbridgeAntennaRSSI : NSObject


/**
 *  Antenna1 RSSI value
 *  
 *  @return An int value of antenna RSSI.
 */
@property (nonatomic, assign, readonly) int antenna1;


/**
 *  Antenna2 RSSI value
 *  
 *  @return An int value of antenna RSSI.
 */
@property (nonatomic, assign, readonly) int antenna2;

@end
