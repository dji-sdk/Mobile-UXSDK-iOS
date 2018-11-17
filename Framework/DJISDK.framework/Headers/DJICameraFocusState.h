//
//  DJICameraFocusState.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJICameraSettingsDef.h>


/**
 *  This class contains information about the lens' current state, including lens
 *  type, focus status, focus mode, focus assistant state, and Auto Focus (AF)
 *  switch state.
 */
@interface DJICameraFocusState : NSObject


/**
 *  `YES` if lens is installed on the camera.
 */
@property(nonatomic, readonly) BOOL isLensMounted;


/**
 *  `YES` if the lens Auto Focus (AF) switch is on. If the lens is not installed,
 *  the value is undefined. If `YES`, `setFocusMode:withCompletion` can be used to
 *  control the focal point.
 */
@property(nonatomic, readonly) BOOL isAFSwitchOn;


/**
 *  The current focus mode. If the lens is not installed, the value is undefined.
 */
@property(nonatomic, readonly) DJICameraFocusMode focusMode;


/**
 *  The current focus status of the lens. If the lens is not installed, the value is
 *  undefined.
 */
@property(nonatomic, readonly) DJICameraFocusStatus focusStatus;


/**
 *  `YES` if the focus assistant is enabled for Manual focus mode. If the lens is
 *  not installed, the value is undefined.
 */
@property(nonatomic, readonly) BOOL isFocusAssistantEnabledForMF;


/**
 *  `YES` if the focus assistant is enabled for Auto focus mode. If the lens is not
 *  installed, the value is undefined.
 */
@property(nonatomic, readonly) BOOL isFocusAssistantEnabledForAF;


/**
 *  `YES` if the focus target is zooming out. If the lens is not installed, the
 *  value is undefined.
 */
@property(nonatomic, readonly) BOOL isFocusAssistantWorking;


/**
 *  The sensor cleaning state.
 */
@property(nonatomic, readonly) DJICameraSensorCleaningState sensorCleaningState;

@end
