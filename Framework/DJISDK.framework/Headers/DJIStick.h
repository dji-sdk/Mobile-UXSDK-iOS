//
//  DJIStick.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#ifndef DJIStick_h
#define DJIStick_h


/**
 *  DJI hardware stick. For example, the joystick on a remote controller, or the
 *  gimbal control stick on a handheld controller.
 */
typedef struct {

    /**
     *  Get the stick's horizontal position value, the value it's in the range of [-660,
     *  660].
     *  
     *  @return An int value.
     */
    int horizontalPosition;

    /**
     *  Get the stick's vertical position value, the value it's in the range of [-660,
     *  660].
     *  
     *  @return An int value.
     */
    int verticalPosition;
} DJIStick;

#endif /* DJIStick_h */
