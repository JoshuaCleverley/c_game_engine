#pragma once

#include "../arraylist.h"
#include "../types.h"

typedef struct physics_state_internal {
  Array_List *body_list;
} Physics_State_Internal;
