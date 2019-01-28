//
//  DUXManualZoomBaseWidget.h
//  DJIUXSDK
//
//  Copyright © 2018 DJI. All rights reserved.
//

#import <DJIUXSDK/DUXWidget.h>
#import "DUXManualZoomModel.h"

/**
 *  Base class for Manual Zoom Widget. This class binds the model
 *  class and provides state change callback blocks for customization.
 */
@interface DUXManualZoomBaseWidget: DUXWidget

/**
 *  To be subclassed. Should be used to setup all the views and
 *  interactions of the widget.
 */
- (void)viewForWidget;

/**
 *  To be called by subclass when it needs to zoom in response to
 *  user interaction.
 */
- (void)zoomToFocalLength:(NSUInteger)focalLength;

/**
 *  This block will be executed whenever DUXManualZoomModel changes
 *  its `isSupported` state. It will give the correct values of
 *  the camera's focal length if available and valid. If the camera
 *  does not support zoom, the focal length values will be default
 *  values which the model sends: 20mm for min, 50 mm for current &
 *  80 mm for max.
 *
 *  Subclass of the DUXManualZoomBaseWidget should implement this
 *  block in its `prepareWidget` method to change the visual
 *  characteristics of the widget in response to changing data.
 */
@property (nonatomic, copy) void (^zoomSupportChangedWithData)(BOOL isSupported, NSUInteger minFocalLength, NSUInteger maxFocalLength, NSUInteger currentFocalLength);

@end
