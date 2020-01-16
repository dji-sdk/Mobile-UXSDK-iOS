//
//  CustomMapViewController.h
//  UXSDKOCSample
//
//  Created by Andrew Lauer Barinov on 11/15/18.
//  Copyright © 2018 DJI. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <DJIUXSDK/DJIUXSDK.h>

NS_ASSUME_NONNULL_BEGIN

@interface CustomMapViewController : UIViewController

@property (nonatomic, strong, nullable) DUXMapViewController *mapViewController;

@property (nonatomic, weak, nullable) IBOutlet UISlider *widthSlider;
@property (nonatomic, weak, nullable) IBOutlet UISlider *alphaSlider;
@property (nonatomic, weak, nullable) IBOutlet UILabel *widthLabel;
@property (nonatomic, weak, nullable) IBOutlet UILabel *alphaLabel;

@property (nonatomic, weak, nullable) IBOutlet UISwitch *lockCameraAircraftSwitch;
@property (nonatomic, weak, nullable) IBOutlet UISwitch *lockHomeCameraSwitch;

@property (nonatomic, weak, nullable) IBOutlet UISwitch *flyZoneDisplaySwitch;

@property (nonatomic, weak, nullable) IBOutlet UIPickerView *colorSelectionPickerView;
@property (nonatomic, weak, nullable) IBOutlet UIPickerView *widthSelectionPickerView;
@property (nonatomic, weak, nullable) IBOutlet UIPickerView *alphaSelectionPickerView;
@property (nonatomic, weak, nullable) IBOutlet UIPickerView *visibleFlyZoneSelectionPickerView;

@property (nonatomic, assign) NSInteger colorPickerCurrentlySelectedRow;
@property (nonatomic, assign) NSInteger widthPickerCurrentlySelectedRow;
@property (nonatomic, assign) NSInteger alphaPickerCurrentlySelectedRow;
@property (nonatomic, assign) NSInteger visibleFlyZonesCurrentlySelectedRow;

@property (nonatomic, weak, nullable) IBOutlet UISegmentedControl *replaceIconSegmentedView;
@property (nonatomic, weak, nullable) IBOutlet UIVisualEffectView *replaceIconBlurView;
@property (nonatomic, weak, nullable) IBOutlet UIImageView *replaceIconImageView;

@end

NS_ASSUME_NONNULL_END
