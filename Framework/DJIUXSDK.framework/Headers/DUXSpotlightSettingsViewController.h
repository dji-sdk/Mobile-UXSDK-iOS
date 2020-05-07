//
//  DUXSpotlightSettingsViewController.h
//  DJIUXSDK
//
//  Created by Jason Rinn on 10/12/18.
//  Copyright © 2018 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DUXObjectProtocol.h"


/**
 *  This panel shows all the information related to the spotlight accessory on the
 *  Mavic 2 Enterprise. This includes a switch to enable/disable it, brightness
 *  control and display of it's temperature value.
 */
@interface DUXSpotlightSettingsViewController : UIViewController<DUXObjectProtocol>

@end
