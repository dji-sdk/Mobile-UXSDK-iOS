//
//  DULPreflightChecklistController.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>


/**
 *  This panel is built on top of `DULPreflightChecklistManager`
 *  
 *  Display:
 *  Panel that shows the preflight checklist that includes a list of items (like
 *  IMU, GPS etc) and their state that roll up into an overall state.
 *  
 *  Interaction:
 *  All the settings are presented in ListView hierachy.
 */
@interface DULPreflightChecklistController : UIViewController


/**
 *  Creates a new instance, configured and ready to use of
 *  DULPreflightChecklistController.
 */
+ (instancetype)preflightChecklistController;

@end
