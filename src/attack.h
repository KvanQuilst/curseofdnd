/*
 * Curse of DND - nCurses DND Character Sheet
 * attack.h
 */

#include <ncurses.h>

#include "char.h"
#include "dnd.h"

extern WINDOW *attack;

extern const int ATTACK_T;
extern const int ATTACK_L;
extern const int ATTACK_R;
extern const int ATTACK_C;

void initAttack(void);
