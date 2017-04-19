//
//  DULFPVViewController.h
//  DJIUILibrary
//
//  Copyright © 2016 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DULContentViewController.h"

#import <DJISDK/DJISDK.h>

@class DULFPVView;

@interface DULFPVViewController : DULContentViewController

@property (readonly, nonatomic, nullable) __kindof DULFPVView *fpvView;

@end
