//
//  DJIMissionAction.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIMissionControl.h>


/**
 *  Base class for all Mission Control Timeline based actions.
 */
@interface DJIMissionAction : NSObject <DJIMissionControlTimelineElement>


/**
 *  `YES` if the action is running.
 */
@property (readonly, nonatomic) BOOL isRunning;


/**
 *  `YES` if the action is paused.
 */
@property (readonly, nonatomic) BOOL isPaused;

@end
