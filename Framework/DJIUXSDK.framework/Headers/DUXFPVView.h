//
//  DUXFPVView.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <DJIUXSDK/DUXContentView.h>


/**
 *  Subclass of DUXContentView which shows the FPV video feed.
 */
@interface DUXFPVView : DUXContentView


/**
 *  Flag to enable/disable automatic configuration of the video feed.
 */
@property (nonatomic, assign) BOOL alwaysShowDJICameraVideoFeed;


/**
 *  Flag to to show/hide the camera display name.
 */
@property (nonatomic, assign) BOOL showCameraDisplayName;


/**
 *  Method which tells the fpv to start checking for the availability of the video
 *  feed.
 */
- (void)startChecking;


/**
 *  Method which tells the fpv to stop checking for the availability of the video
 *  feed.
 */
- (void)stopChecking;

@end
