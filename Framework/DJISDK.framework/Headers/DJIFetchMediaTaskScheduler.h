//
//  DJIFetchMediaTaskScheduler.h
//  DJISDK
//
//  Copyright © 2017 DJI. All rights reserved.
//

#import <DJISDK/DJISDKFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIMediaFile;


/**
 *  The content to download in a fetch media file task.
 */
typedef NS_OPTIONS(NSUInteger, DJIFetchMediaTaskContent) {

    /**
     *  None.
     */
    DJIFetchMediaTaskContentNone = 0,

    /**
     *  The scheduler will download the thumbnail of the media file.
     */
    DJIFetchMediaTaskContentThumbnail = 1 << 0,

    /**
     *  The scheduler will download the preview image of the media file.
     */
    DJIFetchMediaTaskContentPreview = 1 << 1,

    /**
     *  The scheduler will download the custom information of the media file.
     */
    DJIFetchMediaTaskContentCustomInformation = 1 << 2,
};


/**
 *  States of the fetch media file task scheduler `DJIFetchMediaTaskScheduler`.
 */
typedef NS_ENUM(NSUInteger, DJIFetchMediaTaskSchedulerState) {

    /**
     *  Scheduler is waiting for tasks.
     */
    DJIFetchMediaTaskSchedulerStateIdle,

    /**
     *  Scheduler is executing tasks.
     */
    DJIFetchMediaTaskSchedulerStateExecuting,

    /**
     *  Scheduler is suspended. Use `resumeWithCompletion` to resume the scheduler.
     */
    DJIFetchMediaTaskSchedulerStateSuspended,

    /**
     *  Unknown.
     */
    DJIFetchMediaTaskSchedulerStateUnknown = 0xFF
};



/**
 *  Completion block that is called when the scheduler finishes downloading content
 *  for a fetch media file task. If multiple content types are defined for a file,
 *  this completion block will be called at the completion of each content type
 *  being downloaded. The order content types will be downloaded in is first
 *  `DJIFetchMediaTaskContentThumbnail`, then `DJIFetchMediaTaskContentPreview` and
 *  lastly `DJIFetchMediaTaskContentCustomInformation`.
 *  
 *  @param file The media file that the content belongs to.
 *  @param content An enum value of `DJIFetchMediaTaskContent`.
 *  @param error Occurred error if there is any.
 */
typedef void(^DJIFetchMediaTaskCompletionBlock)(DJIMediaFile *file, DJIFetchMediaTaskContent content, NSError *_Nullable error);


/**
 *  Task to fetch contents of a media file. To make `DJIFetchMediaTaskScheduler`
 *  fetch the thumbnail, preview or custom information of a media file, a task
 *  should be created by using `taskWithFile:content:andCompletion`.
 */
@interface DJIFetchMediaTask : NSObject


/**
 *  Media file object to execute task on.
 */
@property (nonatomic, readonly, nonnull) DJIMediaFile *file;


/**
 *  Content types to fetch. A task can fetch more than one content type by using the
 *  bitwise OR operator on different contents.
 */
@property (nonatomic, readonly) DJIFetchMediaTaskContent content;


/**
 *  Creates a task instance.
 *  
 *  @param file Media file to execute task on.
 *  @param content Content to fetch.
 *  @param completion The `completion block` with the returned execution result.
 */
+(instancetype)taskWithFile:(DJIMediaFile *)file
                    content:(DJIFetchMediaTaskContent)content
              andCompletion:(DJIFetchMediaTaskCompletionBlock)completion;

@end


/**
 *  The camera stores the media it captures to SD or SSD storage on the product.
 *  When the mobile device wants to access the media, it needs to download it from
 *  the product over the wireless link between the product, remote controller and
 *  mobile device (depending on the product). Each media file captured by the camera
 *  can have several types of content associated with it including the full
 *  resolution media content, a lower resolution preview, a lower resolution again
 *  thumbnail, and custom data within the file's XML meta data. The full resolution
 *  content can take a long time to download over the wireless link, so it is often
 *  useful to download previews or thumbnails of many media files, and then only
 *  download the full resolution content of fewer select media files. This scheduler
 *  conveniently allows the small content types of media files (preview, thumbnail
 *  and custom data) to be downloaded to the mobile device. The scheduler can be
 *  used to queue and download content from a series of files, as well as used to
 *  re-prioritize files during the download process. The scheduler holds a list of
 *  pending tasks and it completes them one by one in first-in-first-out order. To
 *  prioritize a new task, `moveTaskToNext` can be used. Each task relates to a
 *  media file and can download multiple content types sequentially. When the last
 *  content type of a task starts being downloaded, the task is removed from the
 *  list. Note, the scheduler cannot be used to queue the download of full
 *  resolution media content. Only `fetchFileDataWithOffset:updateQueue:updateBlock`
 *  can be used for this.
 */
@interface DJIFetchMediaTaskScheduler : NSObject


/**
 *  Set `YES` to suspend the scheduler when an error occurs during the execution.
 */
@property (atomic, readwrite) BOOL suspendAfterSingleFetchTaskFailure;


/**
 *  State of the scheduler.
 */
@property (atomic, readonly) DJIFetchMediaTaskSchedulerState state;


/**
 *  Gets a copy of the pending tasks.
 *  
 *  @return An array of `DJIFetchMediaTask` objects.
 */
-(NSArray<DJIFetchMediaTask *> *)pendingTasks;


/**
 *  Pushes a task to the back of the queue. The task will be executed after all
 *  other tasks are complete.
 *  
 *  @param task Task to schedule.
 */
-(void)moveTaskToEnd:(DJIFetchMediaTask *)task;


/**
 *  Pushes a task to the front of the queue. The task will be executed after the
 *  executing task is complete.
 *  
 *  @param task Task to schedule.
 */
-(void)moveTaskToNext:(DJIFetchMediaTask *)task;


/**
 *  Remove content from tasks, and tasks from the scheduler. If all content is
 *  removed from a task, then the task is removed from the scheduler.
 *  
 *  @param file An object of `DJIMediaFile`.
 *  @param content An enum value of `DJIFetchMediaTaskContent`.
 */
-(void)removeTaskWithFile:(DJIMediaFile *)file andContent:(DJIFetchMediaTaskContent)content;


/**
 *  Removes all the pending tasks.
 */
-(void)removeAllTasks;


/**
 *  Suspends the scheduler. The scheduler will not continue to execute tasks in the
 *  queue.
 *  
 *  @param completion The `completion block` with the returned execution result.
 */
-(void)suspendWithCompletion:(DJICompletionBlock)completion;


/**
 *  Resumes the scheduler. The scheduler will execute tasks in the queue
 *  sequentially.
 *  
 *  @param completion The `completion block` with the returned execution result.
 */
-(void)resumeWithCompletion:(DJICompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END

