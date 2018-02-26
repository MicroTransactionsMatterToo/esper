#ifndef __LOGGING_H_
#define __LOGGING_H_
#include "ets_sys.h"
#include "osapi.h"
#include "mem.h"
#include <stdarg.h>


#include "../macros.h"
#include "../romstrings.h"

enum LOG_LEVEL {
  LOW,
  MEDIUM,
  HIGH
};


static char* log_format(const char* module, const char* message, va_list args) __attribute__((format(sprintf, 2, 3)));
void log(const char* module, const char* message, enum LOG_LEVEL level, ...);

static char* log_format_rst(const char module[], const char* message, va_list args) __attribute__((format(sprintf, 2, 3)));
void log_rstr(const char module[], const char message[], enum LOG_LEVEL level, ...);
#endif // __LOGGING_H_
