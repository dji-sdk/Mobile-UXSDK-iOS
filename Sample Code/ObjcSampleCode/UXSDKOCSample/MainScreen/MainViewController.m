//
//  ViewController.m
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

#import "MainViewController.h"
#import "SimulationControlsViewController.h"
#import <DJISDK/DJISDK.h>
#import "AppDelegate.h"
#import "ProductCommunicationService.h"

@interface MainViewController ()

@property(weak, nonatomic) IBOutlet UILabel *version;
@property(weak, nonatomic) IBOutlet UILabel *registered;
@property(weak, nonatomic) IBOutlet UIButton *registerButton;
@property(weak, nonatomic) IBOutlet UILabel *connected;
@property(weak, nonatomic) IBOutlet UIButton *connectButton;
@property (weak, nonatomic) IBOutlet UILabel *simulatorOnOffLabel;
@property (weak, nonatomic) IBOutlet UIButton *simulatorButton;
@property (weak, nonatomic) IBOutlet UISwitch *bridgeModeSwitch;
@property (weak, nonatomic) IBOutlet UITextField *bridgeIPTextField;
@property (weak, nonatomic) IBOutlet UILabel *currentUserAccountStatus;
@property (weak, nonatomic) IBOutlet UIButton *loginOrLogout;

@property (assign, nonatomic) BOOL isSimulatorActive;

- (IBAction)registerAction:(id)sender;
- (IBAction)connectAction:(id)sender;
- (IBAction)handleStartStopSimulator:(id)sender;


@end

@implementation MainViewController

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];

    NSString *versionString = [DJISDKManager SDKVersion];
    if (versionString != nil) {
        self.version.text = [NSString stringWithFormat:@"Version %@", [DJISDKManager SDKVersion]];
    }
    
    [self.bridgeModeSwitch setOn:ProductCommunicationService.sharedInstance.useBridge animated:YES];
    self.bridgeIPTextField.text = ProductCommunicationService.sharedInstance.bridgeAppIP;
    [self.bridgeIPTextField addTarget:self action:@selector(updateBridgeAppIP) forControlEvents:UIControlEventEditingDidEnd];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(productCommunicationDidChange) name:ProductCommunicationServiceStateDidChange object:nil];
}

- (void)productCommunicationDidChange {
    
    // If this demo is used in China, it's required to login to your DJI account to activate the application.
    // Also you need to use DJI Go app to bind the aircraft to your DJI account. For more details, please check this demo's tutorial.
    [self updateUserAccountStatus];
    
    if (ProductCommunicationService.sharedInstance.registered) {
        self.registered.text = @"YES";
        self.registerButton.hidden = YES;
    } else {
        self.registered.text = @"NO";
        self.registerButton.hidden = NO;
    }
    
    if (ProductCommunicationService.sharedInstance.connected) {
        self.connected.text = @"YES";
        self.connectButton.hidden = YES;
    } else {
        self.connected.text = @"NO";
        self.connectButton.hidden = NO;
    }
    [self updateSimulatorControls];
}

- (IBAction)useBridgeAction:(id)sender {
    //NSLog(@"Product Name: %@", [DJISDKManager.keyManager getValueForKey:[DJIProductKey keyWithParam:DJIProductParamModelName]]);
    
    [DJISDKManager.keyManager startListeningForChangesOnKey:[DJIProductKey keyWithParam:DJIProductParamModelName] withListener:self andUpdateBlock:^(DJIKeyedValue * _Nullable oldValue, DJIKeyedValue * _Nullable newValue) {
        if (newValue != nil) {
            NSLog(@"Model Name: %@", newValue);
        } else {
            NSLog(@"Model name nil?");
        }
    }];
	
    ProductCommunicationService.sharedInstance.useBridge = self.bridgeModeSwitch.isOn;
    [ProductCommunicationService.sharedInstance disconnectProduct];
}

- (void)updateBridgeAppIP {
    ProductCommunicationService.sharedInstance.bridgeAppIP = self.bridgeIPTextField.text;
}

- (IBAction)userAccountAction:(id)sender {
    if (DJISDKManager.userAccountManager.userAccountState == DJIUserAccountStateNotLoggedIn ||
        DJISDKManager.userAccountManager.userAccountState == DJIUserAccountStateTokenOutOfDate ||
        DJISDKManager.userAccountManager.userAccountState == DJIUserAccountStateUnknown) {
        [DJISDKManager.userAccountManager logIntoDJIUserAccountWithAuthorizationRequired:NO withCompletion:^(DJIUserAccountState state, NSError * _Nullable error) {
            if(error != nil){
                NSLog(@"Login failed: %@", error.description);
            }
            [self updateUserAccountStatus];
        }];
    } else {
        [DJISDKManager.userAccountManager logOutOfDJIUserAccountWithCompletion:^(NSError * _Nullable error) {
            if(error != nil){
                NSLog(@"Logout failed: %@", error.description);
            }
            [self updateUserAccountStatus];
        }];
    }
}

- (void)updateUserAccountStatus {
    if (DJISDKManager.userAccountManager.userAccountState == DJIUserAccountStateNotLoggedIn) {
        self.currentUserAccountStatus.text = @"Not Logged In";
    } else if (DJISDKManager.userAccountManager.userAccountState == DJIUserAccountStateTokenOutOfDate) {
        self.currentUserAccountStatus.text = @"Token Out of Date";
    } else if (DJISDKManager.userAccountManager.userAccountState ==  DJIUserAccountStateNotAuthorized) {
        self.currentUserAccountStatus.text = @"Not Authorized";
    } else if (DJISDKManager.userAccountManager.userAccountState == DJIUserAccountStateAuthorized) {
        self.currentUserAccountStatus.text = @"Authorized";
    } else if (DJISDKManager.userAccountManager.userAccountState == DJIUserAccountStateNotLoggedIn) {
        self.currentUserAccountStatus.text = @"Unknown";
    }
}

- (IBAction)registerAction:(id)sender {
    [ProductCommunicationService.sharedInstance registerWithProduct];
}

- (IBAction)connectAction:(id)sender {
    [ProductCommunicationService.sharedInstance connectToProduct];
}

- (IBAction)handleStartStopSimulator:(id)sender {
    if (ProductCommunicationService.sharedInstance.isSimulatorActive) {
        if (![ProductCommunicationService.sharedInstance stopSimulator]) {
            NSLog(@"Could Not Begin Stopping Simulator");
        }
    } else {
        UIViewController *simulatorConfigVC = [SimulationControlsViewController new];
        UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:simulatorConfigVC];
        
        UIBarButtonItem *dismissItem = [[UIBarButtonItem alloc] initWithTitle:@"Done" style:UIBarButtonItemStyleDone target:self action:@selector(dismissPresentedViewController)];
        simulatorConfigVC.navigationItem.rightBarButtonItem = dismissItem;
        
        navigationController.modalPresentationStyle = UIModalPresentationFormSheet;
        simulatorConfigVC.modalPresentationStyle = UIModalPresentationFormSheet;
        
        [self presentViewController:navigationController animated:YES completion:nil];
    }
}

- (void)dismissPresentedViewController {
    [self.presentedViewController dismissViewControllerAnimated:YES completion:nil];
}

- (void)updateSimulatorControls {
    self.simulatorOnOffLabel.text = [ProductCommunicationService sharedInstance].isSimulatorActive ? @"ON" : @"OFF";
    NSString *simulatorTitle = [ProductCommunicationService sharedInstance].isSimulatorActive ? @"Stop" : @"Start";
    [self.simulatorButton setTitle:simulatorTitle forState:UIControlStateNormal];
    [self.simulatorButton setTitle:simulatorTitle forState:UIControlStateHighlighted];
    [self.simulatorButton setTitle:simulatorTitle forState:UIControlStateDisabled];
    [self.simulatorButton setTitle:simulatorTitle forState:UIControlStateSelected];
}

@end
