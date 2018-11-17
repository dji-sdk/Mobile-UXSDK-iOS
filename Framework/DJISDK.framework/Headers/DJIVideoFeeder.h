//
//  DJIVideoFeeder.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


/**
 *  The physical source of a video feed.
 */
typedef NS_ENUM(NSInteger, DJIVideoFeedPhysicalSource) {

    /**
     *  The video feed is from the main camera. It is the physical source used by most
     *  of DJI products.  For M210 and M210 RTK, `DJIVideoFeedPhysicalSourceLeftCamera`
     *  and `DJIVideoFeedPhysicalSourceRightCamera` are used instead.
     */
    DJIVideoFeedPhysicalSourceMainCamera,
    

    /**
     *  The video feed is from the FPV camera on Inspire 2 or M200 series.
     */
    DJIVideoFeedPhysicalSourceFPVCamera,


    /**
     *  The video feed is from one of the LB ports (AV or HDMI) while EXT Port is
     *  enabled.  It is only used for stand-alone Lightbridge 2 or aircraft with stand-
     *  alone Lightbridge 2 modules (e.g. M600).
     */
    DJIVideoFeedPhysicalSourceLB,


    /**
     *  The video feed is from EXT port while EXT port is enabled. It is only used for
     *  Lightbridge 2 or aircrafts with Lightbridge 2 (e.g. M600).
     */
    DJIVideoFeedPhysicalSourceEXT,


    /**
     *  The video feed is from the HDMI port while EXT port is disabled.  It is only
     *  used for stand-alone Lightbridge 2 or aircraft with stand-alone Lightbridge 2
     *  modules.
     */
    DJIVideoFeedPhysicalSourceHDMI,


    /**
     *  The video feed is from AV port while EXT port is disabled. It is only used for
     *  stand-alone Lightbridge 2 or aircraft with stand-alone Lightbridge 2 modules.
     */
    DJIVideoFeedPhysicalSourceAV,
    

    /**
     *  The video feed is from the port (left) main camera. It is only used for M210 and
     *  M210 RTK.
     */
    DJIVideoFeedPhysicalSourceLeftCamera,


    /**
     *  The video feed is from the starboard (right) main camera. It is only used for
     *  M210 and M210 RTK.
     */
    DJIVideoFeedPhysicalSourceRightCamera,

    /**
     *  Unknown video physical source.
     */
    DJIVideoFeedPhysicalSourceUnknown = 0xFF,
};

@class DJIVideoFeed;


/**
 *  Listener that receives notifications when a new video physical source becomes
 *  available.
 */
@protocol DJIVideoFeedSourceListener <NSObject>


/**
 *  Called when a video feed is made available from a new physical source.
 *  
 *  @param videoFeed A `DJIVideoFeed` object.
 *  @param physicalSource An enum value of `DJIVideoFeedPhysicalSource`.
 */
- (void)videoFeed:(nonnull DJIVideoFeed *)videoFeed didChangePhysicalSource:(DJIVideoFeedPhysicalSource)physicalSource;

@end


/**
 *  Represents a single video feed from a single channel or port.
 */
@protocol DJIVideoFeedListener <NSObject>


/**
 *  Called when the video feed receives new video data.
 *  
 *  @param videoFeed A `DJIVideoFeed` object.
 *  @param videoData New video data.
 */
- (void)videoFeed:(nonnull DJIVideoFeed *)videoFeed didUpdateVideoData:(nonnull NSData *)videoData;

@end


/**
 *  Video feed. Use it to receive video data from a physical source.
 */
@interface DJIVideoFeed : NSObject


/**
 *  The physical source of the video feed.
 */
@property (nonatomic, assign, readonly) DJIVideoFeedPhysicalSource physicalSource;


/**
 *  Add listener to receive new video data.
 *  
 *  @param videoFeedListener Listener to receive video data.
 *  @param queue The queue that `videoFeed:didUpdateVideoData` is called in.
 */
- (void)addListener:(id <DJIVideoFeedListener>)videoFeedListener withQueue:(nullable dispatch_queue_t)queue;


/**
 *  Remove listener to stop receiving new video data.
 *  
 *  @param videoFeedListener Listener to remove.
 */
- (void)removeListener:(id <DJIVideoFeedListener>)videoFeedListener;


/**
 *  Remove all Listeners for video feed.
 */
- (void)removeAllListeners;

@end


/**
 *  Class that manages live video feed from DJI products to the mobile device.
 */
@interface DJIVideoFeeder : NSObject

- (instancetype)init OBJC_UNAVAILABLE("You must use the singleton");

+ (instancetype)new OBJC_UNAVAILABLE("You must use the singleton");


/**
 *  The primary video feed.
 *   The possible physical sources for the primary video feed include:
 *   - `DJIVideoFeedPhysicalSourceMainCamera`
 *   -  `DJIVideoFeedPhysicalSourceLB`
 *   -  `DJIVideoFeedPhysicalSourceHDMI`
 *   -  `DJIVideoFeedPhysicalSourceLeftCamera`
 *   -  `DJIVideoFeedPhysicalSourceRightCamera`
 *   For M210 and M210 RTK, the  physical sources are controlled by the bandwidth
 *  allocation between the port (left) and starboard  (right) main cameras
 *  (`setBandwidthAllocationForLeftCamera:withCompletion`):
 *   - When bandwidth  is 100% on the left camera, the primary source is
 *  `DJIVideoFeedPhysicalSourceLeftCamera` and the secondary source is
 *  `DJIVideoFeedPhysicalSourceFPVCamera`.
 *   - When bandwidth is 0%  on the left camera, the primary source is
 *  `DJIVideoFeedPhysicalSourceRightCamera`  and the secondary source is
 *  `DJIVideoFeedPhysicalSourceFPVCamera`.
 *   - When  bandwidth is neither 0% nor 100% on the left camera, the primary source
 *  is  `DJIVideoFeedPhysicalSourceLeftCamera` and the secondary source is
 *  `DJIVideoFeedPhysicalSourceRightCamera`.
 */
@property (nonatomic, strong, nonnull) DJIVideoFeed *primaryVideoFeed;


/**
 *  The secondary video feed.
 *   The possible physical sources for the secondary video feed include:
 *   - `DJIVideoFeedPhysicalSourceFPVCamera`
 *   -  `DJIVideoFeedPhysicalSourceEXT`
 *   -  `DJIVideoFeedPhysicalSourceAV`
 *   - `DJIVideoFeedPhysicalSourceRightCamera`. For M210 and M210 RTK, the physical
 *  sources are controlled by the bandwidth allocation between the port (left) and
 *  starboard (right) main cameras
 *  (`setBandwidthAllocationForLeftCamera:withCompletion`):
 *   - When bandwidth is 100% on the left camera, the primary  source is
 *  `DJIVideoFeedPhysicalSourceLeftCamera` and the secondary source is
 *  `DJIVideoFeedPhysicalSourceFPVCamera`.
 *   - When bandwidth is 0% on the left camera,  the primary source is
 *  `DJIVideoFeedPhysicalSourceRightCamera` and the secondary source is
 *  `DJIVideoFeedPhysicalSourceFPVCamera`.
 *   - When bandwidth is neither 0% nor 100% on  the left camera, the primary source
 *  is `DJIVideoFeedPhysicalSourceLeftCamera` and the  secondary source is
 *  `DJIVideoFeedPhysicalSourceRightCamera`.
 */
@property (nonatomic, strong, nonnull) DJIVideoFeed *secondaryVideoFeed;


/**
 *  Add listener to receive the physical source changes.
 *  
 *  @param sourceListener Listener to add.
 */
- (void)addVideoFeedSourceListener:(id <DJIVideoFeedSourceListener>)sourceListener;


/**
 *  Remove listener to stop receiving the physical source changes.
 *  
 *  @param sourceListener Listener to remove.
 */
- (void)removeVideoFeedSourceListener:(id <DJIVideoFeedSourceListener>)sourceListener;


/**
 *  Remove all listeners.
 */
- (void)removeAllListeners;


/**
 *  Parses decoding assistant information for H.264 stream data. The information
 *  will  be useful for the H.264 decoder.
 *  
 *  @param buffer H.264 stream data to parse.
 *  @param length The data's length.
 *  @param assistInfo An allocated memory with at least 8 bytes to receive the assistant information.
 *  
 *  @return `YES` if information is parsed successfully from the stream.
 */
- (BOOL)parseDecodingAssistInfoWithBuffer:(uint8_t *)buffer length:(int)length assistInfo:(void *)assistInfo;


/**
 *  Synchronizes the decoder status (if it is in normal status) to the video feeder.
 *  The  decoder status is useful for the assistant information parser.
 *  
 *  @param isNormal `YES` if the decoder is in normal status.
 */
- (void)syncDecoderStatus:(BOOL)isNormal;


/**
 *  Tells the parser that the decoder has decoded a frame successfully.
 *  
 *  @param timestamp The timestamp of the decoded frame.
 */
- (void)decodingDidSucceedWithTimestamp:(NSUInteger)timestamp;


/**
 *  Tells the parser that the decoder has failed to decode frames from the video
 *  feed.
 */
- (void)decodingDidFail;

@end

NS_ASSUME_NONNULL_END
