//
//  MyBatteryWidget.m
//  UXSDKOCSample
//
//  Created by DJI on 15/4/2017.
//  Copyright © 2017 DJI. All rights reserved.
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
