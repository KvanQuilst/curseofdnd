/*
 * Curse of DND - nCurses DND Character Sheet
 * dnd.h
 */
#pragma once

#include <ncurses.h>
#include <string.h>

#include "char.h"
#include "dnd.h"

extern WINDOW *logo;

extern const int LOGO_T;
extern const int LOGO_L;
extern const int LOGO_R;
extern const int LOGO_C;

void initLogo(void);
