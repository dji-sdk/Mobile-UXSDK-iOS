//
//  DJIIMUState.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*********************************************************************************/
#pragma mark - DJIIMUStatus
/*********************************************************************************/


/**
 *  The different orientations the aircraft needs for a multi-orientation IMU
 *  calibration.
 */
typedef NS_ENUM(uint8_t, DJIIMUCalibrationOrientation) {
 

    /**
     *  The front/nose of the aircraft should be pointed down.
     */
    DJIIMUCalibrationOrientationNoseDown,
 

    /**
     *  The back/tail of the aircraft should be pointed down.
     */
    DJIIMUCalibrationOrientationTailDown,
 

    /**
     *  The right/starboard side of the aircraft should be pointed down.
     */
    DJIIMUCalibrationOrientationRightDown,
 

    /**
     *  The left/port side of the aircraft should be pointed down.
     */
    DJIIMUCalibrationOrientationLeftDown,
 

    /**
     *  The bottom/underbelly of the aircraft should be pointed down.
     */
    DJIIMUCalibrationOrientationBottomDown,
 

    /**
     *  The top of the aircraft should be pointed down.
     */
    DJIIMUCalibrationOrientationTopDown
};


/**
 *  IMU calibration status for the current aircraft orientation.
 */
typedef NS_ENUM(uint8_t, DJIIMUOrientationCalibrationState) {
 

    /**
     *  Calibration of current aircraft orientation is in progress.
     */
    DJIIMUOrientationCalibrationStateCalibrating,
 

    /**
     *  Calibration of current aircraft orientation is done. The orientation will be
     *  added  to `orientationsCalibrated`. The aircraft should be  rotated to a
     *  remaining orientation  in `orientationsToCalibrate`.
     */
    DJIIMUOrientationCalibrationStateCompleted,


    /**
     *  Unknown. Used by products that do not require IMU multi-orientation calibration.
     */
    DJIIMUOrientationCalibrationStateUnknown = 0xFF,
};


/**
 *  This class is used to lead the user through an IMU calibration for products that
 *  require calibration at multiple  orientations. An example workflow is:
 *    <ol> - Direct the user to orient the aircraft in one of the uncalibrated
 *  orientations in `orientationsToCalibrate`.
 *   - Monitor `state`  until `DJIIMUOrientationCalibrationStateCalibrating` turns
 *  to `DJIIMUOrientationCalibrationStateCompleted`.
 *   - Repeat until `orientationsToCalibrate` is empty.
 *   </ol>
 */
@interface DJIIMUMultipleOrientationCalibrationHint : NSObject


/**
 *  An array with the aircraft orientations that have not been calibrated yet. Each
 *  element  is a  'NSNumber' instance with a `DJIIMUCalibrationOrientation` enum
 *  value.
 */
@property(nonatomic, readonly) NSArray<NSNumber *> *orientationsToCalibrate;


/**
 *  An array with the aircraft orientations that have been calibrated. Each element
 *  is  a  'NSNumber' instance with a `DJIIMUCalibrationOrientation` enum value.
 */
@property(nonatomic, readonly) NSArray<NSNumber *> *orientationsCalibrated;


/**
 *  The calibration status of the current orientation.
 */
@property(nonatomic, readonly) DJIIMUOrientationCalibrationState state;

@end


/**
 *  Enum for IMU calibration Status.
 */
typedef NS_ENUM (uint8_t, DJIIMUCalibrationState){
 

    /**
     *  IMU not in calibration; no calibration is executing.
     */
    DJIIMUCalibrationStateNone,
 

    /**
     *  IMU calibration is in progress.
     */
    DJIIMUCalibrationStateCalibrating,
 

    /**
     *  IMU calibration succeeded.
     */
    DJIIMUCalibrationStateSuccessful,
 

    /**
     *  IMU calibration failed.
     */
    DJIIMUCalibrationStateFailed,
    

    /**
     *  Unknown calibration status.
     */
    DJIIMUCalibrationStateUnknown = 0xFF,
};


/**
 *  Enum for IMU calibration Status.
 */
typedef NS_ENUM (NSUInteger, DJIIMUSensorState) {


    /**
     *  The IMU sensor is disconnected from the flight controller.
     */
    DJIIMUSensorStateDisconnected,
 

    /**
     *  The IMU sensor is calibrating
     */
    DJIIMUSensorStateCalibrating,
 

    /**
     *  Calibrate of the IMU sensor failed.
     */
    DJIIMUSensorStateCalibrationFailed,
 

    /**
     *  The IMU sensor has a data exception. Calibrate the IMU and restart the aircraft.
     *  If afterwards the status still  exists, you may need to contact DJI for further
     *  assistance.
     */
    DJIIMUSensorStateDataException,
 

    /**
     *  The IMU sensor is warming up.
     */
    DJIIMUSensorStateWarmingUp,
 

    /**
     *  The IMU sensor is not static; the aircraft may not be stable enough to calculate
     *  sensor data correctly.
     */
    DJIIMUSensorStateInMotion,
 

    /**
     *  The IMU's bias value is normal; the aircraft can safely take off.
     */
    DJIIMUSensorStateNormalBias,
 

    /**
     *  The IMU's bias value is medium; the aircraft can safely take off.
     */
    DJIIMUSensorStateMediumBias,
 

    /**
     *  The IMU's bias value is large; the aircraft cannot take off. IMU calibration is
     *  needed.
     */
    DJIIMUSensorStateLargeBias,
 

    /**
     *  The IMU sensor's status is unknown.
     */
    DJIIMUSensorStateUnknown = 0xFF,

};

/*********************************************************************************/
#pragma mark - DJIInertialMeasurementUnitState
/*********************************************************************************/


/**
 *  This class provides the inertial measurement unit's (IMU) state information.
 */
@interface DJIIMUState : NSObject


/**
 *  The IMU's ID. Starts at 0.
 */
@property(nonatomic, readonly) NSUInteger index;


/**
 *  The gyroscopic sensor's state value.
 */
@property(nonatomic, readonly) DJIIMUSensorState gyroscopeState;


/**
 *  The accelerometers sensor state value.
 */
@property(nonatomic, readonly) DJIIMUSensorState accelerometerState;


/**
 *  The IMU's calibration progress, its range being [1, 100]. If the IMU is  not
 *  calibrating, the value of the calibration progress will be -1.
 */
@property(nonatomic, readonly) NSInteger calibrationProgress;


/**
 *  The status of the IMU's calibration.
 */
@property(nonatomic, readonly) DJIIMUCalibrationState calibrationState;


/**
 *  For products that require the user to orient the aircraft during the IMU
 *  calibration, this method can be used to  inform the user when each orientation
 *  is done. It is supported by flight controller firmware 3.2.0.0 or above.
 */
@property(nonatomic, readonly, nullable) DJIIMUMultipleOrientationCalibrationHint *multipleOrientationCalibrationHint;

@end

NS_ASSUME_NONNULL_END

