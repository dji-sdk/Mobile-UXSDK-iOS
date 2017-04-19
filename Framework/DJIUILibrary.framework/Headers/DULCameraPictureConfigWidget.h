//
//  DULCameraPictureConfigWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUILibrary/DJIUILibrary.h>


/**
 *  Display:
 *  Widget that shows the camera's current image capturing configuration.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: (variable, max:221):30
 */
@interface DULCameraPictureConfigWidget : DULCameraConfigWidget


/**
 *  As this widget may be re-used for SD and SSD storage, this enum differentiates
 *  between the two.
 */
@property DULCameraConfigWidgetStorageType storageType;


/**
 *  The current camera mode.
 */
@property DJICameraMode cameraMode;


/**
 *  The current video resolution. Only relevant when the camera is in video mode.
 */
@property DJICameraVideoResolution videoResolution;


/**
 *  The video frame rate. Only relevant when the camera  is in video mode.
 */
@property DJICameraVideoFrameRate videoFrameRate;


/**
 *  The picture file format. Only relevant when the camera is in picture mode.
 */
@property DJICameraPhotoFileFormat pictureFileFormat;

@end
