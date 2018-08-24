//
//  DUXRecordVideoWidget.h
//  DJIUXSDK
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import "DUXWidget.h"


/**
 *  Display:
 *  Action widget that is used to start and stop recording a video. It also shows a
 *  timer for how long the recording has been running.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 49:65.
 */
@interface DUXRecordVideoWidget : DUXWidget


/**
 *  `YES` if recording is ongoing.
 */
@property BOOL isRecording;

@end
