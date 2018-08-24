//
//  DUXCameraConfigSSDWidget.h
//  DJIUXSDK
//
//  Created by Jason Rinn on 5/31/18.
//  Copyright © 2018 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>


/**
 *  Usage:
 *  Shows SSD Video format, clip name, license, and capacity info.
 */
@interface DUXCameraConfigSSDWidget : DUXWidget


/**
 *  Selects which camera index widget refers to.
 */
@property (nonatomic) NSUInteger preferredCameraIndex;

@end
