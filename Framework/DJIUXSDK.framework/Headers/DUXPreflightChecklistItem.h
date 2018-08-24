//
//  DUXPreflightChecklistItem.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DUXObjectProtocol.h"
#import <DJIUXSDK/UIImage+Assets.h>

@class DUXPreflightChecklistManager;

typedef NS_ENUM(NSInteger, DUXPreflightChecklistItemState) {
    DUXPreflightChecklistItemPendingState,
    DUXPreflightChecklistItemWarningState,
    DUXPreflightChecklistItemErrorState,
    DUXPreflightChecklistItemReadyState,
};


/**
 *  Base class for all items to be used by the `DUXPreflightChecklistManager`
 */
@interface DUXPreflightChecklistItem : NSObject <DUXObjectProtocol>


/**
 *  The Preflight checklist manager this item is assigned to. This will be set by
 *  the manager when the item is added to it.
 */
@property (weak, nonatomic) DUXPreflightChecklistManager *manager;


/**
 *  The current state of the item.
 */
@property (nonatomic) DUXPreflightChecklistItemState state;


/**
 *  The list of states which the item considers as ok and ready to fly.
 */
@property (strong, nonatomic) NSArray *readyToFlyStates;


/**
 *  The ready to fly state of the item.
 */
@property (nonatomic, readonly) BOOL isReadyToFly;


/**
 *  A small default image to be used with the item in the UI context.
 */
@property (readonly) UIImage *pictogram;


/**
 *  A short string describing the item. Should not change during the item's life
 *  cycle.
 */
@property (strong, nonatomic) NSString *title;


/**
 *  A more elaborate string that describes the current state of the item or its
 *  activity.
 */
@property (strong, nonatomic) NSString *stateDetails;


/**
 *  A one or two words describing the current state of the item or its activity.
 */
@property (strong, nonatomic) NSString *shortStateDetails;

/*********************************************************************************/
#pragma mark - Monitoring
/*********************************************************************************/


/**
 *  Start checking for the state defining whether this item is ready to fly or not
 */
- (void)startChecking;


/**
 *  Stops checking for the state defining whether this item is ready to fly or not
 */
- (void)stopChecking;


@end
