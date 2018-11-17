//
//  DJIGimbalAttitudeAction.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIMissionAction.h>
#import <DJISDK/DJIGimbalBaseTypes.h>

NS_ASSUME_NONNULL_BEGIN


/**
 *  The Error domain for DJIGimbalAttitudeAction specific Errors.
 */
extern const NSErrorDomain DJIGimbalAttitudeActionErrorDomain;


/**
 *  A list of all errors relative to the gimbal attitude action.
 */
typedef NS_ENUM(NSInteger, DJIGimbalAttitudeActionError) {
    

    /**
     *  Default error if nothing else matches.
     */
    DJIGimbalAttitudeActionErrorUnknown = -1,


    /**
     *  Yaw value passed is beyond the max capabilities of the gimbal.
     */
    DJIGimbalAttitudeActionErrorYawOutsideMaxCapabilities = 100,


    /**
     *  Pitch value passed is beyond the max capabilities of the gimbal.
     */
    DJIGimbalAttitudeActionErrorPitchOutsideMaxCapabilities = 101,


    /**
     *  Completion Time value passed is invalid (less than 0).
     */
    DJIGimbalAttitudeActionErrorCompletionTimeInvalid = 102,

};


/**
 *  This class represents a gimbal movement action used as an element in a Timeline
 *  mission. By creating an object of this class and adding it to Mission Control's
 *  Timeline,  the camera's gimbal will move to the specified attitude when the
 *  Timeline reaches the action.
 */
@interface DJIGimbalAttitudeAction : DJIMissionAction


/**
 *  Completion time, in seconds, for the gimbal to go to the target attitude from
 *  current  attitude. Default is 1 second.
 */
@property(nonatomic, assign) double completionTime;


/**
 *  Target gimbal attitude.
 */
@property(nonatomic, readonly) DJIGimbalAttitude targetAttitude;


/**
 *  Gimbal mode to switch to when executing the action. When it is
 *  `DJIGimbalModeUnknown`,  the action will not change the gimbal mode.
 */
@property (nonatomic, assign) DJIGimbalMode gimbalMode;


/**
 *  Initialize instance with gimbal target attitude. The value of `DJIGimbalMode` is
 *  `DJIGimbalModeUnknown`.
 *  
 *  @param attitude Gimbal target attitude.
 *  
 *  @return An instance of `DJIGimbalAttitudeAction`.
 */
- (instancetype _Nullable)initWithAttitude:(DJIGimbalAttitude)attitude;


/**
 *  Initialize instance with gimbal target attitude and gimbal mode.
 *  
 *  @param attitude Gimbal target attitude.
 *  @param gimbalMode Gimbal mode to switch to.
 *  
 *  @return An instance of `DJIGimbalAttitudeAction`.
 */
- (instancetype _Nullable)initWithAttitude:(DJIGimbalAttitude)attitude
                                gimbalMode:(DJIGimbalMode)gimbalMode;

@end

NS_ASSUME_NONNULL_END
