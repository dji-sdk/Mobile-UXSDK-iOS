//
//  DJIRemoteControllerBaseTypes.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "DJIStick.h"

#define DJI_RC_CONTROL_CHANNEL_SIZE     (4)

NS_ASSUME_NONNULL_BEGIN

/*********************************************************************************/
#pragma mark - Data Structs and Enums
/*********************************************************************************/

/*********************************************************************************/
#pragma mark DJIRCMode
/*********************************************************************************/


/**
 *  Remote Controller mode of operation can be normal (single RC connected to
 *  aircraft), master, slave, or unknown.
 */
typedef NS_ENUM (uint8_t, DJIRCMode){


    /**
     *  Remote Controller is not connected to another Remote Controller.
     */
    DJIRCModeNormal,


    /**
     *  Remote Controller is a master (will route a connected slave Remote
     *   Controller's commands to the aircraft).
     */
    DJIRCModeMaster,

    /**
     *  Remote Controller is currently a slave Remote Controller (sends commands to
     *  aircraft through a master Remote Controller).
     */
    DJIRCModeSlave,


    /**
     *  The Remote Controller's mode is unknown.
     */
    DJIRCModeUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark DJIRCAircraftMappingStyle
/*********************************************************************************/


/**
 *  The predefined mapping styles available to use. Custom allow to specify all
 *  mapping configurations.
 */
typedef NS_ENUM (uint8_t, DJIRCAircraftMappingStyle){
    

    /**
     *  Style 1.
     */
    DJIRCAircraftMappingStyle1,
    

    /**
     *  Style 2.
     */
    DJIRCAircraftMappingStyle2,
    

    /**
     *  Style 3.
     */
    DJIRCAircraftMappingStyle3,
    

    /**
     *  Custom Style. Requires all mapping configurations.
     */
    DJIRCAircraftMappingStyleCustom,
    

    /**
     *  Unknown style.
     */
    DJIRCAircraftMappingStyleUnknown = 0xFF,
};


/**
 *  The list of controls that may be mapped on a stick.
 */
typedef NS_ENUM (uint8_t, DJIRCAircraftStickMappingTarget) {
    

    /**
     *  None
     */
    DJIRCAircraftStickMappingTargetNone,


    /**
     *  Controls Throttle
     */
    DJIRCAircraftStickMappingTargetThrottle,
    

    /**
     *  Controls Pitch
     */
    DJIRCAircraftStickMappingTargetPitch,
    

    /**
     *  Controls Roll
     */
    DJIRCAircraftStickMappingTargetRoll,
    

    /**
     *  Controls Yaw
     */
    DJIRCAircraftStickMappingTargetYaw,


	/**
	 *  Unknown.
	 */
	DJIRCAircraftStickMappingUnknown = 0xFF,
};


/**
 *  A struct representing a mapping configuration which includes the particular
 *  control and whether or not it is reversed.
 */
typedef struct
{

    /**
     *  The defined control to be mapped.
     */
    DJIRCAircraftStickMappingTarget target;
    

    /**
     *  whether or not the control is to be reversed.
     */
    BOOL isReversed;
} DJIRCAircraftStickMapping;


/**
 *  The gimbal control stick mapping styles.
 */
typedef NS_ENUM (uint8_t, DJIRCGimbalMappingStyle){
    

    /**
     *  Default
     */
    DJIRCGimbalMappingStyleDefault,
    

    /**
     *  Custom
     */
    DJIRCGimbalMappingStyleCustom,
    

    /**
     *  Unknown
     */
    DJIRCGimbalMappingStyleUnknown = 0xFF,
};


/**
 *  The list of available control to be used when creating custom mapping
 *  configurations
 */
typedef NS_ENUM (uint8_t, DJIRCGimbalStickMappingTarget) {
    

    /**
     *  None
     */
    DJIRCGimbalStickMappingTargetNone,
    

    /**
     *  Pitch
     */
    DJIRCGimbalStickMappingTargetPitch,
    

    /**
     *  Roll
     */
    DJIRCGimbalStickMappingTargetRoll,
    

    /**
     *  Yaw
     */
    DJIRCGimbalStickMappingTargetYaw
};


/**
 *  A struct representing a custom mapping configuration.
 */
typedef struct
{

    /**
     *  The specific control to be mapped.
     */
    DJIRCGimbalStickMappingTarget target;
    

    /**
     *  whether or not the control is to be reversed.
     */
    BOOL isReversed;
    
} DJIRCGimbalStickMapping;


/*********************************************************************************/
#pragma mark DJIRCRequestGimbalControlResult
/*********************************************************************************/


/**
 *  Result when a slave Remote Controller requests permission to control the gimbal.
 */
typedef NS_ENUM (uint8_t, DJIRCRequestGimbalControlResult) {
 

    /**
     *  The master Remote Controller agrees to the slave's request.
     */
    DJIRCRequestGimbalControlResultAccepted,
 

    /**
     *  The master Remote Controller denies the slave's request. If the  slave Remote
     *  Controller wants to control the gimbal, it must send  a request to the master
     *  Remote Controller first. Then the master  Remote Controller can decide to
     *  approve or deny the request.
     */
    DJIRCRequestGimbalControlResultRejected,
 

    /**
     *  The slave Remote Controller's request timed out.
     */
    DJIRCRequestGimbalControlResultTimeout,
    

    /**
     *  The slave Remote Controller's request is unknown.
     */
    DJIRCRequestGimbalControlResultUnknown = 0xFF,
};


/*********************************************************************************/
#pragma mark DJIRCGimbalControlSpeedCoefficient
/*********************************************************************************/


/**
 *  Remote Controller's gimbal control speed.
 */
typedef struct
{

    /**
     *  Gimbal's pitch speed with range [0, 100].
     */
    uint8_t pitchSpeedCoefficient;
    

    /**
     *  Gimbal's roll speed with range [0, 100].
     */
    uint8_t rollSpeedCoefficient;
    

    /**
     *  Gimbal's yaw speed with range [0, 100].
     */
    uint8_t yawSpeedCoefficient;
} DJIRCGimbalControlSpeedCoefficient;

/*********************************************************************************/
#pragma mark DJIRCPairingState
/*********************************************************************************/


/**
 *  Remote Controller pairing state.
 */
typedef NS_ENUM (uint8_t, DJIRCPairingState){

    /**
     *  The Remote Controller is not pairing.
     */
    DJIRCPairingStateStateUnpaired,
    

    /**
     *  The Remote Controller is currently pairing.
     */
    DJIRCPairingStateStatePairing,
    

    /**
     *  The Remote Controller's pairing was completed.
     */
    DJIRCPairingStateStatePaired,
    

    /**
     *  The Remote Controller's pairing state is unknown.
     */
    DJIRCPairingStateStateUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark DJIRCConnectToMasterResult
/*********************************************************************************/


/**
 *  Result when a slave Remote Controller tries to join a master Remote Controller.
 */
typedef NS_ENUM (uint8_t, DJIRCConnectToMasterResult){
 

    /**
     *  The slave Remote Controller's attempt to join the master Remote Controller was
     *  successful.
     */
    DJIRCConnectToMasterResultAccepted,
 

    /**
     *  The slave Remote Controller's attempt to join the master Remote Controller was
     *  unsuccessful due to a password error.
     */
    DJIRCConnectToMasterResultPasswordError,
 

    /**
     *  The slave Remote Controller's attempt to join the master Remote Controller was
     *  rejected.
     */
    DJIRCConnectToMasterResultRejected,
 

    /**
     *  The slave Remote Controller's attempt to join the master Remote Controller was
     *  unsuccessful because the master  Remote Controller is at the maximum number of
     *  slaves it can have.
     */
    DJIRCConnectToMasterResultMaximumCapacity,


    /**
     *  The slave Remote Controller's attempt to join the master Remote Controller was
     *  unsuccessful because the request timed out.
     */
    DJIRCConnectToMasterResultTimeout,
    

    /**
     *  The result of the slave Remote Controller's attempt to join the master Remote
     *  Controller is unknown.
     */
    DJIRCConnectToMasterResultUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark DJIRCChargeRemaining
/*********************************************************************************/


/**
 *  Remote Controller's battery info.
 */
typedef struct
{

    /**
     *  The remaining power in the Remote Controller's battery in milliamp hours (mAh).
     */
    uint32_t remainingChargeInmAh;
    

    /**
     *  The remaining power in the Remote Controller's battery as a percentage in the
     *  range of [0, 100].
     */
    uint8_t remainingChargeInPercent;
} DJIRCChargeRemaining;

/*********************************************************************************/
#pragma mark DJIRCGPSTime
/*********************************************************************************/


/**
 *  Remote Controller's GPS time.
 */
typedef struct
{

    /**
     *  Hour value of Remote Controller's GPS time.
     */
    uint8_t hour;
    

    /**
     *  Minute value of Remote Controller's GPS time.
     */
    uint8_t minute;
    

    /**
     *  Second value of Remote Controller's GPS time.
     */
    uint8_t second;
    

    /**
     *  Year value of Remote Controller's GPS time.
     */
    uint16_t year;
    

    /**
     *  Month value of Remote Controller's GPS time.
     */
    uint8_t month;
    

    /**
     *  Day value of Remote Controller's GPS time.
     */
    uint8_t day;
} DJIRCGPSTime;

/*********************************************************************************/
#pragma mark DJIRCGPSData
/*********************************************************************************/


/**
 *  Remote Controller's GPS data. Only Inspire and M100 Remote Controllers have GPS.
 */
typedef struct
{

    /**
     *  The Remote Controller's GPS time.
     */
    DJIRCGPSTime time;
    

    /**
     *  The Remote Controller's location.
     */
    CLLocationCoordinate2D location;
    

    /**
     *  The Remote Controller's speed in the East direction in meters/second. A negative
     *  speed means the Remote  Controller is moving in the West direction.
     */
    float eastSpeed;
    

    /**
     *  The Remote Controller's speed in the North direction in meters/second. A
     *  negative speed means the Remote  Controller is moving in the South direction.
     */
    float northSpeed;
    

    /**
     *  The number of GPS satellites the Remote Controller detects.
     */
    int satelliteCount;
    

    /**
     *  The the margin of error, in meters, for the GPS location.
     */
    float accuracy;
    

    /**
     *  `YES` if the GPS data is valid. The data is not valid if there are too few
     *  satellites  or the signal strength is too low.
     */
    BOOL isValid;
} DJIRCGPSData;

/*********************************************************************************/
#pragma mark DJIRCGimbalAxis
/*********************************************************************************/


/**
 *  Defines what the Gimbal Dial (upper left wheel on the Remote Controller) will
 *  control.
 */
typedef NS_ENUM (uint8_t, DJIRCGimbalAxis){
 

    /**
     *  The upper left wheel will control the gimbal's pitch.
     */
    DJIRCGimbalAxisPitch,
 

    /**
     *  The upper left wheel will control the gimbal's roll.
     */
    DJIRCGimbalAxisRoll,
 

    /**
     *  The upper left wheel will control the gimbal's yaw.
     */
    DJIRCGimbalAxisYaw,
};

/*********************************************************************************/
#pragma mark DJIRCRightWheel
/*********************************************************************************/


/**
 *  Current state of the Camera Settings Dial (upper right wheel on the Remote
 *  Controller).
 */
typedef struct
{

    /**
     *  `YES` if right wheel present.
     */
    BOOL isPresent;
    

    /**
     *  `YES` if wheel value has changed.
     */
    BOOL isTurned;
    

    /**
     *  `YES` if wheel is being pressed.
     */
    BOOL isClicked;
    

    /**
     *  Wheel value in the range of [-660, 660]. The value represents the difference in
     *  an operation.
     */
    NSInteger value;
} DJIRCRightWheel;

/*********************************************************************************/
#pragma mark DJIRCTransformationSwitchState
/*********************************************************************************/


/**
 *  Transformation Switch position states.
 */
typedef NS_ENUM (uint8_t, DJIRCTransformationSwitchState){
 

    /**
     *  Retract landing gear switch state.
     */
    DJIRCTransformationSwitchStateRetract,
 

    /**
     *  Deploy landing gear switch state.
     */
    DJIRCTransformationSwitchStateDeploy,
	

	/**
	 *  Unknown.
	 */
	DJIRCTransformationSwitchStateUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark DJIRCHardwareTransformSwitch
/*********************************************************************************/


/**
 *  Transformation Switch position. The Transformation Switch is around the Return
 *  To Home Button on Inspire,  Inspire 1 and M100 Remote Controllers, and controls
 *  the state of the aircraft's landing gear.
 */
typedef struct
{

    /**
     *  `YES` if the Transformation Switch present.
     */
    BOOL isPresent;
    

    /**
     *  Current transformation switch state.
     */
    DJIRCTransformationSwitchState state;
    
} DJIRCTransformationSwitch;

/*********************************************************************************/
#pragma mark DJIRCFlightModeSwitch
/*********************************************************************************/


/**
 *  Remote Controller Flight Mode switch position.
 */
typedef NS_ENUM (uint8_t, DJIRCFlightModeSwitch){


    /**
     *  Position One. For all products except Mavic Pro, this is the left most position
     *  of the flight mode switch on a remote controller from the perspective of the
     *  pilot. For example, on a Phantom 4 remote controller,  Position One is labeled
     *  "A". For Mavic Pro, Spark and Mavic Air, this is  the position that is furthest
     *  away from the pilot and labeled "Sport".
     */
    DJIRCFlightModeSwitchOne,


    /**
     *  Position Two. For all products except Mavic Pro, this is the middle position of
     *  the flight mode switch on a remote controller from the perspective of the pilot.
     *  For example, on a Phantom 4 remote controller, Position Two is labeled "S". For
     *  Mavic Pro, Spark and Mavic Air, this is the position that is closest  to the
     *  pilot (the P position).
     */
    DJIRCFlightModeSwitchTwo,


    /**
     *  Position Three. For all products except Mavic Pro, this is the right most
     *  position of the flight mode switch on a remote controller from the perspective
     *  of the pilot. For example, on a Phantom 4 remote controller, Position Two is
     *  labeled "P". Mavic Pro, Spark or Mavic Air does not have  a third position for
     *  the flight mode switch.
     */
    DJIRCFlightModeSwitchThree,
};

/*********************************************************************************/
#pragma mark DJIRCButton
/*********************************************************************************/


/**
 *  Remote Controller has numerous momentary push buttons, which will use this
 *  state.
 */
typedef struct
{

    /**
     *  `YES` if the hardware button is present.
     */
    BOOL isPresent;
    

    /**
     *  `YES` if button is pressed down.
     */
    BOOL isClicked;
} DJIRCButton;

/*********************************************************************************/
#pragma mark DJIRCFiveDButton
/*********************************************************************************/


/**
 *  Movement direction of the remote controller's 5D button.
 */
typedef NS_ENUM(NSUInteger, DJIRCFiveDButtonDirection) {
 

    /**
     *  Button has no movement in either the vertical direction or the horizontal
     *  direction.
     */
    DJIRCFiveDButtonDirectionMiddle,
 

    /**
     *  Button is moved in the positive direction which is up or right.
     */
    DJIRCFiveDButtonDirectionPositive,
 

    /**
     *  Button is moved in the negative direction which is down or left.
     */
    DJIRCFiveDButtonDirectionNegative,
};


/**
 *  State of the 5D button on the remote controller. Vertical movement, horizontal
 *  movement and if it is pressed are  not exclusive.
 */
typedef struct{
    

    /**
     *  `YES` if 5D button is present.
     */
    BOOL isPresent;
    

    /**
     *  Get the movement in the vertical direction of the 5D button. Up is the positive
     *  direction and down is the  negative direction.
     */
    DJIRCFiveDButtonDirection verticalDirection;
    

    /**
     *  Get the movement in the horizontal direction of the 5D button. Right is the
     *  positive direction and left is the  negative direction.
     */
    DJIRCFiveDButtonDirection horizontalDirection;
    

    /**
     *  `YES` if the 5D button is pressed down.
     */
    BOOL isClicked;
}DJIRCFiveDButton;

/*********************************************************************************/
#pragma mark DJIRCHardwareState
/*********************************************************************************/


/**
 *  Remote Controller's current state.
 */
typedef struct
{

    /**
     *  Get left stick.
     *  
     *  @return An instance of `DJIStick`.
     */
    DJIStick leftStick;


    /**
     *  Get right stick.
     *  
     *  @return An instance of `DJIStick`.
     */
    DJIStick rightStick;


    /**
     *  Gimbal Dial's (upper left wheel) value in the range of [-660,660], where 0 is
     *  untouched and positive is turned in the clockwise direction.
     *  
     *  @return Gimbal wheel value.
     */
    int leftWheel;
    

    /**
     *  Current state of the upper right wheel on the Remote Controller (Camera Settings
     *  Dial).
     */
    DJIRCRightWheel rightWheel;
    

    /**
     *  Current state of the Transformation Switch on the Remote Controller.
     */
    DJIRCTransformationSwitch transformationSwitch;
    

    /**
     *  Current position of the Flight Mode Switch on the Remote Controller.
     */
    DJIRCFlightModeSwitch flightModeSwitch;
    

    /**
     *  Current state of the Return To Home Button.
     */
    DJIRCButton goHomeButton;
    

    /**
     *  Current state of the Video Recording Button.
     */
    DJIRCButton recordButton;
    

    /**
     *  Current state of the Shutter Button.
     */
    DJIRCButton shutterButton;
    

    /**
     *  Current state of the Playback Button. The Playback Button is not supported on
     *  Phantom 4 remote controllers.
     */
    DJIRCButton playbackButton;
    

    /**
     *  Current state of the Pause Button. The Pause button is only supported on Phantom
     *  4 remote controllers.
     */
    DJIRCButton pauseButton;
    

    /**
     *  Current state of custom button 1 (left Back Button). It is not supported by
     *  remote controllers  for Mavic Air or Spark.
     */
    DJIRCButton c1Button;
    

    /**
     *  Current state of custom button 2 (right Back Button).
     */
    DJIRCButton c2Button;
    

    /**
     *  Current state of fn button. It is only supported by remote controllers for Spark
     *  or Mavic Air.
     */
    DJIRCButton fnButton;
    

    /**
     *  Current state of the 5D button. The button can be moved up, down, left and right
     *  and can be pressed. The 5D  button is supported by Mavic Pro and Mavic 2 remote
     *  controllers.
     */
    DJIRCFiveDButton fiveDButton;
} DJIRCHardwareState;

/*********************************************************************************/
#pragma mark DJIRCFocusControllerControlType
/*********************************************************************************/


/**
 *  Remote Focus Control Type.
 */
typedef NS_ENUM (uint8_t, DJIRCFocusControllerControlType){
    

    /**
     *  Control Aperture.
     */
    DJIRCFocusControllerControlTypeAperture,
    

    /**
     *  Control Focal Length.
     */
    DJIRCFocusControllerControlTypeFocalLength,


    /**
     *  Adjust focus distance.
     */
    DJIRCFocusControllerControlTypeFocusDistance,

    /**
     *  Unknown types.
     */
    DJIRCFocusControllerControlTypeUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark DJIRCFocusControllerDirection
/*********************************************************************************/


/**
 *  Remote Focus Control Direction.
 */
typedef NS_ENUM (uint8_t, DJIRCFocusControllerDirection){
    

    /**
     *  Clockwise.
     */
    DJIRCRemoteFocusControlDirectionClockwise,
 

    /**
     *  CounterClockwise.
     */
    DJIRCRemoteFocusControlDirectionCounterClockwise,
    

    /**
     *  Unknown.
     */
    DJIRCRemoteFocusControlDirectionUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark DJIRCChargeMobileMode
/*********************************************************************************/


/**
 *  Modes to charge an iOS mobile device. Only supported by Inspire 2.
 */
typedef NS_ENUM (uint8_t, DJIRCChargeMobileMode){
 

    /**
     *  The remote controller does not charge the mobile device.
     */
    DJIRCChargeMobileModeNever,
 

    /**
     *  The remote controller charges the mobile device until the the mobile device is
     *  fully charged.
     */
    DJIRCChargeMobileModeAlways,
 

    /**
     *  The remote controller charges the mobile device in an intelligent mode: The
     *  remote controller starts charging  when the mobile device's battery is lowered
     *  then 20% and stops charging when the mobile device's battery is above 50%.
     */
    DJIRCChargeMobileModeIntelligent,
 

    /**
     *  The Remote Controller's charging mode is unknown.
     */
    DJIRCChargeMobileModeUnknown = 0xFF,
};

/*********************************************************************************/
#pragma mark DJIRCFocusControllerState
/*********************************************************************************/


/**
 *  Remote Controller's Remote Focus State. The focus product has one dial (focus
 *  control) that controls two separate parts of the camera: focal length and
 *  aperture. However it can only control one of these at any one time and is an
 *  absolute dial, meaning that a specific rotational position of the dial
 *  corresponds to a specific focal length or aperture. This means that whenever the
 *  dial control mode is changed, the dial first has to be reset to the new mode's
 *  previous dial position before the dial can be used to adjust the setting of the
 *  new mode. Example workflow:<br/><ol> - Use dial to set an Aperture of f2.2
 *   - Change dial control mode to focal length (set
 *  `DJIRCFocusControllerControlType`)
 *  - Use the dial to change the focal length
 *  - Change dial control mode back to aperture
 *  -  set `DJIRCFocusControllerControlType`
 *   - `isWorking` will now be NO
 *  -  Adjust dial back to f2.2
 *  - `DJIRCFocusControllerDirection` is the direction the dial should be rotated
 *  - `isWorking` will become YES when set back to f2.2
 *  - Now the dial can be used to adjust the aperture.</ol>
 */
typedef struct
{

    /**
     *  `YES` if the focus control works. The control can be either changing the
     *  Aperture or  Focal Length. If it is `NO`, follow  the
     *  `DJIRCFocusControllerDirection` to rotate the Remote Focus Device until it
     *  turns to `YES` again.
     */
    BOOL isWorking;
    

    /**
     *  Remote Focus Control Type.
     */
    DJIRCFocusControllerControlType controlType;
    

    /**
     *  Remote Focus Control Direction. Use this with  the `isWorking` value. It will
     *  give you the correct  rotation direction when `isWorking` is  `NO`.
     */
    DJIRCFocusControllerDirection direction;
    
} DJIRCFocusControllerState;

/*********************************************************************************/
#pragma mark - DJIRCInformation
/*********************************************************************************/


/**
 *  This class contains the information for a remote controller.
 */
@interface DJIRCInformation : NSObject


/**
 *  Remote Controller's unique identifier.
 */
@property(nonatomic, readonly) uint32_t ID;


/**
 *  Remote Controller's name.
 */
@property(nonatomic, readonly) NSString *_Nullable name;


/**
 *  Remote Controller's password.
 */
@property(nonatomic, readonly) NSString *_Nullable password;


/**
 *  Signal quality of a connected master or slave Remote Controller in percent [0,
 *  100].
 */
@property(nonatomic, readonly) uint8_t signalQuality;


/**
 *  `YES` if the slave remote controller can control the aircraft's gimbal.  Always
 *  `YES` for a master remote controller.
 */
@property(nonatomic, readonly) BOOL hasGimbalControlPermission;


/**
 *  Converts the Remote Controller's unique identifier from the  property `ID` to a
 *  string. Return the Remote Controller's identifier  as a string.
 *  
 *  @return A NSString object of the Remote Controller's unique identifier.
 */
- (NSString *_Nullable)RCIdentifier;

@end

/*********************************************************************************/
#pragma mark - DJIRCMasterSlaveState
/*********************************************************************************/


/**
 *  State of the remote controller related to the master and slave mode.
 */
@interface DJIRCMasterSlaveState : NSObject


/**
 *  The master/slave mode of the remote controller.
 */
@property(nonatomic, readonly) DJIRCMode mode;


/**
 *  `YES` if a slave remote controller joins a master remote controller.
 */
@property(nonatomic, readonly) BOOL isConnected;


/**
 *  ID of the master remote controller.
 */
@property(nonatomic, readonly) NSString *masterID;


/**
 *  ID of the slave remote controller.
 */
@property(nonatomic, readonly) NSString *slaveID;


/**
 *  Authorization code of the master remote controller that is a 6 element string of
 *  numbers.
 */
@property(nonatomic, readonly) NSString *authorizationCode;


/**
 *  `YES` if the remote controller has gimbal control.  Call
 *  `requestGimbalControlWithCompletion` to attain the gimbal control.
 *  
 *  @return `YES` if the remote controller has gimbal control.
 */
@property(nonatomic, readonly) BOOL hasGimbalControl;

@end


/**
 *  Remote controller credentials.
 */
@interface DJIRCCredentials : NSObject


/**
 *  Remote Controller's ID.
 */
@property(nonatomic, readonly) uint32_t ID;


/**
 *  Remote Controller's name.
 */
@property(nonatomic, readonly) NSString *_Nullable name;


/**
 *  Remote Controller's password.
 */
@property(nonatomic, readonly) NSString *_Nullable password;

+(instancetype) credentialsWithID:(uint32_t)ID name:(NSString * _Nullable)name password:(NSString * _Nullable)password;

@end


/**
 *  The object representing the stick mapping configuration of the remote
 *  controller.
 */
@interface DJIRCAircraftMapping : NSObject


/**
 *  Creates an instance of `DJIRCAircraftMapping` with the given style.
 *  
 *  @param style Error code.
 */
+(instancetype) mappingWithStyle:(DJIRCAircraftMappingStyle)style;


/**
 *  Creates an instance of `DJIRCAircraftMapping` with a custom style and given
 *  mapping configurations.
 *  
 *  @param leftVertical DJIRCAircraftStickMapping object.
 *  @param leftHorizontal DJIRCAircraftStickMapping object.
 *  @param rightVertical DJIRCAircraftStickMapping object.
 *  @param rightHorizontal DJIRCAircraftStickMapping object.
 */
+(instancetype) mappingWithCustomMappingLeftVertical:(DJIRCAircraftStickMapping)leftVertical
                                     leftHorizontal:(DJIRCAircraftStickMapping)leftHorizontal
                                      rightVertical:(DJIRCAircraftStickMapping)rightVertical
                                    rightHorizontal:(DJIRCAircraftStickMapping)rightHorizontal;


/**
 *  The mapping configuration for the left stick on the vertical axis.
 */
@property(nonatomic, readonly) DJIRCAircraftStickMapping leftVertical;


/**
 *  The mapping configuration for the left stick on the horizontal axis.
 */
@property(nonatomic, readonly) DJIRCAircraftStickMapping leftHorizontal;


/**
 *  The mapping configuration for the right stick on the vertical axis.
 */
@property(nonatomic, readonly) DJIRCAircraftStickMapping rightVertical;


/**
 *  The mapping configuration for the right stick on the horizontal axis.
 */
@property(nonatomic, readonly) DJIRCAircraftStickMapping rightHorizontal;


@end


/**
 *  The mapping styles to control the Gimbal.
 */
@interface DJIRCGimbalMapping : NSObject


/**
 *  Creates an instance of `DJIRCGimbalMapping` with the default mapping style.
 */
+(instancetype) mappingWithDefaultStyle;


/**
 *  Creates an instance of `DJIRCGimbalMapping` with a custom mapping style which
 *  will be defined using the passed mapping configurations.
 *  
 *  @param leftVertical The `DJIRCGimbalStickMapping` object.
 *  @param leftHorizontal The `DJIRCGimbalStickMapping` object.
 *  @param rightVertical The `DJIRCGimbalStickMapping` object.
 *  @param rightHorizontal The `DJIRCGimbalStickMapping` object.
 */
+(instancetype) mappingWithCustomMappingLeftVertical:(DJIRCGimbalStickMapping)leftVertical
                                     leftHorizontal:(DJIRCGimbalStickMapping)leftHorizontal
                                      rightVertical:(DJIRCGimbalStickMapping)rightVertical
                                    rightHorizontal:(DJIRCGimbalStickMapping)rightHorizontal;


/**
 *  The mapping configuration for the left stick on the vertical axis.
 */
@property(nonatomic, readonly) DJIRCGimbalStickMapping leftVertical;


/**
 *  The mapping configuration for the left stick on the horizontal axis.
 */
@property(nonatomic, readonly) DJIRCGimbalStickMapping leftHorizontal;


/**
 *  The mapping configuration for the right stick on the vertical axis.
 */
@property(nonatomic, readonly) DJIRCGimbalStickMapping rightVertical;


/**
 *  The mapping configuration for the right stick on the horizontal axis.
 */
@property(nonatomic, readonly) DJIRCGimbalStickMapping rightHorizontal;

@end

/*********************************************************************************/
#pragma mark DJIRCCustomButtonTags
/*********************************************************************************/

/**
 *  Tags for C1 and C2 buttons on the remote controller
 */
@interface DJIRCCustomButtonTags : NSObject


/**
 *  Button tag for custom button 2.
 *  
 *  @return Value that is the tag
 */
@property (nonatomic, nullable, readonly) NSNumber *c1ButtonTag;


/**
 *  Button tag for custom button 2
 *  
 *  @return Value that is the tag
 */
@property (nonatomic, nullable, readonly) NSNumber *c2ButtonTag;


/**
 *  Create a `DJIRCCustomButtonTags` instance with  values for C1 and C2. A valid
 *  tag is an integer in range [0, 255].
 *  
 *  @param c1ButtonTag Button tag for custom button 1 with range [0, 255].
 *  @param c2ButtonTag Button tag for custom button 2 with range [0, 255].
 *  
 *  @return Instance of `DJIRCCustomButtonTags`. `nil` if the value is invalid, or both c1ButtonTag and c2ButtonTag are `nil`.
 */
-(nullable instancetype)initWithC1ButtonTag:(NSNumber *_Nullable)c1ButtonTag
                             andC2ButtonTag:(NSNumber *_Nullable)c2ButtonTag;

@end

/*********************************************************************************/
#pragma mark Customizable Buttons (Cendence)
/*********************************************************************************/


/**
 *  Actions that can be assigned to a customizable button. Some of the actions are
 *  reserved and the firmware will execute the corresponding actions even when the
 *  application is not connected. Some of the actions are defined by the mobile
 *  applications. The application is responsible for implementing the non firmware
 *  actions. The definitions used in DJI Go are provided. It is usually recommended
 *  to follow DJI Go's definitions for compability so if DJI Go is used at the same
 *  time as the SDK application the actions will be expected in both applications.
 */
typedef NS_ENUM(NSUInteger, DJIRCButtonAction) {

    /**
     *  Custom action with value 0. In DJI Go, this value represents the action to
     *  toggle the camera setting view.
     */
    DJIRCButtonActionCustom0                                = 0,

    /**
     *  Custom action with value 3. In DJI Go, this value represents the action to
     *  switch the the live view and the map view.
     */
    DJIRCButtonActionCustom3                                = 3,

    /**
     *  Custom action with value 4. In DJI Go, this value represents the action to
     *  clear the flight path in the map view.
     */
    DJIRCButtonActionCustom4                                = 4,

    /**
     *  Custom action with value 5. In DJI Go, this value represents the action to
     *  toggle the battery setting view.
     */
    DJIRCButtonActionCustom5                                = 5,

    /**
     *  Custom action with value 7. In DJI Go, this value represents the action to
     *  trigger central exposure metering.
     */
    DJIRCButtonActionCustom7                                = 7,

    /**
     *  Custom action with value 8. In DJI Go, this value represents the action to
     *  toggle AE lock.
     */
    DJIRCButtonActionCustom8                                = 8,

    /**
     *  Custom action with value 9. In DJI Go, this value represents the action to
     *  toggle the LEDs on the four arms.
     */
    DJIRCButtonActionCustom9                                = 9,

    /**
     *  Reset FPV gimbal attitude to the center, the gimbal will rotate 45 degrees in
     *  pitch axis up and down when the action is trigger.
     */
    DJIRCButtonActionResetFPVGimbal                         = 12,

    /**
     *  Custom action with value 13. In DJI Go, this value represents the action to
     *  expand  the live view from the FPV camera.
     */
    DJIRCButtonActionCustom13                               = 13,

    /**
     *  Trigger a Quick Spin. This action is handled by the firmware.
     */
    DJIRCButtonActionQuickSpin                              = 14,

    /**
     *  Custom action with value 16. In DJI Go, this value represents the  action to
     *  toggle the playback view.
     */
    DJIRCButtonActionCustom16                               = 16,

    /**
     *  Custom action with value 17. In DJI Go, this value represents the  action to
     *  trigger focusing at the center of the live view.
     */
    DJIRCButtonActionCustom17                               = 17,

    /**
     *  Custom action with value 23. In DJI Go, this value represents the action  to
     *  request gimbal control (for the slave remote controller).
     */
    DJIRCButtonActionCustom23                               = 23,

    /**
     *  Custom action with value 24. In DJI Go, this value represents the action  to
     *  toggle the modes of the gimbal.
     */
    DJIRCButtonActionCustom24                               = 24,

    /**
     *  Custom action with value 25. In DJI Go, this value represents the action  to
     *  toggle the customizable button setting view.
     */
    DJIRCButtonActionCustom25                               = 25,

    /**
     *  Custom action with value 26. In DJI Go, this value represents the action  to
     *  toggle AF and MF for camera.
     */
    DJIRCButtonActionCustom26                               = 26,

    /**
     *  Custom action with value 27. In DJI Go, this value represents the action to
     *  dismiss the warning tips.
     */
    DJIRCButtonActionCustom27                               = 27,

    /**
     *  Custom action with value 28. In DJI Go, this value represents the action to
     *  toggle the automatic movement  of the landing gear.
     */
    DJIRCButtonActionCustom28                               = 28,

    /**
     *  Custom action with value 29. In DJI Go, this value represents the action to
     *  toggle the warning list view.
     */
    DJIRCButtonActionCustom29                               = 29,

    /**
     *  Switch frequency bands of the remote controller. This action is handled by the
     *  firmware.
     */
    DJIRCButtonActionSwitchFrequency                        = 30,

    /**
     *  Trigger the camera focus. This action is handled by the firmware.
     */
    DJIRCButtonActionFocus                                  = 37,

    /**
     *  Custom action with value 41. In DJI Go, this value represents the action to
     *  toggle the  composition mode for the Spotlight.
     */
    DJIRCButtonActionCustom41                               = 41,

    /**
     *  Custom action with value 43. In DJI Go, this value represents the action to
     *  toggle the peak focus.
     */
    DJIRCButtonActionCustom43                               = 43,

    /**
     *  Custom action with value 44. In DJI Go, this value represents the action to
     *  toggle the display of grid.
     */
    DJIRCButtonActionCustom44                               = 44,

    /**
     *  Custom action with value 45. In DJI Go, this value represents the action to
     *  toggle the display of histogram.
     */
    DJIRCButtonActionCustom45                               = 45,

    /**
     *  Custom action with value 46. In DJI Go, this value represents the action to
     *  switch the white balance settings.
     */
    DJIRCButtonActionCustom46                               = 46,

    /**
     *  Custom action with value 47. In DJI Go, this value represents the action to
     *  toggle the over-exposure warning.
     */
    DJIRCButtonActionCustom47                               = 47,

    /**
     *  Custom action with value 52. In DJI Go, this value represents the action to
     *  reset the gimbal yaw to align with the aircraft heading.
     */
    DJIRCButtonActionCustom52                               = 52,

    /**
     *  Retract or deploy the landing gear. This action is handled by the firmware.
     */
    DJIRCButtonActionToggleLandingGear                      = 54,

    /**
     *  Custom action with value 59. In DJI Go, this value represents the action to
     *  toggle the radar map.
     */
    DJIRCButtonActionCustom59                               = 59,

    /**
     *  Custom action with value 60. In DJI Go, this value represents the action to
     *  toggle the downward vision sensors.
     */
    DJIRCButtonActionCustom60                               = 60,

    /**
     *  Custom action with value 61. In DJI Go, this value represents the action to
     *  toggle the forward obstacle avoidance.
     */
    DJIRCButtonActionCustom61                               = 61,

    /**
     *  Custom action with value 63. In DJI Go, this value represents the action to
     *  toggle the full screen mode.
     */
    DJIRCButtonActionCustom63                               = 63,

    /**
     *  Custom action with value 100. This value is reserved for SDK applications.
     */
    DJIRCButtonActionCustom100                              = 100,

    /**
     *  Custom action with value 101. This value is reserved for SDK applications.
     */
    DJIRCButtonActionCustom101                              = 101,

    /**
     *  Custom action with value 102. This value is reserved for SDK applications.
     */
    DJIRCButtonActionCustom102                              = 102,

    /**
     *  Custom action with value 103. This value is reserved for SDK applications.
     */
    DJIRCButtonActionCustom103                              = 103,

    /**
     *  Custom action with value 104. This value is reserved for SDK applications.
     */
    DJIRCButtonActionCustom104                              = 104,

    /**
     *  Custom action with value 105. This value is reserved for SDK applications.
     */
    DJIRCButtonActionCustom105                              = 105,

    /**
     *  Custom action with value 106. This value is reserved for SDK applications.
     */
    DJIRCButtonActionCustom106                              = 106,

    /**
     *  Custom action with value 107. This value is reserved for SDK applications.
     */
    DJIRCButtonActionCustom107                              = 107,

    /**
     *  Custom action with value 108. This value is reserved for SDK applications.
     */
    DJIRCButtonActionCustom108                              = 108,

    /**
     *  Custom action with value 109. This value is reserved for SDK applications.
     */
    DJIRCButtonActionCustom109                              = 109,

    /**
     *  Not defined. It is used to present that no action is bound to a button.
     */
    DJIRCButtonActionNotDefined                             = 110,
};


/**
 *  The customizable buttons.
 */
typedef NS_ENUM(NSUInteger, DJIRCCustomizableButton) {

	/**
	 *  The button with C1 label.
	 */
	DJIRCCustomizableButtonC1,

	/**
	 *  The button with C2 label.
	 */
	DJIRCCustomizableButtonC2,

	/**
	 *  The button with C3 label.
	 */
	DJIRCCustomizableButtonC3,

	/**
	 *  The button with C4 label.
	 */
	DJIRCCustomizableButtonC4,

	/**
	 *  The button with BA label.
	 */
	DJIRCCustomizableButtonBA,

	/**
	 *  The button with BB label.
	 */
	DJIRCCustomizableButtonBB,

	/**
	 *  The button with BC label.
	 */
	DJIRCCustomizableButtonBC,

	/**
	 *  The button with BD label.
	 */
	DJIRCCustomizableButtonBD,

	/**
	 *  The button with BE label.
	 */
	DJIRCCustomizableButtonBE,

	/**
	 *  The button with BF label.
	 */
	DJIRCCustomizableButtonBF,

	/**
	 *  The button with BG label.
	 */
	DJIRCCustomizableButtonBG,

	/**
	 *  The button with BH label.
	 */
	DJIRCCustomizableButtonBH,

	/**
	 *  The button with TD label.
	 */
	DJIRCCustomizableButtonTD,

	/**
	 *  The button with MENU label.
	 */
	DJIRCCustomizableButtonMENU,

	/**
	 *  Unknown.
	 */
	DJIRCCustomizableButtonUnknown = 0xFF,
};

@class DJIMutableRCButtonConfiguration;


/**
 *  The configuration for the customizable buttons on the remote controller. The
 *  configuration returned by SDK interfaces is immutable. Call `mutableCopy` to get
 *  a mutable copy in class `DJIMutableRCButtonConfiguration` and change the
 *  configuration.
 */
@interface DJIRCButtonConfiguration : NSObject <NSCopying, NSMutableCopying>


/**
 *  Action bound to the C1 button.
 */
@property (nonatomic, readonly) DJIRCButtonAction C1Action;


/**
 *  Action bound to the C2 button.
 */
@property (nonatomic, readonly) DJIRCButtonAction C2Action;


/**
 *  Action bound to the C3 button.
 */
@property (nonatomic, readonly) DJIRCButtonAction C3Action;


/**
 *  Action bound to the C4 button.
 */
@property (nonatomic, readonly) DJIRCButtonAction C4Action;


/**
 *  Action bound to the BA button.
 */
@property (nonatomic, readonly) DJIRCButtonAction BAAction;


/**
 *  Action bound to the BB button.
 */
@property (nonatomic, readonly) DJIRCButtonAction BBAction;


/**
 *  Action bound to the BC button.
 */
@property (nonatomic, readonly) DJIRCButtonAction BCAction;


/**
 *  Action bound to the BD button.
 */
@property (nonatomic, readonly) DJIRCButtonAction BDAction;


/**
 *  Action bound to the BE button.
 */
@property (nonatomic, readonly) DJIRCButtonAction BEAction;


/**
 *  Action bound to the BF button.
 */
@property (nonatomic, readonly) DJIRCButtonAction BFAction;


/**
 *  Action bound to the BG button.
 */
@property (nonatomic, readonly) DJIRCButtonAction BGAction;


/**
 *  Action bound to the BH button.
 */
@property (nonatomic, readonly) DJIRCButtonAction BHAction;


/**
 *  Action bound to the TD button.
 */
@property (nonatomic, readonly) DJIRCButtonAction TDAction;


/**
 *  Action bound to the MENU button.
 */
@property (nonatomic, readonly) DJIRCButtonAction MENUAction;


/**
 *  A dictionary representing the mapping between a customizable button and its
 *  action. The key is a `NSNumber` with value among `DJIRCCustomizableButton` and
 *  the value is a `NSNumber` with value among `DJIRCButtonAction`.
 */
@property (nonatomic, readonly)  NSDictionary<NSNumber *, NSNumber *> *buttonActions;


/**
 *  Fetch a dictionary representing the mapping between a customizable button and
 *  its action. The key is a `NSNumber` with value among `DJIRCCustomizableButton`
 *  and the value is a `NSNumber` with value among `DJIRCButtonAction`.
 *  
 *  @return An NSDictionary of NSNumber objects.
 */
+(NSDictionary<NSNumber *,NSNumber *> *)defaultButtonActions;


/**
 *  Gets the valid actions for a button. For the compatbility with DJI Go, there are
 *  rules to follow when assigning an action to a button:
 *   - `DJIRCButtonActionNotDefined` is valid for all buttons and it can be assigned
 *  to multiple buttons.
 *   - An action can be only assigned to one button.
 *   - For Button TD, the possible valid actions include
 *  `DJIRCButtonActionNotDefined`, `DJIRCButtonActionFocus` and the actions reserved
 *  by SDK (e.g. `DJIRCButtonActionCustom100`).
 *  
 *  @param button The button to check.
 *  
 *  @return The list of valid actions for a button.
 */
- (NSArray *)getValidActionsForButton:(DJIRCCustomizableButton)button;

@end


/**
 *  The mutable configuration for the customizable buttons on the remote controller.
 *  For the compatibility with DJI Go, there are rules to follow when assigning an
 *  action to a button. Refer to `getValidActionsForButton` for more detail.
 */
@interface DJIMutableRCButtonConfiguration : DJIRCButtonConfiguration


/**
 *  Action bound to the C1 button.
 */
@property (nonatomic, readwrite) DJIRCButtonAction C1Action;


/**
 *  Action bound to the C2 button.
 */
@property (nonatomic, readwrite) DJIRCButtonAction C2Action;


/**
 *  Action bound to the C3 button.
 */
@property (nonatomic, readwrite) DJIRCButtonAction C3Action;


/**
 *  Action bound to the C4 button.
 */
@property (nonatomic, readwrite) DJIRCButtonAction C4Action;


/**
 *  Action bound to the BA button.
 */
@property (nonatomic, readwrite) DJIRCButtonAction BAAction;


/**
 *  Action bound to the BB button.
 */
@property (nonatomic, readwrite) DJIRCButtonAction BBAction;


/**
 *  Action bound to the BC button.
 */
@property (nonatomic, readwrite) DJIRCButtonAction BCAction;


/**
 *  Action bound to the BD button.
 */
@property (nonatomic, readwrite) DJIRCButtonAction BDAction;


/**
 *  Action bound to the BE button.
 */
@property (nonatomic, readwrite) DJIRCButtonAction BEAction;


/**
 *  Action bound to the BF button.
 */
@property (nonatomic, readwrite) DJIRCButtonAction BFAction;


/**
 *  Action bound to the BG button.
 */
@property (nonatomic, readwrite) DJIRCButtonAction BGAction;


/**
 *  Action bound to the BH button.
 */
@property (nonatomic, readwrite) DJIRCButtonAction BHAction;


/**
 *  Action bound to the TD button.
 */
@property (nonatomic, readwrite) DJIRCButtonAction TDAction;


/**
 *  Action bound to the MENU button.
 */
@property (nonatomic, readwrite) DJIRCButtonAction MENUAction;


/**
 *  Configures a button with an action.
 *  
 *  @param button The button to configure.
 *  @param action The action to be bound with the button.
 *  
 *  @return `YES` if the configuration succeeds.
 */
- (BOOL)configButton:(DJIRCCustomizableButton)button withAction:(DJIRCButtonAction)action;
@end


NS_ASSUME_NONNULL_END
