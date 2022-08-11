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
#define XNUM_L 9
#define STR_L  12
#define DEX_L  15
#define CON_L  18
#define INT_L  21
#define WIS_L  24
#define CHA_L  27

/* Skill Positions */
#define PROF_C  23
#define PASSP_C 45
#define SAVE_H  6
#define SKILL_H 12
#define SKILL_W 58
#define SKILL_C 19
#define SAVE_L  12
#define SKILL_L 18

WINDOW *sheet;

static int initAbil(void)
{
  char score[4], mod[4];

  NBOX inspBox = {ABILITY_H, ABILITY_W, XNUM_L, ABILITY_C, 
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

static int initSkill(void)
{
  char val[4];
  int i;

  const char *save[2][3] = {
    "Strength", "Dexterity", "Constitution",
    "Intelligence", "Wisdom", "Charisma"
  };

  const char *skills[2][9] = {
    /* Right Hand Side */
    "Acrobatics", "Arcana", "Deception", "Insight", "Investigation",
    "Nature", "Performance", "Religion", "Stealth",

    /* Left Hand Side */
    "Animal Handling", "Athletics", "History", "Intimidation",
    "Medicine", "Perception", "Persuasion", "Sleight of Hand", "Survival"
  };

  const char *abil[2][9] = {
    "Dex", "Int", "Cha", "Wis", "Int",
    "Int", "Cha", "Int", "Dex",
    "Wis", "Str", "Int", "Cha",
    "Wis", "Wis", "Cha", "Dex", "Wis"
  };

  const enum color skillColor[2][9] = {
    GREEN, CYAN, MAGENTA, BLUE, CYAN,
    CYAN, MAGENTA, CYAN, GREEN,
    BLUE, RED, CYAN, MAGENTA, 
    BLUE, BLUE, MAGENTA, GREEN, BLUE
  };

  sprintf(val, "%+d", proficiency);
  NBOX profBox = {ABILITY_H, ABILITY_W, XNUM_L, PROF_C,
                  "Proficiency", NULL, val, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, profBox) < 0) return -1;

  sprintf(val, "%d", passPerception);
  NBOX percBox = {ABILITY_H, ABILITY_W, XNUM_L, PASSP_C,
                  "Passive", "Perception", val, COLOR_PAIR(BLUE)};
  if (namedBox(sheet, percBox) < 0) return -1;

  /* Saving Throws */
  NBOX saveBox = {SAVE_H, SKILL_W, SAVE_L, SKILL_C,
                  NULL, "Saving Throws", NULL, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, saveBox) < 0) return -1;

  /* Skills */
  NBOX skillBox = {SKILL_H, SKILL_W, SKILL_L, SKILL_C,
                   NULL, "Skills", NULL, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, skillBox) < 0) return -1;

  for (i = 0; i < 9; i++) {
    mvwprintw(sheet, SKILL_L+i+1, SKILL_C+2, "   %+d  %s", 
        skill[i], skills[0][i]);
    wattron(sheet, COLOR_PAIR(skillColor[0][i]));
    mvwprintw(sheet, SKILL_L+i+1, SKILL_C+25, "%s", abil[0][i]);
    wattroff(sheet, COLOR_PAIR(skillColor[0][i]));
  }

  for (i = 0; i < 9; i++) {
    mvwprintw(sheet, SKILL_L+i+1, SKILL_C+30, "   %+d  %s", 
        skill[i+9], skills[1][i]);
    wattron(sheet, COLOR_PAIR(skillColor[1][i]));
    mvwprintw(sheet, SKILL_L+i+1, SKILL_C+53, "%s", abil[1][i]);
    wattroff(sheet, COLOR_PAIR(skillColor[1][i]));
  }

}

static int initSheet(void)
{
  const char *title = "Curse of DnD - Dungeons and Dragons Character Sheet";

  sheet = newwin(rowSize, colSize, 0, 0);

  /* Character Box */
  NBOX charBox = {CHARBOX_H, colSize, 0, 0, title, NULL, NULL, COLOR_PAIR(WHITE)};
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

  /* Skills */
  if (initSkill() < 0) return -1;

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
