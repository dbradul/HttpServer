/*
 * Traceout.h
 *
 *  Created on: 06/04/2014
 *      Author: DB
 */

#ifndef TRACEOUT_H_
#define TRACEOUT_H_


#include "stdio.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifdef TRC_GROUP
#undef TRC_GROUP
#endif
#define TRC_GROUP "HttpServer"

#define __ENABLE_DEV_DEBUG_OUT__
#define __ENABLE_DEV_DEBUG_SLOG__
#ifdef __ENABLE_DEV_DEBUG_OUT__
   #ifdef TRC_DEBUG
      #undef TRC_DEBUG
   #endif
   #ifdef TRC_INFO
      #undef TRC_INFO
   #endif
   #ifdef TRC_INFO_d
      #undef TRC_INFO_d
   #endif
   #ifdef TRC_WARN
      #undef TRC_WARN
   #endif
   #ifdef TRC_ERROR
      #undef TRC_ERROR
   #endif
   #ifdef TRC_FATAL
      #undef TRC_FATAL
   #endif

   #ifdef __linux__
      #include <syslog.h>
      #define NO_PARENTHESES(...) __VA_ARGS__
      #define TRC_INIT(option, facility)  openlog (TRC_GROUP, option, facility)
      #define TRC_DEINIT()     closelog ()

      #define TRC_INFO( scope, fmt,  args...) syslog( LOG_INFO,    "%s: " fmt, __PRETTY_FUNCTION__, ##args)
      #define TRC_DEBUG(scope, fmt,  args...) syslog( LOG_DEBUG,   "%s: " fmt, __PRETTY_FUNCTION__, ##args)
      #define TRC_WARN( scope, fmt,  args...) syslog( LOG_WARNING, "%s: " fmt, __PRETTY_FUNCTION__, ##args)
      #define TRC_ERROR(scope, fmt,  args...) syslog( LOG_ERR,     "%s: " fmt, __PRETTY_FUNCTION__, ##args)
      #define TRC_FATAL(scope, fmt,  args...) syslog( LOG_CRIT,    "%s: " fmt, __PRETTY_FUNCTION__, ##args)

      #define TRC_DEBUG_FUNC_ENTER(scope, fmt, args...) syslog( LOG_INFO, "%s: ENTER: " fmt, __PRETTY_FUNCTION__, ##args)
      #define TRC_DEBUG_FUNC_EXIT( scope) syslog( LOG_INFO, "%s: EXIT", __PRETTY_FUNCTION__)

#else
      #define TRC_DEBUG(scope, fmt,  args...) do { printf( TRC_GROUP "\t" ); printf( "%s: " fmt, __PRETTY_FUNCTION__, args); printf ("\n"); } while(0);
      #define TRC_INFO (scope, fmt,  args...) do { printf( TRC_GROUP "\t" ); printf( "%s: " fmt, __PRETTY_FUNCTION__, args); printf ("\n"); } while(0);
      #define TRC_WARN (scope, fmt,  args...) do { printf( TRC_GROUP "\t" ); printf( "%s: " fmt, __PRETTY_FUNCTION__, args); printf ("\n"); } while(0);
      #define TRC_ERROR(scope, fmt,  args...) do { printf( TRC_GROUP "\t" ); printf( "%s: " fmt, __PRETTY_FUNCTION__, args); printf ("\n"); } while(0);
      #define TRC_FATAL(scope, fmt,  args...) do { printf( TRC_GROUP "\t" ); printf( "%s: " fmt, __PRETTY_FUNCTION__, args); printf ("\n"); } while(0);
   #endif
#else
   #define TRC_DEBUG(s,m,f)
   #define TRC_INFO(s,m,f)
   #define TRC_WARN(s,m,f)
   #define TRC_ERROR(s,m,f)
   #define TRC_FATAL(s,m,f)
#endif


#ifdef __cplusplus
}
#endif

#endif /* TRACEOUT_H_ */
