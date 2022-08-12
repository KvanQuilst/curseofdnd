/*
 * Curse of DND - nCurses DND Character Sheet
 * char.c
 */

#include "char.h"

char *abilityString[] = {
  "Str", "Dex", "Con", "Int", "Wis", "Cha"
};

enum ability_type skill_abil[] = {
  Dex, Wis, Int, Str, Cha, Int,
  Wis, Cha, Int, Wis, Int, Wis,
  Cha, Cha, Int, Dex, Dex, Wis
};
