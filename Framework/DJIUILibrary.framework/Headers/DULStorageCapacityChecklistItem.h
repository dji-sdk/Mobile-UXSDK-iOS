//
//  DULStorageCapacityChecklistItem.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUILibrary/DULPreflightChecklistItem.h>


/**
 *  Preflight checklist item that reports the storage remaining for photo and video
 *  capture. This item will always report ready to fly.
 */
@interface DULStorageCapacityChecklistItem : DULPreflightChecklistItem

@property NSInteger sdSpaceLeftInMB;
@property NSInteger ssdSpaceLeftInMB;

@end
