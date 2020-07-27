//
//  CustomMapViewController.m
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

#import "CustomMapViewController.h"

@interface CustomMapViewController () <UIPickerViewDataSource, UIPickerViewDelegate>

@end

@implementation CustomMapViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.colorPickerCurrentlySelectedRow = 0;
    self.widthPickerCurrentlySelectedRow = 0;
    self.alphaPickerCurrentlySelectedRow = 0;
    self.visibleFlyZonesCurrentlySelectedRow = 0;
    
    self.widthSlider.minimumValue = 0.5;
    self.widthSlider.maximumValue = 10.0;
    
    self.mapViewController.mapWidget.showDirectionToHome = YES;
    self.replaceIconBlurView.layer.cornerRadius          = 7.0;
    self.replaceIconBlurView.layer.masksToBounds         = YES;
    self.mapViewController.mapWidget.visibleFlyZones     = DUXMapVisibleFlyZonesNone;
    
    self.colorPickerCurrentlySelectedRow = [self.colorSelectionPickerView selectedRowInComponent:0];
    self.alphaPickerCurrentlySelectedRow = [self.alphaSelectionPickerView selectedRowInComponent:0];
    self.widthPickerCurrentlySelectedRow = [self.widthSelectionPickerView selectedRowInComponent:0];
    self.visibleFlyZonesCurrentlySelectedRow = [self.visibleFlyZoneSelectionPickerView selectedRowInComponent:0];
}


#pragma mark - User Interaction
- (IBAction)close:(id)sender {
    [self willMoveToParentViewController:nil];
    [self.view removeFromSuperview];
    [self removeFromParentViewController];
}

- (IBAction)toggleColor:(id)sender {
    [self updateMapWithColor:[UIColor cyanColor]];
}

- (IBAction)directionToHomeValueChanged:(UISwitch *)sender {
    self.mapViewController.mapWidget.showDirectionToHome = sender.isOn;
}

- (IBAction)lockAircraftCameraValueChanged:(UISwitch *)sender {
    self.mapViewController.mapWidget.isMapCameraLockedOnAircraft = sender.isOn;
}

- (IBAction)lockHomePointCameraValueChanged:(UISwitch *)sender {
    self.mapViewController.mapWidget.isMapCameraLockedOnHomePoint = sender.isOn;
}

- (IBAction)showFlightPathValueChanged:(UISwitch *)sender {
    self.mapViewController.mapWidget.showFlightPath = sender.isOn;
}

- (IBAction)showHomePointValueChanged:(UISwitch *)sender {
    self.mapViewController.mapWidget.showHomeAnnotation = sender.isOn;
}

- (IBAction)tapToUnlockEnabledValueChanged:(UISwitch *)sender {
    self.mapViewController.mapWidget.tapToUnlockEnabled = sender.isOn;
}

- (IBAction)showLegendValueChanged:(UISwitch *)sender {
    self.mapViewController.showFlyZoneLegend = sender.isOn;
}

- (IBAction)showCustomUnlockZonesValueChanged:(UISwitch *)sender {
    self.mapViewController.mapWidget.showCustomUnlockZones = sender.isOn;
}

- (IBAction)showDJIAccountLoginIndicator:(UISwitch *)sender {
    self.mapViewController.mapWidget.showDJIAccountLoginIndicator = sender.isOn;
}

- (IBAction)replaceIconButtonPressed:(UIButton *)sender {
    if (self.replaceIconSegmentedView.selectedSegmentIndex == 0) {
        [self.mapViewController.mapWidget changeAnnotationOfType:DUXMapAnnotationTypeAircraft
                                                   toCustomImage:self.replaceIconImageView.image
                                                withCenterOffset:CGPointMake(-8.75, -27.3)];
    } else if (self.replaceIconSegmentedView.selectedSegmentIndex == 1) {
        [self.mapViewController.mapWidget changeAnnotationOfType:DUXMapAnnotationTypeHome
                                                   toCustomImage:self.replaceIconImageView.image
                                                withCenterOffset:CGPointMake(-8, -15)];
    } else if (self.replaceIconSegmentedView.selectedSegmentIndex == 2) {
        [self.mapViewController.mapWidget changeAnnotationOfType:DUXMapAnnotationTypeEligibleFlyZones
                                                   toCustomImage:self.replaceIconImageView.image
                                                withCenterOffset:CGPointMake(-8, -15)];
    } else if (self.replaceIconSegmentedView.selectedSegmentIndex == 3) {
        [self.mapViewController.mapWidget changeAnnotationOfType:DUXMapAnnotationTypeUnlockedFlyZones
                                                   toCustomImage:self.replaceIconImageView.image
                                                withCenterOffset:CGPointMake(-8, -15)];
    } else if (self.replaceIconSegmentedView.selectedSegmentIndex == 4) {
        [self.mapViewController.mapWidget changeAnnotationOfType:DUXMapAnnotationTypeUnlockedFlyZones
                                                   toCustomImage:self.replaceIconImageView.image
                                                withCenterOffset:CGPointMake(-8, -15)];
    }
}
    
- (IBAction)replaceIconValueChanged:(UISegmentedControl *)sender {
    if (sender.selectedSegmentIndex == 0) {
        self.replaceIconImageView.image = [UIImage imageNamed:@"Aircraft"];
    } else {
        self.replaceIconImageView.image = [UIImage imageNamed:@"HomePoint"];
    }
}

- (IBAction)widthSliderControlChanged:(UISlider *)sender {
    CGFloat sliderValue = sender.value;
    self.widthLabel.text = [NSString stringWithFormat:@"%f", sliderValue];
    
    if (self.widthPickerCurrentlySelectedRow == 0) {
        self.mapViewController.mapWidget.flyZoneOverlayBorderWidth = sliderValue;
    } else if (self.widthPickerCurrentlySelectedRow == 1) {
        self.mapViewController.mapWidget.flightPathStrokeWidth = sliderValue;
    } else if (self.widthPickerCurrentlySelectedRow == 2) {
        self.mapViewController.mapWidget.directionToHomeStrokeWidth = sliderValue;
    }
}

- (IBAction)alphaSliderControlChanged:(UISlider *)sender {
    CGFloat sliderValue = sender.value;
    self.alphaLabel.text = [NSString stringWithFormat:@"%f", sliderValue];
    
    if (self.alphaPickerCurrentlySelectedRow == 0) {
        [self.mapViewController.mapWidget setFlyZoneOverlayAlpha:sliderValue
                                              forFlyZoneCategory:DJIFlyZoneCategoryRestricted];
    } else if (self.alphaPickerCurrentlySelectedRow == 1) {
        [self.mapViewController.mapWidget setFlyZoneOverlayAlpha:sliderValue
                                              forFlyZoneCategory:DJIFlyZoneCategoryAuthorization];
    } else if (self.alphaPickerCurrentlySelectedRow == 2) {
        [self.mapViewController.mapWidget setFlyZoneOverlayAlpha:sliderValue
                                              forFlyZoneCategory:DJIFlyZoneCategoryEnhancedWarning];
    } else if (self.alphaPickerCurrentlySelectedRow == 3) {
        [self.mapViewController.mapWidget setFlyZoneOverlayAlpha:sliderValue
                                              forFlyZoneCategory:DJIFlyZoneCategoryWarning];
    } else if (self.alphaPickerCurrentlySelectedRow == 4) {
        self.mapViewController.mapWidget.unlockedFlyZoneOverlayAlpha = sliderValue;
    } else if (self.alphaPickerCurrentlySelectedRow == 5) {
        self.mapViewController.mapWidget.maximumHeightFlyZoneOverlayAlpha = sliderValue;
    } else if (self.alphaPickerCurrentlySelectedRow == 6) {
        self.mapViewController.mapWidget.customUnlockFlyZoneOverlayAlpha = sliderValue;
    } else if (self.alphaPickerCurrentlySelectedRow == 7) {
        self.mapViewController.mapWidget.customUnlockFlyZoneSentToAircraftOverlayAlpha = sliderValue;
    } else if (self.alphaPickerCurrentlySelectedRow == 8) {
        self.mapViewController.mapWidget.customUnlockFlyZoneEnabledOverlayAlpha = sliderValue;
    }
}

- (IBAction)flyZoneDisplaySwitchValueChanged:(UISwitch *)sender {
    BOOL isOn = sender.isOn;
    DUXMapVisibleFlyZones visibleFlyZones = DUXMapVisibleFlyZonesNone;
    
    if (self.visibleFlyZonesCurrentlySelectedRow == 0) {
        visibleFlyZones |= DUXMapVisibleFlyZonesRestricted;
    } else if (self.visibleFlyZonesCurrentlySelectedRow == 1) {
        visibleFlyZones |= DUXMapVisibleFlyZonesAuthorization;
    } else if (self.visibleFlyZonesCurrentlySelectedRow == 2) {
        visibleFlyZones |= DUXMapVisibleFlyZonesEnhancedWarning;
    } else if (self.visibleFlyZonesCurrentlySelectedRow == 3) {
        visibleFlyZones |= DUXMapVisibleFlyZonesWarning;
    }
    
    if (isOn) {
        DUXMapVisibleFlyZones updatedVisibleFlyZones = self.mapViewController.mapWidget.visibleFlyZones | visibleFlyZones;
        self.mapViewController.mapWidget.visibleFlyZones = updatedVisibleFlyZones;
    } else {
        DUXMapVisibleFlyZones updatedVisibleFlyZones = self.mapViewController.mapWidget.visibleFlyZones ^ visibleFlyZones;
        self.mapViewController.mapWidget.visibleFlyZones = updatedVisibleFlyZones;
    }
    
    [self updateFlyZones];
}

#pragma mark - Update Methods

- (void)updateMapWithColor:(UIColor *)color {
    if (self.colorPickerCurrentlySelectedRow == 0) {
        [self.mapViewController.mapWidget setFlyZoneOverlayColor:color
                                              forFlyZoneCategory:DJIFlyZoneCategoryRestricted];
    } else if (self.colorPickerCurrentlySelectedRow == 1) {
        [self.mapViewController.mapWidget setFlyZoneOverlayColor:color
                                              forFlyZoneCategory:DJIFlyZoneCategoryAuthorization];
    } else if (self.colorPickerCurrentlySelectedRow == 2) {
        [self.mapViewController.mapWidget setFlyZoneOverlayColor:color
                                              forFlyZoneCategory:DJIFlyZoneCategoryEnhancedWarning];
    } else if (self.colorPickerCurrentlySelectedRow == 3) {
        [self.mapViewController.mapWidget setFlyZoneOverlayColor:color
                                              forFlyZoneCategory:DJIFlyZoneCategoryWarning];
    } else if (self.colorPickerCurrentlySelectedRow == 4) {
        self.mapViewController.mapWidget.unlockedFlyZoneOverlayColor = color;
    } else if (self.colorPickerCurrentlySelectedRow == 5) {
        self.mapViewController.mapWidget.maximumHeightFlyZoneOverlayColor = color;
    } else if (self.colorPickerCurrentlySelectedRow == 6) {
        self.mapViewController.mapWidget.flightPathStrokeColor = color;
    } else if (self.colorPickerCurrentlySelectedRow == 7) {
        self.mapViewController.mapWidget.directionToHomeStrokeColor = color;
    } else if (self.colorPickerCurrentlySelectedRow == 8) {
        self.mapViewController.mapWidget.customUnlockFlyZoneOverlayColor = color;
    } else if (self.colorPickerCurrentlySelectedRow == 9) {
        self.mapViewController.mapWidget.customUnlockFlyZoneSentToAircraftOverlayColor = color;
    } else if (self.colorPickerCurrentlySelectedRow == 10) {
        self.mapViewController.mapWidget.customUnlockFlyZoneEnabledOverlayColor = color;
    }
}

- (void)updateAlpha {
    if (self.colorPickerCurrentlySelectedRow == 0) {
        CGFloat alpha = [self.mapViewController.mapWidget flyZoneOverlayAlphaForFlyZoneCategory:DJIFlyZoneCategoryRestricted];
        [self updateAlphaWithValue:alpha];
    } else if (self.colorPickerCurrentlySelectedRow == 1) {
        CGFloat alpha = [self.mapViewController.mapWidget flyZoneOverlayAlphaForFlyZoneCategory:DJIFlyZoneCategoryAuthorization];
        [self updateAlphaWithValue:alpha];
    } else if (self.colorPickerCurrentlySelectedRow == 2) {
        CGFloat alpha = [self.mapViewController.mapWidget flyZoneOverlayAlphaForFlyZoneCategory:DJIFlyZoneCategoryEnhancedWarning];
        [self updateAlphaWithValue:alpha];
    } else if (self.colorPickerCurrentlySelectedRow == 3) {
        CGFloat alpha = [self.mapViewController.mapWidget flyZoneOverlayAlphaForFlyZoneCategory:DJIFlyZoneCategoryWarning];
        [self updateAlphaWithValue:alpha];
    } else if (self.colorPickerCurrentlySelectedRow == 4) {
        CGFloat alpha = self.mapViewController.mapWidget.unlockedFlyZoneOverlayAlpha;
        [self updateAlphaWithValue:alpha];
    } else if (self.colorPickerCurrentlySelectedRow == 5) {
        CGFloat alpha = self.mapViewController.mapWidget.maximumHeightFlyZoneOverlayAlpha;
        [self updateAlphaWithValue:alpha];
    } else if (self.colorPickerCurrentlySelectedRow == 6) {
        CGFloat alpha = self.mapViewController.mapWidget.customUnlockFlyZoneOverlayAlpha;
        [self updateAlphaWithValue:alpha];
    } else if (self.colorPickerCurrentlySelectedRow == 7) {
        CGFloat alpha = self.mapViewController.mapWidget.customUnlockFlyZoneSentToAircraftOverlayAlpha;
        [self updateAlphaWithValue:alpha];
    } else if (self.colorPickerCurrentlySelectedRow == 8) {
        CGFloat alpha = self.mapViewController.mapWidget.customUnlockFlyZoneEnabledOverlayAlpha;
        [self updateAlphaWithValue:alpha];
    }
}

- (void)updateAlphaWithValue:(CGFloat)alpha {
    [self.alphaSlider setValue:alpha
                      animated:YES];
    self.alphaLabel.text = [NSString stringWithFormat:@"%f",alpha];
}

- (void)updateFlyZones {
    DUXMapVisibleFlyZones visibleFlyZones = DUXMapVisibleFlyZonesNone;
    
    if (self.visibleFlyZonesCurrentlySelectedRow == 0) {
        visibleFlyZones |= DUXMapVisibleFlyZonesRestricted;
    } else if (self.visibleFlyZonesCurrentlySelectedRow == 1) {
        visibleFlyZones |= DUXMapVisibleFlyZonesAuthorization;
    } else if (self.visibleFlyZonesCurrentlySelectedRow == 2) {
        visibleFlyZones |= DUXMapVisibleFlyZonesEnhancedWarning;
    } else if (self.visibleFlyZonesCurrentlySelectedRow == 3) {
        visibleFlyZones |= DUXMapVisibleFlyZonesWarning;
    }
    
    BOOL isOn = (self.mapViewController.mapWidget.visibleFlyZones & visibleFlyZones);
    
    [self.flyZoneDisplaySwitch setOn:isOn
                            animated:YES];
}

- (void)updateWidth {
    if (self.widthPickerCurrentlySelectedRow == 0) {
        [self.widthSlider setValue:self.mapViewController.mapWidget.flyZoneOverlayBorderWidth
                          animated:YES];
    } else if (self.widthPickerCurrentlySelectedRow == 1) {
        [self.widthSlider setValue:self.mapViewController.mapWidget.flightPathStrokeWidth
                          animated:YES];
    } else if (self.widthPickerCurrentlySelectedRow == 2) {
        [self.widthSlider setValue:self.mapViewController.mapWidget.directionToHomeStrokeWidth
                          animated:YES];
    }
}

#pragma mark - UIPickerViewDataSource

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    if ([pickerView isEqual:self.colorSelectionPickerView]) {
        return 11;
    } else if ([pickerView isEqual:self.widthSelectionPickerView]) {
        return 3;
    } else if ([pickerView isEqual:self.alphaSelectionPickerView]) {
        return 9;
    } else if ([pickerView isEqual:self.visibleFlyZoneSelectionPickerView]) {
        return 4;
    } else {
        return 0;
    }
}

- (nullable NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component {
    if ([pickerView isEqual:self.colorSelectionPickerView]) {
        return [self colorSelectionTitleForRow:row inComponent:component];
    } else if ([pickerView isEqual:self.widthSelectionPickerView]) {
        return [self widthSelectionTitleForRow:row inComponent:component];
    } else if ([pickerView isEqual:self.alphaSelectionPickerView]) {
        return [self alphaSelectionTitleForRow:row inComponent:component];
    } else if ([pickerView isEqual:self.visibleFlyZoneSelectionPickerView]) {
        return [self visibleFlyZoneSelectionTitleForRow:row inComponent:component];
    } else {
        return nil;
    }
}

- (nonnull NSString *)colorSelectionTitleForRow:(NSInteger)row inComponent:(NSInteger)component {
    if (row == 0) {
        return @"Restricted Overlay Color";
    } else if (row == 1) {
        return @"Authorization Overlay Color";
    } else if (row == 2) {
        return @"Enhanced Warning Overlay Color";
    } else if (row == 3) {
        return @"Warning Overlay Color";
    } else if (row == 4) {
        return @"Self Unlocked Overlay Color";
    } else if (row == 5) {
        return @"Max Height Overlay Color";
    } else if (row == 6) {
        return @"Flight Path Color";
    } else if (row == 7) {
        return @"Direction to Home Color";
    } else if (row == 8) {
        return @"Custom Unlock Not Sent Not Enabled Color";
    } else if (row == 9) {
        return @"Custom Unlock Sent Not Enabled Color";
    } else if (row == 10) {
        return @"Custom Unlock Sent Enabled Color";
    } else {
        return @"";
    }
}

- (nonnull NSString *)widthSelectionTitleForRow:(NSInteger)row inComponent:(NSInteger)component {
    if (row == 0) {
        return @"Overlay Border Width";
    } else if (row == 1) {
        return @"Flight Path Stroke Width";
    } else if (row == 2) {
        return @"Direction to Home Stroke Width";
    } else {
        return @"";
    }
}

- (nonnull NSString *)alphaSelectionTitleForRow:(NSInteger)row inComponent:(NSInteger)component {
    if (row == 0) {
        return @"Restricted Overlay Alpha";
    } else if (row == 1) {
        return @"Authorization Overlay Alpha";
    } else if (row == 2) {
        return @"Enhanced Warning Overlay Alpha";
    } else if (row == 3) {
        return @"Warning Overlay Alpha";
    } else if (row == 4) {
        return @"Self Unlocked Overlay Alpha";
    } else if (row == 5) {
        return @"Max Height Overlay Alpha";
    } else if (row == 6) {
        return @"Custom Unlock Not Sent Not Enabled Alpha";
    } else if (row == 7) {
        return @"Custom Unlock Sent Not Enabled Alpha";
    } else if (row == 8) {
        return @"Custom Unlock Sent Enabled Alpha";
    } else {
        return @"";
    }
}

- (nonnull NSString *)visibleFlyZoneSelectionTitleForRow:(NSInteger)row inComponent:(NSInteger)component {
    if (row == 0) {
        return @"Restricted";
    } else if (row == 1) {
        return @"Authorization";
    } else if (row == 2) {
        return @"Enhanced Warning";
    } else if (row == 3) {
        return @"Warning";
    } else {
        return @"";
    }
}

#pragma mark - UIPickerViewDelegate

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component {
    if ([pickerView isEqual:self.colorSelectionPickerView]) {
        [self didSelectColorInRow:row inComponent:component];
    } else if ([pickerView isEqual:self.widthSelectionPickerView]) {
        [self didSelectWidthInRow:row inComponent:component];
    } else if ([pickerView isEqual:self.alphaSelectionPickerView]) {
        [self didSelectAlphaInRow:row inComponent:component];
    } else if ([pickerView isEqual:self.visibleFlyZoneSelectionPickerView]) {
        [self didSelectVisibleFlyZoneInRow:row inComponent:component];
    }
}

- (void)didSelectColorInRow:(NSUInteger)row inComponent:(NSInteger)component {
    self.colorPickerCurrentlySelectedRow = row;
}

- (void)didSelectWidthInRow:(NSUInteger)row inComponent:(NSInteger)component {
    self.widthPickerCurrentlySelectedRow = row;
    [self updateWidth];
}

- (void)didSelectAlphaInRow:(NSUInteger)row inComponent:(NSInteger)component {
    self.alphaPickerCurrentlySelectedRow = row;
    [self updateAlpha];
}

- (void)didSelectVisibleFlyZoneInRow:(NSUInteger)row inComponent:(NSInteger)component {
    self.visibleFlyZonesCurrentlySelectedRow = row;
    [self updateFlyZones];
}

@end
