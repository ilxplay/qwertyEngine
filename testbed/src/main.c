#include "../../engine/src/core/asserts.h"
#include "../../engine/src/core/logger.h"
#include "../../engine/src/platform/platform.h"

int main(void)
{
  KFATAL("A test message: %f", 3.14f);
  KERROR("A test message: %f", 3.14f);
  KWARN("A test message: %f", 3.14f);
  KINFO("A test message: %f", 3.14f);
  KDEBUG("A test message: %f", 3.14f);
  KTRACE("A test message: %f", 3.14f);

  platform_state state;
  if (platform_startup(&state, "qwerty_window", 100, 100, 1280, 720))
  {
    while (TRUE)
    {
      platform_pump_messages(&state);
    }
  }
  platform_shutdown(&state);

  return 0;
}