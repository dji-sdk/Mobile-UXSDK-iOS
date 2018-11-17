//
//  DJIRemoteController.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>
#import <DJISDK/DJIBaseComponent.h>
#import <DJISDK/DJIRemoteControllerBaseTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*********************************************************************************/
#pragma mark - DJIRemoteControllerDelegate
/*********************************************************************************/

@class DJIRemoteController;


/**
 *  This protocol provides delegate methods to receive the updated information
 *  related to the remote controller.
 */
@protocol DJIRemoteControllerDelegate <NSObject>

@optional


/**
 *  Callback function that updates the Remote Controller's current hardware state
 *  (e.g. the state of the physical buttons and joysticks).
 *  
 *  @param rc Instance of the Remote Controller for which the hardware state will be updated.
 *  @param state Current state of the Remote Controller's hardware state.
 */
- (void)remoteController:(DJIRemoteController *_Nonnull)rc didUpdateHardwareState:(DJIRCHardwareState)state;


/**
 *  Callback function that updates the Remote Controller's current GPS data.
 *  
 *  @param rc Instance of the Remote Controller for which the GPS data will be updated.
 *  @param gpsData Current state of the Remote Controller's GPS data.
 */
- (void)remoteController:(DJIRemoteController *_Nonnull)rc didUpdateGPSData:(DJIRCGPSData)gpsData;


/**
 *  Callback function that updates the Remote Controller's current battery state.
 *  
 *  @param rc Instance of the Remote Controller for which the battery state will be updated.
 *  @param chargeRemaining Current state of the Remote Controller's battery state.
 */
- (void)remoteController:(DJIRemoteController *_Nonnull)rc didUpdateChargeRemaining:(DJIRCChargeRemaining)chargeRemaining;


/**
 *  Callback function that gets called when a slave Remote Controller makes a
 *  request to a master Remote Controller to control the gimbal using the method
 *  requestGimbalControlRightWithCallbackBlock.
 *  
 *  @param rc Instance of the Remote Controller.
 *  @param information Information of the slave making the request to the master Remote Controller.
 */
- (void)remoteController:(DJIRemoteController *_Nonnull)rc didReceiveGimbalControlRequestFromSlave:(DJIRCInformation *_Nonnull)information;


/**
 *  Callback function that updates the Remote Focus State, only support Focus
 *  product. If the isRCRemoteFocusCheckingSupported is `YES`, this delegate method
 *  will be called.
 *  
 *  @param rc Instance of the Remote Controller for which the battery state will be updated.
 *  @param state Current state of the Remote Focus state.
 */
- (void)remoteController:(DJIRemoteController *_Nonnull)rc didUpdateFocusControllerState:(DJIRCFocusControllerState)state;



/**
 *  Callback function that updates the remote controller's state related to the
 *  master and slave mode. Only supported by Inspire 2.
 *  
 *  @param rc Instance of the Remote Controller
 *  @param state The remote controller's state related to the master and slave mode.
 */
- (void)remoteController:(DJIRemoteController *_Nonnull)rc didUpdateMasterSlaveState:(DJIRCMasterSlaveState *_Nonnull)state;


/**
 *  Callback function that receives the button action triggered by a button click.
 *  The relationship between a button and an action is defined by
 *  `DJIRCButtonConfiguration`. It is only supported by Cendence.
 *  
 *  @param rc Instance of the Remote Controller
 *  @param action The action triggered by a button click.
 */
- (void)remoteController:(DJIRemoteController *_Nonnull)rc didUpdateButtonAction:(DJIRCButtonAction)action;

@end

/*********************************************************************************/
#pragma mark - DJIRemoteController
/*********************************************************************************/

@class DJIWiFiLink;


/**
 *  This class represents the remote controller of the aircraft. It provides methods
 *  to change the settings of the physical remote controller. For some products
 *  (e.g. Inspire 1 and Matrice 100), the class provides methods to manager the
 *  slave/master mode of the remote controllers. A remote controller is a device
 *  that can have a GPS, battery, radio, buttons, sticks, wheels, and output ports
 *  for video. The mobile device is connected to the remote controller, which is
 *  always sending out information about what everything is doing. The normal remote
 *  controller is called the master. A slave wirelessly connects to the master
 *  remote controller at 5 GHz, and the aircraft can also download information to
 *  the slave. The slave can send gimbal control commands to the master. This
 *  configuration allows one person to fly the aircraft while another person
 *  controls the gimbal. This object is available from the `DJIAircraft` subclass
 *  off `DJIBaseProduct`.
 */
@interface DJIRemoteController : DJIBaseComponent


/**
 *  Returns the delegate of Remote Controller.
 */
@property(nonatomic, weak) id<DJIRemoteControllerDelegate> delegate;


/**
 *  Query method to check if the Remote Controller supports Remote Focus State
 *  Checking.
 *  
 *  @return A boolean value.
 */
- (BOOL)isFocusControllerSupported;


/**
 *  Sets the Remote Controller's name.
 *  
 *  @param name Remote controller name to be set. Six characters at most.
 *  @param completion Completion block.
 */
- (void)setName:(NSString *_Nonnull)name withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the Remote Controller's name.
 *  
 *  @param name The remote controller's name.
 *  @param error Error retrieving the value.
 *  @param completion Completion block.
 */
- (void)getNameWithCompletion:(void (^_Nonnull)(NSString *_Nullable name, NSError *_Nullable error))completion;


/**
 *  Sets the Remote Controller's password.
 *  
 *  @param password Remote controller password to be set, using a string consisted by 4 digits.
 *  @param completion Completion block.
 */
- (void)setPassword:(NSString *_Nonnull)password withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the Remote Controller's password.
 *  
 *  @param password The remote controller's password.
 *  @param error Error retrieving the value.
 *  @param completion Completion block.
 */
- (void)getPasswordWithCompletion:(void (^_Nonnull)(NSString *_Nullable password, NSError *_Nullable error))completion;


/**
 *  Sets the Remote Controller's control mode.
 *  
 *  @param style Remote controller control mode to be set.
 *  @param completion The execution callback with the execution result returned.
 */
-(void)setAircraftMappingStyle:(DJIRCAircraftMappingStyle)style withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the Remote Controller's control mode.
 *  
 *  @param style The remote controller aircraft mapping.
 *  @param error Error retrieving the value.
 *  @param completion Completion block that receives the execution result.
 */
-(void)getAircraftMappingStyleWithCompletion:(void (^_Nonnull)(DJIRCAircraftMappingStyle style, NSError *_Nullable error))completion;


/**
 *  Set the mapping of custom style. It will change the current mapping style to
 *  `DJIRCAircraftMappingStyleCustom`. The setting will only take effect when the
 *  remote controller is in master mode.
 *  
 *  @param mapping The remote controller aircraft mapping.
 *  @param completion Completion block that receives the execution result.
 */
-(void)setCustomAircraftMapping:(DJIRCAircraftMapping *)mapping withCompletion:(DJICompletionBlock)completion;


/**
 *  Retrieves the stick mapping associated with the custom style.
 *  
 *  @param mapping The remote controller aircraft mapping.
 *  @param error Error retrieving the value.
 *  @param completion Completion block that receives the execution result.
 */
-(void)getCustomAircraftMappingWithCompletion:(void (^_Nonnull)(DJIRCAircraftMapping *_Nullable mapping, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark RC pairing
/*********************************************************************************/


/**
 *  Enters pairing mode, in which the Remote Controller starts pairing with the
 *  aircraft. This method is used when the Remote Controller no longer recognizes
 *  which aircraft it is paired with.
 *  
 *  @param completion Completion block.
 */
- (void)startPairingWithCompletion:(DJICompletionBlock)completion;


/**
 *  Exits pairing mode.
 *  
 *  @param completion Completion block.
 */
- (void)stopPairingWithCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the pairing status as the Remote Controller is pairing with the aircraft.
 *  
 *  @param state The pairing state.
 *  @param error Error retrieving the value.
 *  @param completion Completion block.
 */
- (void)getPairingStateWithCompletion:(void (^_Nonnull)(DJIRCPairingState state, NSError *_Nullable error))completion;


/*********************************************************************************/
#pragma mark RC Charging
/*********************************************************************************/


/**
 *  Sets the charge mode of a connected iOS device.  Note: Android devices are
 *  always charging when connected to the remote controller. It is only supported by
 *  Inspire 2, M200 series, Cendence and Mavic 2 series.
 *  
 *  @param mode Charge Mobile mode.
 *  @param completion Completion block that receives the setter result.
 */
- (void)setChargeMobileMode:(DJIRCChargeMobileMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the mode to charge the connected iOS device. Note that Android devices are
 *  always charging when connected to the remote controller. It is only supported by
 *  Inspire 2, M200 series, Cendence, and Mavic 2 series.
 *  
 *  @param mode The mode to charge the connected iOS device.
 *  @param error Error retrieving the value.
 *  @param completion Completion block.
 */
- (void)getChargeMobileModeWithCompletion:(void (^_Nonnull)(DJIRCChargeMobileMode mode, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark RC gimbal control
/*********************************************************************************/


/**
 *  Sets which of the gimbal directions the top left wheel (Gimbal Dial) on the
 *  Remote Controller will control. The three options (pitch, roll, and yaw) are
 *  outlined in the enum named `DJIRCGimbalAxis`.
 *  
 *  @param axis Gimbal direction to be set that the top left wheel on the Remote Controller will control.
 *  @param completion Completion block.
 */
- (void)setLeftWheelGimbalControlAxis:(DJIRCGimbalAxis)axis withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets which of the gimbal directions the top left wheel (Gimbal Dial) on the
 *  Remote Controller will control.
 *  
 *  @param axis The gimbal directions of the top left wheel on the remote controller.
 *  @param error Error retrieving the value.
 *  @param completion Completion block.
 */
- (void)getLeftWheelGimbalControlAxisWithCompletion:(void (^_Nonnull)(DJIRCGimbalAxis axis, NSError *_Nullable error))completion;


/**
 *  Sets gimbal rotation speed of the top left wheel (Gimbal Dial) on the Remote
 *  Controller. The valid range is [0, 100].
 *  
 *  @param coefficient Gimbal control speed coefficient to be set. Setting it to zero can disable the gimbal control by the top left wheel.
 *  @param completion Completion block.
 */
- (void)setLeftWheelGimbalControlSpeedCoefficient:(NSUInteger)coefficient withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets gimbal rotation speed of the top left wheel (Gimbal Dial) on the Remote
 *  Controller. The valid range is [0, 100].
 *  
 *  @param coefficient The gimbal control speed coefficient of the top left wheel on the Remote Controller. When it is zero, gimbal control by the top left wheel is disabled.
 *  @param error Error retrieving the value.
 *  @param completion Completion block.
 */
- (void)getLeftWheelGimbalControlSpeedCoefficientWithCompletion:(void (^_Nonnull)(NSUInteger coefficient, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark RC custom buttons
/*********************************************************************************/


/**
 *  Sets custom button's (Back Button's) tags, which can be used by the user to
 *  record user settings for a particular Remote Controller. Unlike all other
 *  buttons, switches and sticks on the Remote Controller, the custom buttons only
 *  send state to the Mobile Device and not the aircraft.
 *  
 *  @param tags Back Buttons' custom tags, the value should in the range of [0, 255].
 *  @param completion Completion block.
 */
- (void)setCustomButtonTags:(DJIRCCustomButtonTags *)tags withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the custom button's (Back Button's) tags.
 *  
 *  @param tags Back Buttons' custom tags.
 *  @param error Error retrieving the value.
 *  @param completion Completion block.
 */
- (void)getCustomButtonTagsWithCompletion:(void (^_Nonnull)(DJIRCCustomButtonTags *_Nullable tags,
                                                            NSError *_Nullable error))completion;


/**
 *  Set C1 button enable binding DJI Go app state. If it's enabled, when the user
 *  presses the C1 button, an alertView will pop up and ask if you want to open the
 *  DJI Go app. This feature only supports MFI certificated Remote Controller.
 *  @attention This feature will affect the user of DJI Go app, we suggest you to
 *  call this interface to enable the C1 binding feature when your application enter
 *  background. Otherwise, the C1 button will be unbound with DJI Go app forever.
 *  
 *  @param enabled Enable C1 button bind DJI Go app.
 *  @param completion Completion block.
 */
- (void)setC1ButtonBindingEnabled:(BOOL)enabled withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the C1 button enable binding DJI Go app state. This feature only supports
 *  MFI certificated Remote Controller.
 *  
 *  @param enabled The enable value.
 *  @param error Error retrieving the value.
 *  @param completion Completion block.
 */
- (void)getC1ButtonBindingEnabledWithCompletion:(void (^_Nonnull)(BOOL enabled, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark RC master and slave mode
/*********************************************************************************/


/**
 *  Query method to check if the Remote Controller supports master/slave mode.
 *  Master-slave mode is supported by the Inspire 1, Inspire 1 Pro, Matrice 100,
 *  Lightbridge 2 (including Matrice 600, Matrice 600 Pro, A3 and N3) and Inspire 2.
 *  Inspire 2 is using a new set of interfaces to control the master and slave
 *  connection.
 *   - Similar to other products, Inspire 2's remote controller also use set/get
 *  `DJIRCMode` to change the mode.
 *  - A slave remote controller can use `getMastersWithCompletion` and
 *  `connectToMasterWithID:authorizationCode:withCompletion` to join a master remote
 *  controller.
 *  - A master remote controller can use `setMasterAuthorizationCode:withCompletion`
 *  to change the authentication code.
 *  
 *  @return A boolean value.
 */
- (BOOL)isMasterSlaveModeSupported;


/**
 *  Sets the Remote Controller's mode. See the `DJIRCMode` enum for all possible
 *  Remote Controller modes. The master and slave modes are only supported for the
 *  Inspire 1, Inspire 1 Pro, M100, Lightbridge 2 (including Matrice 600, Matrice
 *  600 Pro, A3 and N3) and Inspire 2.
 *  
 *  @param mode Mode of type `DJIRCMode` to be set for the Remote Controller.
 *  @param completion Completion block.
 */
- (void)setMode:(DJIRCMode)mode withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the Remote Controller's mode. It is supported by the Inspire 1, Inspire 1
 *  Pro, Matrice 100, Lightbridge 2 (including Matrice 600, Matrice 600 Pro, A3 and
 *  N3) and Inspire 2.
 *  
 *  @param mode The Remote Controller's mode.
 *  @param error Error retrieving the value.
 *  @param completion Completion block.
 */
- (void)getModeWithCompletion:(void (^_Nonnull)(DJIRCMode mode,
                                                NSError *_Nullable error))completion;


/**
 *  Gets the Remote Controller's master and slave connection state. It is supported
 *  by the Inspire 1, Inspire 1 Pro, Matrice 100, Lightbridge 2 (including Matrice
 *  600, Matrice 600 Pro, A3 and N3) and Inspire 2.
 *  
 *  @param isConnected Yes if the master and slave remote controller are connected.
 *  @param error Error retrieving the value.
 *  @param completion Completion block.
 */
- (void)getMasterSlaveConnectionStateWithCompletion:(void (^_Nonnull)(BOOL isConnected,
                                                                      NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark RC master and slave mode - Slave RC methods
/*********************************************************************************/


/**
 *  Used by a slave Remote Controller to join a master Remote Controller. If the
 *  master Remote Controller accepts the request, the master Remote Controller will
 *  control the aircraft, and the slave Remote Controller will control the gimbal
 *  and/or be able to view the downlink video.
 *  
 *  @param credentials Include master's name and master's password.
 *  @param result The result of joining master remote controller.
 *  @param error Error retrieving the value.
 *  @param completion Completion block.
 */
- (void)connectToMasterWithCredentials:(DJIRCCredentials* _Nullable)credentials
                        withCompletion:(void (^_Nonnull)(DJIRCConnectToMasterResult result, NSError *_Nullable error))completion;


/**
 *  Returns the master Remote Controller's information, which includes the unique
 *  identifier, name, and password.
 *  
 *  @param credentials Include master's name and master's password.
 *  @param error Error retrieving the value.
 *  @param completion Remote execution result callback block.
 */
- (void)getConnectedMasterCredentials:(void (^_Nonnull)(DJIRCCredentials* _Nullable credentials, NSError *_Nullable error))completion;


/**
 *  Starts a search by slave Remote Controller for nearby master Remote Controllers.
 *  
 *  @param masters RC information of master remote controllers
 *  @param updateBlock updateBlock called every 1 seconds.
 *  @param completion Block that receives the information of available master remote controllers. `updateBlock` will be called repeated with 1 second interval once master searching is started successfully. It will stop when the searching is stopped either by the remote controller itself or by calling `stopMasterSearchingWithCompletion`.
 */
- (void)startMasterSearchingWithUpdateBlock:(void (^_Nonnull)(NSArray<DJIRCInformation *> *_Nonnull masters))updateBlock
                             withCompletion:(DJICompletionBlock)completion;


/**
 *  Used by a slave Remote Controller to stop the search for nearby master Remote
 *  Controllers.
 *  
 *  @param completion Remote execution result callback block.
 */
- (void)stopMasterSearchingWithCompletion:(DJICompletionBlock)completion;


/**
 *  Returns the state of the master Remote Controller search. The search is
 *  initiated by the Mobile Device, but performed by the Remote Controller.
 *  Therefore, if the Mobile Device's application crashes while a search is ongoing,
 *  this method can be used to let the new instance of the application understand
 *  the Remote Controller state.
 *  
 *  @param isStarted isStarted value.
 *  @param error Error retrieving the value.
 *  @param completion Remote execution result callback block.
 */
- (void)getMasterSearchingStateWithCompletion:(void (^_Nonnull)(BOOL isStarted, NSError *_Nullable error))completion;


/**
 *  Called by the slave Remote Controller to request gimbal control from the master
 *  Remote Controller. It is only supported by Inspire 1 and DJI Lightbridge 2.
 *  
 *  @param result DJIRCRequestGimbalControlResult object.
 *  @param error Error retrieving the value.
 *  @param completion Remote execution result callback block.
 */
- (void)requestLegacyGimbalControlWithCompletion:(void (^_Nonnull)(DJIRCRequestGimbalControlResult result, NSError *_Nullable error))completion;


/**
 *  Sets the Remote Controller's slave control mode.
 *  
 *  @param style Control mode to be set.
 *  @param completion Remote execution result error callback.
 */
-(void)setGimbalMappingStyle:(DJIRCGimbalMappingStyle)style withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the Remote Controller's slave control mode.
 *  
 *  @param style Mapping style.
 *  @param error Error state of asynchronous execution.
 *  @param completion The execution callback with the value(s) returned.
 */
-(void)getGimbalMappingStyleWithCompletion:(void (^_Nonnull)(DJIRCGimbalMappingStyle style, NSError *_Nullable error))completion;



/**
 *  Sets the Remote Controller's slave control mode.
 *  
 *  @param mapping The DJIRCGimbalMapping object.
 *  @param completion Remote execution result completion block.
 */
-(void)setCustomGimbalMapping:(DJIRCGimbalMapping *)mapping withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the Remote Controller's slave control mode.
 *  
 *  @param mapping The DJIRCGimbalMapping object.
 *  @param error Error retrieving the value
 *  @param completion Remote execution result completion block.
 */
-(void)getCustomGimbalMappingWithCompletion:(void (^_Nonnull)(DJIRCGimbalMapping *_Nullable mapping, NSError *_Nullable error))completion;


/**
 *  Called by the slave Remote Controller to set the gimbal's pitch, roll, and yaw
 *  speed with a range of [0, 100].
 *  
 *  @param speedCoefficient Speed to be set for gimbal's pitch, roll, and yaw, which should be in the range of [0, 100].
 *  @param completion Completion block.
 */
- (void)setGimbalControlSpeedCoefficient:(DJIRCGimbalControlSpeedCoefficient)speedCoefficient withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the current slave's gimbal's pitch, roll, and yaw speed with a range of [0,
 *  100].
 *  
 *  @param speedCoefficient The DJIRCGimbalControlSpeedCoefficient object.
 *  @param error Error retrieving the value.
 *  @param completion The completion block.
 */
- (void)getGimbalControlSpeedCoefficientWithCompletion:(void (^_Nonnull)(DJIRCGimbalControlSpeedCoefficient speedCoefficient, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark RC master and slave mode - Master RC methods
/*********************************************************************************/


/**
 *  Used by the current master Remote Controller to get all the slaves connected to
 *  it.
 *  
 *  @param slaveList The array of DJIRCInformation objects.
 *  @param error Error retrieving the value.
 *  @param completion The completion block.
 */
- (void)getSlaveListWithCompletion:(void (^_Nonnull)(NSArray<DJIRCInformation *> *_Nullable slaveList, NSError *_Nullable error))completion;


/**
 *  When a slave Remote Controller requests a master Remote Controller to control
 *  the gimbal, this method is used by a master Remote Controller to respond to the
 *  slave Remote Controller's request.
 *  
 *  @param response <code>YES</code> if the master Remote Controller agrees to give the slave Remote Controller the right to control the gimbal.
 *  @param rcID The slave Remote Controller's identifier.
 */
-(void) respondToRequestForGimbalControl:(BOOL)response fromSlaveRC:(uint32_t)rcID;

/*********************************************************************************/
#pragma mark RC Master and Slave Mode - Inspire 2 Only
/*********************************************************************************/


/**
 *  Sets the authorization code of a master remote controller. The slave remote
 *  controller needs to know the authorization code in order to join the master. A
 *  valid input is a string with 6 digits. The default value is "888888". It can
 *  only be called when the remote controller is in master mode.
 *  
 *  @param authorizationCode Authorization code to set.
 *  @param completion Completion block that receives the setter result.
 */
- (void)setMasterAuthorizationCode:(NSString*)authorizationCode
                    withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets a list of the nearby remote controllers in master mode. It can only be
 *  called when the remote controller is in slave mode.
 *  
 *  @param masters The array of master remote controllers.
 *  @param error Error retrieving the value.
 *  @param completion The completion block.
 */
- (void)getMastersWithCompletion:(void (^_Nonnull)(NSArray<NSString *> *_Nullable masters,
                                                   NSError *_Nullable error))completion;



/**
 *  Joins the master remote controller with the specific ID. If the remote
 *  controller has joined the same master before, the authorization code is not
 *  required until the master remote controller changes its authorization code. In
 *  this case, <code>code</code> can be `nil`. It can only be called when the remote
 *  controller is in slave mode.
 *  
 *  @param masterID Master remote controller with the specific ID to join.
 *  @param code Authorization code of the master remote controller.
 *  @param result The DJIRCJoinMasterResult object.
 *  @param error Error retrieving the value.
 *  @param completion The completion block.
 */
- (void)connectToMasterWithID:(NSString *_Nonnull)masterID
            authorizationCode:(NSString *_Nullable)code
               withCompletion:(void (^_Nonnull)(DJIRCConnectToMasterResult result, NSError *_Nullable error))completion;


/**
 *  Requests the gimbal control from the other remote controller. Different  from
 *  `requestLegacyGimbalControlWithCompletion`, the gimbal control  permission is
 *  transferred to the remote controller without the reply from  the master remote
 *  controller. The master remote controller can attain the  gimbal control back by
 *  calling the same method. It is only supported by  Inspire 2, M200 series and
 *  Cendence.
 *  
 *  @param completion The completion block.
 */
- (void)requestGimbalControlWithCompletion:(DJICompletionBlock)completion;

/*********************************************************************************/
#pragma mark Custom buttons (Cendence)
/*********************************************************************************/

/**
 *  `YES` if the remote controller supports customizable buttons. With the
 *  customizable buttons, the user can define the action bound to a button. When the
 *  button is clicked, the corresponding action can be received from the delegate
 *  method `remoteController:didUpdateButtonAction`.
 *    Only Cendence supports customizable buttons. This is distinct from remote
 *    controllers with buttons C1 and C2 that support custom tags and a binding to
 *  DJI Go.
 */
@property(nonatomic, readonly) BOOL isCustomizableButtonSupported;


/**
 *  Gets the names of the customizable button profile groups. The configurations of
 *  the customizable buttons are organized as groups. The maximum number of groups
 *  is 5 and each group contains 3 profiles. It is only valid when
 *  `isCustomizableButtonSupported` returns `YES`.
 *  
 *  @param groups The names of the customizable button profile groups.
 *  @param error Error if there is any.
 *  @param completion The completion block to receive the result.
 */
- (void)getButtonProfileGroupsWithCompletion:(void (^)(NSArray<NSString *> *_Nullable groups,
                                                       NSError *_Nullable error))completion;


/**
 *  Adds a group of customizable button profiles. Three default profiles will be
 *  created for the newly added group. The default profile can accessed through
 *  `defaultButtonActions`. It is only valid when `isCustomizableButtonSupported`
 *  returns `YES`.
 *  
 *  @param groupName The name of the group to be added.
 *  @param completion The completion block to receive the result.
 */
- (void)addButtonProfileGroup:(NSString *)groupName withCompletion:(DJICompletionBlock)completion;


/**
 *  Removes a group from the customizable button profiles. There must be at least
 *  one group, therefore, the removal of the last group will fail. It is only valid
 *  when `isCustomizableButtonSupported` returns `YES`.
 *  
 *  @param groupName The name of the group to be removed.
 *  @param completion The completion block to receive the result.
 */
- (void)removeButtonProfileGroup:(NSString *)groupName withCompletion:(DJICompletionBlock)completion;


/**
 *  Renames a profile group to a new name. It is only valid when
 *  `isCustomizableButtonSupported` returns `YES`.
 *  
 *  @param oldProfileName The name of the group to be renamed.
 *  @param newProfileName The new profile group name.
 *  @param completion The completion block to receive the result.
 */
- (void)renameButtonProfileGroup:(NSString *)oldProfileName to:(NSString *)newProfileName withCompletion:(DJICompletionBlock)completion;


/**
 *  Selects the customizable button profile group. The profile with 0 configIndex in
 *  the group will be applied. It is only valid when `isCustomizableButtonSupported`
 *  returns `YES`.
 *  
 *  @param groupName The name of the group to select.
 *  @param completion The completion block to receive the result.
 */
- (void)selectButtonProfileGroup:(NSString *)groupName withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the name of the selected customizable button profile group. It is only
 *  valid when `isCustomizableButtonSupported` returns `YES`.
 *  
 *  @param groupName The name of the selected profile group.
 *  @param error Error if there is any.
 *  @param completion Completion block to receive the result.
 */
- (void)getSelectedButtonProfileGroupWithCompletion:(void (^)(NSString *_Nullable groupName,
                                                              NSError *_Nullable error))completion;


/**
 *  Selects the customizable button profile with the specific index in the selected
 *  profile group. It is only valid when `isCustomizableButtonSupported` returns
 *  `YES`.
 *  
 *  @param profileIndex The index of the profile to select. The valid range is [0, 2].
 *  @param completion Completion block to receive the result.
 */
- (void)selectButtonProfile:(uint8_t)profileIndex withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the index of the selected button profile in the selected group. It is only
 *  valid when `isCustomizableButtonSupported` returns `YES`.
 *  
 *  @param profileIndex The index of the selected profile.
 *  @param error Error if there is any.
 *  @param completion The completion block to receive the result.
 */
- (void)getSelectedButtonProfileWithCompletion:(void (^_Nonnull)(uint8_t profileIndex,
                                                                 NSError *_Nullable error))completion;


/**
 *  Customizes the button configuration. The configuration will be applied to the
 *  remote controller immediately and will be stored into the selected profile of
 *  the selected profile group. It is only valid when
 *  `isCustomizableButtonSupported` returns `YES`.
 *  
 *  @param config The configuration to be set.
 *  @param completion Completion block if there is any.
 */
- (void)setButtonConfig:(DJIRCButtonConfiguration *)config withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the button configuration being applied to the remote controller. It is only
 *  valid when `isCustomizableButtonSupported` returns `YES`.
 *  
 *  @param config The current configuration.
 *  @param error Error if there is any.
 *  @param completion Completion block to receive the result.
 */
- (void)getButtonConfigWithCompletion:(void (^)(DJIRCButtonConfiguration *_Nullable config,
                                                NSError *_Nullable error))completion;


/**
 *  Resets the selected button configuration to the default settings. The default
 *  configuration will be applied to the remote controller and will be stored into
 *  the selected index of the activated user. It is only valid when
 *  `isCustomizableButtonSupported` returns `YES`.
 *  
 *  @param completion Completion block to receive the result.
 */
- (void)resetButtonConfigWithCompletion:(DJICompletionBlock)completion;


/**
 *  Customizes the action of a button. The new setting will be applied to the remote
 *  controller and will be stored into the selected profile index of the selected
 *  profile group. It is only valid when `isCustomizableButtonSupported` returns
 *  `YES`.
 *  
 *  @param button The customizable button.
 *  @param action The action to be bound to the button.
 *  @param completion Completion block to receive the result.
 */
- (void)customizeButton:(DJIRCCustomizableButton)button withAction:(DJIRCButtonAction)action withCompletion:(DJICompletionBlock)completion;


/**
 *  Fetches the customized action of a button in the selected configuration. It is
 *  only valid when `isCustomizableButtonSupported` returns `YES`.
 *  
 *  @param button The customizable button.
 *  @param action The customized action bound to the button.
 *  @param error Error if there is any.
 *  @param completion Completion block to receive the result.
 */
- (void)fetchCustomizedActionOfButton:(DJIRCCustomizableButton)button withCompletion:(void (^)(DJIRCButtonAction action,
                                                                                      NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Dual Gimbal Control
/*********************************************************************************/

/**
 *  Directs commands of the physical buttons on the remote controller (rotating
 *  gimbal, shoot photo, record video, etc.) to the specific gimbal, when there are
 *  multiple gimbals connected. If there is only one gimbal connected, this setting
 *  is reset to the remaining gimbal. Enabling
 *  `setAttitudeSynchronizationEnabled:withCompletion` will reset this setting to
 *  index 0 and when `setAttitudeSynchronizationEnabled:withCompletion` is enabled,
 *  index can only be set to 0. It is only supported by M210 and M210 RTK.
 *  
 *  @param index Index of the gimbal to receive the remote controller commands.
 *  @param completion Completion block to receive the result.
 */
- (void)setControllingGimbalIndex:(NSUInteger)index withCompletion:(DJICompletionBlock)completion;



/**
 *  The index of the gimbal that the remote controller is controlling. Commands of
 *  the physical buttons (rotating gimbal, shoot photo, record video, etc.) will be
 *  directed to the specific gimbal. If there is only one gimbal connected, this
 *  setting is reset to the remaining gimbal's index. Enabling
 *  `setAttitudeSynchronizationEnabled:withCompletion` will reset the value to 0.
 *  For product that supports only one gimbal, the value is always 0.
 *  
 *  @param index Get the index of the gimbal that the remote controller is controlling.
 *  @param error Error retrieving the value.
 *  @param completion Completion block to receive the result.
 */
- (void)getControllingGimbalIndexWithCompletion:(void (^)(NSUInteger index,
														  NSError *_Nullable error))completion;
@end

NS_ASSUME_NONNULL_END
