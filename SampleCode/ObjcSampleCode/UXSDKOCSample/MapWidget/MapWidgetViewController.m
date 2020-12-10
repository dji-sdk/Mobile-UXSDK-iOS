//
//  MapWidgetViewController.m
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
#import "MapWidgetViewController.h"
#import "CustomMapViewController.h"

@interface MapWidgetViewController ()

@property (nonatomic, strong, nullable) DUXMapViewController *mapViewController;

@end

@implementation MapWidgetViewController

#pragma mark - View Lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    [self setupMapWidget];
}

- (void)setupMapWidget {
    self.mapViewController = [[DUXMapViewController alloc] init];
    self.mapViewController.mapWidget.translatesAutoresizingMaskIntoConstraints = NO;
    [self.mapViewController willMoveToParentViewController:self];
    [self addChildViewController:self.mapViewController];
    [self.view addSubview:self.mapViewController.mapWidget];
    [self.mapViewController didMoveToParentViewController:self];
    
    if ([UIImage imageNamed:@"Lock"]) {
        [self.mapViewController.mapWidget changeAnnotationOfType:DUXMapAnnotationTypeEligibleFlyZones
                                                   toCustomImage:[UIImage imageNamed:@"Lock"]
                                                withCenterOffset:CGPointMake(-8, -15)];
    }
    
    [self.mapViewController.mapWidget.topAnchor constraintEqualToAnchor:self.view.topAnchor].active = YES;
    [self.mapViewController.mapWidget.bottomAnchor constraintEqualToAnchor:self.view.bottomAnchor].active = YES;
    [self.mapViewController.mapWidget.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor].active = YES;
    [self.mapViewController.mapWidget.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor].active = YES;
    
    [self.mapViewController.mapWidget setNeedsDisplay];
    [self.view sendSubviewToBack:self.mapViewController.mapWidget];
}

#pragma mark - User Interface

- (IBAction)close:(id)sender {
    [self dismissViewControllerAnimated:YES
                             completion:nil];
}

- (IBAction)customize:(id)sender {
    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"MapWidget"
                                                         bundle:[NSBundle bundleForClass:[MapWidgetViewController class]]];
    CustomMapViewController *mapCustomizationViewController = (CustomMapViewController *)[storyboard instantiateViewControllerWithIdentifier:@"CustomMapViewController"];
    mapCustomizationViewController.mapViewController = self.mapViewController;
    
    [self addChildViewController:mapCustomizationViewController];
    [self.view addSubview:mapCustomizationViewController.view];
    [mapCustomizationViewController didMoveToParentViewController:self];
    
    mapCustomizationViewController.view.translatesAutoresizingMaskIntoConstraints = NO;
    [mapCustomizationViewController.view.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor].active = YES;
    [mapCustomizationViewController.view.topAnchor constraintEqualToAnchor:self.view.topAnchor].active = YES;
    [mapCustomizationViewController.view.bottomAnchor constraintEqualToAnchor:self.view.bottomAnchor].active = YES;
    [mapCustomizationViewController.view.widthAnchor constraintEqualToConstant:self.view.frame.size.width/3].active = YES;
    [mapCustomizationViewController.view setNeedsLayout];
    [mapCustomizationViewController.view layoutIfNeeded];
}

- (IBAction)mapTypeValueChanged:(UISegmentedControl *)sender {
    if (sender.selectedSegmentIndex == 0) {
        self.mapViewController.mapWidget.mapView.mapType = MKMapTypeStandard;
    } else if (sender.selectedSegmentIndex == 1) {
        self.mapViewController.mapWidget.mapView.mapType = MKMapTypeSatellite;
    } else if (sender.selectedSegmentIndex == 2) {
        self.mapViewController.mapWidget.mapView.mapType = MKMapTypeHybrid;
    }
}

- (IBAction)clearFlightPathButtonPressed:(id)sender {
    [self.mapViewController.mapWidget clearCurrentFlightPath];
}

- (IBAction)syncCustomUnlockZonesButtonTapped:(id)sender {
    [self.mapViewController.mapWidget syncCustomUnlockZones];
}

@end
