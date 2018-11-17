//
//  DJIBatteryKey.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import "DJIKey.h"

NS_ASSUME_NONNULL_BEGIN

EXTERN_KEY NSString *const DJIBatteryComponent;

//-----------------------------------------------------------------
#pragma mark DJIBatteryState Keys
//-----------------------------------------------------------------
EXTERN_KEY NSString *const DJIBatteryParamFullChargeCapacity;
EXTERN_KEY NSString *const DJIBatteryParamChargeRemaining;
EXTERN_KEY NSString *const DJIBatteryParamChargeRemainingInPercent;
EXTERN_KEY NSString *const DJIBatteryParamVoltage;
EXTERN_KEY NSString *const DJIBatteryParamCurrent;
EXTERN_KEY NSString *const DJIBatteryParamLifetimeRemainingInPercent;
EXTERN_KEY NSString *const DJIBatteryParamTemperature;
EXTERN_KEY NSString *const DJIBatteryParamNumberOfDischarges;
EXTERN_KEY NSString *const DJIBatteryParamIsBeingCharged;
EXTERN_KEY NSString *const DJIBatteryParamCellVoltageLevel;
EXTERN_KEY NSString *const DJIBatteryParamIsInSingleBatteryMode;

//-----------------------------------------------------------------
#pragma mark Properties
//-----------------------------------------------------------------
EXTERN_KEY NSString *const DJIBatteryParamNumberOfCells;
EXTERN_KEY NSString *const DJIBatteryParamIsSmartBattery;

//-----------------------------------------------------------------
#pragma mark Setter & Getters
//-----------------------------------------------------------------
EXTERN_KEY NSString *const DJIBatteryParamWarningInformationRecords;
EXTERN_KEY NSString *const DJIBatteryParamLatestWarningRecord;
EXTERN_KEY NSString *const DJIBatteryParamCellVoltages;
EXTERN_KEY NSString *const DJIBatteryParamPairState;
EXTERN_KEY NSString *const DJIBatteryParamSelfDischargeInDays;
EXTERN_KEY NSString *const DJIBatteryParamLevel1CellVoltageThreshold;
EXTERN_KEY NSString *const DJIBatteryParamLevel2CellVoltageThreshold;
EXTERN_KEY NSString *const DJIBatteryParamLevel1CellVoltageBehavior;
EXTERN_KEY NSString *const DJIBatteryParamLevel2CellVoltageBehavior;
EXTERN_KEY NSString *const DJIBatteryParamHeatingState;

//-----------------------------------------------------------------
#pragma mark Actions
//-----------------------------------------------------------------
EXTERN_KEY NSString *const DJIBatteryParamPairBatteries;

//-----------------------------------------------------------------
#pragma mark Aggregation
//-----------------------------------------------------------------
EXTERN_KEY NSString *const DJIBatteryParamAggregationState;


/**
 *  `DJIBatteryKey` is a key dedicated to accessing Battery related attributes.
 */
@interface DJIBatteryKey : DJIKey

@end

NS_ASSUME_NONNULL_END
