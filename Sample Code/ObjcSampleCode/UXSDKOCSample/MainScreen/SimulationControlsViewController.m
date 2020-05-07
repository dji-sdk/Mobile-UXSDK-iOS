//
//  SimulationControlsViewController.m
//  UXSDKOCSample
//
//

#import "SimulationControlsViewController.h"
#import <DJISDK/DJISDK.h>
#import "ProductCommunicationService.h"

static NSString * const UserDefaultsLatitudeKey = @"Latitude";
static NSString * const UserDefaultsLongitudeKey = @"Longitude";
static NSString * const UserDefaultsSimulatorLocationKey = @"PriorSimulatorLocation";


@interface SimulationControlsViewController ()

@property (assign, nonatomic) double latitude;
@property (assign, nonatomic) double longitude;
@property (strong, nonatomic) UILabel *savedStatusLabel;
@property (strong, nonatomic) UITextField *latitudeTextField;
@property (strong, nonatomic) UITextField *longitudeTextField;
@property (strong, nonatomic) NSNumberFormatter *numberFormatter;

@end

@implementation SimulationControlsViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.numberFormatter = [[NSNumberFormatter alloc] init];
    self.numberFormatter.usesSignificantDigits = YES;
    self.numberFormatter.minimumSignificantDigits = 8;
    self.numberFormatter.alwaysShowsDecimalSeparator = YES;
    
    self.view.backgroundColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.0 alpha:0.65];
    self.title = @"Enter Lat / Long and Tap Start";
    
    NSDictionary *textFieldAttributes = @{ NSForegroundColorAttributeName : UIColor.lightTextColor };
    
    UITextField *latitudeTextField = [[UITextField alloc] init];
    latitudeTextField.translatesAutoresizingMaskIntoConstraints = NO;
    latitudeTextField.attributedPlaceholder = [[NSAttributedString alloc] initWithString:@"Enter Latitude Here" attributes:textFieldAttributes];
    latitudeTextField.textColor = [UIColor whiteColor];
    latitudeTextField.textAlignment = NSTextAlignmentCenter;
    latitudeTextField.font = [UIFont systemFontOfSize:32.0];
    [self.view addSubview:latitudeTextField];
    [latitudeTextField addTarget:self action:@selector(updateLatitude) forControlEvents:UIControlEventEditingDidEnd | UIControlEventEditingDidEndOnExit];
    self.latitudeTextField = latitudeTextField;
    
    UITextField *longitudeTextField = [[UITextField alloc] init];
    longitudeTextField.translatesAutoresizingMaskIntoConstraints = NO;
    longitudeTextField.attributedPlaceholder = [[NSAttributedString alloc] initWithString:@"Enter Latitude Here" attributes:textFieldAttributes];
    longitudeTextField.textColor = [UIColor whiteColor];
    longitudeTextField.textAlignment = NSTextAlignmentCenter;
    longitudeTextField.font = [UIFont systemFontOfSize:32.0];
    [self.view addSubview:longitudeTextField];
    [longitudeTextField addTarget:self action:@selector(updateLongitude) forControlEvents:UIControlEventEditingDidEnd | UIControlEventEditingDidEndOnExit];
    self.longitudeTextField = longitudeTextField;
    
    // Fill in values from User Defaults if they exist
    if ([NSUserDefaults.standardUserDefaults valueForKey:UserDefaultsSimulatorLocationKey] != nil) {
        NSDictionary *savedLocation = (NSDictionary *)[NSUserDefaults.standardUserDefaults valueForKey:UserDefaultsSimulatorLocationKey];
        self.latitude = [[savedLocation valueForKey:UserDefaultsLatitudeKey] doubleValue];
        self.longitude = [[savedLocation valueForKey:UserDefaultsLongitudeKey] doubleValue];

        longitudeTextField.text = [self.numberFormatter stringFromNumber:[NSNumber numberWithDouble:self.longitude]];
        latitudeTextField.text = [self.numberFormatter stringFromNumber:[NSNumber numberWithDouble:self.latitude]];
    }
    
    UIButton *startSimulatorButton = [UIButton buttonWithType:UIButtonTypeSystem];
    startSimulatorButton.translatesAutoresizingMaskIntoConstraints = NO;
    [startSimulatorButton setTitle:@"Start" forState: UIControlStateNormal];
    [startSimulatorButton setTitle:@"Start" forState: UIControlStateDisabled];
    [startSimulatorButton setTitle:@"Start" forState: UIControlStateSelected];
    [startSimulatorButton setTitle:@"Start" forState: UIControlStateHighlighted];
    startSimulatorButton.titleLabel.font = [UIFont systemFontOfSize:32.0];
    [self.view addSubview:startSimulatorButton];
    
    UIButton *saveSimulatorLocationButton = [UIButton buttonWithType:UIButtonTypeSystem];
    saveSimulatorLocationButton.translatesAutoresizingMaskIntoConstraints = NO;
    [saveSimulatorLocationButton setTitle:@"Save" forState: UIControlStateNormal];
    [saveSimulatorLocationButton setTitle:@"Save" forState: UIControlStateDisabled];
    [saveSimulatorLocationButton setTitle:@"Save" forState: UIControlStateSelected];
    [saveSimulatorLocationButton setTitle:@"Save" forState: UIControlStateHighlighted];
    saveSimulatorLocationButton.titleLabel.font = [UIFont systemFontOfSize:32.0];
    [self.view addSubview:saveSimulatorLocationButton];
    
    [saveSimulatorLocationButton addTarget:self action:@selector(saveSimulatorLocation) forControlEvents:UIControlEventTouchUpInside];
    
    [startSimulatorButton addTarget:self action:@selector(startSimulator) forControlEvents:UIControlEventTouchUpInside];

    self.savedStatusLabel = [UILabel new];
    self.savedStatusLabel.translatesAutoresizingMaskIntoConstraints = NO;
    self.savedStatusLabel.text = @"";
    self.savedStatusLabel.textColor = UIColor.whiteColor;
    [self.view addSubview:self.savedStatusLabel];
    
    [latitudeTextField.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor].active = YES;
    [longitudeTextField.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor].active = YES;
    [startSimulatorButton.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor].active = YES;
    [saveSimulatorLocationButton.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor].active = YES;
    
    [longitudeTextField.centerYAnchor constraintEqualToAnchor:self.view.centerYAnchor].active = YES;
    [latitudeTextField.bottomAnchor constraintEqualToAnchor:longitudeTextField.topAnchor constant:-20.0].active = YES;
    [startSimulatorButton.topAnchor constraintEqualToAnchor:longitudeTextField.bottomAnchor constant:20.0].active = YES;
    [saveSimulatorLocationButton.topAnchor constraintEqualToAnchor:startSimulatorButton.bottomAnchor constant:20.0].active = YES;
    
    [self.savedStatusLabel.leadingAnchor constraintEqualToAnchor:saveSimulatorLocationButton.trailingAnchor constant:8.0].active = YES;
    [self.savedStatusLabel.centerYAnchor constraintEqualToAnchor:saveSimulatorLocationButton.centerYAnchor].active = YES;
}

- (void)startSimulator {
    if ([ProductCommunicationService.sharedInstance startSimulatorAt:CLLocationCoordinate2DMake(self.latitude, self.longitude)]) {
        [self dismissViewControllerAnimated:YES completion:nil];
    }
}

- (void)saveSimulatorLocation {
    if ([NSNumber numberWithDouble:self.longitude] != nil && [NSNumber numberWithDouble:self.latitude] != nil) {
        NSDictionary *savedLocation = @{UserDefaultsLatitudeKey : [NSNumber numberWithDouble:self.latitude],
                                        UserDefaultsLongitudeKey : [NSNumber numberWithDouble:self.longitude],
        };
        
        [NSUserDefaults.standardUserDefaults setObject:savedLocation forKey:UserDefaultsSimulatorLocationKey];
        
        self.savedStatusLabel.text = @"✅ Saved for Next Time";
    }
}

- (void)updateLatitude {
    self.latitude = [self.numberFormatter numberFromString:self.latitudeTextField.text].doubleValue;
}


- (void)updateLongitude {
    self.longitude = [self.numberFormatter numberFromString:self.longitudeTextField.text].doubleValue;
}

@end
