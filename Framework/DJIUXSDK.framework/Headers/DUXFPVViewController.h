//
//  DUXFPVViewController.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <DJIUXSDK/DUXContentViewController.h>

#import <DJISDK/DJISDK.h>
#import <DJIUXSDK/DUXPIPVideoFeedWidget.h>

@class DUXFPVViewController;
@class DUXFPVView;

@protocol DUXFPVViewControllerDelegate <NSObject>

@optional

- (void)fpvViewController:(nonnull DUXFPVViewController *)fpvViewController didUpdateCurrentFPVViewCurrentCameraIndexTo:(NSUInteger)updatedFPVViewCurrentCameraIndex;

@end


/**
 *  Subclass of DUXContentViewController which manages the logic for showing the FPV
 *  video and touch handling over the FPV view.
 */
@interface DUXFPVViewController : DUXContentViewController <DUXPIPVideoFeedWidgetDelegate>


/**
 *  Reference for the actual view which shows the video feed.
 */
@property (readonly, nonatomic, nullable) __kindof DUXFPVView *fpvView;


/**
 *  Flag which enables/disables interactivity of the FPVView. Used for
 *  enabling/disabling FPV view response to touches for focus and exposure when
 *  toggling between full screen and floating window.
 */
@property (nonatomic) BOOL isHUDInteractionEnabled;

// Delegate to observe camera index changes
@property (nonatomic, weak, nullable) id <DUXFPVViewControllerDelegate> delegate;

@end
