//
//  ProductCommunicationService.h
//  UXSDKOCSample
//
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJISDK.h>

static NSString * _Nonnull const ProductCommunicationServiceStateDidChange = @"ProductCommunicationServiceStateDidChange";

static NSString * _Nonnull const UserDefaultsBridgeIP = @"bridgeAppIP";

#if TARGET_IPHONE_SIMULATOR
static const BOOL defaultUseBridgeSetting = YES;
#else
static const BOOL defaultUseBridgeSetting = NO;
#endif


NS_ASSUME_NONNULL_BEGIN

@interface ProductCommunicationService : NSObject <DJISDKManagerDelegate>

@property (nonatomic) BOOL registered;
@property (nonatomic) BOOL connected;
@property (nonatomic) BOOL isSimulatorActive;
@property (nonatomic) BOOL useBridge;
@property (strong, nonatomic) NSString *bridgeAppIP;

+ (instancetype)sharedInstance;

- (void)registerWithProduct;

- (void)connectToProduct;

- (void)disconnectProduct;

- (BOOL)startSimulatorAt:(CLLocationCoordinate2D)locationCoordinates;

- (BOOL)stopSimulator;

@end

NS_ASSUME_NONNULL_END
