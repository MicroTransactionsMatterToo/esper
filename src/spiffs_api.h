#ifndef __SPIFFS_API__
#define __SPIFFS_API__

#include "spi_flash.h"
#include "user_interface.h"
#include "mem.h"

#include "spiffs/spiffs.h"

#include "macros.h"


#define LOG_PAGE_SIZE 256

void init_spiffs();

extern spiffs fs;

int spiffs_read_flash(uint32_t addr, uint32_t size, uint8_t *dest);
int spiffs_write_flash(uint32_t addr, uint32_t size, uint8_t *src);
int spiffs_erase_flash(uint32_t addr, uint32_t size);

extern spiffs_config def_cfg;

extern u8_t spiffs_work_buf[LOG_PAGE_SIZE*2];
extern u8_t spiffs_fds[32*4];
extern u8_t spiffs_cache_buf[(LOG_PAGE_SIZE+32)*4];

#endif // __SPIFFS_API__
