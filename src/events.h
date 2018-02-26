#ifndef _EVENTS_H_
#define _EVENTS_H_
// System Includes
#include "ets_sys.h"
#include "user_interface.h"
#include "osapi.h"
// Local Includes
#include "macros.h"
#include "logging/logging.h"
#include "spiffs_api.h"


// Event Queue
os_event_t global_task_queue[16];

// Event Enumerations
enum GLOBAL_SIGNALS {
  BOOT_UP_FINISHED,
  TASK_INIT_FINISHED,
  EVENT_DISPATCH
};

// Dispatch Info
typedef struct DispatchInfo {
  os_event_t* calling_signal;
  os_signal_t sig;
  os_param_t par;
} dispatch_info_t;

// Init Function
void IRAM0 init_events();

// Event Dispatcher
static void IRAM0 ev_task_dispatch(os_event_t* ev);

// Event Handlers
void IRAM0 ev_post_boot();
static void IRAM0 ev_post_event_init(os_event_t* ev);

#endif // _EVENTS_H_
