//
//  DJIPanoramaMissionOperator.h
//  DJISDK
//
//  Created by Tim Lee on 2017/3/8.
//  Copyright © 2017年 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DJIPanoramaMissionTypes.h"
#import "DJISDKFoundation.h"

NS_ASSUME_NONNULL_BEGIN

@class DJIMediaFile; 


/**
 *  Panorama Mission State.
 */
typedef NS_ENUM(NSInteger, DJIPanoramaMissionState) {
    

    /**
     *  The state of the operator is unknown. This is the initial state when the
     *  operator  has just been created.
     */
    DJIPanoramaMissionStateUnknown = -1,
    

    /**
     *  The connection between the mobile device and Osmo is broken.
     */
    DJIPanoramaMissionStateDisconnected,
    

    /**
     *  The connected product does not support Panorama mission.
     */
    DJIPanoramaMissionStateNotSupported,
    

    /**
     *  The operator is ready to setup a Panorama mission.
     */
    DJIPanoramaMissionStateReadyToSetup,
    

    /**
     *  The operator is setting up for a Panorama mission.
     */
    DJIPanoramaMissionStateSettingUp,
    

    /**
     *  The setup for the Panorama mission is complete. The operator is ready to  start
     *  the execution.
     */
    DJIPanoramaMissionStateReadyToExecute,
    

    /**
     *  The operator is executing a Panorama mission.
     */
    DJIPanoramaMissionStateExecuting,
};


/**
 *  This class encapsulates all the state changes of the Panorama mission operator.
 */
@interface DJIPanoramaMissionEvent : NSObject


/**
 *  The previous state of the operator.
 */
@property (nonatomic, readonly) DJIPanoramaMissionState previousState;


/**
 *  The current state of the operator.
 */
@property (nonatomic, readonly) DJIPanoramaMissionState currentState;


/**
 *  The detailed state of the executing Panorama mission. It is only valid when
 *  `currentState` is  `DJIPanoramaMissionStateExecuting`. For the other states, it
 *  is `nil`.
 */
@property (nonatomic, readonly) DJIPanoramaMissionExecutionState *executionState;


/**
 *  The error of DJIPanoramaMissionEvent.
 */
@property (nonatomic, readonly, nullable) NSError *error;

@end

@class DJIPanoramaMissionOperator;


/**
 *  The panorama mission operator is the only object that controls, runs and
 *  monitors Panorama Missions. It can be accessed from `DJIMissionControl`.
 */
@interface DJIPanoramaMissionOperator : NSObject


/**
 *  The current state of the operator.
 */
@property(nonatomic, readonly) DJIPanoramaMissionState currentState;


/**
 *  Block to receive the Panorama mission operator event.
 *  
 *  @param event The Panorama mission operator event with the state change.
 */
typedef void (^DJIPanoramaMissionOperatorEventBlock)(DJIPanoramaMissionEvent *event);


/**
 *  Adds listener to receive all events of the Panorama mission operator.
 *  
 *  @param listener Listener that is interested in Panorama mission operator.
 *  @param queue The dispatch queue that `block` will be called on.
 *  @param block Block will be called when there is event updated.
 */
-(void)addListenerToEvents:(id)listener
                 withQueue:(nullable dispatch_queue_t)queue
                  andBlock:(DJIPanoramaMissionOperatorEventBlock)block;


/**
 *  Removes listener. The listener will not receive any update after calling this
 *  method.
 *  
 *  @param listener Listener to be removed.
 */
- (void)removeListener:(id)listener;


/**
 *  Remove all listeners.
 */
- (void)removeAllListeners;


/**
 *  Sets up the Panorama mission with the specific mode. It can only be called  when
 *  the `currentState` is one of the  following:
 *   - `DJIPanoramaMissionStateReadyToSetup`
 *   - `DJIPanoramaMissionStateReadyToExecute`
 *   If the setup starts  successfully, `currentState` will become
 *  `DJIPanoramaMissionStateSettingUp`. Normally, it will take seconds to  complete
 *  the setup. Once setup is completed successfully,  `currentState` will become
 *  `DJIPanoramaMissionStateReadyToExecute`.
 *  
 *  @param mode An enum value of `DJIPanoramaMode`.
 *  @param completion Completion block that will be called when the operator succeeds or fails  to start the setup. If it fails, an error will be returned.
 */
- (void)setupWithMode:(DJIPanoramaMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Starts to execute the mission that has been setup.
 *   It can only be called when  the `currentState` is
 *  `DJIPanoramaMissionStateReadyToExecute`.
 *   If the mission is started successfully, the  `currentState` will become
 *  `DJIPanoramaMissionStateExecuting`.
 *  
 *  @param completion Completion block that will be called when the operator succeeds or fails to  start the execution. If it fails, an error will be returned.
 */
- (void)startMissionWithCompletion:(DJICompletionBlock)completion;


/**
 *  Stops the executing mission. It can only be called when the  `currentState` is
 *  `DJIPanoramaMissionStateExecuting`. After a mission is stopped successfully,
 *  `currentState` will become  `DJIPanoramaMissionStateReadyToExecute`.
 *  
 *  @param completion Completion block that will be called when the operator succeeds or fails to  stop the mission. If it fails, an error will be returned.
 */
- (void)stopMissionWithCompletion:(DJICompletionBlock)completion;


/**
 *  Retrieves the `DJIMediaFile` object for the recently finished panorama  mission.
 *  
 *  @param panoMedia A `DJIMediaFile` file.
 *  @param error Error retrieving the value.
 *  @param completion Completion block that receives the execution result.
 */
-(void) getRecentPanoramaMediaFileWithCompletion:(void(^)(DJIMediaFile* _Nullable panoMedia, NSError* _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END

