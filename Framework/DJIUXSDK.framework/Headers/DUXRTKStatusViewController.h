//
//  DUXRTKStatusViewController.h
//  DJIUXSDK
//
//  Created by Arnaud Thiercelin on 8/3/17.
//  Copyright © 2017 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DUXObjectProtocol.h"


/**
 *  Display:
 *  This panel shows all the information related to RTK.  This includes coordinates
 *  and altitude of the aircraft and base station, course angle, GLONASS, Beidou and
 *  GPS satellite counts for both antennas and the base station, and overall status
 *  of the RTK system.
 *  
 *  Interaction:
 *  RTK can be toggled using a switch at the top of the panel.
 */
@interface DUXRTKStatusViewController : UIViewController <DUXObjectProtocol>


/**
 *  Creates a new instance, configured and ready to use of RTKStatusViewController.
 */
+ (instancetype)rtkStatusController;

@end
