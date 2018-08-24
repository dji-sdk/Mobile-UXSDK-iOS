//
//  DUXDefaultLayoutView.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>

@class DUXStatusBarView;
@class DUXSideBarView;
@class DUXDockView;
@class DUXContentView;


/**
 *  This is the view used by the DUXDefaultLayoutViewController which is the
 *  starting point of the default layout of the DJI UXSDK.
 */
@interface DUXDefaultLayoutView : UIView


/**
 *  statusView is the view managed by DUXStatusBarViewController. It is the
 *  collection which usually sits on top of the UI and is prepopulated to be similar
 *  to DJI Go.
 */
@property (readonly, nullable) IBOutlet DUXStatusBarView *statusView;


/**
 *  leadingView is the view managed by DUXLeadingViewController It is the collection
 *  which sits vertically on the leading side of the UI and is prepopulated to be
 *  similar to DJI Go with actions to take off, land and go home.
 */
@property (readonly, nullable) IBOutlet DUXSideBarView *leadingView;


/**
 *  trailingView is the view managed by DUXTrailingViewController It is the
 *  collection which sits vertically on the trailing side of the UI and is
 *  prepopulated to be similar to DJI Go with actions related to  the camera like
 *  changing its mode and capturing photos and video.
 */
@property (readonly, nullable) IBOutlet DUXSideBarView *trailingView;


/**
 *  dockView is the view manager by DUXDockViewController It is the collection which
 *  sits on the bottom of the UI and is prepopulated to be similar to DJI Go
 */
@property (readonly, nullable) IBOutlet DUXDockView *dockView;


/**
 *  contentView is the view which occupies the background. It can be an FPV or Map
 *  or any other content. By default it shows the live video from the main camera.
 */
@property (readonly, nullable) IBOutlet DUXContentView *contentView;


/**
 *  PreviewView is the view which is shown as a small rectangle on the bottom right
 *  side of the screen. It usually shows either the video feed from the camera or
 *  the map widget.
 */
@property (readonly, nullable) IBOutlet DUXContentView *previewView;


@end
