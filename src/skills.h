/*
 * Curse of DND - nCurses DND Character Sheet
 * skills.h
 */
#pragma once

#include <ncurses.h>

#include "char.h"
#include "dnd.h"

extern const int SKILLS_L;
extern const int SKILLS_R;
extern const int SKILLS_T;
extern const int SKILLS_B;

extern WINDOW *skills;

void initSkills();