#pragma once

#include "render.h"
#include "config.h"
#include "time.h"

typedef struct global {
  Render_State render;
  Config_State config;
  Time_State time;
  Input_State input;
} Global;

extern Global global;
