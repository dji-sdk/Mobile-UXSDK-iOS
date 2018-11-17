//
//  DJITakeOffAction.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIMissionAction.h>

NS_ASSUME_NONNULL_BEGIN


/**
 *  This class represents a take-off action used as an element in a Timeline
 *  mission. By creating an object of this class and adding it to Mission Control's
 *  Timeline,  the aircraft will take-off when the Timeline reaches the action.
 *  Note: This action  has 60 seconds TIME_OUT mechanism. Before invoking this
 *  action, please make sure the  aircraft's motors are turned off.
 */
@interface DJITakeOffAction : DJIMissionAction

@end

NS_ASSUME_NONNULL_END
