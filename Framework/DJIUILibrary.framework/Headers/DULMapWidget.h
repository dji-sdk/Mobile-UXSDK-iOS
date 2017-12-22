//
//  DULMapWidget.h
//  DJIUILibrary
//
//  Copyright © 2017 DJI. All rights reserved.
//

#import <DJIUILibrary/DJIUILibrary.h>
#import <MapKit/MapKit.h>


/**
 *  An enum about different annotations on the map.
 */
typedef NS_ENUM(NSUInteger, DULMapAnnotationType) {

    /**
     *  Annotation of the aircraft currently on the map.
     */
    DULMapAnnotationTypeAircraft,

    /**
     *  Annotation of the home location currently on the map.
     */
    DULMapAnnotationTypeHome
};


/**
 *  Display:
 *  Widget that displays the aircraft's state and information on the map this
 *  includes aircraft location, home location, aircraft trail path, aircraft
 *  heading, and No Fly Zones.
 *  
 *  Usage:
 *  Preferred Aspect Ratio: 1:1
 */
@interface DULMapWidget : DULWidget


/**
 *  Standard iOS Map for manipulating general settings.
 */
@property (nonatomic, strong) MKMapView *mapView;


/**
 *  A Boolean value indicating whether the map displays a line showing the direction
 *  to home. The default value of this property is false.
 */
@property BOOL showDirectionToHome;


/**
 *  A Boolean value that determines whether the map locks the camera view on the
 *  aircraft. The default value of this property is false.
 */
@property BOOL isMapCameraLockedOnAircraft;


/**
 *  A Boolean value indicating whether the map displays all fly zones in surrounding
 *  area. The default value of this property is true.
 */
@property BOOL showAllFlyZones;


/**
 *  A Boolean value indicating whether the map displays a line of aircraft's flight
 *  path. The default value of this property is false.
 */
@property BOOL showFlightPath;


/**
 *  A Boolean value indicating whether the map displays the home annotation. The
 *  default value of this property is true.
 */
@property BOOL showHomeAnnotation;


/**
 *  Replaces current annotation type with given image. The default image for all
 *  annotation types are set.
 *  
 *  @param annotationType An enum value of `DULMapAnnotationType`.
 *  @param image Image used to represent the annotation.
 */
- (void)changeAnnotation:(DULMapAnnotationType)annotationType withImage:(UIImage *)image;


/**
 *  Removes the current flight path generated, regardless of being hidden.
 */
- (void)clearCurrentFlightPath;

@end
