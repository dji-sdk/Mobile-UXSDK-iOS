//
//  DJIRemoteLogger.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 *  The DJI Remote Log levels.
 */
typedef NS_ENUM(NSUInteger, DJILogLevel) {


    /**
     *  Remote Log level off.
     */
    DJILogLevelOff = 0,


    /**
     *  Remote Log level Error.
     */
    DJILogLevelError,


    /**
     *  Remote Log level Warn.
     */
    DJILogLevelWarn,


    /**
     *  Remote Log level Debug.
     */
    DJILogLevelDebug,


    /**
     *  Remote Log level Info.
     */
    DJILogLevelInfo,


    /**
     *  Remote Log level Verbose.
     */
    DJILogLevelVerbose
    
};


/**
 *  This class provides methods to configure and use the remote logger.
 */
@interface DJIRemoteLogger : NSObject


/**
 *  Returns the current log level.
 *  
 *  @return A `DJILogLevel` enum value.
 */
+ (DJILogLevel)currentLogLevel;


/**
 *  Sets the current level of the remote log.
 *  
 *  @param level DJILogLevel object.
 */
+ (void)setCurrentLogLevel:(DJILogLevel)level;


/**
 *  This method allows configuration of the logger.
 *  
 *  @param deviceID Device ID string.
 *  @param urlString URL string.
 *  @param showLogInConsole Show log in console.
 */
+ (void)configureLoggerWithDeviceId:(NSString *)deviceID URLString:(NSString *)urlString showLogInConsole:(BOOL)showLogInConsole;


/**
 *  Reset remote logger.
 */
+ (void)resetLogger;


/**
 *  Log with level, file, function, line and format.
 *  
 *  @param level An enum value of `DJILogLevel`.
 *  @param file A const char value.
 *  @param function A const char value.
 *  @param line An NSUInteger value.
 *  @param format An NSString object.
 */
+ (void)logWithLevel:(DJILogLevel)level
                file:(const char *)file
            function:(const char *)function
                line:(NSUInteger)line
              format:(NSString *)format, ...;


/**
 *  Log with level, file, function, line and string.
 *  
 *  @param level An enum value of `DJILogLevel`.
 *  @param file A const char value.
 *  @param function A const char value.
 *  @param line An NSUInteger value.
 *  @param string An NSString object.
 */
+ (void)logWithLevel:(DJILogLevel)level
                file:(const char *)file
            function:(const char *)function
                line:(NSUInteger)line
              string:(NSString *)string;


@end

#define DJILogError(frmt, ...)   [DJIRemoteLogger logWithLevel : DJILogLevelError file : __FILE__ function : __PRETTY_FUNCTION__ line : __LINE__ format : (frmt), ## __VA_ARGS__]
#define DJILogWarn(frmt, ...)    [DJIRemoteLogger logWithLevel : DJILogLevelWarn file : __FILE__ function : __PRETTY_FUNCTION__ line : __LINE__ format : (frmt), ## __VA_ARGS__]
#define DJILogInfo(frmt, ...)    [DJIRemoteLogger logWithLevel : DJILogLevelInfo file : __FILE__ function : __PRETTY_FUNCTION__ line : __LINE__ format : (frmt), ## __VA_ARGS__]
#define DJILogDebug(frmt, ...)   [DJIRemoteLogger logWithLevel : DJILogLevelDebug file : __FILE__ function : __PRETTY_FUNCTION__ line : __LINE__ format : (frmt), ## __VA_ARGS__]
#define DJILogVerbose(frmt, ...) [DJIRemoteLogger logWithLevel : DJILogLevelVerbose file : __FILE__ function : __PRETTY_FUNCTION__ line : __LINE__ format : (frmt), ## __VA_ARGS__]
