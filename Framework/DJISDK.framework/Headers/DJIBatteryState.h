//
//  DJIBatteryState.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 *  Battery cell voltage level threshold. Different thresholds will initiate
 *  different aircraft behaviors or operations. Level 3 is the lowest level. It is
 *  only supported when the connected product is stand-alone A3 and N3.
 */
typedef NS_ENUM (uint8_t, DJIBatteryCellVoltageLevel){
 

    /**
     *  The cell voltage is at a safe level; the aircraft can fly normally.
     */
    DJIBatteryCellVoltageLevel0,
 

    /**
     *  The cell voltage is equal to or lower than threshold Level 1. At this level the
     *  Level 1 operation will be executed. The threshold value and operation for Level
     *  1 can be configured by the user.
     */
    DJIBatteryCellVoltageLevel1,
 

    /**
     *  The cell voltage is equal to or lower than threshold Level 2. At this level the
     *  Level 2 operation will be executed. The threshold value and operation for Level
     *  2 can be configured by the user.
     */
    DJIBatteryCellVoltageLevel2,
 

    /**
     *  The cell voltage is equal to or lower than Level 3. At this level, the aircraft
     *  will start landing. The threshold for Level 3 cannot be configured by the user
     *  and is fixed at 3400mV.
     */
    DJIBatteryCellVoltageLevel3,


    /**
     *  The cell voltage level is unknown.
     */
    DJIBatteryCellVoltageLevelUnknown = 0xFF
};


/**
 *  Defines aircraft's behavior when the cell voltage is low.
 */
typedef NS_ENUM (uint8_t, DJIBatteryLowVoltageBehavior){
    

    /**
     *  LED lights go into warning mode.
     */
    DJIBatteryLowVoltageBehaviorFlashLED,
    

    /**
     *  Return-to-Home.
     */
    DJIBatteryLowVoltageBehaviorGoHome,
    

    /**
     *  Land aircraft immediately.
     */
    DJIBatteryLowVoltageBehaviorLand,


    /**
     *  Unknown.
     */
    DJIBatteryLowVoltageBehaviorUnknown = 0xFF
};


/**
 *  Battery pairing state for batteries that can be paired.
 */
typedef NS_ENUM (uint8_t, DJIBatteryPairingState){
 

    /**
     *  The batteries didn't match; they're not paired.
     */
    DJIBatteryPairingStateUnpaired,
 

    /**
     *  Batteries are paired.
     */
    DJIBatteryPairingStatePaired,
 

    /**
     *  Can't get the pair state or the batteries.
     */
    DJIBatteryPairingStateUnknown,
};


/**
 *  Provides the self-heating state for the battery. When the temperature of the
 *  battery is below a threshold, it will warm up automatically. For Mavic 2
 *  Enterprise,  the self-heating is triggered when the temperature is lower than 6
 *  Celsius degrees. When the  temperature reaches 8 Celsius degrees, the battery
 *  will start to preserve the temperature and  maintain it between 6 Celsius
 *  degrees and 8 Celsius degrees.
 */
typedef NS_ENUM (uint8_t, DJIBatterySelfHeatingState) {

    /**
     *  The auto heating feature is idle.
     */
    DJIBatterySelfHeatingStateIdle,
    

    /**
     *  The battery is warming itself up automatically.
     */
    DJIBatterySelfHeatingStateWarmingUp,
    

    /**
     *  The battery is preserving its temperature. For Mavic 2 Enterprise,  the
     *  temperature will be maintained between 6 Celsius degrees and 8 Celsius degrees.
     */
    DJIBatterySelfHeatingStatePreserving,
    

    /**
     *  Unknown.
     */
    DJIBatterySelfHeatingStateUnknown = 0xFF
};

/*********************************************************************************/
#pragma mark - DJIBatteryState
/*********************************************************************************/


/**
 *  Supported by both smart and non-smart batteries, this class keeps track of the
 *  real-time state of the battery. Non-smart batteries only support the following
 *  properties:
 *   - When the connected product is A3 and N3, only `voltage` and
 *  `cellVoltageLevel` are valid.
 *   - When the connected product is A2, only `voltage` is valid.
 */
@interface DJIBatteryState : NSObject


/**
 *  Returns the total amount of energy, in mAh (milliamp hours), stored in the
 *  battery when the battery is fully charged. The energy of the battery at full
 *  charge changes over time as the battery continues to get used. Over time, as the
 *  battery continues to be recharged, the value of `fullChargeCapacity` will
 *  decrease.
 */
@property(nonatomic, readonly) NSUInteger fullChargeCapacity;


/**
 *  Returns the remaining energy stored in the battery in mAh (milliamp hours).
 */
@property(nonatomic, readonly) NSUInteger chargeRemaining;


/**
 *  Returns the percentage of battery energy left with range [0, 100].
 */
@property(nonatomic, readonly) NSUInteger chargeRemainingInPercent;


/**
 *  Returns the current battery voltage (mV).
 */
@property(nonatomic, readonly) NSUInteger voltage;


/**
 *  Returns the real time current draw of the battery (mA). A negative value means
 *  the battery is being discharged, and a positive value means it is being charged.
 */
@property(nonatomic, readonly) NSInteger current;


/**
 *  Returns the battery's remaining lifetime as a percentage, with range [0, 100]. A
 *  new battery will be close to 100%. As a battery experiences charge/discharge
 *  cycles, the value will go down. In unsupported products, this value will always
 *  be 0.  These products are Phantom 4 Pro, Inspire 2, and Phantom 4 Advanced.
 */
@property(nonatomic, readonly) NSUInteger lifetimeRemaining;


/**
 *  Returns the battery's temperature, in Celsius, with range [-128, 127] degrees.
 */
@property(nonatomic, readonly) double temperature;


/**
 *  Returns the total number of discharges the battery has gone through over its
 *  lifetime. The total number of discharges includes discharges that happen through
 *  normal use and discharges that are manually set.
 */
@property(nonatomic, readonly) NSUInteger numberOfDischarges;


/**
 *  Current cell voltage level of the battery. It is only supported when the
 *  connected product is stand-alone A3 or N3.
 */
@property(nonatomic, readonly) DJIBatteryCellVoltageLevel cellVoltageLevel; 


/**
 *  `YES` if the battery is being charged.
 */
@property(nonatomic, readonly) BOOL isBeingCharged;


/**
 *  `YES` if only one battery is inserted on the the right or starboard side of the
 *  aircraft. The aircraft can still take off but the flight time will be shorter.
 *  It is only supported by Inspire 2: Inspire 2 must always have a battery in the
 *  right/starboard slot.
 */
@property(nonatomic, readonly) BOOL isInSingleBatteryMode;


/**
 *  The state of the battery's auto heating feature. It is
 *  `DJIBatterySelfHeatingStateUnknown`  if the battery does not support this
 *  feature.
 */
@property(nonatomic, readwrite) DJIBatterySelfHeatingState selfHeatingState;

@end

/*********************************************************************************/
#pragma mark - DJIBatteryWarningRecord
/*********************************************************************************/


/**
 *  Used to keep a record of any unusual battery statues in the past 30 discharges.
 *  For all the properties below, monitor these values frequently to ensure the
 *  battery's state is normal. If any of the properties below indicate there is an
 *  issue with the battery, notifying the user is recommended. </br></br> NOTE: No
 *  automatic action will be taken if any of the properties below return `YES`,
 *  which is why it is imperative that the user is notified of the issue.
 */
@interface DJIBatteryWarningRecord : NSObject


/**
 *  `YES` if the battery should be discharged due to a current overload.
 */
@property(nonatomic, readonly) BOOL isCurrentOverloaded;


/**
 *  `YES` if the battery has overheated.
 */
@property(nonatomic, readonly) BOOL isOverHeated;


/**
 *  `YES` if the battery has experienced a temperature that is too low.
 */
@property(nonatomic, readonly) BOOL isLowTemperature;


/**
 *  `YES` if the battery has been or is short circuited.
 */
@property(nonatomic, readonly) BOOL isShortCircuited;


/**
 *  `YES` if the battery has been configured to be discharged over a specific number
 *  of days. Once the battery is fully recharged, the battery will again discharge
 *  over the number of days set here. This process is cyclical.
 */
@property(nonatomic, readonly) BOOL isCustomDischargeEnabled;


/**
 *  Returns the index at which one of the cells in the battery is below the normal
 *  voltage. The first cell has an index of 0.  -1 represents no battery cells under
 *  voltage. Phantom Series Aircraft have four cell batteries. Inspire series
 *  aircraft and the M100 have 6 cell batteries.
 */
@property(nonatomic, readonly) int lowVoltageCellIndex;


/**
 *  Returns the index at which one of the cells in the battery is damaged. The first
 *  cell has an index of 0. -1 represents no damaged battery cells. Phantom 3
 *  aircraft have 4 cell batteries. Inspire series aircraft and the M100 have 6 cell
 *  batteries.
 */
@property(nonatomic, readonly) int damagedCellIndex;

@end

/*********************************************************************************/
#pragma mark - DJIBatteryOverview
/*********************************************************************************/


/**
 *  Provides an overview of a battery when aircraft is using multiple batteries.
 */
@interface DJIBatteryOverview : NSObject


/**
 *  Index of the battery. Index starts from 0. For Matrice 600, the number 1 battery
 *  compartment relates to index 0.
 */
@property(nonatomic, readonly) NSUInteger index;


/**
 *  `YES` if the battery is currently connected to the aircraft.
 */
@property(nonatomic, readonly) BOOL isConnected;


/**
 *  The remaining percentage energy of the battery with range [0, 100].
 */
@property(nonatomic, readonly) NSInteger chargeRemainingInPercent;

@end

/*********************************************************************************/
#pragma mark - DJIBatteryAggregationState
/*********************************************************************************/


/**
 *  Provides a real time summary of the aggregated battery system.
 */
@interface DJIBatteryAggregationState : NSObject


/**
 *  The number of currently connected batteries.
 */
@property(nonatomic, readonly) NSUInteger numberOfConnectedBatteries;


/**
 *  Returns the overview of batteries in the battery group. When a battery is not
 *  connected, the `isConnected` property is `NO` and the `chargeRemainingInPercent`
 *  is zero. For Matrice 600, there are 6 elements in this array.
 */
@property(nonatomic, readonly) NSArray<DJIBatteryOverview *> *_Nullable batteryOverviews;


/**
 *  Returns the current voltage (mV) provided by the battery group.
 */
@property(nonatomic, readonly) NSInteger voltage;


/**
 *  Returns the real time current draw through the batteries. A negative value means
 *  the batteries are being discharged.
 */
@property(nonatomic, readonly) NSInteger current;


/**
 *  Returns the the total amount of energy, in mAh (milliamp hours), stored in the
 *  batteries when the batteries are fully charged.
 */
@property(nonatomic, readonly) NSInteger fullChargeCapacity;


/**
 *  Returns the remaining energy stored in the batteries in mAh (milliamp hours).
 */
@property(nonatomic, readonly) NSInteger chargeRemaining;


/**
 *  Returns the percentage of energy left in the battery group with range [0,100].
 */
@property(nonatomic, readonly) NSInteger chargeRemainingInPercent;


/**
 *  Returns the highest temperature (in Celsius) among the batteries in the group,
 *  with range [-128, 127] degrees.
 */
@property(nonatomic, readonly) NSInteger highestTemperature;


/**
 *  `YES` if one of the batteries in the group is disconnected. When `YES`, the
 *  aircraft is not allowed to take off.
 */
@property(nonatomic, readonly) BOOL isAnyBatteryDisconnected;


/**
 *  `YES` if there is significant difference between the voltage (above 1.5V) of two
 *  batteries. When  `YES`, the aircraft is not allowed to take off.
 */
@property(nonatomic, readonly) BOOL isVoltageDifferenceDetected;


/**
 *  `YES` if one of the batteries in the group has cells with low voltage. When
 *  `YES`, the aircraft is not allowed to take off.
 */
@property(nonatomic, readonly) BOOL isLowCellVoltageDetected;


/**
 *  `YES` if one of the batteries in the group has damaged cells. When `YES`, the
 *  aircraft is not allowed to take off.
 */
@property(nonatomic, readonly) BOOL isCellDamaged;


/**
 *  `YES` if one of the batteries in the group has a firmware version different from
 *  the others. When it is `YES`, the aircraft is not allowed to take off.
 */
@property(nonatomic, readonly) BOOL isFirmwareDifferenceDetected;

@end
