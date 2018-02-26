#include "spiffs_api.h"

spiffs_config def_cfg = {
  spiffs_read_flash,
  spiffs_write_flash,
  spiffs_erase_flash,
  0x100000,
  0x100000,
  8*4000,
  8*4000,
  LOG_PAGE_SIZE
};

u8_t spiffs_work_buf[LOG_PAGE_SIZE*2];
u8_t spiffs_fds[32*4];
u8_t spiffs_cache_buf[(LOG_PAGE_SIZE+32)*4];

spiffs fs;
/**
 * Default SPIFFS mount
 */
void init_spiffs() {
  os_printf("Attemting to mount SPIFFS at %d ms\n", system_get_time());
  int mnt_res = SPIFFS_mount(
    &fs,
    &def_cfg,
    spiffs_work_buf,
    spiffs_fds,
    sizeof(spiffs_fds),
    spiffs_cache_buf,
    sizeof(spiffs_cache_buf),
    0
  );
  os_printf("Finished mounting at %d ms, result of mount was: %d\n",
    system_get_time(),
    mnt_res
  );
}



int spiffs_read_flash(uint32_t addr, uint32_t size, uint8_t *dest) {
  spi_flash_read(addr, (uint32_t *) dest, size);
  return 0;
}

int spiffs_write_flash(uint32_t addr, uint32_t size, uint8_t *src) {
  spi_flash_write(addr, (uint32_t *) src, size);
  return 0;
}

int spiffs_erase_flash(uint32_t addr, uint32_t size) {
  uint8_t* zeroed_array = (uint8_t*) os_zalloc(size);
  spi_flash_write(addr, (uint32_t *) zeroed_array, size);
  return 0;
}
