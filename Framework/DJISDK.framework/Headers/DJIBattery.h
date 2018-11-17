//
//  DJIBattery.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIBaseComponent.h>
#import <DJISDK/DJIBatteryState.h>

NS_ASSUME_NONNULL_BEGIN

@class DJIBattery;

/*********************************************************************************/
#pragma mark - DJIBatteryDelegate
/*********************************************************************************/


/**
 *  This protocol provides a delegate method to update the battery's current state.
 */
@protocol DJIBatteryDelegate <NSObject>

@optional


/**
 *  Delegate to update battery state.
 *  
 *  @param battery Battery having an updated state.
 *  @param state The battery's state.
 */
- (void)battery:(DJIBattery *_Nonnull)battery didUpdateState:(DJIBatteryState *_Nonnull)state;

@end

/*********************************************************************************/
#pragma mark - DJIBatteryAggregationDelegate
/*********************************************************************************/


/**
 *  This protocol provides a delegate method to update the current aggregated
 *  battery state.
 */
@protocol DJIBatteryAggregationDelegate <NSObject>

@optional


/**
 *  Callback to update aggregated battery state.
 *  
 *  @param state The aggregated battery state.
 */
- (void)batteriesDidUpdateState:(DJIBatteryAggregationState *_Nonnull)state;

@end

/*********************************************************************************/
#pragma mark - DJIBattery
/*********************************************************************************/


/**
 *  This class manages information and real-time status of the connected product's
 *  batteries. This object is available from the `DJIAircraft` or `DJIHandheld`
 *  object which is a subclass of `DJIBaseProduct`.
 */
@interface DJIBattery : DJIBaseComponent


/**
 *  Delegate that receives the updated state pushed by the battery.
 *  
 *  @param delegate The delegate that will receive the aggregation information.
 */
+ (void)setAggregationDelegate:(id<DJIBatteryAggregationDelegate>_Nullable)delegate;


/**
 *  Gets the delegate that receives the battery aggregation state. It is only useful
 *  when the aircraft has multiple batteries.
 *  
 *  @return The delegate setup to receive battery aggregation information.
 */
+ (id<DJIBatteryAggregationDelegate>_Nullable)aggregationDelegate;


/**
 *  Returns the number of battery cells.
 */
@property(nonatomic, readonly) NSUInteger numberOfCells;


/**
 *  Delegate that receives the updated state pushed by the battery.
 */
@property(nonatomic, weak) id<DJIBatteryDelegate> delegate;


/**
 *  `YES` if the battery is a smart battery. When the connected battery is a DJI
 *  smart battery, more information can be obtained by communicating with the
 *  battery.
 *  
 *  @return <code>Yes</code>> if battery is smart battery.
 */
- (BOOL)isSmartBattery;

/*********************************************************************************/
#pragma mark Get battery properties and status
/*********************************************************************************/


/**
 *  Gets the battery's history, which is kept for 30 days. The 'records' variable in
 *  the block stores objects of type `DJIBatteryWarningRecord`.
 *  
 *  @param records Warning records.
 *  @param error Error retrieving the value.
 *  @param completion Remote execution result callback block.
 */
- (void)getWarningRecordsWithCompletion:(void (^_Nonnull)(NSArray<DJIBatteryWarningRecord *> *_Nullable records, NSError *_Nullable error))completion;


/**
 *  Gets the battery's most recent warning record. Anytime the battery experiences a
 *  significant exception, it will get recorded as a warning record.
 *  
 *  @param completion Asynchronous execution result block that contains the latest warning record.
 *  @param record Warning record.
 *  @param error Error retrieving the value.
 */
- (void)getLatestWarningRecordWithCompletion:(void (^_Nonnull)(DJIBatteryWarningRecord *_Nullable record, NSError *_Nullable error))completion;


/**
 *  Gets the battery's cell voltages. There will be a voltage for each cell in the
 *  battery.
 *  
 *  @param cellVoltages Array of battery cell voltages. For example, the Inspire 1 has a 6 cell battery and therefore will have a 6 element array.
 *  @param error Error retrieving the value.
 *  @param completion Asynchronous execution result block.
 */
- (void)getCellVoltagesWithCompletion:(void (^_Nonnull)(NSArray<NSNumber *> *_Nullable cellVoltages,
                                                        NSError *_Nullable error))completion;


/**
 *  A battery's full charge capacity reduces a little every time it goes through a
 *  discharge and recharge cycle. Therefore, older batteries that have gone through
 *  many cycles will have lower full charge capacity than newer batteries. When
 *  multiple batteries are used simultaneously in a product, the aggregate full
 *  charge capacity will be limited by the battery with the lowest full charge
 *  capacity.
 *   To optimize the amount of energy delivered by a battery over its lifetime to a
 *  product, batteries should be matched or paired with other batteries of similar
 *  full charge capacity. The operational challenges of always using paired
 *  batteries can be alleviated using the battery pairing interfaces.
 *  This method will pair two batteries by recording the aggregate of their serial
 *  numbers in each of their firmwares. `getPairingStateWithCompletion` can then be
 *  used to determine if the installed battery combination is a previously assigned
 *  pair or not. Batteries can be repaired.
 *  
 *  @param completion Completion block that receives the execution result.
 */
- (void)pairBatteriesWithCompletion:(DJICompletionBlock)completion;


/**
 *  A battery's full charge capacity reduces a little every time it goes through a
 *  discharge and recharge cycle. Therefore, older batteries that have gone through
 *  many cycles will have lower full charge capacity than newer batteries. When
 *  multiple batteries are used simultaneously in a product, the aggregate full
 *  charge capacity will be limited by the battery with lowest full charge capacity.
 *   To optimize the amount of energy delivered by a battery over its lifetime to a
 *  product, batteries should be matched or paired with other batteries of similar
 *  full charge capacity. The operational challenges of always using paired
 *  batteries can be alleviated using the battery pairing interfaces. This method
 *  can then be used to determine if the installed battery combination is a
 *  previously assigned pair or not.
 *  
 *  @param completion Block that receives the pairing state.
 *  @param pairingState Pairing state.
 *  @param error Error retrieving the value.
 */
- (void)getPairingStateWithCompletion:(void (^_Nonnull)(DJIBatteryPairingState pairingState, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Battery self discharge
/*********************************************************************************/


/**
 *  Smart batteries can be setup to automatically discharge over a custom period of
 *  time. This method sets the battery's self discharge period in days with range
 *  [1, 10]. For Inspire 2 and M200 series products, the max range value  can be 20.
 *  Not supported by non-smart batteries, Spark and the Osmo series.
 *  
 *  @param days Day for self-discharge
 *  @param completion Asynchronous execution result block.
 */
- (void)setSelfDischargeInDays:(uint8_t)days withCompletion:(DJICompletionBlock)completion;


/**
 *  Smart batteries can be setup to automatically discharge over a custom period of
 *  time. This method gets the battery's self discharge period in days with range
 *  [1, 10]. For Inspire 2 and M200 series products, the max range value  can be 20.
 *  Not supported by non-smart batteries and the Osmo series.
 *  
 *  @param completion Asynchronous execution result block that contains the number of days to discharge over.
 *  @param days Number of days to discharge over.
 *  @param error Error retrieving the value.
 */
- (void)getSelfDischargeInDaysWithCompletion:(void (^_Nonnull)(uint8_t days, NSError *_Nullable error))completion;

/*********************************************************************************/
#pragma mark Stand-alone A3 Non-smart Battery
/*********************************************************************************/


/**
 *  When the connected battery is not a smart battery, the number of cells needs to
 *  be set manually. The flight controller uses the number of cells and the cell
 *  voltage threshold to determine if the aircraft should go home or land. The valid
 *  range is [3, 12] cells.
 *  
 *  @param numberOfCells Number of cells inside the battery.
 *  @param completion Asynchronous execution result block.
 */
- (void)setNumberOfCells:(NSUInteger)numberOfCells withCompletion:(DJICompletionBlock)completion;


/**
 *  Sets the Level 1 cell voltage threshold in mV. When the cell voltage of the
 *  battery crosses below the threshold, Level 1 behavior will be executed. The
 *  valid range is [3600, 4000] mV. When the new value is not 100 mV higher than the
 *  Level 2 cell voltage threshold, the Level 2 threshold will be set to (new value
 *  - 100) mV.
 *  
 *  @param voltage Level 1 cell voltage threshold to set in mV.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setLevel1CellVoltageThreshold:(NSUInteger)voltage withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the Level 1 cell voltage threshold in mV. When the cell voltage of the
 *  battery crosses below the threshold, Level 1 behavior will be executed. The
 *  valid range is [3600, 4000] mV.
 *  
 *  @param completion Asynchronous execution result block that contains the voltage threshold.
 *  @param voltage Voltage in mV
 *  @param error Error retrieving the value.
 */
- (void)getLevel1CellVoltageThresholdWithCompletion:(void (^_Nonnull)(NSUInteger voltage, NSError *_Nullable error))completion;


/**
 *  Sets the Level 2 cell voltage threshold in mV. When the cell voltage of the
 *  battery crosses below the threshold, Level 2 behavior will be executed. The
 *  valid range is [3500, 3800] mV and must be at least 100 mV lower than the Level
 *  1 voltage threshold.
 *  
 *  @param voltage Level 2 cell voltage threshold to set in mV.
 *  @param completion Asynchronous execution result block.
 */
- (void)setLevel2CellVoltageThreshold:(NSUInteger)voltage withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the Level 2 cell voltage threshold in mV. When the cell voltage of the
 *  battery crosses below the threshold, Level 2 behavior will be executed.
 *  
 *  @param completion Asynchronous execution result block that contains the voltage threshold.
 *  @param voltage Voltage in mV
 *  @param error Error retrieving the value.
 */
- (void)getLevel2CellVoltageThresholdWithCompletion:(void (^_Nonnull)(NSUInteger voltage, NSError *_Nullable error))completion;


/**
 *  Sets the behavior that will be executed when the cell voltage crosses under the
 *  Level 1 threshold. It can only be set when the motors are off.
 *  
 *  @param behavior Level 1 behavior.
 *  @param completion Completion block that receives the setter execution result.
 */
- (void)setLevel1CellVoltageBehavior:(DJIBatteryLowVoltageBehavior)behavior
                      withCompletion:(DJICompletionBlock)completion;


/**
 *  Gets the behavior that will be executed when the cell voltage crosses under the
 *  Level 1 threshold.
 *  
 *  @param completion Asynchronous execution result block that contains the voltage threshold behavior.
 *  @param behavior Aircraft behavior when voltage threshold is crossed.
 *  @param error Error retrieving the value.
 */
- (void)getLevel1CellVoltageBehaviorWithCompletion:(void (^_Nonnull)(DJIBatteryLowVoltageBehavior behavior, NSError *_Nullable error))completion;


/**
 *  Sets the operation that will be executed when the cell voltage crosses under
 *  Level 2 threshold. It can only be set when motors are off.
 *  
 *  @param behavior Level 2 behavior.
 *  @param completion Asynchronous execution result block.
 */
- (void)setLevel2CellVoltageBehavior:(DJIBatteryLowVoltageBehavior)behavior
                      withCompletion:(DJICompletionBlock)completion;


/**
 *  Sets the behavior that will be executed when the cell voltage crosses under the
 *  Level 2 threshold.
 *  
 *  @param completion Asynchronous execution result block that contains the voltage threshold behavior.
 *  @param behavior Aircraft behavior when voltage threshold is crossed.
 *  @param error Error retrieving the value.
 */
- (void)getLevel2CellVoltageBehaviorWithCompletion:(void (^_Nonnull)(DJIBatteryLowVoltageBehavior behavior, NSError *_Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
