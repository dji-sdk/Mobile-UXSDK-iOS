//
//  DUXLeadingBarViewController.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DUXSideBarViewController.h>

@class DUXTakeOffWidget;
@class DUXReturnHomeWidget;
@class DUXSpeakerWidget;
@class DUXSpeakerSettingsViewController;
@class DUXSpotlightWidget;
@class DUXSpotlightSettingsViewController;


/**
 *  Subclass of DUXSideBarViewController which  manages the logic for pre-populating
 *  the leading  side bar view with widgets similar to DJI Go.
 */
@interface DUXLeadingBarViewController : DUXSideBarViewController


/**
 *  The instance of DUXTakeOffWidget which is actually shown in the
 *    `DUXLeadingBarViewController`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXTakeOffWidget *takeOffWidget;


/**
 *  The instance of DUXReturnHomeWidget which is actually shown in the
 *    `DUXLeadingBarViewController`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXReturnHomeWidget *goHomeWidget;


/**
 *  The instance of DUXSpeakerWidget which is actually shown in the
 *    `DUXLeadingBarViewController`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXSpeakerWidget *speakerWidget;


/**
 *  The instance of DUXSpotlightWidget which is actually shown in the
 *    `DUXLeadingBarViewController`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXSpotlightWidget *spotlightWidget;


/**
 *  The instance of DUXSpotlightSettingsViewController which is actually shown in
 *  the
 *    `DUXLeadingBarViewController`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXSpotlightSettingsViewController *spotlightSettingsController;


/**
 *  The instance of DUXSpeakerSettingsViewController which is actually shown in the
 *    `DUXLeadingBarViewController`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXSpeakerSettingsViewController *speakerSettingsController;

@end
