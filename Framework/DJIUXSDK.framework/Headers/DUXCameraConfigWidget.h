//
//  DUXCameraConfigWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DUXWidget.h>

typedef NS_ENUM(NSInteger, DUXCameraConfigWidgetStorageType) {
    DUXCameraConfigInfoSD,
    DUXCameraConfigInfoSSD,
};


/**
 *  Display:
 *  Base class for all widgets used in the FPV camera state widgets. These are the
 *  widgets usually visible over the FPV that give a quick view to the current
 *  exposure settings, white balance and storage of the camera.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 45:22
 */
@interface DUXCameraConfigWidget : DUXWidget


/**
 *  The NSString value of the label or title of the camera setting (e.g. "ISO")
 */
@property (strong, nonatomic) NSString *labelString;


/**
 *  The NSString of the camera setting value (e.g. "100" for ISO).
 */
@property (strong, nonatomic) NSString *valueString;


/**
 *  This bool defines whether or not the value is to be highlighted. For example,
 *  for exposure state widgets, it is used to highlight which exposure setting is
 *  prioritized. In shutter priority mode, the shutter speed would be highlighted.
 */
@property BOOL attributeIsActive;

@end
