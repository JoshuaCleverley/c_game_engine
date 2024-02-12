#include "engine/render.h"
#include <glad/glad.h>
#include <stdbool.h>
#include <stdio.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "engine/config.h"
#include "engine/global.h"
#include "engine/input.h"
#include "engine/physics.h"
#include "engine/time.h"
#include "engine/util.h"

static bool running = true;
static vec2 pos; // Testing input and time systems

static void input_handle(void) {
  if (global.input.escape == KS_PRESSED || global.input.escape == KS_HELD)
    running = false;

  i32 x, y;
  SDL_GetMouseState(&x, &y);
  pos[0] = (f32)x;
  pos[1] = global.render.height - y;
}

int main(int argc, char *argv[]) {
  time_init(60);
  config_init();
  render_init();
  physics_init();

  pos[0] = global.render.width * 0.5;
  pos[1] = global.render.height * 0.5;

  SDL_ShowCursor(false);

  AABB test_aabb = {
      .position = {global.render.width * 0.5, global.render.height * 0.5},
      .half_size = {50, 50},
  };

  AABB cursor_aabb = {.half_size = {75, 76}};
  AABB sum_aabb = {
      .position = {test_aabb.position[0], test_aabb.position[1]},
      .half_size = {test_aabb.half_size[0] + cursor_aabb.half_size[0],
                    test_aabb.half_size[1] + cursor_aabb.half_size[1]},
  };

  while (running) {
    time_update();
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        running = false;
        break;
      default:
        break;
      }
    }

    input_update();
    input_handle();
    physics_update();

    render_begin();

    cursor_aabb.position[0] = pos[0];
    cursor_aabb.position[1] = pos[1];

    render_aabb((f32 *)&test_aabb, WHITE);
    render_aabb((f32 *)&sum_aabb, WHITE);
    render_aabb((f32 *)&cursor_aabb, WHITE);

    if (physics_point_intersect_aabb(pos, test_aabb))
      render_quad(pos, (vec2){10, 10}, RED);
    else
      render_quad(pos, (vec2){10, 10}, GREEN);

    render_end();
    time_update_late();
  }

  return 0;
}
