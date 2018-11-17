//
//  ViewController.m
//  UXSDKOCSample
//
//  Created by DJI on 14/4/2017.
//  Copyright © 2017 DJI. All rights reserved.
//

#import "MainViewController.h"
#import <DJISDK/DJISDK.h>
#import "AppDelegate.h"

//To use DJI Bridge app, change `ENTER_DEBUG_MODE` to 1 and add bridge app IP address in `debugIP` string.
#define ENTER_DEBUG_MODE 0

@interface MainViewController ()<DJISDKManagerDelegate>

@property(weak, nonatomic) IBOutlet UILabel *version;
@property(weak, nonatomic) IBOutlet UILabel *registered;
@property(weak, nonatomic) IBOutlet UIButton *registerBtn;
@property(weak, nonatomic) IBOutlet UILabel *connected;
@property(weak, nonatomic) IBOutlet UIButton *connectBtn;

- (IBAction)registerButton:(id)sender;
- (IBAction)connectButton:(id)sender;

@end

@implementation MainViewController

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];

    NSString *versionString = [DJISDKManager SDKVersion];
    if (versionString != nil) {
        self.version.text = [NSString stringWithFormat:@"Version %@", [DJISDKManager SDKVersion]];
    }

}


- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self registerWithProduct];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)registerButton:(id)sender {
    
    [self registerWithProduct];

}

- (IBAction)connectButton:(id)sender {

    [self connectToProduct];
}

- (void) connectToProduct
{
    if (ENTER_DEBUG_MODE) {
        NSString *debugIP = @"Please enter your Debug IP address here.";
        NSLog(@"Connecting to Product using debug IP address: %@",debugIP);
        [DJISDKManager enableBridgeModeWithBridgeAppIP:debugIP];
    }else
    {
        NSLog(@"Connecting to product...");
        [DJISDKManager startConnectionToProduct];
    }
}

- (void) registerWithProduct
{
    [DJISDKManager registerAppWithDelegate:self];
}

#pragma mark - DJISDKManager Delegate Methods
- (void)appRegisteredWithError:(NSError *)error
{
    if (error == nil) {
        NSLog(@"Registration Succeeded");
        [self connectToProduct];
        self.registered.text = @"YES";
        self.registerBtn.hidden = YES;
    } else {
        NSLog(@"Error Registrating App: %@", error.description);
        self.registered.text = @"NO";
        self.registerBtn.hidden = NO;
    }
}

- (void)productConnected:(DJIBaseProduct *)product
{
    if (product != nil) {
        NSLog(@"Connection to new product successed!");
        self.connected.text = @"YES";
        self.connectBtn.hidden = YES;
    }
    
    //If this demo is used in China, it's required to login to your DJI account to activate the application. Also you need to use DJI Go app to bind the aircraft to your DJI account. For more details, please check this demo's tutorial.
    [[DJISDKManager userAccountManager] logIntoDJIUserAccountWithAuthorizationRequired:NO withCompletion:^(DJIUserAccountState state, NSError * _Nullable error) {
        if (error) {
            NSLog(@"Login failed: %@", error.description);
        }
    }];
}

- (void)productDisconnected{
    
    NSLog(@"Disconnected from product!");
    self.connected.text = @"NO";
    self.connectBtn.hidden = NO;
    
}

@end
