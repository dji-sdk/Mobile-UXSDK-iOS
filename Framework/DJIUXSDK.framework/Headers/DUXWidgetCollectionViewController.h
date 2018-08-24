//
//  DUXWidgetCollectionViewController.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <DJIUXSDK/DUXWidgetCollectionViewProtocol.h>
#import <DJIUXSDK/DUXWidgetCollectionViewControllerProtocol.h>
#import <DJIUXSDK/DUXWidgetItem.h>


/**
 *  A base widget collection view controller to manage a standard widget collection.
 */
@interface DUXWidgetCollectionViewController : UIViewController <DUXWidgetCollectionViewControllerProtocol>


/**
 *  The view acting as the widget collection.
 */
@property (nonatomic, strong, nullable) IBOutlet __kindof UICollectionView <DUXWidgetCollectionViewProtocol> *widgetCollectionView;

@property (nonatomic) NSUInteger preferredCameraIndex;

/*********************************************************************************/
#pragma mark - View Management
/*********************************************************************************/


/**
 *  Places the MainView of the VC as a full size subview of base view..
 *  
 *  @param view The view being installed as the main view.
 */
- (void)installMainView:(nonnull UIView *)view;

/*********************************************************************************/
#pragma mark - Additional Widget Controls
/*********************************************************************************/


/**
 *  returns the widget item at the passed index.
 *  
 *  @param index The index of the desired widget item contained inside the view.
 *  
 *  @return a widget or nil
 */
- (nullable DUXWidgetItem *)widgetItemAtIndex:(NSInteger)index;


/**
 *  returns the first widget with the passed class.
 *  
 *  @param widgetClass The class of the desired widget item contained inside the view.
 *  
 *  @return a widget or nil
 */
- (nullable UIView<DUXWidgetProtocol> *)widgetWithClass:(nonnull Class)widgetClass;


/**
 *  inserts the widget at the passed index.
 *  
 *  @param widget The widget item being inserted inside the view.
 *  @param destinationIndex The desired index of the widget being inserted.
 */
- (void)insertWidget:(nonnull UIView <DUXWidgetProtocol> *)widget atIndex:(NSUInteger)destinationIndex;


/**
 *  insert the passed widgets at the given index and applies the edge inset.
 *  
 *  @param widget The widget item being inserted inside the view.
 *  @param edgeInset The edge inset of the widget item being inserted.
 *  @param destinationIndex The desired index of the widget being inserted.
 */
- (void)insertWidget:(nonnull UIView <DUXWidgetProtocol> *)widget withEdgeInset:(UIEdgeInsets)edgeInset atIndex:(NSUInteger)destinationIndex;


/**
 *  moves the widget to another index.
 *  
 *  @param widget The widget item being moved.
 *  @param destinationIndex The desired new index of the widget item.
 */
- (void)moveWidget:(nonnull UIView <DUXWidgetProtocol> *)widget toIndex:(NSUInteger)destinationIndex;

@end
