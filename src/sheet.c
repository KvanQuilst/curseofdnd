/*
 * Curse of DND - nCurses DND Character Sheet
 * sheet.c
 */

#include "common.h"
#include "draw.h"

/* Character Box Positions */
#define CHARBOX_H  9
#define CHARNAME_L 4
#define CHARNAME_C 3
#define CHARBOX_L1 2
#define CHARBOX_L2 6
#define CHARBOX_C1 31
#define CHARBOX_C2 64
#define CHARBOX_C3 102

/* Ability Positions */
#define ABILITY_H 3
#define ABILITY_W 18
#define ABILITY_C 0
#define INSP_L 9
#define STR_L  12
#define DEX_L  15
#define CON_L  18
#define INT_L  21
#define WIS_L  24
#define CHA_L  27

WINDOW *sheet;

static int initAbil(void)
{
  char score[4], mod[4];

  NBOX inspBox = {ABILITY_H, ABILITY_W, INSP_L, ABILITY_C, 
                  "Inspiration", NULL, "**", WHITE};
  if (namedBox(sheet, inspBox) < 0)
    return -1;

  sprintf(score, "%d", ability[Str]);
  sprintf(mod, "%+d", abilityMod[Str]);
  NBOX strBox = {ABILITY_H, ABILITY_W, STR_L, ABILITY_C,
                 "Strength", score, mod, COLOR_PAIR(RED)};
  if (namedBox(sheet, strBox) < 0)
    return -1;

  sprintf(score, "%d", ability[Dex]);
  sprintf(mod, "%+d", abilityMod[Dex]);
  NBOX dexBox = {ABILITY_H, ABILITY_W, DEX_L, ABILITY_C,
                 "Dexterity", score, mod, COLOR_PAIR(GREEN)};
  if (namedBox(sheet, dexBox) < 0)
    return -1;

  sprintf(score, "%d", ability[Con]);
  sprintf(mod, "%+d", abilityMod[Con]);
  NBOX conBox = {ABILITY_H, ABILITY_W, CON_L, ABILITY_C,
                 "Constitution", score, mod, COLOR_PAIR(YELLOW)};
  if (namedBox(sheet, conBox) < 0)
    return -1;

  sprintf(score, "%d", ability[Int]);
  sprintf(mod, "%+d", abilityMod[Int]);
  NBOX intBox = {ABILITY_H, ABILITY_W, INT_L, ABILITY_C,
                 "Intelligence", score, mod, COLOR_PAIR(CYAN)};
  if (namedBox(sheet, intBox) < 0)
    return -1;

  sprintf(score, "%d", ability[Wis]);
  sprintf(mod, "%+d", abilityMod[Wis]);
  NBOX wisBox = {ABILITY_H, ABILITY_W, WIS_L, ABILITY_C,
                 "Wisdom", score, mod, COLOR_PAIR(BLUE)};
  if (namedBox(sheet, wisBox) < 0)
    return -1;

  sprintf(score, "%d", ability[Cha]);
  sprintf(mod, "%+d", abilityMod[Cha]);
  NBOX chaBox = {ABILITY_H, ABILITY_W, CHA_L, ABILITY_C,
                 "Charisma", score, mod, COLOR_PAIR(MAGENTA)};
  if (namedBox(sheet, chaBox) < 0)
    return -1;
}

static int initSheet(void)
{
  const char *title = "Curse of DnD - Dungeons and Dragons Character Sheet";

  sheet = newwin(rowSize, colSize, 0, 0);

  /* Character Box */
  NBOX charBox = {CHARBOX_H, colSize, 0, 0, title, NULL, NULL, WHITE};
  if (namedBox(sheet, charBox) < 0)
    return -1;
  mvwprintw(sheet, CHARNAME_L, CHARNAME_C, "%s", name);
  mvwprintw(sheet, CHARBOX_L1, CHARBOX_C1, "Class: %s %d", charClass, level);
  mvwprintw(sheet, CHARBOX_L2, CHARBOX_C1, "Race:  %s", race);
  mvwprintw(sheet, CHARBOX_L1, CHARBOX_C2, "Background: %s", background);
  mvwprintw(sheet, CHARBOX_L2, CHARBOX_C2, "Experience: %d", xp);
  mvwprintw(sheet, CHARBOX_L1, CHARBOX_C3, "Player Name: %s", playerName);
  mvwprintw(sheet, CHARBOX_L2, CHARBOX_C3, "Alignmnet:   %s", alignment);

  /* Abilities */
  if (initAbil() < 0) return -1;

  return 0;
}

int drawSheet(void)
{
  if (stdscr == NULL) {
    log_print("[ERROR] stdscr is NULL; can't write to screen!");
    return -1;
  }

  /* Initialize the window if it hasn't been, */
  /* check if initialization completed        */
  if (sheet == NULL && initSheet()) return -1;

  touchwin(sheet);
  wnoutrefresh(sheet);

  return 0;
}

void destroySheet(void)
{
  if (sheet != NULL)
    delwin(sheet);
}
