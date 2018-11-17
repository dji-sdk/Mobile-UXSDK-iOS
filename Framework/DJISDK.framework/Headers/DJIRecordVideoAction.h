//
//  DJIRecordVideoAction.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIMissionAction.h>

NS_ASSUME_NONNULL_BEGIN


/**
 *  The error domain associated with errors specific to `DJIRecordVideoAction`.
 */
extern const NSErrorDomain DJIRecordVideoActionErrorDomain;


/**
 *  Error codes for `DJIRecordVideoActionErrorDomain`.
 */
typedef NS_ENUM(NSInteger, DJIRecordVideoActionError) {

    /**
     *  Default error.
     */
    DJIRecordVideoActionErrorUnknown = -1,
    

    /**
     *  Duration value is invalid (less than 0).
     */
    DJIRecordVideoActionErrorInvalidDuration = 100
};


/**
 *  This class represents a video recording action used as an element in a Timeline
 *  mission. By creating an object of this class and adding it to Mission Control's
 *  Timeline,  the camera can start or stop video recording when the Timeline
 *  reaches the action.
 */
@interface DJIRecordVideoAction : DJIMissionAction


/**
 *  Initialize instance with video recording duration in seconds.
 *  
 *  @param duration Time in seconds.
 *  
 *  @return An instance of `DJIRecordVideoAction`
 */
- (instancetype _Nullable)initWithDuration:(double)duration;


/**
 *  Initialize instance for start video recording only.
 *  
 *  @return An instance of `DJIRecordVideoAction`
 */
- (instancetype _Nullable)initWithStartRecordVideo;


/**
 *  Initialize instance for stop video recording only.
 *  
 *  @return An instance of `DJIRecordVideoAction`
 */
- (instancetype _Nullable)initWithStopRecordVideo;

@end

NS_ASSUME_NONNULL_END
