//
//  DJIAppActivationSystemTypes.h
//  DJISDK
//
//  Copyright © 2017 DJI. All rights reserved.
//

#ifndef DJIAppActivationSystemTypes_h
#define DJIAppActivationSystemTypes_h


/**
 *  The aircraft's binding state.
 */
typedef NS_ENUM (NSUInteger, DJIAppActivationAircraftBindingState) {


    /**
     *  The binding state of the aircraft is not yet determined. The aircraft will only
     *  be in this  state until DJI Go or a DJI Mobile SDK based application rights the
     *  binding information to  the aircraft. Binding is only required if the user is in
     *  China. If the user is not in China,  then this state will become
     *  `DJIAppActivationAircraftBindingStateNotRequired` after the  country code check
     *  is complete. If country code check has been disabled, the user will need  to use
     *  DJI Go to move to the `DJIAppActivationAircraftBindingStateNotRequired` state.
     *  In  this state, the aircraft will have the 30m height and 50m radius limitation.
     */
    DJIAppActivationAircraftBindingStateInitial,

    /**
     *  The aircraft is not currently bound, and needs to be (as it is in China). In
     *  this state, the  aircraft will have 30m max flight height and 50m max flight
     *  distance limitation. User should  finish the one-off binding process with DJI Go
     *  to remove the flight limitation.
     */
    DJIAppActivationAircraftBindingStateUnbound,
    

    /**
     *  The aircraft is flying inside China and is unbound. The aircraft can be bound
     *  using DJI Go.  If DJI Go is connected to the aircraft, then the binding will be
     *  stored in the aircraft. If  DJI Go is not connected to the aircraft during the
     *  binding process, then the binding result  will be stored on a server. The SDK
     *  can query this server to see if the binding has already  happened, and if it
     *  has, download the binding to the aircraft. However, if the aircraft is  unbound,
     *  and the server is not reachable, then this state will be presented. The user
     *  should  connect the mobile device to the Internet to refresh this state.
     */
    DJIAppActivationAircraftBindingStateUnboundButCannotSync,

    /**
     *  The aircraft is bound.
     */
    DJIAppActivationAircraftBindingStateBound,

    /**
     *  The aircraft is not bound but it is not currently located in China. Therefore,
     *  binding the aircraft is not required.
     */
    DJIAppActivationAircraftBindingStateNotRequired,

    /**
     *  The aircraft's firmware does not support the App Activation system.
     */
    DJIAppActivationAircraftBindingStateNotSupported,

    /**
     *  Either the aircraft is disconnected or the connected product is not a DJI
     *  aircraft.
     */
    DJIAppActivationAircraftBindingStateUnknown = 0xFF,
};


/**
 *  The App Activation state.
 */
typedef NS_ENUM(NSInteger, DJIAppActivationState) {

    /**
     *  The aircraft's firmware does not support the App Activation System.
     */
    DJIAppActivationStateNotSupported,

    /**
     *  The application needs to be activated by the user through their DJI account.
     *  Use `DJIUserAccountManager` to enable the user to log in. Log in is only
     *  required if the  aircraft is located in China.
     */
    DJIAppActivationStateLoginRequired,

    /**
     *  The application is activated and flight restrictions turned off.
     */
    DJIAppActivationStateActivated,

    /**
     *  Either the aircraft is disconnected or the connected product is not a DJI
     *  aircraft.
     */
    DJIAppActivationStateUnknown = 0xFF,
};


#endif /* DJIAppActivationSystemTypes_h */
