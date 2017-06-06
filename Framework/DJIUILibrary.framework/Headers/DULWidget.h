//
//  DULWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <DJISDK/DJISDK.h>

#import "DULWidgetProtocol.h"
#import "UIImage+Assets.h"

IB_DESIGNABLE

/**
 *  DULWidget is the base class of all widgets in the UILibrary. It is the default
 *  implementation of a UIView that implements the `DULWidgetProtocol`.
 */
@interface DULWidget : UIView <DULWidgetProtocol, NSCopying>


/**
 *  The aspect ratio of the widget in width/height. This value may change. A widget
 *  with a variable aspectRatio inside a widget collection will request the
 *  collection to invalidate its layout. Default is 1.0.
 */
@property IBInspectable CGFloat aspectRatio;


/**
 *  If this widget is in a collection view, this will be set to that view when
 *  adding the widget to the collection.
 */
@property (nullable, nonatomic, weak) DULWidgetCollectionView *collectionView;


/**
 *  The level of interaction that is expected by the widget. Some widget collections
 *  will carry a specific expectation for interaction. This information may be used
 *  by the widget in order to adjust its behavior slightly based on where it sits in
 *  the UI.
 */
@property IBInspectable DULWidgetInteractionExpectionLevel interactionExpectationLevel;


/**
 *  An action block that defines wether or not a widget will trigger an action and
 *  what action it will trigger on TouchUp Inside.
 */
@property (strong, nonatomic, nullable) DULWidgetActionBlock action;


/**
 *  prepareWidget is called after init to allow you to customize basic information
 *  about the widget such as aspectRatio and interactionExpectationLevel.
 */
- (void)prepareWidget;

@end
