#include "logger.h"
#include "asserts.h"
#include "../platform/platform.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

b8 initialize_logging()
{
  return TRUE;
}

void shutdown_logging()
{
}

void log_output(log_level level, const char *message, ...)
{
  const char *level_strings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]:  ", "[INFO]:  ", "[DEBUG]: ", "[TRACE]: "};
  b8 is_error = level < LOG_LEVEL_WARN;

  char out_message[32000];
  const i32 msg_length = 32000;
  memset(out_message, 0, sizeof(out_message));

  va_list arg_ptr;
  va_start(arg_ptr, message);
  vsnprintf(out_message, msg_length, message, arg_ptr);
  va_end(arg_ptr);

  char out_message2[32000];
  sprintf(out_message2, "%s%s\n", level_strings[level], out_message);

  if (is_error)
  {
    platform_console_write_error(out_message2, level);
  }
  else
  {
    platform_console_write(out_message2, level);
  }
}

void report_assertion_failure(const char *expression, const char *message, const char *file, i32 line)
{
  log_output(LOG_LEVEL_FATAL, "Assertion Failure: %s, message: '%s', in file: %s, line: %d\n", expression, message, file, line);
}