//
//  DUXAccessLockerWidget.h
//  DJIUXSDK
//
//  Created by Andrew Lauer Barinov on 10/17/18.
//  Copyright © 2018 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>

NS_ASSUME_NONNULL_BEGIN


/**
 *  The access locker widget is used to manage the password protection status of the
 *  aircraft. When password protection is enabled, data on the aircraft is only
 *  accessible to the user after entering the password. Tapping on the widget will
 *  bring up prompts according to the state of the access locker.
 */
@interface DUXAccessLockerWidget : DUXWidget


/**
 *  The view controller that will present alerts related to the access locker
 *  widget.
 */
@property (nonatomic, weak) UIViewController *presentingViewController;

@end

NS_ASSUME_NONNULL_END
