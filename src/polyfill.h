#ifndef _POLYFILLS_H_
#define _POLYFILLS_H_

#include <stdarg.h>

#include "osapi.h"
#include "ets_sys.h"
#include "mem.h"

void ets_install_putc1(void(*p)(char c));
int ets_sprintf(char *str, const char *format, ...)  __attribute__ ((format (printf, 2, 3)));
int ets_vsprintf(char *str, const char *format, va_list arg)  __attribute__ ((format (printf, 2, 0)));
int ets_vsnprintf(char * s, size_t n, const char * format, va_list arg)  __attribute__ ((format (printf, 3, 0)));
int ets_putc(int);
void hexdump (const char *desc, uint8_t* addr, size_t len);
void writeUserData();
void setDeviceName(const char* name);

#define memcmp ets_memcmp
#define memcpy ets_memcpy
#define memmove ets_memmove
#define memset ets_memset
#define strcmp ets_strcmp
#define strcpy ets_strcpy
#define strlen ets_strlen
#define strncmp ets_strncmp
#define strncpy ets_strncpy
#define strstr ets_strstr

typedef signed int s32_t;
typedef unsigned int u32_t;
typedef signed short s16_t;
typedef unsigned short u16_t;
typedef signed char s8_t;
typedef unsigned char u8_t;
typedef int intptr_t;

#endif // _POLYFILLS_H_
