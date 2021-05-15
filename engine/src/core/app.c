#include "app.h"
#include "log.h"
#include "platform/platform.h"

typedef struct {
    platform_state* state;
    b8 running;
    b8 paused;
    i16 width;
    i16 height;
} app_state;

static b8 initialized = FALSE;
static app_state  state;

b8 app_create(app_config* config) {
    if (initialized)
    {
        LL_ERROR("Trying to create multiple application instances.");
        return FALSE;
    }

    // Initialize subsystems
    initialize_log();

    state.running = TRUE;
    state.paused = FALSE;

    if (!platform_init(state.state, config->name, config->x, config->y, config->width, config->height)) {
        return FALSE;
    }
    
    initialized = TRUE;
    return TRUE;
}

b8 app_run() {
    while (state.running) {
        if (!platform_poll_events(state.state)) {
            state.running = FALSE;
        }
    }
    state.running = FALSE;
    platform_destroy(state.state);
    return FALSE;
}