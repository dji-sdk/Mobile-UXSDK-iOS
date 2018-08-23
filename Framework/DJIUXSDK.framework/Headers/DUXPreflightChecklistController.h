//
//  DUXPreflightChecklistController.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DUXPreflightChecklistManager.h"


/**
 *  This panel is built on top of `DUXPreflightChecklistManager`
 *  
 *  Display:
 *  Panel that shows the preflight checklist that includes a list of items (like
 *  IMU, GPS etc) and their state that roll up into an overall state.
 *  
 *  Interaction:
 *  All the settings are presented in ListView hierarchy.
 */
@interface DUXPreflightChecklistController : UIViewController


/**
 *  Creates a new instance, configured and ready to use of
 *  DUXPreflightChecklistController.
 */
+ (instancetype)preflightChecklistController;

@property (strong, nonatomic) DUXPreflightChecklistManager *checklistManager;

@end
