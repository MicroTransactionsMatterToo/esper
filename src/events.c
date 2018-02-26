#include "events.h"



// Setup Event Queues
/**
 * Starts the event loop
 */
void IRAM0 init_events() {
  // Register our base event for post_boot
  system_os_task(ev_task_dispatch, 0, global_task_queue, __asize(global_task_queue));
  system_os_post(0, TASK_INIT_FINISHED, 0);
}

/**
 * Called once boot has completed. Called via `system_init_done_cb`
 */
void IRAM0 ev_post_boot() {
  os_printf("BOOT SUCCESSFUL, %d ms since power on\n", system_get_time());
  init_spiffs();
}

// General Event Handler
/**
 * Primary event dispatcher, passes on it's `ev` parameter to the related event
 * handler
 * @param  ev Event information
 * @static
 */
static void IRAM0 ev_task_dispatch(os_event_t* ev) {
  // Fetch signal information
  enum GLOBAL_SIGNALS signal = (enum GLOBAL_SIGNALS)ev->sig;

  switch (signal) {
    case TASK_INIT_FINISHED:
      ev_post_event_init(ev);
      break;
  }
}

// Event Handlers
/**
 * Called once the primary event handler is started
 * @param  ev Event information
 */
static void IRAM0 ev_post_event_init(os_event_t* ev) {
  os_printf("EVENT QUEUE STARTED\n");
}
