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
@class DUXFPVInteractionController;


/**
 *  Represents the types of grid lines that can be set to be on top of the FPV.
 */
typedef NS_ENUM(NSUInteger, DUXFPVViewGridOverlayType) {

/**
 *  No grid lines are visible.
 */
    DUXFPVViewGridOverlayTypeNone = 1,

/**
 *  Horizontal and vertical grid lines are visible in using a 3x3 grid.
 */
    DUXFPVViewGridOverlayTypeGrid,

/**
 *  Same as `DUXFPVViewGridOverlayTypeGrid` with the addition of 2 diagonal lines
 *  running through the center.
 */
    DUXFPVViewGridOverlayTypeGridWithDiagonals,

/**
 *  The type of grid is unknown.
 */
    DUXFPVViewGridOverlayTypeUnknown = 0xFF,
};


/**
 *  This protocol allows you to receive updates regarding the `DUXFPVViewController`
 *  state.
 */
@protocol DUXFPVViewControllerDelegate <NSObject>

@optional


/**
 *  This method is called whenever `DUXFPVViewController` changes the camera it is
 *  getting it's video feed from. If the camera is the FPV camera (which does not
 *  have an index) then the value of the camera index will be NSNotFound.
 *  
 *  @param fpvViewController The FPV view controller whose index has been updated.
 *  @param updatedFPVViewCurrentCameraIndex The updated value of the camera index. Cameras with no index (such as the FPV camera) will have a value of NSNotFound.
 */
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
@property (nonatomic) BOOL isHUDInteractionEnabled; // DEPRECATED_ATTRIBUTE This gets deprecated, use interaction controller instead


/**
 *  Enables/disables interactivity of the FPV at a greater granularity than
 *  `isHUDInteractionEnabled`.
 */
@property (nonatomic, readonly, nonnull) DUXFPVInteractionController *interactionController;


/**
 *  Enables/disables the color waveform widget overlayed on top of the FPV. Color
 *  waveform widget will  still only appear on products that support it.
 */
@property (nonatomic) BOOL isColorWaveformWidgetVisible;


/**
 *  Enables/disables the radar widget overlayed on top of the FPV. Radar widget will
 *  still only appear on products that support it.
 */
@property (nonatomic) BOOL isRadarWidgetVisible;


/**
 *  When set to `NO` the FPV view controller will not respond to grid settings
 *  control inside the camera settings panel. `YES` by default.
 */
@property (nonatomic) BOOL canDisplayGridOverlay;


/**
 *  The type of grid that is displayed above the video feed on top of the FPV. For
 *  the types of grid available  see `DUXFPVViewGridOverlayType`.
 */
@property (nonatomic, assign) DUXFPVViewGridOverlayType currentGridOverlayType;

// Delegate to observe camera index changes
@property (nonatomic, weak, nullable) id <DUXFPVViewControllerDelegate> delegate;

@end
