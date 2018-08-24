//
//  WidgetsViewController.m
//  UXSDKOCSample
//
//  Created by DJI on 15/4/2017.
//  Copyright © 2017 DJI. All rights reserved.
//

#import "WidgetsViewController.h"

@interface WidgetsViewController ()
- (IBAction)onBackButtonClicked:(id)sender;

@end

@implementation WidgetsViewController

- (IBAction)onBackButtonClicked:(id)sender {
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end
