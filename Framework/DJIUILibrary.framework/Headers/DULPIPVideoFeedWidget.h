//
//  DULPIPVideoFeedWidget.h
//  DJIUILibrary
//
//  Copyright © 2017 DJI. All rights reserved.
//

#import <DJISDK/DJISDK.h>
#import "DULWidget.h"

@class DULPIPVideoFeedWidget;

@protocol DULPIPVideoFeedWidgetDelegate <NSObject>

// When the widget is tapped, it can notify a delegate object to display the full size video feed
- (void)videoFeedWidget:(nonnull DULPIPVideoFeedWidget *)videoFeedWidget didRequestFullDisplayOfVideoFeed:(nullable DJIVideoFeed *)videoFeed;

@end

@interface DULPIPVideoFeedWidget : DULWidget

@property (nonatomic, strong, nullable) DJIVideoFeed *videoFeed;

@property (nonatomic, weak, nullable) id<DULPIPVideoFeedWidgetDelegate> delegate;

@end
