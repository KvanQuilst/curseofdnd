/*
 * Curse of DND - nCurses DND Character Sheet
 * sheet.c
 */

#include <stdlib.h>

#include "common.h"
#include "draw.h"
#include "sheet.h"

#define CHARBOX_H  9

#define BOX_H 3
#define BOX_SM 12
#define BOX_MED 18
#define BOX_LG 24

#define SKILL_H 12
#define SKILL_W 58
#define SAVE_H  6

#define NOTES_H 21

WINDOW *sheet;

int updateHealth(void)
{
  if (sheet == NULL) {
    log_print("[ERROR] attempted to write to null window: sheet");
    return -1;
  }

  mvwprintw(sheet, HEALTH_L+1, HEALTH_C+3, "%3d", c.currHP);

  return 0;
}

int updateTempHealth(void)
{
  if (sheet == NULL) {
    log_print("[ERROR] attempted to write to null window: sheet");
    return -1;
  }

  mvwprintw(sheet, HEALTH_L+1, HEALTH_C+19, "%-2d", c.tempHP);

  return 0;
}

int updateDeathSave(void)
{
  if (sheet == NULL) {
    log_print("[ERROR] attempted to write to null window: sheet");
    return -1;
  }

  wattron(sheet, COLOR_PAIR(RED));
  mvwprintw(sheet, DEATH_L+1, DEATH_C+2, "%.*s", (c.deathSave>>2) & 0x3, "ooo");
  wattroff(sheet, COLOR_PAIR(RED));
  wattron(sheet, COLOR_PAIR(GREEN));
  mvwprintw(sheet, DEATH_L+1, DEATH_C+7, "%.*s", c.deathSave & 0x3, "ooo");
  wattroff(sheet, COLOR_PAIR(GREEN));

  return 0;
}

int updateInspiration(void)
{
  if (sheet == NULL) {
    log_print("[ERROR] attempted to write to null window: sheet");
    return -1;
  }

  mvwprintw(sheet, INSP_L, INSP_C, "%s", c.inspiration == 1 ? "**" : "  ");

  return 0;
}

int updateExperience(void)
{
  if (sheet == NULL) {
    log_print("[ERROR] attempted to write to null window: sheet");
    return -1;
  }

  const int fieldSize = (colSize - 32)/3;
  const int c2 = CHARBOX_C + 41 + fieldSize;

  mvwprintw(sheet, CHARBOX_L+6, c2, "%-*d", fieldSize-12, c.xp);

  return 0;
}

static int initCharBox(void)
{
  const char *title = "Curse of DnD - Dungeons and Dragons Character Sheet";
  const int fieldSize = (colSize - 32)/3;
  const int c1 = CHARBOX_C + 26;
  const int c2 = c1 + fieldSize + 2;
  const int c3 = c2 + fieldSize + 2;
  char *classTrim = malloc((fieldSize-9) * sizeof(char));
  snprintf(classTrim, fieldSize-10, "%s", c.charClass);
  log_print("Check it %d", fieldSize);

  NBOX charBox = {CHARBOX_H, colSize, 0, 0, title, NULL, NULL, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, charBox) < 0) return -1;
  mvwprintw(sheet, CHARBOX_L+4, CHARBOX_C+3, "%s", c.name);
  mvwprintw(sheet, CHARBOX_L+2, c1, "Class: %s %d", classTrim, c.level);
  mvwprintw(sheet, CHARBOX_L+6, c1, "Race:  %-.*s", fieldSize-7, c.race);
  mvwprintw(sheet, CHARBOX_L+2, c2, "Background: %-.*s", fieldSize-12, c.background);
  mvwprintw(sheet, CHARBOX_L+6, c2, "Experience: %-*d", fieldSize-12, c.xp);
  mvwprintw(sheet, CHARBOX_L+2, c3, "Player Name: %-.*s", fieldSize-13, c.playerName);
  mvwprintw(sheet, CHARBOX_L+6, c3, "Alignment:   %-.*s", fieldSize-13, c.alignment);

  return 0;
}

static int initAbil(void)
{
  char score[4], mod[4];
  int i; 

  const int pos[6][2] = {
    {STR_L, STR_C}, {DEX_L, DEX_C}, {CON_L, CON_C},
    {INT_L, INT_C}, {WIS_L, WIS_C}, {CHA_L, CHA_C}
  };

  const char *abil[] = {
    "Strength", "Dexterity", "Constitution",
    "Intelligence", "Wisdom", "Charisma"
  };

  const enum color abilColor[] = {
    RED, GREEN, YELLOW, CYAN, BLUE, MAGENTA
  };

  NBOX inspBox = {BOX_H, BOX_MED, INSP_L, INSP_C, 
                  "Inspiration", NULL, c.inspiration == 1 ? "**" : "  ", WHITE};
  if (namedBox(sheet, inspBox) < 0)
    return -1;

  for (i = 0; i < 6; i++) {
    sprintf(score, "%d", c.ability[i]);
    sprintf(mod, "%+d", c.abilityMod[i]);
    NBOX box = {BOX_H, BOX_MED, pos[i][0], pos[i][1],
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
  NBOX profBox = {BOX_H, BOX_MED, PROF_L, PROF_C,
                  "Proficiency", NULL, val, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, profBox) < 0) return -1;

  sprintf(val, "%d", c.passWisdom);
  NBOX percBox = {BOX_H, BOX_MED, PASSWIS_L, PASSWIS_C,
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

  NBOX healthBox = {BOX_H, BOX_LG, HEALTH_L, HEALTH_C,
    "Health", NULL, NULL, COLOR_PAIR(RED)};
  if (namedBox(sheet, healthBox) < 0) return -1;
  mvwprintw(sheet, HEALTH_L, HEALTH_C+18, "Temp");
  mvwprintw(sheet, HEALTH_L+1, HEALTH_C+3, "%3d  /  %-3d  |  %-2d",
     c.currHP, c.maxHP, c.tempHP);

  NBOX battleBox = {BOX_H, BOX_LG, BATTLE_L, BATTLE_C,
    "AC", NULL, NULL, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, battleBox) < 0) return -1;
  mvwprintw(sheet, BATTLE_L, BATTLE_C+10, "Init");
  mvwprintw(sheet, BATTLE_L, BATTLE_C+19, "Spd");
  mvwprintw(sheet, BATTLE_L+1, BATTLE_C+3, "%d  |   %+d   |  %d",
      c.armor, c.initiative, c.speed);

  sprintf(val, "%d", c.level & 0x3F);
  NBOX hitBox = {BOX_H, BOX_SM, HITDIE_L, HITDIE_C,
    "Hit Die", val, NULL, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, hitBox) < 0) return -1;
  mvwprintw(sheet, HITDIE_L+1, HITDIE_C+5, "d%d", c.hitDie);

  NBOX deathBox = {BOX_H, BOX_SM, DEATH_L, DEATH_C,
    "Death", "Saves", "ooo  ooo", COLOR_PAIR(WHITE)};
  if (namedBox(sheet, deathBox) < 0) return -1;
  updateDeathSave();

  return 0;
}

static int initSpell(void)
{
  char val[4];

  NBOX castBox = {BOX_H, BOX_MED, SPLCST_L, SPLCST_C,
    "Spellcasting", NULL, abilityString[c.castingAbil], COLOR_PAIR(WHITE)};
  if (namedBox(sheet, castBox) < 0) return -1;

  sprintf(val, "%d", c.spellSave & 0x3F);
  NBOX saveBox = {BOX_H, BOX_MED, SPLSAV_L, SPLSAV_C,
    "Spell Save", "DC", val, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, saveBox) < 0) return -1;

  sprintf(val, "%+d", c.spellAttack & 0x3F);
  NBOX attackBox = {BOX_H, BOX_MED, SPLATK_L, SPLATK_C,
    "Spell Attack", "Bonus", val, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, attackBox) < 0) return -1;

  return 0;
}

static int initNotes(void)
{
  NBOX noteBox = {NOTES_H, colSize-NOTES_C, NOTES_L, NOTES_C,
    NULL, "Notes", NULL, COLOR_PAIR(WHITE)};
  if (namedBox(sheet, noteBox) < 0) return -1;

  return 0;
}

static int initSheet(void)
{
  sheet = newwin(rowSize, colSize, 0, 0);
  if (sheet == NULL) {
    log_print("[ERROR] failed to create window <sheet>!");
    return -1;
  }

  /* Character Box */
  if (initCharBox() < 0) return -1;

  /* Abilities */
  if (initAbil() < 0) return -1;

  /* Skills */
  if (initSkill() < 0) return -1;

  /* Vitality */
  if (initVital() < 0) return -1;

  /* Spell */
  if (initSpell() < 0) return -1;

  /* Notes */
  if (initNotes() < 0) return -1;

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
