/*
 * Curse of DND - nCurses DND Character Sheet
 * health.h
 */

#include <ncurses.h>

#include "char.h"
#include "dnd.h"

extern WINDOW *health;

extern const int HEALTH_L;
extern const int HEALTH_T;
extern const int HEALTH_R;
extern const int HEALTH_C;

void initHealth();
