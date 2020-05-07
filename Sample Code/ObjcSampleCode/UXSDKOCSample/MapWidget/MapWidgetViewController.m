//
//  MapWidgetViewController.m
//  UXSDKOCSample
//
//  Created by Andrew Lauer Barinov on 11/13/18.
//  Copyright © 2018 DJI. All rights reserved.
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
