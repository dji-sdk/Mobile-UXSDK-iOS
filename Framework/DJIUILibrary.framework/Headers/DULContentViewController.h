//
//  DULContentViewController.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <DJIUILibrary/UIImage+Assets.h>


/**
 *  DULContentViewController manages the logic for pre-populating the content view
 *  with the relevant view (i.e. map or video).
 */
@interface DULContentViewController : UIViewController


/**
 *  Method which is used to set the content view.
 *  
 *  @param mainView The view is used to set the content view.
 */
- (void)installMainView:(UIView *)mainView;

@end
