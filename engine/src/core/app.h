#pragma once

#include "defines.h"

typedef struct {
    i16 x;
    i16 y;
    i16 width;
    i16 height;
    char* name;
} app_config;

YAPI b8 app_create(app_config* config);
YAPI b8 app_run();