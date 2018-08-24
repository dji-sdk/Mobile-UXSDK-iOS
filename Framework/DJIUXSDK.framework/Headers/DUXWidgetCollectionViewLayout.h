//
//  DUXWidgetCollectionViewLayout.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>


/**
 *  A base sub class of UICollectionView to be used for all custom collection layout
 *  used in standard UXSDK objects.
 */
@interface DUXWidgetCollectionViewLayout : UICollectionViewLayout


/**
 *  The scrollDirection of the layout.
 */
@property(nonatomic) UICollectionViewScrollDirection scrollDirection;


/**
 *  The minimum space to be kept between items.
 */
@property(nonatomic) CGFloat minimumInteritemSpacing;


/**
 *  Convenience calculation method calculating the total width of all widgets in the
 *  passed array.
 *  
 *  @param widgets The widgets whose total width is desired.
 *  
 *  @return a width in pixels
 */
- (CGFloat)widthSumOfWidgets:(NSArray *)widgets;


/**
 *  Convenience calculation method calculating the total height of all widgets in
 *  the passed array.
 *  
 *  @param widgets The widgets whose total height is desired.
 *  
 *  @return a height in pixels
 */
- (CGFloat)heightSumOfWidgets:(NSArray *)widgets;


/**
 *  Convenience calculation method calculating the total width of all widgets in the
 *  associated collection.
 *  
 *  @return a width in pixels
 */
- (CGFloat)totalWidgetWidth;


/**
 *  Convenience calculation method calculating the total height of all widgets in
 *  the associated collection.
 *  
 *  @return a height in pixels
 */
- (CGFloat)totalWidgetHeight;

@end
