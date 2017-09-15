//
//  DULWidgetCollectionViewProtocol.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <DJIUILibrary/DULWidget.h>

@class DULWidgetItem;
@class DULWidget;


/**
 *  This protocol defines the behavior expected for view to become widget collection
 *  views.
 */
@protocol DULWidgetCollectionViewProtocol <NSObject>

@required


/**
 *  The array of `DULWidgetItem` widgets items.
 */
@property (readonly, nonatomic, nonnull) NSArray <DULWidgetItem *> *widgets;


/**
 *  The index in the widget item array of the passed widget.
 *  
 *  @param widget The widget whose index is desired.
 *  
 *  @return An index
 */
- (NSInteger)indexOfWidget:(nonnull UIView <DULWidgetProtocol> *)widget;


/**
 *  Adds the passed widget to the collection. The collection layout system will then
 *  place it where it belongs visually.
 *  
 *  @param newWidget The widget being added.
 */
- (void)addWidget:(nonnull UIView<DULWidgetProtocol> *)newWidget;

/**
 *  Adds the passed widgets and applies the given edge insets.
 *  
 *  @param newWidget The widget being added.
 *  @param edgeInset The desired edge inset of the widget.
 */
- (void)addWidget:(nonnull UIView<DULWidgetProtocol> *)newWidget withEdgeInset:(UIEdgeInsets)edgeInset;


/**
 *  Removes the widget from the collection. Its widgetItem will be removed too.
 *  
 *  @param oldWidget The widget being removed.
 */
- (void)removeWidget:(nonnull UIView<DULWidgetProtocol> *)oldWidget;


/**
 *  Inserts the passed widget at the passed index.
 *  
 *  @param widget The widget being inserted.
 *  @param index The desired index of the widget.
 */
- (void)insertWidget:(nonnull UIView<DULWidgetProtocol> *)widget atIndex:(NSUInteger)index;

/**
 *  Inserts the passed widget at the passed index and then applies the given edge
 *  insets.
 *  
 *  @param newWidget The widget being inserted.
 *  @param edgeInset The desired edge inset of the widget.
 *  @param index The desired index of the widget.
 */
- (void)insertWidget:(nonnull UIView<DULWidgetProtocol> *)newWidget withEdgeInset:(UIEdgeInsets)edgeInset atIndex:(NSUInteger)index;


/**
 *  Extracts the widgets from the widgetItems array passed and returns them into a
 *  new array.
 *  
 *  @param widgetItems The widgets extracted from the widgetItems array.
 *  
 *  @return a UIView <DULWidgetProtocol> * object
 */
- (nullable NSArray <DULWidget *> *)widgetsInWidgetItems:(nonnull NSArray <DULWidgetItem *> *)widgetItems;

@end
