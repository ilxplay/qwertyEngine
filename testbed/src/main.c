#include "../../engine/src/core/asserts.h"
#include "../../engine/src/core/logger.h"
#include "../../engine/src/core/application.h"
int main(void)
{
  application_config config;

  config.start_pos_x = 100;
  config.start_pos_y = 100;
  config.start_width = 1280;
  config.start_height = 720;
  config.name = "Qwerty Engine";

  application_create(&config);

  application_run();
  return 0;
}