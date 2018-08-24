//
//  DUXPIPVideoFeedWidget.h
//  DJIUXSDK
//
//  Copyright © 2017 DJI. All rights reserved.
//

#import <DJISDK/DJISDK.h>
#import "DUXWidget.h"

@class DUXPIPVideoFeedWidget;

@protocol DUXPIPVideoFeedWidgetDelegate <NSObject>

// When the widget is tapped, it can notify a delegate object to display the full size video feed
- (void)videoFeedWidget:(nonnull DUXPIPVideoFeedWidget *)videoFeedWidget didRequestFullDisplayOfVideoFeed:(nullable DJIVideoFeed *)videoFeed;

@end

@interface DUXPIPVideoFeedWidget : DUXWidget

@property (nonatomic, strong, nullable) DJIVideoFeed *videoFeed;

@property (nonatomic, weak, nullable) id<DUXPIPVideoFeedWidgetDelegate> delegate;

@end
