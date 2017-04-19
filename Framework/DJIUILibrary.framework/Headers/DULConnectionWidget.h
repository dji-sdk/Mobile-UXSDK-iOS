//
//  DULConnectionWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import "DULWidget.h"

IB_DESIGNABLE

/**
 *  Display:
 *  Widget has two states representing by two icons. Red triangle icon indicates
 *  there is no connection with the product. Green circle icon indicates there is
 *  connection with the product.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 1:1.
 */
@interface DULConnectionWidget : DULWidget


/**
 *  YES if mobile device is connected to aircraft.
 */
@property IBInspectable BOOL isConnected;

@end
