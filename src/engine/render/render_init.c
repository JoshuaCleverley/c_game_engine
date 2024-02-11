#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "../global.h"
#include "../render.h"
#include "../util.h"
#include "render_internal.h"

SDL_Window *render_init_window(u32 width, u32 height) {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    ERROR_EXIT("SDL_Init error: %s\n", SDL_GetError());
  }

  SDL_Window *window =
      SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       800, 600, SDL_WINDOW_OPENGL);
  if (!window) {
    ERROR_EXIT("SDL_CreateWindow Error: %s\n", SDL_GetError());
  }

  SDL_GL_CreateContext(window);
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    ERROR_EXIT("Failed to initialize GLAD: %s\n", SDL_GetError());
  }

  printf("OpenGL Loaded");
  printf("Vendor: %s\n", glGetString(GL_VENDOR));
  printf("Renderer: %s\n", glGetString(GL_RENDERER));
  printf("Version: %s\n", glGetString(GL_VERSION));

  return window;
}

void render_init_shaders(Render_State_Internal *state) {
  state->shader_default =
      render_shader_create("./shaders/default.vert", "./shaders/default.frag");
  mat4x4_ortho(state->projection, 0, global.render.width, 0,
               global.render.height, -2, 2);
  glUseProgram(state->shader_default);
  glUniformMatrix4fv(glGetUniformLocation(state->shader_default, "projection"),
                     1, GL_FALSE, &state->projection[0][0]);
}

void render_init_color_texture(u32 *texture) {
  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture);

  u8 solid_white[4] = {255, 255, 255, 255};
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               solid_white);

  glBindTexture(GL_TEXTURE_2D, 0);
}

void render_init_quad(u32 *vao, u32 *vbo, u32 *ebo) {
  f32 vertices[] = {0.5,  0.5,  0, 0, 0, 0.5,  -0.5, 0, 0, 1,
                    -0.5, -0.5, 0, 1, 1, -0.5, 0.5,  0, 1, 0};

  u32 indices[] = {0, 1, 3, 1, 2, 3};

  glGenVertexArrays(1, vao);
  glGenBuffers(1, vbo);
  glGenBuffers(1, ebo);

  glBindVertexArray(*vao);

  glBindBuffer(GL_ARRAY_BUFFER, *vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // xyz
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), NULL);
  glEnableVertexAttribArray(0);

  // uv
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32),
                        (void *)(3 * sizeof(f32)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);
}
