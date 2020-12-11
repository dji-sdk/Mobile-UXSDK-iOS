//
//  DefaultLayoutCustomizationViewController.m
//  UXSDKOCSample
//
//  MIT License
//
//  Copyright © 2018-2020 DJI
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:

//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.

//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//

#import "DefaultLayoutCustomizationViewController.h"
#import <DJIUXSDK/DJIUXSDK.h>

@interface DefaultLayoutCustomizationViewController ()

@property (assign, nonatomic) BOOL isContentViewSwitched;
@property (strong, nonatomic) DUXFPVViewController *oldViewController;
@property (strong, nonatomic) UIViewController *redViewController;

@end

@implementation DefaultLayoutCustomizationViewController

- (instancetype)initWithCoder:(NSCoder *)coder {
    if (self = [super initWithCoder:coder]) {
        _isContentViewSwitched = NO;
    }
    return self;
}

- (IBAction)swapContent:(id)sender {
    if (self.isContentViewSwitched) {
        self.isContentViewSwitched = NO;
        self.contentViewController = self.oldViewController;
    } else {
        self.isContentViewSwitched = YES;
        if (self.redViewController == nil) {
            self.redViewController = [UIViewController new];
            self.redViewController.view.backgroundColor = UIColor.redColor;
        }
        self.oldViewController = (DUXFPVViewController *)self.contentViewController;
        self.contentViewController = self.redViewController;
    }
}

- (IBAction)close:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end
