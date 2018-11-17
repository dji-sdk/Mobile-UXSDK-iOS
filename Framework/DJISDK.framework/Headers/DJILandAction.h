//
//  DJILandAction.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIMissionAction.h>


/**
 *  This class represents a land action used as an element in a Timeline mission. By
 *  creating  an object of this class and adding it to Mission Control's Timeline,
 *  the aircraft will  land at its current location when the Timeline reaches the
 *  action.
 */
@interface DJILandAction : DJIMissionAction


/**
 *  `YES` to enable automatic confirmation during landing. For flight controller
 *  firmware  version 3.2.0.0 or above, when the clearance between the aircraft and
 *  the ground is less  than 0.3m, the aircraft will pause landing and wait for the
 *  user's confirmation to continue  (see `confirmLandingWithCompletion`). Enabling
 *  this auto confirmation, allows the  aircraft to continue landing without the
 *  user's confirmation during the Timeline execution.  For firmware that does not
 *  require landing confirmation, the value is ignored. The default  value is `YES`.
 */
@property (nonatomic, readwrite) BOOL autoConfirmLandingEnabled;

@end
