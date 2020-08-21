//
//  ProductCommunicationService.m
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

#import "ProductCommunicationService.h"

// Automatically set default to bridge when on iOS simulator

@interface ProductCommunicationService ()

@end

@implementation ProductCommunicationService

+ (instancetype)sharedInstance {
    static ProductCommunicationService *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[ProductCommunicationService alloc] init];
        sharedInstance.isSimulatorActive = NO;
        sharedInstance.connected = NO;
        sharedInstance.registered = NO;
        sharedInstance.useBridge = defaultUseBridgeSetting;
        if ([NSUserDefaults.standardUserDefaults valueForKey:UserDefaultsBridgeIP]) {
            sharedInstance.bridgeAppIP = [NSUserDefaults.standardUserDefaults valueForKey:@"bridgeAppIP"];
        } else {
            sharedInstance.bridgeAppIP = @"0.0.0.0";
        }
    });
    return sharedInstance;
}

- (void)registerWithProduct {
    NSString *path = [NSBundle.mainBundle pathForResource:@"Info" ofType:@"plist"];
    NSDictionary *appKeyEntry = [NSDictionary dictionaryWithContentsOfFile:path];
    NSString *appKey = appKeyEntry[@"DJISDKAppKey"];
    
    if (!appKey) {
        NSLog(@"couldn't retrieve app key");
        return;
    }
    
    if ([appKey isEqualToString:@"PASTE_YOUR_DJI_APP_KEY_HERE"]) {
        NSLog(@"\n<<<ERROR: Please add DJI App Key in Info.plist after registering as developer>>>\n");
        return;
    }
    
    dispatch_after(DISPATCH_TIME_NOW + 1, dispatch_get_main_queue(), ^{
        NSLog(@"Registering Product with registration ID: %@", appKey);
        [DJISDKManager registerAppWithDelegate:self];
    });
}

- (void)connectToProduct {
    if (self.useBridge) {
        NSLog(@"Connecting to Product using debug IP address: %@", self.bridgeAppIP);
        [DJISDKManager enableBridgeModeWithBridgeAppIP:self.bridgeAppIP];
    } else {
        NSLog(@"Connecting to product...");
        [DJISDKManager startConnectionToProduct];
    }
}

- (void)disconnectProduct {
    [DJISDKManager stopConnectionToProduct];
    self.connected = NO;
}

- (void)postNotificationNamed:(NSString *)rawStringName {
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:rawStringName object:nil]];
}

- (void)startListeningToProductState {
    DJIFlightControllerKey *isSimulatorActiveKey = [DJIFlightControllerKey keyWithParam:DJIFlightControllerParamIsSimulatorActive];

    [DJISDKManager.keyManager startListeningForChangesOnKey:isSimulatorActiveKey withListener:self andUpdateBlock:^(DJIKeyedValue * _Nullable oldValue, DJIKeyedValue * _Nullable newValue) {
        self.isSimulatorActive = newValue.boolValue;
        [self postNotificationNamed:ProductCommunicationServiceStateDidChange];
    }];
    
    [DJISDKManager.keyManager getValueForKey:isSimulatorActiveKey withCompletion:^(DJIKeyedValue * _Nullable value, NSError * _Nullable error) {
        if (error) {
            NSLog(@"Error getting simulator active: %@", error.description);
        } else {
            self.isSimulatorActive = value.boolValue;
            [self postNotificationNamed:ProductCommunicationServiceStateDidChange];
        }
    }];
}

- (void)stopListeningToProductState {
    DJIFlightControllerKey *isSimulatorActiveKey = [DJIFlightControllerKey keyWithParam:DJIFlightControllerParamIsSimulatorActive];
    [DJISDKManager.keyManager stopListeningOnKey:isSimulatorActiveKey ofListener:self];
}

- (void)dealloc {
    [self stopListeningToProductState];
}


- (BOOL)startSimulatorAt:(CLLocationCoordinate2D)locationCoordinates {
    DJIBaseProduct *baseProduct = [DJISDKManager product];
    
    if (![baseProduct isKindOfClass:DJIAircraft.class]){
        return NO;
    }
    
    DJIAircraft *aircraft = (DJIAircraft *)baseProduct;
    
    [aircraft.flightController.simulator startWithLocation:locationCoordinates updateFrequency:20 GPSSatellitesNumber:12 withCompletion:^(NSError * _Nullable error) {
        if (error != nil) {
            NSLog(@"Error Starting Simulator: %@", error.description);
        } else {
            NSLog(@"Started Simulator Successfully");
        }
    }];
    return YES;
}

- (BOOL)stopSimulator {
    DJIFlightControllerKey *stopSimulatorKey = [DJIFlightControllerKey keyWithParam:DJIFlightControllerParamStopSimulator];
    
    if (stopSimulatorKey == nil) {
        return NO;
    }
    
    DJIKeyManager *keyManager = DJISDKManager.keyManager;
    
    if (keyManager == nil) {
        return NO;
    }
    
    [keyManager performActionForKey:stopSimulatorKey withArguments:nil andCompletion:^(BOOL finished, DJIKeyedValue * _Nullable response, NSError * _Nullable error) {
        if (error == nil) {
            NSLog(@"Stop Simulator Command Acked");
        } else {
            NSLog(@"Stop Simulator Error: %@", error.description);
        }
    }];
    return YES;
}

- (void)setBridgeAppIP:(NSString *)bridgeAppIP {
    [NSUserDefaults.standardUserDefaults setObject:bridgeAppIP forKey:UserDefaultsBridgeIP];
    _bridgeAppIP = bridgeAppIP;
}

//MARK: - DJISDKManagerDelegate
- (void)appRegisteredWithError:(NSError * _Nullable)error {
    if (error == nil) {
        self.registered = YES;
        [self postNotificationNamed:ProductCommunicationServiceStateDidChange];
        [self connectToProduct];
    } else {
        NSLog(@"Error Registrating App: %@", error.description);
    }
}

- (void)didUpdateDatabaseDownloadProgress:(nonnull NSProgress *)progress {
    NSLog(@"Downloading Database Progress: %lld / %lld", progress.completedUnitCount, progress.totalUnitCount);
}

- (void)productConnected:(DJIBaseProduct *)product {
    if (product != nil) {
        self.connected = YES;
        [self postNotificationNamed:ProductCommunicationServiceStateDidChange];
        NSLog(@"Connection to new product succeeded!");
        [self startListeningToProductState];
    }
}

- (void)productDisconnected {
    self.connected = NO;
    [self postNotificationNamed:ProductCommunicationServiceStateDidChange];
}

@end
