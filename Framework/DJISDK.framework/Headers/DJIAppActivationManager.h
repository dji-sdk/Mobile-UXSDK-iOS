//
//  DJIAppActivationManager.h
//  DJISDK
//
//  Copyright © 2017 DJI. All rights reserved.
//

#import <DJISDK/DJISDKFoundation.h>
#import "DJIAppActivationSystemTypes.h"

@class DJIAppActivationManager;


/**
 *  This protocol provides delegate methods to receive the updated state related to
 *  activation of the application.
 */
@protocol DJIAppActivationManagerDelegate <NSObject>

@optional


/**
 *  Called when the App Activation state changes.
 *  
 *  @param manager The App Activation manager that updates the current state.
 *  @param appActivationState The App Activation state. Use this state to check if login is required to unrestrict the flight limitation.
 */
-(void)manager:(DJIAppActivationManager *)manager didUpdateAppActivationState:(DJIAppActivationState)appActivationState;


/**
 *  Called when the App Activation manager updates the aircraft binding state.
 *  
 *  @param manager The App Activation manager that updates the current state.
 *  @param aircraftBindingState The aircraft binding state. Use this state to check if it is required to use DJI Go to bind the aircraft.
 */
-(void)manager:(DJIAppActivationManager *)manager didUpdateAircraftBindingState:(DJIAppActivationAircraftBindingState)aircraftBindingState;

@end


/**
 *  DJI aircraft firmware require mobile applications that control DJI aircraft to
 *  be activated with the user's DJI account, if that application is being used in
 *  China. This will ensure operators use the correct set of geospatial information
 *  and flight functions for their aircraft, as determined by their geographical
 *  location and user profile.
 *   A summary of the activation system is:
 *   - Users in China are required to activate their application by logging into
 *  their DJI account at least once every three months within the application
 *   - Activation will be persistent in the application until the user logs out
 *   - A data connection will be required to log into a DJI account
 *   - Outside of China, the SDK will automatically activate the application without
 *  requiring the user to log in
 *   - Additionally, users in china are required to bind their aircraft to their
 *  user account in DJI Go. This is required only once.
 *   If an application is not activated, the aircraft not bound (if required), or a
 *  legacy version of the SDK (<4.1) is being used, all camera live streams will be
 *  disabled, and flight will be limited to a cylinder of 100m diameter and 30m
 *  height to ensure the aircraft stays within line of sight.
 *   This class is used to check the state of application activation and aircraft
 *  binding.
 */
@interface DJIAppActivationManager : NSObject

- (instancetype)init OBJC_UNAVAILABLE("You must use the singleton");

+ (instancetype)new OBJC_UNAVAILABLE("You must use the singleton");


/**
 *  Delegate to receive the state update.
 */
@property (nonatomic, weak)  id<DJIAppActivationManagerDelegate> delegate;


/**
 *  Current App Activation state.
 */
@property (nonatomic, readonly) DJIAppActivationState appActivationState;


/**
 *  Current aircraft binding state. Users in China need to bind additional account
 *  details with  the aircraft one-time through DJI Go. These details need to be
 *  bound and the application  needs to be activated by logging into their DJI Go
 *  account to lift the flight restrictions.
 */
@property (nonatomic, readonly) DJIAppActivationAircraftBindingState aircraftBindingState;

@end
