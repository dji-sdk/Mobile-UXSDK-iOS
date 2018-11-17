//
//  DJIPayloadWidget.h
//  DJISDK
//
//  Copyright © 2018 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 *  Types of widgets on the payload device.
 */
typedef NS_ENUM(NSUInteger, DJIPayloadWidgetType) {

    /**
     *  None.
     */
    DJIPayloadWidgetTypeNone = 0,

    /**
     *  The widget is a button. The value is a value of `DJIPayloadButtonState`.  A
     *  button widget is not configurable by the mobile side and the state is controlled
     *  by the hardware.
     */
    DJIPayloadWidgetTypeButton,

    /**
     *  The widget is a switch. The value is a value of `DJIPayloadSwitchState`.
     */
    DJIPayloadWidgetTypeSwitch,

    /**
     *  The widget is a range bar with percentage as the value. The valid value is from
     *  0 to 100.
     */
    DJIPayloadWidgetTypeRange,

    /**
     *  The widget is a list. The value represents the single selected item in the list.
     *  The valid  value is from 0 to the list size - 1. The list size is returned by
     *  the hardware.
     */
    DJIPayloadWidgetTypeList,

    /**
     *  The widget is an input box. The value should an unsigned 32-bit integer.
     */
    DJIPayloadWidgetTypeInput,
};


/**
 *  States of a button widget.
 */
typedef NS_ENUM(NSUInteger, DJIPayloadButtonState) {

    /**
     *  The button is in pull state.
     */
    DJIPayloadButtonStatePull = 0,

    /**
     *  The button is being pressed.
     */
    DJIPayloadButtonStatePress,
};


/**
 *  States of a switch widget.
 */
typedef NS_ENUM(NSUInteger, DJIPayloadSwitchState) {

    /**
     *  The switch is off.
     */
    DJIPayloadSwitchStateOff = 0,

    /**
     *  The switch is on.
     */
    DJIPayloadSwitchStateOn,
};


/**
 *  Class to represent the properties of a payload widget. Payload SDK defines
 *  different types of widgets for the interaction between the payload device  and
 *  the mobile device.
 */
@interface DJIPayloadWidget : NSObject<NSCopying>


/**
 *  The type of the widget. Different types have different type of values.
 */
@property (nonatomic, readonly) DJIPayloadWidgetType type;

/**
 *  The index of the widget. An index is used to differentiate widgets of the same
 *  type.
 */
@property (nonatomic, readonly) NSUInteger index;

/**
 *  The name of the widget. This is determined by the payload device and not
 *  configurable  through the mobile device.
 */
@property (nonatomic, readonly, copy) NSString *name;

/**
 *  The button state. It is only valid when `DJIPayloadWidgetType` is
 *  `DJIPayloadWidgetTypeButton`.
 */
@property (nonatomic, readonly) DJIPayloadButtonState buttonState;

/**
 *  The switch state. It is only valid when `DJIPayloadWidgetType` is
 *  `DJIPayloadWidgetTypeSwitch`.  It is possible to configure the switch value
 *  through `configureWidgetValue:type:index:withCompletion`.
 */
@property (nonatomic, readonly) DJIPayloadSwitchState switchState;

/**
 *  The progress value of a range bar. It is only valid when `DJIPayloadWidgetType`
 *  is `DJIPayloadWidgetTypeRange`. It is  possible to configure the range value
 *  through `configureWidgetValue:type:index:withCompletion`.
 */
@property (nonatomic, readonly) NSProgress *percentage;

/**
 *  All the items in the list. It is only valid when `DJIPayloadWidgetType` is
 *  `DJIPayloadWidgetTypeList`.
 */
@property (nonatomic, readonly, copy) NSArray *list;

/**
 *  The index of the selected item in the list. It is only valid when
 *  `DJIPayloadWidgetType` is `DJIPayloadWidgetTypeList`.  It is possible to
 *  configure the selected item index through
 *  `configureWidgetValue:type:index:withCompletion`.
 */
@property (nonatomic, readonly, assign) NSUInteger selectedListItem;

/**
 *  The hint for an input box determined by the payload device. It is only valid
 *  when `DJIPayloadWidgetType`  is `DJIPayloadWidgetTypeInput`.
 */
@property (nonatomic, readonly, copy) NSString *inputHint;

/**
 *  The value of an input box. It is only valid when `DJIPayloadWidgetType` is
 *  `DJIPayloadWidgetTypeInput`.  It is possible to configure the value through
 *  `configureWidgetValue:type:index:withCompletion`.
 */
@property (nonatomic, readonly, assign) NSInteger inputValue;

@end

