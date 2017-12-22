//
//  DULWidgetProtocol.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJISDK.h>

#import <DJIUILibrary/DULSDKModel.h>
#import <DJIUILibrary/DULSDKModelValue.h>
#import <DJIUILibrary/DULObjectProtocol.h>


/**
 *  Action block for Widget.
 */
typedef void (^DULWidgetActionBlock)();


/**
 *  Interaction level expected by a widget. May be used to have different behavior
 *  implementation in a single widget depending on this value.
 */
typedef NS_ENUM(NSUInteger, DULWidgetInteractionExpectionLevel) {

    /**
     *  No interaction expected.
     */
    DULWidgetInteractionExpectionLevelNone,

    /**
     *  Full interaction expected.
     */
    DULWidgetInteractionExpectionLevelFull,
};

@class DULWidgetCollectionView;


/**
 *  This protocol defines the behavior of a widget. This is usually to be
 *  implemented by a subclass of UIView
 */
@protocol DULWidgetProtocol <NSObject, DULObjectProtocol>

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
@property (nullable, nonatomic, weak) DULWidgetCollectionView *collectionView;


/**
 *  Defines the level of interaction that is expected from the Widget. For instance,
 *  a widget with a None level is not expected to provide any touch handling. On the
 *  other hand, a widget with a Full level is expected to provide touch handling and
 *  events.
 */
@property DULWidgetInteractionExpectionLevel interactionExpectationLevel;


/**
 *  An action block that defines whether or not a widget will trigger an action and
 *  what action it will trigger on TouchUp Inside.
 */
@property (strong, nonatomic, nullable) DULWidgetActionBlock action;


@end
