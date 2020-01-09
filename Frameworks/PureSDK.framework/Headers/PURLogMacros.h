// Software License Agreement (BSD License)
//
// Copyright (c) 2010-2019, Deusty, LLC
// All rights reserved.
//
// Redistribution and use of this software in source and binary forms,
// with or without modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// * Neither the name of Deusty nor the names of its contributors may be used
//   to endorse or promote products derived from this software without specific
//   prior written permission of Deusty, LLC.

// Disable legacy macros
#ifndef PUR_LEGACY_MACROS
    #define PUR_LEGACY_MACROS 0
#endif

#import <PureSDK/PURLog.h>

/**
 * The constant/variable/method responsible for controlling the current log level.
 **/
#ifndef LOG_LEVEL_DEF
    #define LOG_LEVEL_DEF ddLogLevel
#endif

/**
 * Whether async should be used by log messages, excluding error messages that are always sent sync.
 **/
#ifndef LOG_ASYNC_ENABLED
    #define LOG_ASYNC_ENABLED YES
#endif

/**
 * These are the two macros that all other macros below compile into.
 * These big multiline macros makes all the other macros easier to read.
 **/
#define LOG_MACRO(isAsynchronous, lvl, flg, ctx, atag, fnct, frmt, ...) \
        [PURLog log : isAsynchronous                                    \
             level : lvl                                                \
              flag : flg                                                \
           context : ctx                                                \
              file : __FILE__                                           \
          function : fnct                                               \
              line : __LINE__                                           \
               tag : atag                                               \
            format : (frmt), ## __VA_ARGS__]

#define LOG_MACRO_TO_PURLOG(ddlog, isAsynchronous, lvl, flg, ctx, atag, fnct, frmt, ...) \
        [ddlog log : isAsynchronous                                                      \
             level : lvl                                                                 \
              flag : flg                                                                 \
           context : ctx                                                                 \
              file : __FILE__                                                            \
          function : fnct                                                                \
              line : __LINE__                                                            \
               tag : atag                                                                \
            format : (frmt), ## __VA_ARGS__]

/**
 * Define version of the macro that only execute if the log level is above the threshold.
 * The compiled versions essentially look like this:
 *
 * if (logFlagForThisLogMsg & ddLogLevel) { execute log message }
 *
 * When LOG_LEVEL_DEF is defined as ddLogLevel.
 *
 * As shown further below, Lumberjack actually uses a bitmask as opposed to primitive log levels.
 * This allows for a great amount of flexibility and some pretty advanced fine grained logging techniques.
 *
 * Note that when compiler optimizations are enabled (as they are for your release builds),
 * the log messages above your logging threshold will automatically be compiled out.
 *
 * (If the compiler sees LOG_LEVEL_DEF/ddLogLevel declared as a constant, the compiler simply checks to see
 *  if the 'if' statement would execute, and if not it strips it from the binary.)
 *
 * We also define shorthand versions for asynchronous and synchronous logging.
 **/
#define LOG_MAYBE(async, lvl, flg, ctx, tag, fnct, frmt, ...) \
        do { if(lvl & flg) LOG_MACRO(async, lvl, flg, ctx, tag, fnct, frmt, ##__VA_ARGS__); } while(0)

#define LOG_MAYBE_TO_PURLOG(ddlog, async, lvl, flg, ctx, tag, fnct, frmt, ...) \
        do { if(lvl & flg) LOG_MACRO_TO_PURLOG(ddlog, async, lvl, flg, ctx, tag, fnct, frmt, ##__VA_ARGS__); } while(0)

/**
 * Ready to use log macros with no context or tag.
 **/
#define PURLogError(frmt, ...)   LOG_MAYBE(NO,                LOG_LEVEL_DEF, PURLogFlagError,   0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define PURLogWarn(frmt, ...)    LOG_MAYBE(LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, PURLogFlagWarning, 0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define PURLogInfo(frmt, ...)    LOG_MAYBE(LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, PURLogFlagInfo,    0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define PURLogDebug(frmt, ...)   LOG_MAYBE(LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, PURLogFlagDebug,   0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define PURLogVerbose(frmt, ...) LOG_MAYBE(LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, PURLogFlagVerbose, 0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)

#define PURLogErrorToPURLog(ddlog, frmt, ...)   LOG_MAYBE_TO_PURLOG(ddlog, NO,                LOG_LEVEL_DEF, PURLogFlagError,   0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define PURLogWarnToPURLog(ddlog, frmt, ...)    LOG_MAYBE_TO_PURLOG(ddlog, LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, PURLogFlagWarning, 0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define PURLogInfoToPURLog(ddlog, frmt, ...)    LOG_MAYBE_TO_PURLOG(ddlog, LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, PURLogFlagInfo,    0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define PURLogDebugToPURLog(ddlog, frmt, ...)   LOG_MAYBE_TO_PURLOG(ddlog, LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, PURLogFlagDebug,   0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)
#define PURLogVerboseToPURLog(ddlog, frmt, ...) LOG_MAYBE_TO_PURLOG(ddlog, LOG_ASYNC_ENABLED, LOG_LEVEL_DEF, PURLogFlagVerbose, 0, nil, __PRETTY_FUNCTION__, frmt, ##__VA_ARGS__)