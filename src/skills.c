/*
 * Curse of DND - nCurses DND Character Sheet
 * skills.c
 */

#include "skills.h"

WINDOW *skills = NULL;

const char *STR = "Str";
const char *DEX = "Dex";
const char *CON = "Con";
const char *INT = "Int";
const char *WIS = "Wis";
const char *CHA = "Cha";

/* Prototypes */
static int calcSkillMod(int score);
static void initMod();
static void initAbil();
static void initSaves();
static void initOther();

void initSkills()
{
  /*const unsigned SKILLS_L = 0;
  const unsigned SKILLS_R = SKILLS_L + 82;
  const unsigned SKILLS_T = LOGO_B+1;
  const unsigned SKILLS_B = SKILLS_T+20;*/

  const int SKILLS_L = 0;
  const int SKILLS_R = 82;
  const int SKILLS_T = 13;
  const int SKILLS_B = 33;

  skills = newwin(SKILLS_B-SKILLS_T+1, SKILLS_R-SKILLS_L+2, SKILLS_T, SKILLS_L);
  wborder(skills,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,
      ACS_LTEE,ACS_URCORNER,ACS_LTEE,ACS_LRCORNER);
  mvwaddch(skills, 2, 83, ACS_BTEE);
  wattron(skills, COLOR_PAIR(6));
  mvwaddch(skills, 3, 83, 'A');
  mvwaddch(skills, 4, 83, 'b');
  mvwaddch(skills, 5, 83, 'i');
  mvwaddch(skills, 6, 83, 'l');
  mvwaddch(skills, 7, 83, 'i');
  mvwaddch(skills, 8, 83, 't');
  mvwaddch(skills, 9, 83, 'i');
  mvwaddch(skills, 10, 83, 'e');
  mvwaddch(skills, 11, 83, 's');
  wattroff(skills, COLOR_PAIR(6));
  mvwaddch(skills, 12, 83, ACS_TTEE);

  initMod();
  initAbil();
  initSaves();
  initOther();

  wrefresh(skills);
}

static void initMod()
{
  char score[3] = {0};
  char mod[4] = {0};

  /* Strength */
  snprintf(score, 3, "%02d", str);
  snprintf(mod, 4, "%+d", calcSkillMod(str));
  NBOX bStr = {3, 16, 1, 1, "Strength", score, mod, COLOR_PAIR(4)};
  namedBox(skills, bStr);

  /* Dexterity */
  snprintf(score, 3, "%02d", dex);
  snprintf(mod, 4, "%+d", calcSkillMod(dex));
  NBOX bDex = {3, 16, 1, 17, "Dexterity", score, mod, COLOR_PAIR(1)};
  namedBox(skills, bDex);

  /* Constitution */
  snprintf(score, 3, "%02d", con);
  snprintf(mod, 4, "%+d", calcSkillMod(con));
  NBOX bCon = {3, 16, 1, 33, "Constitution", score, mod, COLOR_PAIR(5)};
  namedBox(skills, bCon);

  /* Intelligence */
  snprintf(score, 3, "%02d", intt);
  snprintf(mod, 4, "%+d", calcSkillMod(intt));
  NBOX bInt = {3, 16, 4, 1, "Intelligence", score, mod, COLOR_PAIR(3)};
  namedBox(skills, bInt);

  /* Wisdom */
  snprintf(score, 3, "%02d", wis);
  snprintf(mod, 4, "%+d", calcSkillMod(wis));
  NBOX bWis = {3, 16, 4, 17, "Wisdom", score, mod, COLOR_PAIR(6)};
  namedBox(skills, bWis);

  /* Charisma */
  snprintf(score, 3, "%02d", cha);
  snprintf(mod, 4, "%+d", calcSkillMod(cha));
  NBOX bCha = {3, 16, 4, 33, "Charisma", score, mod, COLOR_PAIR(2)};
  namedBox(skills, bCha); }

static void initAbil()
{
  int i, r, c;
  short color;
  const char *abils[36] = 
    {"Acrobatics", DEX, "Animal Handling", WIS,
     "Arcana", INT, "Athletics", STR, 
     "Deception", CHA, "History", INT,
     "Insight", WIS, "Intimidation", CHA,
     "Investigation", INT, "Medicine", WIS,
     "Nature", INT, "Perception", WIS,
     "Performance", CHA, "Persuasion", CHA,
     "Religion", INT, "Sleight of Hand", DEX,
     "Stealth", DEX, "Survival", WIS};

  NBOX bAbil = {8, 78, 8, 2, "Skills", NULL, NULL, 0};
  namedBox(skills, bAbil);

  for (i = 0; i < 18; i++) {
    r = (i % 6) + 9;
    c = (i / 6) * 25 + 4;
    color = 0;
    mvwprintw(skills, r, c, "   %s", abils[i*2]);

    if (abils[i*2+1] == STR)
      color = COLOR_PAIR(4);
    else if (abils[i*2+1] == DEX)
      color = COLOR_PAIR(1);
    else if (abils[i*2+1] == CON)
      color = COLOR_PAIR(5);
    else if (abils[i*2+1] == INT)
      color = COLOR_PAIR(3);
    else if (abils[i*2+1] == WIS)
      color = COLOR_PAIR(6);
    else if (abils[i*2+1] == CHA)
      color = COLOR_PAIR(2);

    wattron(skills, color);
    mvwprintw(skills, r, c+19, "(%s)", abils[i*2+1]);
    wattroff(skills, color);
  }
}

static void initSaves()
{
  NBOX bThrows = {4, 54, 16, 13, "Saving Throws", NULL, NULL, 0};
  namedBox(skills, bThrows);

}

static void initOther()
{
  char bonus[4] = {0};
  snprintf(bonus, 4, "%+d", 2);

  NBOX bInsp = {3, 16, 1, 50, "Inspiration", NULL, NULL, 0};
  namedBox(skills, bInsp);
  NBOX bPerc = {3, 16, 1, 66, "Passive", "Perception", NULL, 0};
  namedBox(skills, bPerc);
  NBOX bProf = {3, 16, 4, 50, "Proficiency", "Bonus", bonus, 0};
  namedBox(skills, bProf);
}

static int calcSkillMod(int score)
{
  return score/2-5;
}
