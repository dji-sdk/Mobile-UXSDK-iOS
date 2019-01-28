//
//  DUXStorageCapacityChecklistItem.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DUXPreflightChecklistItem.h>


/**
 *  An enum that returns the comprehensive state of the storage capacity.
 */
typedef NS_ENUM(NSUInteger, DUXStorageCapacityComprehensiveState) {
    

    /**
     *  Enum value that is returned when the storage capacity comprehensive state is
     *  unknown.
     */
    DUXStorageCapacityComprehensiveStateUnknown,
    

    /**
     *  Enum value that is returned when the storage capacity comprehensive state is
     *  normal with no warnings or errors.
     */
    DUXStorageCapacityComprehensiveStateNormal,
    

    /**
     *  Enum value that is returned when the storage capacity comprehensive state is too
     *  slow.
     */
    DUXStorageCapacityComprehensiveStateSlow,
    

    /**
     *  Enum value that is returned when the storage capacity comprehensive state is
     *  busy with either saving, formatting, initializing or recovering files.
     */
    DUXStorageCapacityComprehensiveStateBusy,
    

    /**
     *  Enum value that is returned when the storage capacity comprehensive state is a
     *  warning such as format recommended, recovering files, or writing slowly.
     */
    DUXStorageCapacityComprehensiveStateWarning,
    

    /**
     *  Enum value that is returned when the storage capacity comprehensive state is an
     *  error such as invalid, read only, invalid file system, or no remaining file
     *  indices.
     */
    DUXStorageCapacityComprehensiveStateError,
    

    /**
     *  Enum value that is returned when the storage capacity comprehensive state should
     *  allow formatting such as when storage is full or needs formatting.
     */
    DUXStorageCapacityComprehensiveStateAllowFormatting
};


/**
 *  Preflight checklist item that reports the storage remaining for photo and video
 *  capture. This item will always report ready to fly.
 */
@interface DUXStorageCapacityChecklistItem : DUXPreflightChecklistItem


/**
 *  The space (MB) left in the SD card.
 */
@property (nonatomic, assign) NSInteger sdSpaceLeftInMB;


/**
 *  The space (MB) left in the solid state drive.
 */
@property (nonatomic, assign) NSInteger ssdSpaceLeftInMB;


/**
 *  The space (MB) left in the internal storage.
 */
@property (nonatomic, assign) NSInteger internalStorageSpaceLeftInMB;


/**
 *  The camera index the checklist item refers to. Default value is 0.
 */
@property (nonatomic) NSUInteger preferredCameraIndex;


/**
 *  The storage location the checklist item refers to if available.
 */
@property (nonatomic) DJICameraStorageLocation preferredCameraStorageLocation;


/**
 *  The current camera storage location.
 */
@property (nonatomic, assign) DJICameraStorageLocation currentCameraStorageLocation;


/**
 *  The enum value for the comprehensive state of the storage location.
 */
@property (assign, nonatomic, readonly) DUXStorageCapacityComprehensiveState comprehensiveState;

@end
