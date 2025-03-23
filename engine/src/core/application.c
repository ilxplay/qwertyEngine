#include "application.h"
#include "logger.h"
#include "../platform/platform.h"

typedef struct application_state
{
  b8 is_running;
  b8 is_suspended;
  platform_state platform;
  i16 width;
  i16 height;
  f64 last_time;
} application_state;

static application_state app_state;
static b8 initialized = FALSE;

b8 application_create(application_config *config)
{
  if (initialized)
  {
    KERROR("application_create called twice or more");
    return FALSE;
  }

  // init subsystems
  initialize_logging();

  KFATAL("test: \n%f", 3.14f);
  KERROR("test: \n%f", 3.14f);
  KWARN("test \n%f", 3.14f);
  KINFO("test \n%f", 3.14f);
  KDEBUG("test \n%f", 3.14f);
  KTRACE("test \n%f", 3.14f);

  app_state.is_running = TRUE;
  app_state.is_suspended = FALSE;

  if (!platform_startup(
          &app_state.platform,
          config->name,
          config->start_pos_x,
          config->start_pos_y,
          config->start_width,
          config->start_height))
  {
    return FALSE;
  }
  initialized = TRUE;
  return TRUE;
}

b8 application_run()
{
  while (app_state.is_running)
  {
    if (platform_pump_messages(&app_state.platform) == 0)
    {
      app_state.is_running = FALSE;
    }
  }
  app_state.is_running = FALSE;
  platform_shutdown(&app_state.platform);

  return TRUE;
}