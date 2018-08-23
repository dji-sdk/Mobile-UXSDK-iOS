//
//  DUXColorWaveformWidget.h
//  DJIUXSDK
//
//  Created by Jason Rinn on 5/7/18.
//  Copyright © 2018 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>

@class DUXFPVViewController;


/**
 *  Display:
 *  Widget to display color waveform of live video.
 */
@interface DUXColorWaveformWidget : DUXWidget


/**
 *  Class method to check if color waveform is supported by current camera.
 *  
 *  @return A boolean value to check if color waveform is supported by current camera.
 */
+ (BOOL) isSupported;

- (instancetype) initWithFPVViewController:(DUXFPVViewController *)fpvViewController;
@end
