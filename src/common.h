/*
 * Curse of DND - nCurses DND Character Sheet
 * common.h
 */
#pragma once

#include "log.h"
#include "char.h"

#define MAX_SHORT_LEN 24
#define MAX_LONG_LEN 1024

#define ctrl(x) ((x) & 0x1f)

extern char *APP_NAME;

enum state {s_quit, s_home, s_sheet, s_menu};
