//
//  DJIAccessLockerBaseTypes.h
//  SDKSharedLib
//
//  Copyright © 2018 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


/**
 *  The aircraft's access locker state.
 */
typedef NS_ENUM(uint8_t, DJIAccessLockerState) {

    /**
     *  The access locker is not initialized. Set up user account to initialize the
     *  system.
     */
    DJIAccessLockerStateNotInitialized,

    /**
     *  The aircraft is locked and protected. In this state, the internal  storage
     *  cannot be accessed, the aircraft will stop streaming the  live view and the
     *  aircraft cannot take off. Use the Security Code  to unlock the aircraft.
     */
    DJIAccessLockerStateLocked,

    /**
     *  The aircraft is unlocked.
     */
    DJIAccessLockerStateUnlocked,

    /**
     *  Either the aircraft is disconnected or the connected product does not  support
     *  the access locker.
     */
    DJIAccessLockerStateUnknown = 0xFF,
};


/**
 *  The aircraft's access locker formatting progress state.
 */
typedef NS_ENUM(uint8_t, DJIAccessLockerFormattingProgressState) {

    /**
     *  No formatting operation is executing or executed in this aircraft's power cycle.
     */
    DJIAccessLockerFormattingProgressStateInitial,

    /**
     *  The aircraft's data is being formatted.
     */
    DJIAccessLockerFormattingProgressStateFormatting,

    /**
     *  The aircraft has formatted data in the internal storage and the user account
     *  set up for the security feature.
     */
    DJIAccessLockerFormattingProgressStateSuccessful,

    /**
     *  The formatting operation is failed. Check `DJIAccessLockerFormattingState` for
     *  detail.
     */
    DJIAccessLockerFormattingProgressStateFailure,
};


/**
 *  Formatting state of the access locker.
 */
@interface DJIAccessLockerFormattingState : NSObject


/**
 *  The progress state.
 */
@property (nonatomic, readonly) DJIAccessLockerFormattingProgressState progressState;


/**
 *  Checks if the formatting operation is successfully completed. The  recent
 *  formatting operation failure if any. NULL if the recent formatting operation
 *  succeeded.
 */
@property (nonatomic, readonly) NSError *error;

@end


/**
 *  The class represents the user account information of the access locker.
 */
@interface DJIAccessLockerUserAccountInfo : NSObject


/**
 *  The user name.
 *  
 *  @return A string value.
 */
@property (nonatomic, readonly) NSString *username;


/**
 *  The security code of the account.
 *  
 *  @return A string value.
 */
@property (nonatomic, readonly) NSString *securityCode;


/**
 *  Constructor method for the UserAccountInfo.
 *  
 *  @param username The user name.
 *  @param securityCode The security code of current user account.
 */
- (instancetype)initWithUserName:(NSString *)username securityCode:(NSString *)securityCode;

@end

NS_ASSUME_NONNULL_END
