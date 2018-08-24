//
//  DUXConnectionWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DUXWidget.h>


/**
 *  Display:
 *  Widget has two states representing by two icons. Red triangle icon indicates
 *  there is no connection with the product. Green circle icon indicates there is
 *  connection with the product.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 1:1.
 */
@interface DUXConnectionWidget : DUXWidget


/**
 *  YES if mobile device is connected to aircraft.
 */
@property BOOL isConnected;

@end
