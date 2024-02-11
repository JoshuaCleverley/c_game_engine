#include <SDL2/SDL_video.h>
#include <glad/glad.h>
#include <stdbool.h>
#include <stdio.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "engine/global.h"
#include "engine/render/render.h"

int main(int argc, char *argv[]) {
  render_init();

  bool running = true;
  while (running) {
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

    render_begin();
    render_quad((vec2){global.render.width * 0.5, global.render.height * 0.5},
                (vec2){50, 50}, (vec4){1, 1, 1, 1});
    render_end();
  }

  return 0;
}
