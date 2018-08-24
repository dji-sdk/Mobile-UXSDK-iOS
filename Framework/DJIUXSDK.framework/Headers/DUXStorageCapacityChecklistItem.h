//
//  DUXStorageCapacityChecklistItem.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DUXPreflightChecklistItem.h>


/**
 *  Preflight checklist item that reports the storage remaining for photo and video
 *  capture. This item will always report ready to fly.
 */
@interface DUXStorageCapacityChecklistItem : DUXPreflightChecklistItem

@property NSInteger sdSpaceLeftInMB;
@property NSInteger ssdSpaceLeftInMB;

@property (nonatomic) NSUInteger preferredCameraIndex;

@end
