#ifndef _ROMSTRINGS_H_
#define _ROMSTRINGS_H_

#include <stdarg.h>
#include <stdlib.h>

#include "ets_sys.h"
#include "mem.h"
#include "user_interface.h"

#include "macros.h"
#include "polyfill.h"

// Returns dst, just like memcpy
void* ROMmemcpy(void* dst, const void* src, size_t len);

// Returns dst + strlen(src) to allow strings to be chained
char* ROMCopyString(char* dst, const char* src);

size_t ROMstrlen(const char* s);
int ROMstrcmp(const char* s1, const char* s2);
const char* ROMstrstr(const char* s1, const char* s2);

int ROMsnprintf (char * s, size_t n, const char * format, ...);
int ROMvsnprintf (char * s, size_t n, const char * format, va_list arg);

static inline uint8_t IRAM0 readRomByte(const uint8_t* addr) {
    uint32_t bytes;
    bytes = *(uint32_t*)((uint32_t)addr & ~3);
    return ((uint8_t*)&bytes)[(uint32_t)addr & 3];
}

#endif // _ROMSTRINGS_H_
