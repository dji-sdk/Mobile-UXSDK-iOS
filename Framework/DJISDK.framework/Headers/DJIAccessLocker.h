//
//  DJIAccessLocker.h
//  DJISDK
//
//  Copyright © 2018 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJISDK.h>
#import <DJISDK/DJIAccessLockerBaseTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIAccessLockerUserAccountInfo;
@class DJIAccessLockerChangePasswordSettings;
@class DJIAccessLocker;


/**
 *  Define the state of Access Locker.
 */
@protocol DJIAccessLockerDelegate <NSObject>

@optional


/**
 *  Delegate method to receive the latest state of the Access Locker.
 *  
 *  @param accessLocker The Access Locker that updates the state.
 *  @param state The `DJIAccessLocker` state.
 */
- (void)accessLocker:(DJIAccessLocker *)accessLocker didUpdateState:(DJIAccessLockerState)state;


/**
 *  Delegate method to receive the latest formatting state.
 *  
 *  @param accessLocker The Access Locker that updates the state.
 *  @param state The `DJIAccessLocker` formatting state.
 */
- (void)accessLocker:(DJIAccessLocker *)accessLocker didUpdateFormattingState:(DJIAccessLockerFormattingState *)state;

@end


/**
 *  The Access Locker provides methods to control the permission to access the
 *  aircraft. For an aircraft with advanced security features, the aircraft is
 *  locked after a user account is set up: the storage is not accessible; the live
 *  view is not available; the aircraft cannot take off. The user can unlock  the
 *  aircraft with the security code to access all features of the aircraft. The
 *  security code is encrypted in the aircraft. DJI will not be able to fetch  the
 *  security code. If the security code is forgotten, the user has to format the
 *  storage to reset the protection system. All the files in the internal  storage
 *  and the user account information will be deleted. The Access Locker is only
 *  supported by Mavic 2 Enterprise.
 */
@interface DJIAccessLocker : NSObject


/**
 *  Delegate that receives the information sent by the Access Locker.
 */
@property (nonatomic, weak) id<DJIAccessLockerDelegate> delegate;


/**
 *  The latest state of the Access Locker.
 */
@property (nonatomic, readonly) DJIAccessLockerState state;


/**
 *  The latest formatting state of the Access Locker.
 */
@property (nonatomic, readonly) DJIAccessLockerFormattingState *formattingState;


/**
 *  The version of the security feature.
 *  
 *  @param version Version of the security feature.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getVersionWithCompletion:(void (^_Nullable)(NSUInteger version, NSError *_Nullable error))completion;


/**
 *  Returns the username of the current Access Locker account.
 *  
 *  @param userName User name of the current Access Locker account.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getUsernameWithCompletion:(void (^_Nullable)(NSString *userName, NSError *_Nullable error))completion;


/**
 *  Sets up a user account to enable the access protection of  the aircraft. After
 *  setting up a user account, the security  code of the user is required in each
 *  power-cycle of the  aircraft or the aircraft is just paired with the remote
 *  controller. The security code is also required to access  data in the aircraft
 *  through DJI Assistant 2. This method  is only valid when the state is
 *  `DJIAccessLockerStateNotInitialized`. If  the method executes successfully, the
 *  state will change  to `DJIAccessLockerStateUnlocked`.
 *  
 *  @param account User account info to be set to the Access Locker system.
 *  @param completion Completion block to receive the result.
 */
- (void)setUpUserAccount:(DJIAccessLockerUserAccountInfo *)account withCompletion:(DJICompletionBlock)completion;


/**
 *  Logs in to unlock the access protection of the aircraft.  This method is valid
 *  when the state is `DJIAccessLockerStateLocked`.  If the user is logged in
 *  successfully, the state will change to `DJIAccessLockerStateUnlocked`.
 *  
 *  @param account User account info to be set to the Access Locker system.
 *  @param completion Completion block to receive the result.
 */
- (void)login:(DJIAccessLockerUserAccountInfo *)account withCompletion:(DJICompletionBlock)completion;


/**
 *  Modifies the user account. The old user account information will be overridden
 *  by the new one. This method is valid when the state is  either
 *  `DJIAccessLockerStateUnlocked`  or `DJIAccessLockerStateLocked`. If the user
 *  account is  modified, the aircraft will be locked and the state will change  to
 *  `DJIAccessLockerStateLocked`.
 *  
 *  @param currentAccountInfo Current user account info to be set to the Access Locker system.
 *  @param newUserAccountInfo New user account info to be set to the Access Locker system.
 *  @param completion Completion block to receive the result.
 */
- (void)modifyUserAccount:(DJIAccessLockerUserAccountInfo *)currentAccountInfo newUserAccountInfo:(DJIAccessLockerUserAccountInfo *)newUserAccountInfo withCompletion:(DJICompletionBlock)completion;


/**
 *  Resets the user account to disable the protection. The user account information
 *  (e.g.  user name, security code) will be deleted and the aircraft is accessible
 *  without  validating the user. This method is valid when the state is either
 *  `DJIAccessLockerStateUnlocked`  or `DJIAccessLockerStateLocked`. If the user
 *  account is reset, the state will change  to
 *  `DJIAccessLockerStateNotInitialized`.
 *  
 *  @param userAccountInfo User account info to be set to the Access Locker system.
 *  @param completion Completion block to receive the result.
 */
- (void)resetUserAccount:(DJIAccessLockerUserAccountInfo *)userAccountInfo withCompletion:(DJICompletionBlock)completion;


/**
 *  Formats the protected data in the aircraft, including data in the internal
 *  storage and the user account information.  This method is only valid when the
 *  user account is set up. Use `DJIAccessLockerFormattingState`  to check the
 *  progress of formatting.  When formatting is done, the state will change to
 *  `DJIAccessLockerStateNotInitialized`.
 *  
 *  @param completion Completion block to receive the result.
 */
- (void)formatWithCompletion:(DJICompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END
