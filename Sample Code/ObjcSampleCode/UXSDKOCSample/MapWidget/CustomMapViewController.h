//
//  CustomMapViewController.h
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
