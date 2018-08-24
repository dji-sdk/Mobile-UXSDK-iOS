//
//  DefaultLayoutViewController.m
//  UXSDKOCSample
//
//  Created by DJI on 15/4/2017.
//  Copyright © 2017 DJI. All rights reserved.
//

#import "DefaultLayoutViewController.h"

@interface DefaultLayoutViewController ()
- (IBAction)onBackButtonClicked:(id)sender;

@end

@implementation DefaultLayoutViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)onBackButtonClicked:(id)sender {
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end
