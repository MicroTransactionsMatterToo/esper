#include "romstrings.h"


void* ROMmemcpy(void* dst, const void* src, size_t len)
{
    uint8_t* s = (uint8_t*) src;
    uint8_t* d = (uint8_t*) dst;
    while (len--) {
      system_soft_wdt_feed();
        *d++ = readRomByte(s++);
    }

    return dst;
}

char* ROMCopyString(char* dst, const char* src)
{
    uint8_t* s = (uint8_t*) src;
    char c;
    while ((c = (char) readRomByte(s++))) {
      system_soft_wdt_feed();
        *dst++ = c;
    }
    *dst = '\0';

    return dst;
}

size_t ROMstrlen(const char* s)
{
    const char* p;
    for (p = s; readRomByte((const uint8_t*)(p)) != '\0'; p++) ;
    return (size_t) (p - s);
}

int ROMstrcmp(const char* s1, const char* s2)
{
    const uint8_t* p1 = (const uint8_t*)(s1);
    const uint8_t* p2 = (const uint8_t*)(s2);

    uint8_t c1;
    uint8_t c2;
    while (true) {
        system_soft_wdt_feed();
        c1 = readRomByte(p1++);
        c2 = readRomByte(p2++);
        if (c1 != c2) {
            break;
        }
        if (c1 == '\0') {
            return 0;
        }
    }
    return c1 - c2;
}

const char* ROMstrstr(const char* s1, const char* s2)
{
    int i, j;


    for( i = 0; ; i++) {
      system_soft_wdt_feed();
        char c1 = readRomByte((const uint8_t*)(s1 + i));
        if (c1 == '\0') {
            return 0;
        }

        char c2 = readRomByte((const uint8_t*)s2);
        if (c1 == c2) {
            for (j = i; ; j++) {
              system_soft_wdt_feed();
                c2 = readRomByte((const uint8_t*)(s2 + (j - i)));
                if (c2 == '\0') {
                    return s1 + i;
                }
                c1 = readRomByte((const uint8_t*)(s1 + j));
                if (c1 != c2) {
                    break;
                }
            }
        }
    }
}

int ROMsnprintf (char* s, size_t n, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    int result = ROMvsnprintf(s, n, format, args);
    va_end(args);
    return result;
}

int ROMvsnprintf (char* s, size_t n, const char* format, va_list args)
{
    size_t fmtlen = ROMstrlen(format);
    char *fmtbuf = (char *) os_malloc(fmtlen*sizeof(char));
    ROMCopyString(fmtbuf, format);
    int result = ets_vsnprintf(s, n, fmtbuf, args);
    os_free(fmtbuf);
    return result;
}
