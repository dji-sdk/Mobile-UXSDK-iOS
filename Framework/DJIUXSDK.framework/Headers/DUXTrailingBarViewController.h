//
//  DUXTrailingBarViewController.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DUXSideBarViewController.h>

@class DUXCameraSettingsMenu;
@class DUXCameraSettingsController;
@class DUXPictureVideoSwitchWidget;
@class DUXCaptureWidget;
@class DUXExposureSettingsController;


/**
 *  Subclass of DUXSideBarViewController which  manages the logic for
 *    pre-populating the trailing side bar view with widgets similar
 *    to DJI Go.
 */
@interface DUXTrailingBarViewController : DUXSideBarViewController


/**
 *  The instance of DUXCameraSettingsMenu which is actually shown in the
 *    `DUXTrailingBarViewController`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXCameraSettingsMenu *cameraSettingMenuWidget;


/**
 *  The instance of DUXCameraSettingsController which is actually shown in the
 *    `DUXTrailingBarViewController`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXCameraSettingsController *cameraSettingsController;


/**
 *  The instance of DUXPictureVideoSwitchWidget which is actually shown in the
 *    `DUXTrailingBarViewController`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXPictureVideoSwitchWidget *pictureVideoSwitchWidget;


/**
 *  The instance of DUXCaptureWidget which is actually shown in the
 *    `DUXTrailingBarViewController`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXCaptureWidget *captureWidget;


/**
 *  The instance of DUXExposureSettingsController which is actually shown in the
 *    `DUXTrailingBarViewController`.
 */
@property (readonly, nonatomic, nullable) __kindof DUXExposureSettingsController *exposureSettingsController;

@end
