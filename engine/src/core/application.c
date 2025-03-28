#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include "application.h"
#include "../game_types.h"
#include "event.h"
#include "logger.h"
#include "kmemory.h"
#include "../platform/platform.h"
#include "input.h"
#include "clock.h"

typedef struct application_state
{
  game *game_inst;
  b8 is_running;
  b8 is_suspended;
  platform_state platform;
  i16 width;
  i16 height;
  f64 last_time;
  clock clock;
} application_state;

static b8 initialized = FALSE;
static application_state app_state;

b8 application_on_event(u16 code, void *sender, void *listener_inst, event_context context);
b8 application_on_key(u16 code, void *sender, void *listener_inst, event_context context);

b8 application_create(game *game_inst)
{
  if (initialized)
  {
    KERROR("application_create called more than once.");
    return FALSE;
  }

  app_state.game_inst = game_inst;

  initialize_logging();

  /*
  KFATAL("A test message: \n%f", 3.14f);
  KERROR("A test message: \n%f", 3.14f);
  KWARN("A test message: \n%f", 3.14f);
  KINFO("A test message: \n%f", 3.14f);
  KDEBUG("A test message: \n%f", 3.14f);
  KTRACE("A test message: \n%f", 3.14f);
*/
  app_state.is_running = TRUE;
  app_state.is_suspended = FALSE;

  if (!event_initialize())
  {
    KERROR("event system had failed to initialize!");
    return FALSE;
  }

  event_register(EVENT_CODE_APPLICATION_QUIT, 0, application_on_event);
  event_register(EVENT_CODE_KEY_PRESSED, 0, application_on_key);
  event_register(EVENT_CODE_KEY_RELEASED, 0, application_on_key);

  if (!platform_startup(
          &app_state.platform,
          game_inst->app_config.name,
          game_inst->app_config.start_pos_x,
          game_inst->app_config.start_pos_y,
          game_inst->app_config.start_width,
          game_inst->app_config.start_height))
  {
    return FALSE;
  }

  if (!app_state.game_inst->initialize(app_state.game_inst))
  {
    KFATAL("Game failed to initialize.");
    return FALSE;
  }

  app_state.game_inst->on_resize(app_state.game_inst, app_state.width, app_state.height);

  initialized = TRUE;

  return TRUE;
}

b8 application_run()
{
  clock_start(&app_state.clock);
  clock_update(&app_state.clock);
  app_state.last_time = app_state.clock.elapsed;
  f64 running_time = 0;
  i8 frame_count = 0;
  f64 target_frame_seconds = 1.0f / 60;

  // A MEMORY LEAK!      //no. coz i am calling it once
  KINFO(get_memory_usage_str());

  while (app_state.is_running)
  {
    if (!platform_pump_messages(&app_state.platform))
    {
      app_state.is_running = FALSE;
    }

    if (!app_state.is_suspended)
    {
      clock_update(&app_state.clock);
      f64 current_time = app_state.clock.elapsed;
      f64 delta = (current_time - app_state.last_time);
      f64 frame_start_time = platform_get_absolute_time();

      if (!app_state.game_inst->update(app_state.game_inst, (f32)delta))
      {
        KFATAL("Game update failed, shutting down.");
        app_state.is_running = FALSE;
        break;
      }

      if (!app_state.game_inst->render(app_state.game_inst, (f32)delta))
      {
        KFATAL("Game render failed, shutting down.");
        app_state.is_running = FALSE;
        break;
      }

      f64 frame_end_time = platform_get_absolute_time();
      f64 frame_elapsed_time = frame_end_time - frame_start_time;
      running_time += frame_elapsed_time;
      f64 remaining_seconds = target_frame_seconds - frame_start_time;

      if (remaining_seconds > 0)
      {
        u64 remaining_ms = (remaining_seconds * 1000);

        b8 limit_frames = FALSE;
        if (remaining_ms > 0 && limit_frames)
        {
          platform_sleep(remaining_ms - 1);
        }

        frame_count++;
      }

      // for safety reasons input should be handled the last
      input_update(delta);

      app_state.last_time = current_time;
    }
  }

  app_state.is_running = FALSE;

  event_unregister(EVENT_CODE_APPLICATION_QUIT, 0, application_on_event);
  event_unregister(EVENT_CODE_KEY_PRESSED, 0, application_on_key);
  event_unregister(EVENT_CODE_KEY_RELEASED, 0, application_on_key);

  event_shutdown();
  input_shutdown();

  platform_shutdown(&app_state.platform);

  return TRUE;
}

b8 application_on_event(u16 code, void *sender, void *listener_inst, event_context context)
{
  switch (code)
  {
  case EVENT_CODE_APPLICATION_QUIT:
  {
    KINFO("EVENT_CODE_APPLICATION_QUIT recieved, shutting down.\n");
    app_state.is_running = FALSE;
    return TRUE;
  }
  }

  return FALSE;
}

b8 application_on_key(u16 code, void *sender, void *listener_inst, event_context context)
{
  if (code == EVENT_CODE_KEY_PRESSED)
  {
    u16 key_code = context.data.u16[0];
    if (key_code == KEY_ESCAPE)
    {
      // firing an event to itself there still may be other listeners
      event_context data = {};
      event_fire(EVENT_CODE_APPLICATION_QUIT, 0, data);

      return TRUE;
    }
    else if (key_code == KEY_A)
    {
      KDEBUG("Explicit - A key pressed!");
    }
    else
    {
      KDEBUG("'%c' key pressed in window.", key_code);
    }
  }
  else if (code == EVENT_CODE_KEY_RELEASED)
  {
    u16 key_code = context.data.u16[0];
    if (key_code == KEY_B)
    {
      KDEBUG("Explicit - B key released!");
    }
    else
    {
      KDEBUG("'%c' key released in window.", key_code);
    }
  }
  return FALSE;
}