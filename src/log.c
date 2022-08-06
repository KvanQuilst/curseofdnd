/*
 * Curse of DND - nCurses DND Character Sheet
 * log.c
 */

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#include "common.h"

int logStream = -1;

int log_init()
{
  if(logStream == -1) 
    logStream = 2;
  return 0;
}

void log_print(const char *fmt, ...)
{
  /* if log stream hasn't been initialized */
  if (logStream == -1)
    return;

  char msg[MAX_LONG_LEN];
  va_list args;

  va_start(args, fmt);
  if (vsprintf(msg, fmt, args) < 0) msg[0] = 0;
  va_end(args);

  if (msg[0]) {
    time_t rawtime = time(NULL);
    struct tm *timeinfo = localtime(&rawtime);
    dprintf(logStream, "[%02d:%02d:%02d] %s: %s\n", 
        timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
        APP_NAME, msg);
  } else 
    dprintf(logStream, "Error while logging message: Memory allocation failed\n");
}
