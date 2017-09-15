//
//  DULFPVViewController.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <DJIUILibrary/DULContentViewController.h>

#import <DJISDK/DJISDK.h>
#import <DJIUILibrary/DULPIPVideoFeedWidget.h>

@class DULFPVView;


/**
 *  Subclass of DULContentViewController which manages the logic for showing the FPV
 *  video and touch handling over the FPV view.
 */
@interface DULFPVViewController : DULContentViewController <DULPIPVideoFeedWidgetDelegate>


/**
 *  Reference for the actual view which shows the video feed.
 */
@property (readonly, nonatomic, nullable) __kindof DULFPVView *fpvView;


/**
 *  Flag which enables/disables interactivity of the FPVView. Used for
 *  enabling/disabling FPV view response to touches for focus and exposure when
 *  toggling between full screen and floating window.
 */
@property BOOL isHUDInteractionEnabled;

@end
