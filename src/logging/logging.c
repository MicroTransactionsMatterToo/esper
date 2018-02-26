#include "logging.h"

static void prepend(char* s, const char* t) {
    size_t len = strlen(t);
    size_t i;

    os_memmove(s + len, s, strlen(s) + 1);

    for (i = 0; i < len; ++i)
    {
        s[i] = t[i];
    }
}

/**
 * log formatter for use with standard strings
 * @param  module  module the log function was called from
 * @param  message message to log
 * @param  args    va_list of arguments to pass to `ets_vsnprintf`
 * @return         formatted log messagee
 */
static char* log_format(const char* module, const char* message, va_list args) {
  // Fetch sizes
  size_t module_len = __asize(module);
  size_t msg_len = __asize(message);
  size_t decided_len = (msg_len + module_len) + 20;
  // Allocate memory for string
  char* format_buffer = (char*)(os_malloc(decided_len*sizeof(char)));

  ets_vsnprintf(format_buffer, decided_len-module_len, message, args);
  prepend(format_buffer, " ");
  prepend(format_buffer, module);

  return format_buffer;
}

/**
 * log_format for use with flash stored strings
 * @param  module  ROM String of the module log is called from
 * @param  message Format string/messsagee
 * @param  args    va_list to pass to `ets_vsnprintf`
 * @return         Formatted string (not ROM string)
 */
static char* log_format_rstr(const char module[], const char message[], va_list args) {
  // Allocate memory for strings
  size_t module_rstr_len = ROMstrlen(module);
  size_t msg_rstr_len = ROMstrlen(message);
  size_t decided_len = (module_rstr_len + msg_rstr_len) + 20;
  char* retrieved_mod_str = (char*)(os_malloc(module_rstr_len*sizeof(char)));
  char* retrieved_msg_str = (char*)(os_malloc(msg_rstr_len*sizeof(char)));
  char* format_buffer = (char*)(os_malloc(decided_len*sizeof(char)));

  // Copy ROMSTRING's from FLASH
  ROMCopyString(retrieved_mod_str, module);
  ROMCopyString(retrieved_msg_str, message);

  // Insert formatted string
  ets_vsnprintf(format_buffer, decided_len-module_rstr_len, retrieved_msg_str, args);

  // Prepend module name
  prepend(format_buffer, " ");
  prepend(format_buffer, retrieved_mod_str);
  // Free retrieved strings
  os_free(retrieved_mod_str);
  os_free(retrieved_msg_str);

  return format_buffer;
}


void log(const char* module, const char* message, enum LOG_LEVEL level, ...) {
  va_list args;
  va_start(args, level);

  char* log_message = log_format(module, message, args);

  switch (level) {
    default:
      os_printf("%s\n", log_message);
  }

  os_free(log_message);
}

void log_rstr(const char module[], const char message[], enum LOG_LEVEL level, ...) {
  va_list args;
  va_start(args, level);

  char* log_message = log_format_rstr(module, message, args);

  switch (level) {
    default:
      os_printf("%s\n", log_message);
  }

  os_free(log_message);
}
