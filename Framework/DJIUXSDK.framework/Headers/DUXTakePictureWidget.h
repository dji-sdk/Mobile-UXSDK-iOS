//
//  DUXTakePictureWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <DJIUXSDK/DUXWidget.h>


/**
 *  Display:
 *  Action widget to capture a photo that shows a different image depending on what
 *  shoot photo mode the camera is in (burst, auto exposure bracketing (AEB),
 *  interval etc.).
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 1:1
 */
@interface DUXTakePictureWidget : DUXWidget


/**
 *  The shoot photo mode.
 */
@property DJICameraShootPhotoMode shootMode;


/**
 *  The burst count value. Only relevant when shootmode is in burst mode.
 */
@property DJICameraPhotoBurstCount burstCount;


/**
 *  The AEB count value. Only relevant when shootmode is in AEB mode.
 */
@property DJICameraPhotoAEBCount aebCount;


/**
 *  The interval settings value. Only relevant when shootmode is in interval mode.
 */
@property DJICameraPhotoTimeIntervalSettings intervalSettings;


@end
