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

   #ifdef __ENABLE_DEV_DEBUG_SLOG__
      #include <syslog.h>
      #define NO_PARENTHESES(...) __VA_ARGS__
      #define PF syslog( LOG_DEBUG, __PRETTY_FUNCTION__);
      #define TRC_INIT(option, facility)  openlog (TRC_GROUP, option, facility)
      #define TRC_DEBUG(s,m,f) PF syslog( LOG_DEBUG, (const char *)NO_PARENTHESES m)
      #define TRC_INFO(s,m,f)  PF syslog( LOG_INFO, (const char *)NO_PARENTHESES m)
      #define TRC_WARN(s,m,f)  PF syslog( LOG_WARNING, (const char *)NO_PARENTHESES m)
      #define TRC_ERROR(s,m,f) PF syslog( LOG_ERR, (const char *)NO_PARENTHESES m)
      #define TRC_FATAL(s,m,f) PF syslog( LOG_CRIT, (const char *)NO_PARENTHESES m)
      #define TRC_DEINIT()     closelog ()
   #else
      #define TRC_DEBUG(s,m,f) do { printf( TRC_GROUP "\t" ); printf( __PRETTY_FUNCTION__ ); printf( ": " ); printf m; printf ("\n"); } while(0);
      #define TRC_INFO(s,m,f)  do { printf( TRC_GROUP "\t" ); printf( __PRETTY_FUNCTION__ ); printf( ": " ); printf m; printf ("\n"); } while(0);
      #define TRC_WARN(s,m,f)  do { printf( TRC_GROUP "\t" ); printf( __PRETTY_FUNCTION__ ); printf( ": " ); printf m; printf ("\n"); } while(0);
      #define TRC_ERROR(s,m,f) do { printf( TRC_GROUP "\t" ); printf( __PRETTY_FUNCTION__ ); printf( ": " ); printf m; printf ("\n"); } while(0);
      #define TRC_FATAL(s,m,f) do { printf( TRC_GROUP "\t" ); printf( __PRETTY_FUNCTION__ ); printf( ": " ); printf m; printf ("\n"); } while(0);
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
