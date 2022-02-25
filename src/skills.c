/*
 * Curse of DND - nCurses DND Character Sheet
 * skills.c
 */

#include "skills.h"

WINDOW *skills = NULL;

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
  char *abils[18] = {"Acrobatics", "Animal Handling", "Arcana",
                     "Athletics", "Deception", "History",
                     "Insight", "Intimidation", "Investigation",
                     "Medicine", "Nature", "Perception",
                     "Performance", "Persuasion", "Religion",
                     "Sleight of Hand", "Stealth", "Survival"};

  NBOX bAbil = {8, 78, 8, 2, "Skills", NULL, NULL, 0};
  namedBox(skills, bAbil);

  mvwaddstr(skills, 9, 4, "   Acrobatics");
  wattron(skills, COLOR_PAIR(1));
  mvwaddstr(skills, 9, 23, "(Dex)");
  wattroff(skills, COLOR_PAIR(1));

  mvwaddstr(skills, 10, 4, "   Animal Handling");
  wattron(skills, COLOR_PAIR(6));
  mvwaddstr(skills, 10, 23, "(Wis)");
  wattroff(skills, COLOR_PAIR(6));

  mvwaddstr(skills, 11, 4, "   Arcana");
  wattron(skills, COLOR_PAIR(3));
  mvwaddstr(skills, 11, 23, "(Int)");
  wattroff(skills, COLOR_PAIR(3));

  mvwaddstr(skills, 12, 4, "   Athletics");
  wattron(skills, COLOR_PAIR(4));
  mvwaddstr(skills, 12, 23, "(Str)");
  wattroff(skills, COLOR_PAIR(4));

  mvwaddstr(skills, 13, 4, "+2 Deception");
  wattron(skills, COLOR_PAIR(2));
  mvwaddstr(skills, 13, 23, "(Cha)");
  wattroff(skills, COLOR_PAIR(2));

  mvwaddstr(skills, 14, 4, "   History");
  wattron(skills, COLOR_PAIR(3));
  mvwaddstr(skills, 14, 23, "(Int)");
  wattroff(skills, COLOR_PAIR(3));

  /* --- */

  mvwaddstr(skills, 9, 29, "   Insight");
  wattron(skills, COLOR_PAIR(3));
  mvwaddstr(skills, 9, 48, "(Int)");
  wattroff(skills, COLOR_PAIR(3));

  mvwaddstr(skills, 10, 29, "   Intimidation");
  wattron(skills, COLOR_PAIR(2));
  mvwaddstr(skills, 10, 48, "(Cha)");
  wattroff(skills, COLOR_PAIR(2));

  mvwaddstr(skills, 11, 29, "   Investigation");
  wattron(skills, COLOR_PAIR(3));
  mvwaddstr(skills, 11, 48, "(Int)");
  wattroff(skills, COLOR_PAIR(3));
  
  mvwaddstr(skills, 12, 29, "   Medicine");
  wattron(skills, COLOR_PAIR(6));
  mvwaddstr(skills, 12, 48, "(Wis)");
  wattroff(skills, COLOR_PAIR(6));

  wattron(skills, A_UNDERLINE);
  mvwaddstr(skills, 13, 29, "+2 Nature");
  wattroff(skills, A_UNDERLINE);
  wattron(skills, COLOR_PAIR(3));
  mvwaddstr(skills, 13, 48, "(Int)");
  wattroff(skills, COLOR_PAIR(3));

  mvwaddstr(skills, 14, 29, "   Perception");
  wattron(skills, COLOR_PAIR(6));
  mvwaddstr(skills, 14, 48, "(Wis)");
  wattroff(skills, COLOR_PAIR(6));

  /* --- */


  mvwaddstr(skills, 9, 54, "   Performance");
  wattron(skills, COLOR_PAIR(2));
  mvwaddstr(skills, 9, 73, "(Cha)");
  wattroff(skills, COLOR_PAIR(2));

  mvwaddstr(skills, 10, 54, "   Persuasion");
  wattron(skills, COLOR_PAIR(2));
  mvwaddstr(skills, 10, 73, "(Cha)");
  wattroff(skills, COLOR_PAIR(2));

  mvwaddstr(skills, 11, 54, "   Religion");
  wattron(skills, COLOR_PAIR(3));
  mvwaddstr(skills, 11, 73, "(Int)");
  wattroff(skills, COLOR_PAIR(3));

  mvwaddstr(skills, 12, 54, "   Sleight of Hand");
  wattron(skills, COLOR_PAIR(1));
  mvwaddstr(skills, 12, 73, "(Dex)");
  wattroff(skills, COLOR_PAIR(1));

  mvwaddstr(skills, 13, 54, "   Stealth");
  wattron(skills, COLOR_PAIR(1));
  mvwaddstr(skills, 13, 73, "(Dex)");
  wattroff(skills, COLOR_PAIR(1));

  mvwaddstr(skills, 14, 54, "+2 Survival");
  wattron(skills, COLOR_PAIR(6));
  mvwaddstr(skills, 14, 73, "(Wis)");
  wattroff(skills, COLOR_PAIR(6));
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
