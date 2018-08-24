//
//  DUXDefaultLayoutViewController.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <DJIUXSDK/DUXSDKModel.h>

@class DUXDefaultLayoutView;
@class DUXStatusBarViewController;
@class DUXLeadingBarViewController;
@class DUXTrailingBarViewController;
@class DUXDockViewController;

#import <DJIUXSDK/DUXWidgetCollectionViewControllerProtocol.h>


/**
 *  The RootViewController is a ViewController designed around 5
 *  childViewControllers: - status sits on the top and is used to display low
 *  frequency state information - leading and trailing are side controller to be
 *  used for controls - keeping the hands from blocking the view to the most
 *  important information: the content. - content sits full screen in the background
 *  and shows the most important info - live video, Mission, etc - dock sits in the
 *  bottom of the screen and shows high frequency information widgets along with
 *  some actionable widgets.
 */
@interface DUXDefaultLayoutViewController : UIViewController


/**
 *  The rootView holds all subviews, in this controller self.view contains
 *  self.rootView.
 */
@property (readonly, nonatomic, nullable) DUXDefaultLayoutView *rootView;


/**
 *  The statusViewController holds the top of the UI in a bar.
 */
@property (nullable, nonatomic) DUXStatusBarViewController *statusViewController;


/**
 *  The leadingViewController holds the leading position in the UI and contains
 *  controls such as take off, land and go home.
 */
@property (nullable, nonatomic) DUXLeadingBarViewController *leadingViewController;


/**
 *  The trailingViewController holds the trailing part of the UI and contains
 *  controls for the camera such as capture photo and change camera mode. By default
 *  it contains camera controls.
 */
@property (nullable, nonatomic) DUXTrailingBarViewController *trailingViewController;


/**
 *  The dockViewController holds the bottom part of the screen. By default it
 *  contains the DashboardWidget.
 */
@property (nullable, nonatomic) DUXDockViewController *dockViewController;


/**
 *  This is the view controller that occupies the background. By default it's a
 *  DUXFPVViewController and contains the live video stream from the aircraft.
 */
@property (nullable, nonatomic) UIViewController *contentViewController;


/**
 *  This is the view controller that occupies the bottom right side. By default it's
 *  a DUXMapViewController and contains the small preview of the map widget. When
 *  tapped, it swaps the with the contentViewController.
 */
@property (nullable, nonatomic) UIViewController *previewViewController;

@end


/**
 *  The Versatile Controller interface allows display of multiple controllers on the
 *  left and right side of the UI. For instance, they are used for the camera
 *  settings, the exposure settings and the preflight checklist view controllers.
 */
@interface DUXDefaultLayoutViewController (VersatileControllers)

/*********************************************************************************/
#pragma mark - Versatile View Controller
/*********************************************************************************/


/**
 *  The currently presented view controller in the left versatile space.
 *  
 *  @return the currently presented view controller or nil if none.
 */
- (nullable UIViewController *)presentedLeftVersatileViewController;


/**
 *  Presents the given view controller inside the left versatile space. This will
 *  make the given controller a child controller and install its view.
 *  
 *  @param leftVersatileViewController A valid view controller.
 */
- (void)presentLeftVersatileViewController:(nonnull UIViewController *)leftVersatileViewController;


/**
 *  Removes the currently presented left view controller. Has no effect if none in
 *  place.
 */
- (void)removeLeftVersatileViewController;



/**
 *  The currently presented view controller in the right versatile space.
 *  
 *  @return the currently presented view controller or nil if none.
 */
- (nullable UIViewController *)presentedRightVersatileViewController;


/**
 *  Presents the given view controller inside the right versatile space. This will
 *  make the given controller a child controller and install its view.
 *  
 *  @param rightVersatileViewController The view controller to be presented
 */
- (void)presentRightVersatileViewController:(nonnull UIViewController *)rightVersatileViewController;


/**
 *  Removes the currently presented right view controller. Has no effect if none in
 *  place.
 */
- (void)removeRightVersatileViewController;

@end
