//
//  DULFPVView.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <DJIUILibrary/DULContentView.h>


/**
 *  Subclass of DULContentView which shows the FPV video feed.
 */
@interface DULFPVView : DULContentView


/**
 *  Flag to enable/disable automatic configuration of the video feed.
 */
@property (nonatomic, assign) BOOL alwaysShowDJICameraVideoFeed;


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
