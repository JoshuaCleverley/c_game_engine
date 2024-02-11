#include "../physics.h"

void physics_init();
void physics_update();
usize physics_body_create(vec2 position, vec2 size);
Body *physics_body_get(usize index);
