//
//  DULRecordVideoWidget.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import "DULWidget.h"

IB_DESIGNABLE
/**
 *  Action widget that is used to start and stop recording a video.
 *  It also shows a timer for how long the recording has been running.
 *
 *  Preferred Aspect Ratio: 49:65
 */
@interface DULRecordVideoWidget : DULWidget

/**
 *  `YES` if recording is ongoing.
 */
@property BOOL isRecording;

@end
