/*
 * Curse of DND - nCurses DND Character Sheet
 * sheet.c
 */

#include <stdlib.h>

#include "common.h"
#include "draw.h"

/* Character Box Positions */
#define CHARBOX_H  9
#define CHARNAME_L 4
#define CHARNAME_C 3
#define CHARBOX_L1 2
#define CHARBOX_L2 6
#define CHARBOX_C1 26

/* Ability Positions */
#define ABILITY_H 3
#define ABILITY_W 18
#define ABILITY_L 12
#define ABILITY_C 0
#define XNUM_L 9
#define STR_L  12
#define DEX_L  15
#define CON_L  18
#define INT_L  21
#define WIS_L  24
#define CHA_L  27

/* Skill Positions */
#define PROF_C  25
#define PASSW_C 52
#define SAVE_H  6
#define SKILL_H 12
#define SKILL_W 58
#define SKILL_C 19
#define SAVE_L  12
#define SKILL_L 18

/* Vital Positions */
#define HEALTH_H 3
#define HEALTH_W 24
#define HEALTH_L 9
#define HEALTH_C 78

#define BATTLE_H 3
#define BATTLE_W 24
#define BATTLE_L 12
#define BATTLE_C 78

#define HITDIE_H 3
#define HITDIE_W 12
#define HITDIE_L 15
#define HITDIE_C 78

#define DEATH_H 3
#define DEATH_W 12
#define DEATH_L 15
#define DEATH_C 90

/* Spell Positions */
#define SPLCST_H 3
#define SPLCST_W 16
#define SPLCST_L 19
#define SPLCST_C 82

#define SPLSAV_H 3
#define SPLSAV_W 16
#define SPLSAV_L 23
#define SPLSAV_C 82

#define SPLATK_H 3
#define SPLATK_W 16
#define SPLATK_L 27
#define SPLATK_C 82

WINDOW *sheet;
static int initAbil(void)
{
  char score[4], mod[4];
  int i; 

  const char *abil[] = {
    "Strength", "Dexterity", "Constitution",
    "Intelligence", "Wisdom", "Charisma"
  };

  const enum color abilColor[] = {
    RED, GREEN, YELLOW, CYAN, BLUE, MAGENTA
  };

  NBOX inspBox = {ABILITY_H, ABILITY_W, XNUM_L, ABILITY_C, 
                  "Inspiration", NULL, c.inspiration == 1 ? "**" : "  ", WHITE};
  if (namedBox(sheet, inspBox) < 0)
    return -1;

  for (i = 0; i < 6; i++) {
    sprintf(score, "%d", c.ability[i]);
    sprintf(mod, "%+d", c.abilityMod[i]);
    NBOX box = {ABILITY_H, ABILITY_W, ABILITY_L+i*3, ABILITY_C,
                   abil[i], score, mod, COLOR_PAIR(abilColor[i])};
    if (namedBox(sheet, box) < 0)
      return -1;
  }

  return 0;
}

static char *profCharSkill(enum skill_type skill) 
{
  if (c.skillProf[skill] == 0)
    return "  ";
  if (c.skillProf[skill] == 1)
    return "* ";
  return "**";
}

static int initSkill(void)
{
  char val[4];
  int i;

  const char *save[2][3] = {
    {"Strength", "Dexterity", "Constitution"},
    {"Intelligence", "Wisdom", "Charisma"}
  };

  const enum color saveColor[2][3] = {
    {RED, GREEN, YELLOW}, {CYAN, BLUE, MAGENTA}
  };

  const char *skills[2][9] = {
    /* Right Hand Side */
    {"Acrobatics", "Arcana", "Deception", "Insight", "Investigation",
    "Nature", "Performance", "Religion", "Stealth"},

    /* Left Hand Side */
    {"Animal Handling", "Athletics", "History", "Intimidation",
    "Medicine", "Perception", "Persuasion", "Sleight of Hand", "Survival"}
  };

  const char *abil[2][9] = {
    {"Dex", "Int", "Cha", "Wis", "Int",
    "Int", "Cha", "Int", "Dex"},
    {"Wis", "Str", "Int", "Cha",
    "Wis", "Wis", "Cha", "Dex", "Wis"}
  };

  const enum color skillColor[2][9] = {
    {GREEN, CYAN, MAGENTA, BLUE, CYAN,
    CYAN, MAGENTA, CYAN, GREEN},
    {BLUE, RED, CYAN, MAGENTA, 
    BLUE, BLUE, MAGENTA, GREEN, BLUE}
  };

  sprintf(val, "%+d", c.proficiency);
  NBOX profBox = {ABILITY_H, ABILITY_W, XNUM_L, PROF_C,
                  "Proficiency", NULL, val, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, profBox) < 0) return -1;

  sprintf(val, "%d", c.passWisdom);
  NBOX percBox = {ABILITY_H, ABILITY_W, XNUM_L, PASSW_C,
                  "Passive Wisdom", NULL, val, COLOR_PAIR(BLUE)};
  if (namedBox(sheet, percBox) < 0) return -1;

  /* Saving Throws */

  NBOX saveBox = {SAVE_H, SKILL_W, SAVE_L, SKILL_C,
                  NULL, "Saving Throws", NULL, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, saveBox) < 0) return -1;
  
  /* Left Side */
  for (i = 0; i < 3; i++) {
    mvwprintw(sheet, SAVE_L+i+1, SKILL_C+2, "%s  %+d",
        c.saveProf[i] == 1 ? "*" : " ", c.saveThrow[i]);
    wattron(sheet, COLOR_PAIR(saveColor[0][i]));
    mvwprintw(sheet, SAVE_L+i+1, SKILL_C+9, "%s", save[0][i]);
    wattroff(sheet, COLOR_PAIR(saveColor[0][i]));
  }

  /* Right Side */
  for (i = 0; i < 3; i++) {
    mvwprintw(sheet, SAVE_L+i+1, SKILL_C+30, "%s  %+d",
        c.saveProf[i+3] == 1 ? "*" : " ", c.saveThrow[i+3]);
    wattron(sheet, COLOR_PAIR(saveColor[1][i]));
    mvwprintw(sheet, SAVE_L+i+1, SKILL_C+37, "%s", save[1][i]);
    wattroff(sheet, COLOR_PAIR(saveColor[1][i]));
  }

  /* Skills */

  NBOX skillBox = {SKILL_H, SKILL_W, SKILL_L, SKILL_C,
                   NULL, "Skills", NULL, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, skillBox) < 0) return -1;

  /* Left Side */
  for (i = 0; i < 9; i++) {
    mvwprintw(sheet, SKILL_L+i+1, SKILL_C+2, "%s %+d  %s", 
        profCharSkill(i*2), c.skill[i*2], skills[0][i]);
    wattron(sheet, COLOR_PAIR(skillColor[0][i]));
    mvwprintw(sheet, SKILL_L+i+1, SKILL_C+25, "%s", abil[0][i]);
    wattroff(sheet, COLOR_PAIR(skillColor[0][i]));
  }

  /* Right Side */
  for (i = 0; i < 9; i++) {
    mvwprintw(sheet, SKILL_L+i+1, SKILL_C+30, "%s %+d  %s", 
        profCharSkill(i*2+1), c.skill[i*2+1], skills[1][i]);
    wattron(sheet, COLOR_PAIR(skillColor[1][i]));
    mvwprintw(sheet, SKILL_L+i+1, SKILL_C+53, "%s", abil[1][i]);
    wattroff(sheet, COLOR_PAIR(skillColor[1][i]));
  }

  return 0;
}

static int initVital(void)
{
  char val[4];

  NBOX healthBox = {HEALTH_H, HEALTH_W, HEALTH_L, HEALTH_C,
    "Health", NULL, NULL, COLOR_PAIR(RED)};
  if (namedBox(sheet, healthBox) < 0) return -1;
  mvwprintw(sheet, HEALTH_L, HEALTH_C+18, "Temp");
  mvwprintw(sheet, HEALTH_L+1, HEALTH_C+3, "%3d  /  %-3d  |  %-2d",
     c.currHP, c.maxHP, c.tempHP);

  NBOX battleBox = {BATTLE_H, BATTLE_W, BATTLE_L, BATTLE_C,
    "AC", NULL, NULL, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, battleBox) < 0) return -1;
  mvwprintw(sheet, BATTLE_L, BATTLE_C+10, "Init");
  mvwprintw(sheet, BATTLE_L, BATTLE_C+19, "Spd");
  mvwprintw(sheet, BATTLE_L+1, BATTLE_C+3, "%d  |   %+d   |  %d",
      c.armor, c.initiative, c.speed);

  sprintf(val, "%d", c.level & 0x3F);
  NBOX hitBox = {HITDIE_H, HITDIE_W, HITDIE_L, HITDIE_C,
    "Hit Die", val, NULL, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, hitBox) < 0) return -1;
  mvwprintw(sheet, HITDIE_L+1, HITDIE_C+5, "d%d", c.hitDie);

  NBOX deathBox = {DEATH_H, DEATH_W, DEATH_L, DEATH_C,
    "Death", "Saves", "ooo  ooo", COLOR_PAIR(WHITE)};
  if (namedBox(sheet, deathBox) < 0) return -1;
  wattron(sheet, COLOR_PAIR(RED));
  mvwprintw(sheet, DEATH_L+1, DEATH_C+2, "%.*s", (c.deathSave>>2) & 0x3, "ooo");
  wattroff(sheet, COLOR_PAIR(RED));
  wattron(sheet, COLOR_PAIR(GREEN));
  mvwprintw(sheet, DEATH_L+1, DEATH_C+7, "%.*s", c.deathSave & 0x3, "ooo");
  wattroff(sheet, COLOR_PAIR(GREEN));

  return 0;
}

static int initSpell(void)
{
  char val[4];

  NBOX castBox = {SPLCST_H, SPLCST_W, SPLCST_L, SPLCST_C,
    "Spellcasting", NULL, c.castingAbil, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, castBox) < 0) return -1;

  sprintf(val, "%d", c.spellSave & 0x3F);
  NBOX saveBox = {SPLSAV_H, SPLSAV_W, SPLSAV_L, SPLSAV_C,
    "Spell Save", "DC", val, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, saveBox) < 0) return -1;

  sprintf(val, "%+d", c.spellAttack & 0x3F);
  NBOX attackBox = {SPLATK_H, SPLATK_W, SPLATK_L, SPLATK_C,
    "Spell Attack", "Bonus", val, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, attackBox) < 0) return -1;

  return 0;
}

static int initSheet(void)
{
  const char *title = "Curse of DnD - Dungeons and Dragons Character Sheet";
  const int fieldSize = (colSize - 32)/3;
  const int CHARBOX_C2 = CHARBOX_C1 + fieldSize + 2;
  const int CHARBOX_C3 = CHARBOX_C2 + fieldSize + 2;
  char *classTrim = malloc((fieldSize-9) * sizeof(char));
  snprintf(classTrim, fieldSize-10, "%s", c.charClass);

  sheet = newwin(rowSize, colSize, 0, 0);

  /* Character Box */
  NBOX charBox = {CHARBOX_H, colSize, 0, 0, title, NULL, NULL, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, charBox) < 0)
    return -1;
  mvwprintw(sheet, CHARNAME_L, CHARNAME_C, "%s", c.name);
  mvwprintw(sheet, CHARBOX_L1, CHARBOX_C1, "Class: %s %d", classTrim, c.level);
  mvwprintw(sheet, CHARBOX_L2, CHARBOX_C1, "Race:  %-*s", fieldSize-7, c.race);
  mvwprintw(sheet, CHARBOX_L1, CHARBOX_C2, "Background: %-*s", fieldSize-12, c.background);
  mvwprintw(sheet, CHARBOX_L2, CHARBOX_C2, "Experience: %-*d", fieldSize-12, c.xp);
  mvwprintw(sheet, CHARBOX_L1, CHARBOX_C3, "Player Name: %-*s", fieldSize-13, c.playerName);
  mvwprintw(sheet, CHARBOX_L2, CHARBOX_C3, "Alignment:   %-*s", fieldSize-13, c.alignment);

  /* Abilities */
  if (initAbil() < 0) return -1;

  /* Skills */
  if (initSkill() < 0) return -1;

  /* Vitality */
  if (initVital() < 0) return -1;

  /* Spell */
  if (initSpell() < 0) return -1;

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
