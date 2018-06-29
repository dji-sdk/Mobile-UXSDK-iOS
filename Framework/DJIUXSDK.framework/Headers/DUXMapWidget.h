//
//  DUXMapWidget.h
//  DJIUXSDK
//
//  Copyright © 2017 DJI. All rights reserved.
//

#import <DJIUXSDK/DJIUXSDK.h>
#import <MapKit/MapKit.h>


/**
 *  An enum about different annotations on the map.
 */
typedef NS_ENUM(NSUInteger, DUXMapAnnotationType) {

    /**
     *  Annotation of the aircraft currently on the map.
     */
    DUXMapAnnotationTypeAircraft,

    /**
     *  Annotation of the home location currently on the map.
     */
    DUXMapAnnotationTypeHome,

    /**
     *  Annotation of a fly zone that can be self-unlocked, currently on the map. Only
     *  visible when DUXMapWidget_tapToUnlockEnabled is set to `TRUE`.
     */
    DUXMapAnnotationTypeEligibleFlyZones,

    /**
     *  Annotation of a fly zone that is unlocked currently. Only visible when
     *  DUXMapWidget_tapToUnlockEnabled is set to `TRUE`.
     */
    DUXMapAnnotationTypeUnlockedFlyZones,

    /**
     *  Annotation of a fly zone that is a custom unlock zone. Only visible when
     *  DUXMapWidget_tapToUnlockEnabled is set to `TRUE`.
     */
    DUXMapAnnotationTypeCustomUnlockedFlyZones,
};


/**
 *  An enum bitmask indicating which fly zones are to be displayed by the map
 *  widget.
 */
typedef NS_OPTIONS(NSUInteger, DUXMapVisibleFlyZones) {

    /**
     *  No fly zones will be visible on the map widget.
     */
    DUXMapVisibleFlyZonesNone = 0,

    /**
     *  Restricted fly zones will be visible on the map widget.
     */
    DUXMapVisibleFlyZonesRestricted = 1 << 0,

    /**
     *  Authorization fly zones will be visible on the map widget.
     */
    DUXMapVisibleFlyZonesAuthorization = 1 << 1,

    /**
     *  Warning fly zones will be visible on the map widget.
     */
    DUXMapVisibleFlyZonesWarning  = 1 << 2,

    /**
     *  Enhanced warning fly zones will be visible on the map widget.
     */
    DUXMapVisibleFlyZonesEnhancedWarning  = 1 << 3,
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
@interface DUXMapWidget : DUXWidget


/**
 *  Standard iOS Map for manipulating general settings.
 */
@property (nonatomic, strong) MKMapView *mapView;


/**
 *  A Boolean value indicating whether the map displays a line showing the direction
 *  to home. The default value of this property is false.
 */
@property (nonatomic, assign) BOOL showDirectionToHome;


/**
 *  A Boolean value that determines whether the map locks the camera view on the
 *  aircraft. The default value of this property is false.
 */
@property (nonatomic, assign) BOOL isMapCameraLockedOnAircraft;


/**
 *  Boolean property that if enabled will lock map center onto aircraft home
 *  location.
 */
@property (nonatomic, assign) BOOL isMapCameraLockedOnHomePoint;


/**
 *  Sets the types of fly zones to be displayed on the map. Set to
 *  `DUXMapWidget_DUXMapVisibleFlyZonesNone` to hide all fly zone types.
 */
@property (nonatomic, assign) DUXMapVisibleFlyZones visibleFlyZones;


/**
 *  A boolean value indicating if tapping to unlock select fly zones is enabled.
 *  Only self-unlocking is supported at this time.  If this option is enabled, you
 *  MUST use `DUXMapViewController` to present the widget via view controller
 *  containment.
 */
@property (nonatomic, assign) BOOL tapToUnlockEnabled;


/**
 *  A Boolean value indicating whether the map displays a line of aircraft's flight
 *  path. The default value of this property is false.
 */
@property (nonatomic, assign) BOOL showFlightPath;


/**
 *  A Boolean value indicating whether the map displays the home annotation. The
 *  default value of this property is true.
 */
@property (nonatomic, assign) BOOL showHomeAnnotation;


/**
 *  Replaces current annotation type with given image. The default image for all
 *  annotation types are set.
 *  
 *  @param annotationType An enum value of `DUXMapAnnotationType`.
 *  @param image Image used to represent the annotation.
 */
- (void)changeAnnotation:(DUXMapAnnotationType)annotationType withImage:(UIImage *)image DEPRECATED_ATTRIBUTE;


/**
 *  Change the annotation type of the map widget.
 *  
 *  @param annotationType An enum value of `DUXMapAnnotationType`.
 *  @param image Image used to represent the annotation.
 *  @param centerOffset A CGPoint struct for the center offset.
 */
- (void)changeAnnotationOfType:(DUXMapAnnotationType)annotationType toCustomImage:(nonnull UIImage *)image withCenterOffset:(CGPoint)centerOffset;


/**
 *  Removes the current flight path generated, regardless of being hidden.
 */
- (void)clearCurrentFlightPath;

#pragma mark - Customization


/**
 *  Change the rendered color for a given fly zone category.
 *  
 *  @param color The desired color.
 *  @param category The fly zone category for which the color would apply.
 */
- (void)setFlyZoneOverlayColor:(nullable UIColor *)color
            forFlyZoneCategory:(DJIFlyZoneCategory)category;


/**
 *  Returns the currently used color for a given fly zone category. This does not
 *  include unlocked zones.
 *  
 *  @param category The fly zone category associated with the returned color.
 *  
 *  @return A UIColor object.
 */
- (nonnull UIColor *)flyZoneOverlayColorForFlyZoneCategory:(DJIFlyZoneCategory)category;


/**
 *  Change the rendered alpha for a given fly zone category.
 *  
 *  @param alpha The desired alpha.
 *  @param category The fly zone category for which the alpha would apply.
 */
- (void)setFlyZoneOverlayAlpha:(CGFloat)alpha
            forFlyZoneCategory:(DJIFlyZoneCategory)category;


/**
 *  Returns the currently used alpha for a given fly zone category. This does not
 *  include unlocked zones.
 *  
 *  @param category The fly zone category associated with the returned alpha.
 *  
 *  @return A CGFloat value.
 */
- (CGFloat)flyZoneOverlayAlphaForFlyZoneCategory:(DJIFlyZoneCategory)category;


/**
 *  Current color of the self-unlocked fly zone overlay.
 */
@property (nonatomic, strong, nonnull) UIColor *unlockedFlyZoneOverlayColor;


/**
 *  Current alpha of the self-unlocked fly zone overlay.
 */
@property (nonatomic, assign) CGFloat unlockedFlyZoneOverlayAlpha;


/**
 *  Current color of a fly zone with maximum height.
 */
@property (nonatomic, strong, nonnull) UIColor *maximumHeightFlyZoneOverlayColor;


/**
 *  Current alpha of a fly zone with maximum height.
 */
@property (nonatomic, assign) CGFloat maximumHeightFlyZoneOverlayAlpha;


/**
 *  Width of the solid colored boreder of all fly zone overlays.
 */
@property (nonatomic, assign) CGFloat flyZoneOverlayBorderWidth;


/**
 *  Current color of the rendered flight path.
 */
@property (nonatomic, strong, nonnull) UIColor *flightPathStrokeColor;

/**
 *  Current stroke width of the rendered flight path.
 */
@property (nonatomic, assign) CGFloat flightPathStrokeWidth;


/**
 *  Current color of the rendered direction to home line.
 */
@property (nonatomic, strong, nonnull) UIColor *directionToHomeStrokeColor;


/**
 *  Current stroke width of the rendered direction to home line.
 */
@property (nonatomic, assign) CGFloat directionToHomeStrokeWidth;

@end
