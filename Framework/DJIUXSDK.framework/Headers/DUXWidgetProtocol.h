//
//  DUXWidgetProtocol.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJISDK.h>

#import <DJIUXSDK/DUXSDKModel.h>
#import <DJIUXSDK/DUXSDKModelValue.h>
#import <DJIUXSDK/DUXObjectProtocol.h>


/**
 *  Action block for Widget.
 */
typedef void (^DUXWidgetActionBlock)();


/**
 *  Interaction level expected by a widget. May be used to have different behavior
 *  implementation in a single widget depending on this value.
 */
typedef NS_ENUM(NSUInteger, DUXWidgetInteractionExpectionLevel) {

    /**
     *  No interaction expected.
     */
    DUXWidgetInteractionExpectionLevelNone,

    /**
     *  Full interaction expected.
     */
    DUXWidgetInteractionExpectionLevelFull,
};

@class DUXWidgetCollectionView;


/**
 *  This protocol defines the behavior of a widget. This is usually to be
 *  implemented by a subclass of UIView
 */
@protocol DUXWidgetProtocol <NSObject, DUXObjectProtocol>

@required


/**
 *  The aspect ratio of the widget design. Used by the widgetCollection to provide a
 *  resolution independant size that will fit the needs of the widget.
 */
@property CGFloat aspectRatio;


/**
 *  The optional widget collection view that contains the widget. This allows some
 *  widgets to let the collection know that they have resizing need.
 */
@property (nullable, nonatomic, weak) DUXWidgetCollectionView *collectionView;


/**
 *  Defines the level of interaction that is expected from the Widget. For instance,
 *  a widget with a None level is not expected to provide any touch handling. On the
 *  other hand, a widget with a Full level is expected to provide touch handling and
 *  events.
 */
@property DUXWidgetInteractionExpectionLevel interactionExpectationLevel;


/**
 *  An action block that defines whether or not a widget will trigger an action and
 *  what action it will trigger on TouchUp Inside.
 */
@property (strong, nonatomic, nullable) DUXWidgetActionBlock action;


@end
