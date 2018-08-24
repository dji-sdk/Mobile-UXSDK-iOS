//
//  DUXWidgetCollectionView.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <DJIUXSDK/DUXWidgetCollectionViewProtocol.h>
#import <DJIUXSDK/DUXWidgetProtocol.h>

@class DUXWidgetItem;


/**
 *  This subclass of UICollectionView is used as a base class for all predefined
 *  views under control by any of the predefined collection view controllers. This
 *  implements the `DUXWidgetCollectionViewProtocol` which enables the control over
 *  widgets.
 */
@interface DUXWidgetCollectionView : UICollectionView <DUXWidgetCollectionViewProtocol>


/**
 *  The interaction expectation level to be applied by default to all widgets
 *  inserted into this collection view.
 */
@property DUXWidgetInteractionExpectionLevel interactionExpectationLevel;

/*********************************************************************************/
#pragma mark - DUXWidgetCollectionViewProtocol
/*********************************************************************************/


/**
 *  The array of `DUXWidgetItem` widgets items.
 */
@property (readonly, nonatomic, nonnull) NSArray <DUXWidgetItem *> *widgets;

@end
