//
//  DefaultLayoutCustomizationViewController.m
//  UXSDKOCSample
//
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
