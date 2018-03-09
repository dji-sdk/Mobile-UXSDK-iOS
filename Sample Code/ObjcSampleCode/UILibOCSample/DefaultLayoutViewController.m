//
//  DefaultLayoutViewController.m
//  UILibOCSample
//
//  Created by DJI on 15/4/2017.
//  Copyright © 2017 DJI. All rights reserved.
//

#import "DefaultLayoutViewController.h"

@interface DefaultLayoutViewController ()
- (IBAction)onBackButtonClicked:(id)sender;

@end

@implementation DefaultLayoutViewController

- (IBAction)onBackButtonClicked:(id)sender {
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end
