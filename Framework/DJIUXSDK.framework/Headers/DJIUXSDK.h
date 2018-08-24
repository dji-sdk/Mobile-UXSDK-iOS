//
//  DJIUXSDK.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for DJIUXSDK.
FOUNDATION_EXPORT double DJIUXSDKVersionNumber;

//! Project version string for DJIUXSDK.
FOUNDATION_EXPORT const unsigned char DJIUXSDKVersionString[];

/*********************************************************************************/
#pragma mark - Widgets
/*********************************************************************************/
#import <DJIUXSDK/DUXWidgetProtocol.h>
#import <DJIUXSDK/DUXWidget.h>
#import <DJIUXSDK/DUXObjectProtocol.h>

// Dashboard
#import <DJIUXSDK/DUXDashboardWidget.h>
#import <DJIUXSDK/DUXAltitudeWidget.h>
#import <DJIUXSDK/DUXCompassWidget.h>
#import <DJIUXSDK/DUXDistanceHomeWidget.h>
#import <DJIUXSDK/DUXDistanceRCWidget.h>
#import <DJIUXSDK/DUXHorizontalVelocityWidget.h>
#import <DJIUXSDK/DUXVerticalVelocityWidget.h>

// Camera Config
#import <DJIUXSDK/DUXCameraConfigWidget.h>

#import <DJIUXSDK/DUXCameraConfigInfoWidget.h>
#import <DJIUXSDK/DUXCameraConfigApertureWidget.h>
#import <DJIUXSDK/DUXCameraConfigWBWidget.h>
#import <DJIUXSDK/DUXCameraConfigEVWidget.h>
#import <DJIUXSDK/DUXCameraConfigExposureSensitivityWidget.h>
#import <DJIUXSDK/DUXCameraConfigShutterWidget.h>

#import <DJIUXSDK/DUXCameraConfigStorageWidget.h>
#import <DJIUXSDK/DUXCameraPictureConfigWidget.h>
#import <DJIUXSDK/DUXCameraCapacityConfigWidget.h>
#import <DJIUXSDK/DUXCameraConfigSSDWidget.h>

// Camera Controls
#import <DJIUXSDK/DUXCameraSettingsMenu.h>
#import <DJIUXSDK/DUXPictureVideoSwitchWidget.h>
#import <DJIUXSDK/DUXCaptureWidget.h>
#import <DJIUXSDK/DUXRecordVideoTimeWidget.h>
#import <DJIUXSDK/DUXRecordVideoWidget.h>
#import <DJIUXSDK/DUXTakePictureWidget.h>
#import <DJIUXSDK/DUXExposureSettingsMenu.h>
#import <DJIUXSDK/DUXFocusModeWidget.h>
#import <DJIUXSDK/DUXManualFocusAdjustmentWidget.h>
#import <DJIUXSDK/DUXFocusTargetWidget.h>
#import <DJIUXSDK/DUXExposureFocusSwitchWidget.h>
#import <DJIUXSDK/DUXAutoExposureSwitchWidget.h>

// Statuses
#import <DJIUXSDK/DUXBatteryWidget.h>
#import <DJIUXSDK/DUXConnectionWidget.h>
#import <DJIUXSDK/DUXDJILogoWidget.h>
#import <DJIUXSDK/DUXFlightModeWidget.h>
#import <DJIUXSDK/DUXGPSSignalWidget.h>
#import <DJIUXSDK/DUXPreFlightStatusWidget.h>
#import <DJIUXSDK/DUXRemoteControlSignalWidget.h>
#import <DJIUXSDK/DUXVideoSignalWidget.h>
#import <DJIUXSDK/DUXVisionWidget.h>
#import <DJIUXSDK/DUXRemainingFlightTimeWidget.h>
#import <DJIUXSDK/DUXWifiSignalWidget.h>
#import <DJIUXSDK/DUXRadarWidget.h>

// Actions
#import <DJIUXSDK/DUXReturnHomeWidget.h>
#import <DJIUXSDK/DUXTakeOffWidget.h>

// Map
#import <DJIUXSDK/DUXMapWidget.h>
#import <DJIUXSDK/DUXMapViewController.h>

/*********************************************************************************/
#pragma mark - Panels
/*********************************************************************************/
#import <DJIUXSDK/DUXCameraSettingsController.h>
#import <DJIUXSDK/DUXExposureSettingsController.h>
#import <DJIUXSDK/DUXPreflightChecklistController.h>
#import <DJIUXSDK/DUXRTKStatusViewController.h>

/*********************************************************************************/
#pragma mark - View Controllers and Widget Collections - MAY CHANGE IN FUTURE
/*********************************************************************************/
/**
 *  View Controllers
 */
#import <DJIUXSDK/DUXDefaultLayoutViewcontroller.h>
#import <DJIUXSDK/DUXDefaultLayoutView.h>

// WidgetCollection
#import <DJIUXSDK/DUXWidgetCollectionViewProtocol.h>
#import <DJIUXSDK/DUXWidgetcollectionView.h>
#import <DJIUXSDK/DUXWidgetCollectionViewControllerProtocol.h>
#import <DJIUXSDK/DUXWidgetCollectionViewController.h>
#import <DJIUXSDK/DUXWidgetItem.h>
#import <DJIUXSDK/DUXWidgetCollectionViewCenterLayout.h>
#import <DJIUXSDK/DUXWidgetCollectionViewStacksLayout.h>

// Status
#import <DJIUXSDK/DUXStatusBarViewController.h>
#import <DJIUXSDK/DUXStatusBarView.h>

// SideBar
#import <DJIUXSDK/DUXSideBarViewController.h>
#import <DJIUXSDK/DUXSideBarView.h>
#import <DJIUXSDK/DUXLeadingBarViewController.h>
#import <DJIUXSDK/DUXTrailingBarViewController.h>

// Dock
#import <DJIUXSDK/DUXDockViewController.h>
#import <DJIUXSDK/DUXDockView.h>

// Content
#import <DJIUXSDK/DUXContentViewController.h>
#import <DJIUXSDK/DUXContentView.h>

// FPV
#import <DJIUXSDK/DUXFPVViewController.h>
#import <DJIUXSDK/DUXFPVView.h>
#import <DJIUXSDK/DUXFPVInteractionController.h>

// Preflight Checklist Manager
#import <DJIUXSDK/DUXPreflightChecklistManager.h>
#import <DJIUXSDK/DUXPreflightChecklistItem.h>
#import <DJIUXSDK/DUXOverallChecklistItem.h>
#import <DJIUXSDK/DUXAircraftConnectionChecklistItem.h>
#import <DJIUXSDK/DUXAircraftLocationChecklistItem.h>
#import <DJIUXSDK/DUXFlightModeChecklistItem.h>
#import <DJIUXSDK/DUXCompassChecklistItem.h>
#import <DJIUXSDK/DUXIMUChecklistItem.h>
#import <DJIUXSDK/DUXESCChecklistItem.h>
#import <DJIUXSDK/DUXRemoteControllerChecklistItem.h>
#import <DJIUXSDK/DUXRadioQualityChecklistItem.h>
#import <DJIUXSDK/DUXAircraftBatteryChecklistItem.h>
#import <DJIUXSDK/DUXGimbalChecklistItem.h>
#import <DJIUXSDK/DUXStorageCapacityChecklistItem.h>
#import <DJIUXSDK/DUXVisionChecklistItem.h>
#import <DJIUXSDK/DUXRemoteControllerBatteryChecklistItem.h>
#import <DJIUXSDK/DUXAircraftBatteryTemperatureChecklistItem.h>

// Color Waveform
#import <DJIUXSDK/DUXColorWaveformWidget.h>

/**
 *  SDKModel
 */
 
#import <DJIUXSDK/DUXSDKModel.h>
