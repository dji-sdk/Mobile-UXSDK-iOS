//
//  DJIUILibrary.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for DJIUILibrary.
FOUNDATION_EXPORT double DJIUILibraryVersionNumber;

//! Project version string for DJIUILibrary.
FOUNDATION_EXPORT const unsigned char DJIUILibraryVersionString[];

/*********************************************************************************/
#pragma mark - Widgets
/*********************************************************************************/
#import <DJIUILibrary/DULWidgetProtocol.h>
#import <DJIUILibrary/DULWidget.h>

// Dashboard
#import <DJIUILibrary/DULDashboardWidget.h>
#import <DJIUILibrary/DULAltitudeWidget.h>
#import <DJIUILibrary/DULCompassWidget.h>
#import <DJIUILibrary/DULDistanceHomeWidget.h>
#import <DJIUILibrary/DULDistanceRCWidget.h>
#import <DJIUILibrary/DULHorizontalVelocityWidget.h>
#import <DJIUILibrary/DULVerticalVelocityWidget.h>

// Camera Config
#import <DJIUILibrary/DULCameraConfigWidget.h>

#import <DJIUILibrary/DULCameraConfigInfoWidget.h>
#import <DJIUILibrary/DULCameraConfigApertureWidget.h>
#import <DJIUILibrary/DULCameraConfigWBWidget.h>
#import <DJIUILibrary/DULCameraConfigEVWidget.h>
#import <DJIUILibrary/DULCameraConfigIsoWidget.h>
#import <DJIUILibrary/DULCameraConfigShutterWidget.h>

#import <DJIUILibrary/DULCameraConfigStorageWidget.h>
#import <DJIUILibrary/DULCameraPictureConfigWidget.h>
#import <DJIUILibrary/DULCameraCapacityConfigWidget.h>

// Camera Controls
#import <DJIUILibrary/DULCameraSettingsMenu.h>
#import <DJIUILibrary/DULPictureVideoSwitchWidget.h>
#import <DJIUILibrary/DULCaptureWidget.h>
#import <DJIUILibrary/DULRecordVideoTimeWidget.h>
#import <DJIUILibrary/DULRecordVideoWidget.h>
#import <DJIUILibrary/DULTakePictureWidget.h>
#import <DJIUILibrary/DULExposureSettingsMenu.h>

// Statuses
#import <DJIUILibrary/DULBatteryWidget.h>
#import <DJIUILibrary/DULConnectionWidget.h>
#import <DJIUILibrary/DULDJILogoWidget.h>
#import <DJIUILibrary/DULFlightModeWidget.h>
#import <DJIUILibrary/DULGPSSignalWidget.h>
#import <DJIUILibrary/DULPreFlightStatusWidget.h>
#import <DJIUILibrary/DULRemoteControlSignalWidget.h>
#import <DJIUILibrary/DULVideoSignalWidget.h>
#import <DJIUILibrary/DULVisionWidget.h>
#import <DJIUILibrary/DULRemainingFlightTimeWidget.h>

// Actions
#import <DJIUILibrary/DULReturnHomeWidget.h>
#import <DJIUILibrary/DULTakeOffWidget.h>

/*********************************************************************************/
#pragma mark - Panels
/*********************************************************************************/
#import <DJIUILibrary/DULCameraSettingsController.h>
#import <DJIUILibrary/DULExposureSettingsController.h>
#import <DJIUILibrary/DULPreflightChecklistController.h>

/*********************************************************************************/
#pragma mark - View Controllers and Widget Collections - MAY CHANGE IN FUTURE
/*********************************************************************************/
/**
 *  View Controllers
 */
#import <DJIUILibrary/DULDefaultLayoutViewcontroller.h>
#import <DJIUILibrary/DULDefaultLayoutView.h>

// WidgetCollection
#import <DJIUILibrary/DULWidgetCollectionViewProtocol.h>
#import <DJIUILibrary/DULWidgetcollectionView.h>
#import <DJIUILibrary/DULWidgetCollectionViewControllerProtocol.h>
#import <DJIUILibrary/DULWidgetCollectionViewController.h>
#import <DJIUILibrary/DULWidgetItem.h>
#import <DJIUILibrary/DULWidgetCollectionViewCenterLayout.h>
#import <DJIUILibrary/DULWidgetCollectionViewStacksLayout.h>

// Status
#import <DJIUILibrary/DULStatusBarViewController.h>
#import <DJIUILibrary/DULStatusBarView.h>

// SideBar
#import <DJIUILibrary/DULSideBarViewController.h>
#import <DJIUILibrary/DULSideBarView.h>
#import <DJIUILibrary/DULLeadingBarViewController.h>
#import <DJIUILibrary/DULTrailingBarViewController.h>

// Dock
#import <DJIUILibrary/DULDockViewController.h>
#import <DJIUILibrary/DULDockView.h>

// Content
#import <DJIUILibrary/DULContentViewController.h>
#import <DJIUILibrary/DULContentView.h>

// FPV
#import <DJIUILibrary/DULFPVViewController.h>
#import <DJIUILibrary/DULFPVView.h>

// Preflight Checklist Manager
#import <DJIUILibrary/DULPreflightChecklistManager.h>
#import <DJIUILibrary/DULPreflightChecklistItem.h>
#import <DJIUILibrary/DULAircraftConnectionChecklistItem.h>
#import <DJIUILibrary/DULAircraftLocationChecklistItem.h>
#import <DJIUILibrary/DULFlightModeChecklistItem.h>
#import <DJIUILibrary/DULCompassChecklistItem.h>
#import <DJIUILibrary/DULIMUChecklistItem.h>
#import <DJIUILibrary/DULESCChecklistItem.h>
#import <DJIUILibrary/DULRemoteControllerChecklistItem.h>
#import <DJIUILibrary/DULRadioQualityChecklistItem.h>
#import <DJIUILibrary/DULAircraftBatteryChecklistItem.h>
#import <DJIUILibrary/DULGimbalChecklistItem.h>
#import <DJIUILibrary/DULStorageCapacityChecklistItem.h>


/**
 *  SDKModel
 */
 
#import <DJIUILibrary/DULSDKModel.h>
