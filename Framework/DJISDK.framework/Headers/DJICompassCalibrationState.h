//
//  DJICompassCalibrationState.h
//  DJISDK
//
//  Copyright © 2016, DJI. All rights reserved.
//

#ifndef DJICompassCalibrationState_h
#define DJICompassCalibrationState_h


/**
 *  Compass Calibration Status.
 */
typedef NS_ENUM (NSUInteger, DJICompassCalibrationState){
 

    /**
     *  Normal state. Compass not in calibration.
     */
    DJICompassCalibrationStateNotCalibrating,
 

    /**
     *  Compass horizontal calibration. The user should hold the aircraft horizontally
     *  and rotate it 360 degrees.
     */
    DJICompassCalibrationStateHorizontal,
 

    /**
     *  Compass vertical calibration. The user should hold the aircraft vertically, with
     *  the nose pointed towards the  ground, and rotate the aircraft 360 degrees.
     */
    DJICompassCalibrationStateVertical,


    /**
     *  Compass calibration succeeded.
     */
    DJICompassCalibrationStateSuccessful,
 

    /**
     *  Compass calibration failed. Make sure there are no magnets or metal objects near
     *  the compass and retry.
     */
    DJICompassCalibrationStateFailed,
 

    /**
     *  Compass calibration status unknown.
     */
    DJICompassCalibrationStateUnknown,
};

#endif /* DJICompassCalibrationState_h */
