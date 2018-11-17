//
//  DJIUserAccountManager.h
//  DJISDK
//
//  Copyright © 2017 DJI. All rights reserved.
//

#import "DJISDKFoundation.h"


/**
 *  User account status. Users need to be logged in.
 */
typedef NS_ENUM(uint8_t, DJIUserAccountState) {


    /**
     *  User is not logged in. User needs to be logged in to retrieve currently
     *  unlocked,  and unlock authorization zones.
     */
    DJIUserAccountStateNotLoggedIn,


    /**
     *  User is logged in but has not been authorized to unlock authorization zones.
     */
    DJIUserAccountStateNotAuthorized,


    /**
     *  User is logged in and has been authorized to unlock authorization zones.
     */
    DJIUserAccountStateAuthorized,


    /**
     *  The token of the user account is out of date.
     */
    DJIUserAccountStateTokenOutOfDate,


    /**
     *  Unknown.
     */
    DJIUserAccountStateUnknown = 0xFF
};


/**
 *  DJI Account State Completion Block.
 *  
 *  @param state An enum value of `DJIUserAccountState`.
 *  @param error Error retrieving the value.
 */
typedef void (^_Nullable DJIAccountStateCompletionBlock)(DJIUserAccountState state, NSError *_Nullable error);


/**
 *  Class used to manage the DJI account.
 */
@interface DJIUserAccountManager : NSObject


/**
 *  Current state of DJI user account.
 *  
 *  @return An enum value of `DJIUserAccountState`.
 */
@property (nonatomic, readonly) DJIUserAccountState userAccountState;


/**
 *  The name of the currently logged in user account.  It is `nil`  if
 *  `userAccountState` is either:   `DJIUserAccountStateNotLoggedIn`,
 *  `DJIUserAccountStateTokenOutOfDate`  or `DJIUserAccountStateUnknown`.
 */
@property(nonatomic, readonly, nullable) NSString *loggedInDJIUserAccountName;


/**
 *  After invoking this method, a dialog redirecting users to log into their DJI
 *  account  will be shown. For users outside of China, authorization is required to
 *  unlock  authorization zones. After the login process, if `authorizationRequired`
 *  is `YES`,  and the user is currently out of China and the account has not been
 *  authorized to  unlock authorization zones, the dialog will then redirect users
 *  to authorize their account.
 *  
 *  @param authorizationRequired `YES` if authorization is required.
 *  @param completion The execution block with the returned execution result.
 */
-(void)logIntoDJIUserAccountWithAuthorizationRequired:(BOOL)authorizationRequired
                                       withCompletion:(DJIAccountStateCompletionBlock)completion;


/**
 *  Logs out the DJI user that is logged in.
 *  
 *  @param completion The `completion block` with the returned execution result.
 */
-(void)logOutOfDJIUserAccountWithCompletion:(DJICompletionBlock)completion;

@end
