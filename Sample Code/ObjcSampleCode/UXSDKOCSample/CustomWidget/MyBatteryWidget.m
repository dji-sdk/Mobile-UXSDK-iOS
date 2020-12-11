//
//  MyBatteryWidget.m
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

#import "MyBatteryWidget.h"

@interface MyBatteryWidget ()

@property(nonatomic, strong) UILabel *percentageLabel;

@end

@implementation MyBatteryWidget

- (void)prepareWidget // This override func prepare() in Swift
{
    
    // We do not call super, because we are overriding the whole design aspect

    self.percentageLabel = [[UILabel alloc] init];
    self.percentageLabel.textColor = [UIColor greenColor];
    self.percentageLabel.adjustsFontSizeToFitWidth = YES;
    self.percentageLabel.font =  [UIFont systemFontOfSize:100];
    self.percentageLabel.minimumScaleFactor = 0.1;
    self.percentageLabel.numberOfLines = 0;
    self.percentageLabel.textAlignment = NSTextAlignmentCenter;
    self.percentageLabel.translatesAutoresizingMaskIntoConstraints = NO;
    [self addSubview:self.percentageLabel];
    
    [self.percentageLabel.topAnchor constraintEqualToAnchor:self.topAnchor].active = YES;
    [self.percentageLabel.bottomAnchor constraintEqualToAnchor:self.bottomAnchor].active = YES;
    [self.percentageLabel.leadingAnchor constraintEqualToAnchor:self.leadingAnchor].active = YES;
    [self.percentageLabel.trailingAnchor constraintEqualToAnchor:self.trailingAnchor].active = YES;
    
    [self update];

}

- (void)update {

    if(self.battery1Percentage < 10){
        self.percentageLabel.textColor = [UIColor redColor];
    }else{
        self.percentageLabel.textColor = [UIColor greenColor];
    }
    
    NSString *uiString = [NSString stringWithFormat:@"%.0f%%", self.battery1Percentage];
    [self.percentageLabel setText:uiString];
    
}


@end
