//
//  DULWidgetCollectionViewControllerProtocol.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJIUILibrary/DULWidgetCollectionViewProtocol.h>

@class DULWidget;


/**
 *  This protocol defines the expected behavior for view controller to manage widget
 *  collection views.
 */
@protocol DULWidgetCollectionViewControllerProtocol <NSObject>

@required


/**
 *  The actual instance of the widget collection.
 */
@property (strong, nonatomic, nullable) __kindof UIView<DULWidgetCollectionViewProtocol> *widgetCollectionView;


/**
 *  Adds the passed widget to the collection.
 *  
 *  @param newWidget The widget item being added.
 */
- (void)addWidget:(nonnull UIView <DULWidgetProtocol> *)newWidget;

/**
 *  Adds the passed widget to the collection and applies the given edge insets.
 *  
 *  @param newWidget The widget item being added.
 *  @param edgeInset The widget item.
 */
- (void)addWidget:(nonnull UIView <DULWidgetProtocol> *)newWidget withEdgeInset:(UIEdgeInsets)edgeInset;


/**
 *  The number of widgets currently in the collection.
 *  
 *  @return the count of widgets
 */
- (NSUInteger)widgetsCount;

/**
 *  The index of the passed widget.
 *  
 *  @param widget The widget item whose index is returned.
 *  
 *  @return an index
 */
- (NSInteger)indexOfWidget:(nonnull UIView <DULWidgetProtocol> *)widget;

/**
 *  Returns the widget at the passed index.
 *  
 *  @param index The index of the widget item returned.
 *  
 *  @return a widget or nil
 */
- (nullable UIView <DULWidgetProtocol> *)widgetAtIndex:(NSInteger)index;


/**
 *  Removes the passed widget.
 *  
 *  @param oldWidget The previous widget.
 */
- (void)removeWidget:(nonnull UIView <DULWidgetProtocol> *)oldWidget;

@end
