//
//  DULWidgetProtocol.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJISDK.h>

#import "DULSDKModel.h"
#import "DULSDKModelValue.h"


/**
 *  Action block for Widget.
 */
typedef void (^DULWidgetActionBlock)();


/**
 *  Interteraction level expected by a widget. May be used to have different
 *  behavior implementation in a single widget depending on this value.
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
@protocol DULWidgetProtocol <NSObject>

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
 *  An action block that defines wether or not a widget will trigger an action and
 *  what action it will trigger on TouchUp Inside.
 */
@property (strong, nonatomic, nullable) DULWidgetActionBlock action;


/**
 *  An array of DJIKey to be used by the UILibrary CoreModel in order to retrieve
 *  data from the SDK automatically.
 *  
 *  @return the list of dependent keys
 */
- (nonnull NSArray <__kindof DJIKey *> *)dependentKeys;


/**
 *  This method is called by the UILibrary CoreModel when a value has been received
 *  from the drone. It is the entry point in the widget for drone data. @param value
 *  A valid DULSDKModelValue object containing the value associated with the DJIKey
 *  @param key The original key that was registered as a dependentKey
 *  
 *  @param value the value associated with the key.
 *  @param key the SDK key as registered in the dependentKey
 */
- (void)transformValue:(nonnull DULSDKModelValue *)value forKey:(nonnull __kindof DJIKey *)key;


/**
 *  Method that triggers drawing. Automatically called once after the action block
 *  is triggered and again after data has been used by transform.
 */
- (void)update;


@end
