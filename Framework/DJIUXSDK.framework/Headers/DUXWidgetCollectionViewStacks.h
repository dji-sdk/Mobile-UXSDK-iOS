//
//  DUXWidgetCollectionViewStacks.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DUXWidgetCollectionView.h"

NS_ASSUME_NONNULL_BEGIN


/**
 *  An enum defining each stack of the widgetCollectionStacksView
 */
typedef NS_ENUM(NSUInteger, DUXWidgetCollectionViewStack){

/**
 *  No stack.
 */
    DUXWidgetCollectionViewStackNone,

    /**
     *  First Stack. Leading for horizontal, top for vertical
     */
    DUXWidgetCollectionViewStackFirst, // Leading, Top

    /**
     *  Last Stack. Trailing for horizontal, bottom for vertical.
     */
    DUXWidgetCollectionViewStackLast, // Trailing, Bottom
};



/**
 *  A special widget collection view build around a stack layout which allows widget
 *  to be placed inside either stacks.
 */
@interface DUXWidgetCollectionViewStacks : DUXWidgetCollectionView


/**
 *  Adds the passed widget to the given stack with the passed edget insets.
 *  
 *  @param newWidget The widget being added.
 *  @param stack The stack the widget is being added to.
 *  @param edgeInset The desired edge inset of the widget.
 */
- (void)addWidget:(UIView<DUXWidgetProtocol> *)newWidget
               to:(DUXWidgetCollectionViewStack)stack
    withEdgeInset:(UIEdgeInsets)edgeInset;


/**
 *  Moves the passed widget to the given stack with the passed edget insets.
 *  
 *  @param widget The widget being moved.
 *  @param stack The stack the widget is being moved to.
 */
- (void)moveWidget:(UIView<DUXWidgetProtocol> *)widget
                to:(DUXWidgetCollectionViewStack)stack;


/**
 *  Returns the current stack of the passed widget.
 *  
 *  @param widget The widget whose stack is returned.
 *  
 *  @return the stack of the widget
 */
- (DUXWidgetCollectionViewStack)stackOfWidget:(UIView<DUXWidgetProtocol> *)widget;

@end

NS_ASSUME_NONNULL_END
