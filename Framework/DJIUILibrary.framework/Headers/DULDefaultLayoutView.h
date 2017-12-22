//
//  DULDefaultLayoutView.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>

@class DULStatusBarView;
@class DULSideBarView;
@class DULDockView;
@class DULContentView;


/**
 *  This is the view used by the DULDefaultLayoutViewController which is the
 *  starting point of the default layout of the DJI UILibrary.
 */
@interface DULDefaultLayoutView : UIView


/**
 *  statusView is the view managed by DULStatusBarViewController. It is the
 *  collection which usually sits on top of the UI and is prepopulated to be similar
 *  to DJI Go.
 */
@property (readonly, nullable) IBOutlet DULStatusBarView *statusView;


/**
 *  leadingView is the view managed by DULLeadingViewController It is the collection
 *  which sits vertically on the leading side of the UI and is prepopulated to be
 *  similar to DJI Go with actions to take off, land and go home.
 */
@property (readonly, nullable) IBOutlet DULSideBarView *leadingView;


/**
 *  trailingView is the view managed by DULTrailingViewController It is the
 *  collection which sits vertically on the trailing side of the UI and is
 *  prepopulated to be similar to DJI Go with actions related to  the camera like
 *  changing its mode and capturing photos and video.
 */
@property (readonly, nullable) IBOutlet DULSideBarView *trailingView;


/**
 *  dockView is the view manager by DULDockViewController It is the collection which
 *  sits on the bottom of the UI and is prepopulated to be similar to DJI Go
 */
@property (readonly, nullable) IBOutlet DULDockView *dockView;


/**
 *  contentView is the view which occupies the background. It can be an FPV or Map
 *  or any other content. By default it shows the live video from the main camera.
 */
@property (readonly, nullable) IBOutlet DULContentView *contentView;


/**
 *  PreviewView is the view which is shown as a small rectangle on the bottom right
 *  side of the screen. It usually shows either the video feed from the camera or
 *  the map widget.
 */
@property (readonly, nullable) IBOutlet DULContentView *previewView;


@end
