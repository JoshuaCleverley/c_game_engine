#include <SDL2/SDL.h>
#include <string.h>

#include "../config.h"
#include "../global.h"
#include "../io.h"
#include "../util.h"

static const char *CONFIG_DEFAULT = "[controls]\n"
                                    "left = A\n"
                                    "right = D\n"
                                    "up = W\n"
                                    "down = S\n"
                                    "escape = Escape\n";

static char tmp_buffer[20] = {0};

static char *config_get_value(const char *config_buffer, const char *value) {
  char *line = strstr(config_buffer, value);
  if (!line)
    ERROR_EXIT("Could not find config value: %s.\n"
               "Try deleting config.ini and starting again.\n",
               value);
  size_t len = strlen(line);
  char *end = line + len;

  char *curr = line;
  char *tmp_ptr = &tmp_buffer[0];

  // Consume all characters up to the first non-space char after an '=' symbol
  while (*curr != '=' && curr != end)
    ++curr;
  ++curr;
  while (*curr == ' ' && curr != end)
    ++curr;

  // Read rest of line
  while (*curr != '\n' && *curr != 0 && curr != end)
    *tmp_ptr++ = *curr++;

  *(tmp_ptr + 1) = 0;

  return tmp_buffer;
}

static void load_controls(const char *config_buffer) {
  config_key_bind(INPUT_KEY_LEFT, config_get_value(config_buffer, "left"));
  config_key_bind(INPUT_KEY_RIGHT, config_get_value(config_buffer, "right"));
  config_key_bind(INPUT_KEY_UP, config_get_value(config_buffer, "up"));
  config_key_bind(INPUT_KEY_DOWN, config_get_value(config_buffer, "down"));
  config_key_bind(INPUT_KEY_ESCAPE, config_get_value(config_buffer, "escape"));
}

static int config_load(void) {
  File file_config = io_file_read("./config.ini");
  if (!file_config.is_valid)
    return 1;

  load_controls(file_config.data);
  free(file_config.data);
  return 0;
}

void config_init(void) {
  if (config_load() == 0)
    return;

  io_file_write((void *)CONFIG_DEFAULT, strlen(CONFIG_DEFAULT), "./config.ini");

  if (config_load() == 0)
    ERROR_EXIT("Could not create or load config file.");
}

void config_key_bind(Input_Key key, const char *key_name) {
  SDL_Scancode scan_code = SDL_GetScancodeFromName(key_name);
  if (scan_code == SDL_SCANCODE_UNKNOWN)
    ERROR_RETURN(, "Invalid scancode when binding key: %s\n", key_name);

  global.config.keybinds[key] = scan_code;
}
