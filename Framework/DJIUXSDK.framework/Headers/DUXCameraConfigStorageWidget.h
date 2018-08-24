//
//  DUXCameraConfigStorageWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Display:
 *  First text from the left shows format/resolution of photo/video that camera wil
 *  capture. Second text shows how many shots can be taken, or how many minutes can
 *  be recorded.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: (variable, max:221):30.
 */
@interface DUXCameraConfigStorageWidget : DUXWidget

@property (nonatomic) NSUInteger preferredCameraIndex;

@end
