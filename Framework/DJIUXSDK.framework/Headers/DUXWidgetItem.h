//
//  DUXWidgetItem.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJIUXSDK/DUXWidgetProtocol.h>


/**
 *  A carrying object that associates a widgets with additional layout-related
 *  attributes.
 */
@interface DUXWidgetItem : NSObject


/**
 *  The associated widget.
 */
@property UIView <DUXWidgetProtocol> *widget;


/**
 *  The edget inset attributes. These will be a padding around the widget inside its
 *  collection.
 */
@property UIEdgeInsets edgeInset;

@end
