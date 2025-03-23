#pragma once

#include "core/application.h"

typedef struct game
{
  // application config.
  application_config app_config;

  // function pointer to game's initialize function.
  b8 (*initialize)(struct game *game_inst);

  // to game update function.
  b8 (*update)(struct game *game_inst, f32 delta_time);

  // to game render function.
  b8 (*render)(struct game *game_inst, f32 delta_time);

  // to handle resizes
  void (*on_resize)(struct game *game_inst, u32 width, u32 height);

  // game specific state,created and managed by the game itself.
  void *state;
} game;