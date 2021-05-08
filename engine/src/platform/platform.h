#pragma once

#include "defines.h"

typedef struct {
    void* internal_state;
} platform_state;

b8 platform_init(
    platform_state* state,
    const char* app_name,
    i32 x,
    i32 y,
    i32 width,
    i32 height);

void platform_destroy(platform_state* state);
b8 platform_poll_events(platform_state* state);

// TODO: Platform specific memory management
