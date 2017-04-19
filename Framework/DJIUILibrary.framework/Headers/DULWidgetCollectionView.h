//
//  DULWidgetCollectionView.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DULWidgetCollectionViewProtocol.h"
#import "DULWidgetProtocol.h"

@class DULWidgetItem;

IB_DESIGNABLE

/**
 *  This subclass of UICollectionView is used as a base class for all predefined
 *  views under control by any of the predefined collection view controllers. This
 *  implements the `DULWidgetCollectionViewProtocol` which enables the control over
 *  widgets.
 */
@interface DULWidgetCollectionView : UICollectionView <DULWidgetCollectionViewProtocol>


/**
 *  The interaction expectation level to be applied by default to all widgets
 *  inserted into this collection view.
 */
@property DULWidgetInteractionExpectionLevel interactionExpectationLevel;

/*********************************************************************************/
#pragma mark - DULWidgetCollectionViewProtocol
/*********************************************************************************/


/**
 *  The array of `DULWidgetItem` widgets items.
 */
@property (readonly, nonatomic, nonnull) NSArray <DULWidgetItem *> *widgets;

@end
