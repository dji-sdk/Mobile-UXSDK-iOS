//
//  DULWidgetItem.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DULWidgetProtocol.h"


/**
 *  A carrying object that associates a widgets with additional layout-related
 *  attributes.
 */
@interface DULWidgetItem : NSObject


/**
 *  The associated widget.
 */
@property UIView <DULWidgetProtocol> *widget;


/**
 *  The edget inset attributes. These will be a padding around the widget inside its
 *  collection.
 */
@property UIEdgeInsets edgeInset;

@end
