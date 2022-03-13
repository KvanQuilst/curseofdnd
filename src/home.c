/*
 * Curse of DND - nCurses DND Character Sheet
 * home.c
 */

#include "home.h"

WINDOW *home[4]; /* 0: Logo | 1: Skills | 2: Armor | 3: Atacks */
PANEL *pHome[4];

const int logo_r = 17;
const int logo_c = 74;
const int skill_r = 21;
const int skill_c = 84;

int row, col;
short mStr, mDex, mCon, mInt, mWis, mCha;

static void logo(void);

static void skills(void);
static void skillsMod(void);
static void skillsAbil(void);
static void skillsSaves(void);
static void skillsOther(void);
static int calcSkillMod(int score);

void loadHome(void)
{
  getmaxyx(stdscr, row, col);

  logo();
  skills();
  //home[2] = newwin();
  //home[3] = newwin();
  
  pHome[0] = new_panel(home[0]);
  pHome[1] = new_panel(home[1]);
  update_panels();
}

static void logo(void)
{
  const char *dnd[10] = {
    "     _______  ___   _____    __________  ______________  __    ___     ",
    "    /  ___  \\/  /  /  /  \\  /  /  _____)/ _____/  ___  \\/  \\  /  /_____",
    "   /  /  /  /  /  /  /    \\/  /  /  ___/  __) /  /  /  /    \\/  /  ___/",
    "  /  /__/  /  /__/  /  /\\    /  /__/  /  /___/  /__/  /  /\\    (___  ) ", 
    " /________/\\_______/__/  \\__/\\_______/______/________/__/  \\__/_____/  ",
    "         _______  ______  _______  _______  _______  __    ___         ",
    "        /  ___  \\/  __  \\/  ___  \\/  _____)/  ___  \\/  \\  /  /_____    ",
    "   &   /  /  /  /  /_/  /  /__/  /  /  ___/  /  /  /    \\/  /  ___/    ",
    "      /  /__/  /      _/  ___   /  /__/  /  /__/  /  /\\    (___  )     ",
    "     /________/__/ \\__/__/  /__/\\_______/________/__/  \\__/_____/      "
  }; 

  home[0] = newwin(logo_r, logo_c, 0, col/2 - logo_c/2);
  wborder(home[0], ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
      ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    
  /* Logo */
  wattron(home[0], COLOR_PAIR(2));
  for (int i = 0; i < 5; i++)
    mvwprintw(home[0], i+1, 1, "%s", dnd[i]);
  wattron(home[0], COLOR_PAIR(6));
  for (int i = 5; i < 10; i++)
    mvwprintw(home[0], i+1, 1, "%s", dnd[i]);
  wattroff(home[0], COLOR_PAIR(6));
  makeBox(home[0], 5, 74, 12, 0);
  mvwaddch(home[0], 12, 0, ACS_LTEE);
  mvwaddch(home[0], 12, 73, ACS_RTEE);
  mvwprintw(home[0], 12, 2, "Name");
  mvwaddch(home[0], 12, 25, ACS_RTEE);
  mvwprintw(home[0], 12, 26, "|        Race        |");
  mvwaddch(home[0], 12, 48, ACS_LTEE);
  mvwprintw(home[0], 12, 63, "Alignment");
  mvwprintw(home[0], 16, 62, "Experience");
  mvwaddch(home[0], 16, 25, ACS_RTEE);
  mvwprintw(home[0], 16, 26, "|       Class        |");
  mvwaddch(home[0], 16, 48, ACS_LTEE);
  mvwprintw(home[0], 16, 2, "Background");

  wattron(home[0], A_BOLD | COLOR_PAIR(5));
  mvwprintw(home[0], 13, 2, "%s", name);
  mvwprintw(home[0], 13, 72-strlen(alignment), "%s", alignment);
  mvwprintw(home[0], 13, 3+(71-3)/2-(strlen(race)/2), "%s", race);
  mvwprintw(home[0], 15, 2, "%s", background);
  mvwprintw(home[0], 15, 3+(71-3)/2-((strlen(pclass)+5)/2), "%s:  %02d", pclass, level);
  mvwprintw(home[0], 15, 68, "%4d", expr);
  wattroff(home[0], A_BOLD | COLOR_PAIR(5));

  wnoutrefresh(home[0]);
}

static void skills(void)
{
  home[1] = newwin(skill_r, skill_c, logo_r+1, col/2 - skill_c/2);
  wborder(home[1],ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,
      ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);

  mvwaddch(home[1], 1, 83, ACS_BTEE);
  wattron(home[1], COLOR_PAIR(5));
  mvwaddch(home[1], 2, 83, 'A');
  mvwaddch(home[1], 3, 83, 'b');
  mvwaddch(home[1], 4, 83, 'i');
  mvwaddch(home[1], 5, 83, 'l');
  mvwaddch(home[1], 6, 83, 'i');
  mvwaddch(home[1], 7, 83, 't');
  mvwaddch(home[1], 8, 83, 'i');
  mvwaddch(home[1], 9, 83, 'e');
  mvwaddch(home[1], 10, 83, 's');
  wattroff(home[1], COLOR_PAIR(5));
  mvwaddch(home[1], 11, 83, ACS_TTEE);

  skillsMod();
  skillsAbil();
  skillsSaves();
  skillsOther();

  wnoutrefresh(home[1]);
}

static void skillsMod(void)
{
  char score[3] = {0};
  char mod[4] = {0};

  /* Strength */
  snprintf(score, 3, "%02d", sStr);
  snprintf(mod, 4, "%+d", (mStr = calcSkillMod(sStr)));
  NBOX bStr = {3, 16, 1, 1, "Strength", score, mod, COLOR_PAIR(1)};
  namedBox(home[1], bStr);

  /* Dexterity */
  snprintf(score, 3, "%02d", sDex);
  snprintf(mod, 4, "%+d", (mDex = calcSkillMod(sDex)));
  NBOX bDex = {3, 16, 1, 17, "Dexterity", score, mod, COLOR_PAIR(2)};
  namedBox(home[1], bDex);

  /* Constitution */
  snprintf(score, 3, "%02d", sCon);
  snprintf(mod, 4, "%+d", (mCon = calcSkillMod(sCon)));
  NBOX bCon = {3, 16, 1, 33, "Constitution", score, mod, COLOR_PAIR(3)};
  namedBox(home[1], bCon);

  /* Intelligence */
  snprintf(score, 3, "%02d", sInt);
  snprintf(mod, 4, "%+d", (mInt = calcSkillMod(sInt)));
  NBOX bInt = {3, 16, 4, 1, "Intelligence", score, mod, COLOR_PAIR(4)};
  namedBox(home[1], bInt);

  /* Wisdom */
  snprintf(score, 3, "%02d", sWis);
  snprintf(mod, 4, "%+d", (mWis = calcSkillMod(sWis)));
  NBOX bWis = {3, 16, 4, 17, "Wisdom", score, mod, COLOR_PAIR(5)};
  namedBox(home[1], bWis);

  /* Charisma */
  snprintf(score, 3, "%02d", sCha);
  snprintf(mod, 4, "%+d", (mCha = calcSkillMod(sCha)));
  NBOX bCha = {3, 16, 4, 33, "Charisma", score, mod, COLOR_PAIR(6)};
  namedBox(home[1], bCha); 
}

static void skillsAbil(void)
{
  int i, r, c;
  short mod, color;

  const char *STR = "Str";
  const char *DEX = "Dex";
  const char *CON = "Con";
  const char *INT = "Int";
  const char *WIS = "Wis";
  const char *CHA = "Cha";
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
  namedBox(home[1], bAbil);

  for (i = 0; i < 18; i++) {
    r = (i % 6) + 9;
    c = (i / 6) * 25 + 4;
    color = 0;

    if (abils[i*2+1] == STR) {
      mod = mStr;
      color = COLOR_PAIR(1);
    } else if (abils[i*2+1] == DEX) {
      mod = mDex;
      color = COLOR_PAIR(2);
    } else if (abils[i*2+1] == CON) {
      mod = mCon;
      color = COLOR_PAIR(3);
    } else if (abils[i*2+1] == INT) {
      mod = mInt;
      color = COLOR_PAIR(4);
    } else if (abils[i*2+1] == WIS) {
      mod = mWis;
      color = COLOR_PAIR(5);
    } else if (abils[i*2+1] == CHA) {
      mod = mCha;
      color = COLOR_PAIR(6);
    }

    mvwprintw(home[1], r, c, "%+d %s", mod, abils[i*2]);
    wattron(home[1], color);
    mvwprintw(home[1], r, c+19, "(%s)", abils[i*2+1]);
    wattroff(home[1], color);
  }
}

static void skillsSaves(void)
{
  NBOX bThrows = {4, 54, 16, 13, "Saving Throws", NULL, NULL, 0};
  namedBox(home[1], bThrows);

  mvwprintw(home[1], 17, 15, "%+d", mStr);
  wattron(home[1], COLOR_PAIR(1));
  mvwprintw(home[1], 17, 18, "Strength");
  wattroff(home[1], COLOR_PAIR(1));

  mvwprintw(home[1], 17, 34, "%+d", mDex);
  wattron(home[1], COLOR_PAIR(2));
  mvwprintw(home[1], 17, 37, "Dexterity");
  wattroff(home[1], COLOR_PAIR(2));

  mvwprintw(home[1], 17, 50, "%+d", mCon);
  wattron(home[1], COLOR_PAIR(3));
  mvwprintw(home[1], 17, 53, "Constitution");
  wattroff(home[1], COLOR_PAIR(3));

  mvwprintw(home[1], 18, 15, "%+d", mInt);
  wattron(home[1], COLOR_PAIR(4));
  mvwprintw(home[1], 18, 18, "Intelligence");
  wattroff(home[1], COLOR_PAIR(4));

  mvwprintw(home[1], 18, 34, "%+d", mWis);
  wattron(home[1], COLOR_PAIR(5));
  mvwprintw(home[1], 18, 37, "Wisdom");
  wattroff(home[1], COLOR_PAIR(5));

  mvwprintw(home[1], 18, 50, "%+d", mCha);
  wattron(home[1], COLOR_PAIR(6));
  mvwprintw(home[1], 18, 53, "Charisma");
  wattroff(home[1], COLOR_PAIR(6));
}

static void skillsOther(void)
{
  char bonus[4] = {0};
  snprintf(bonus, 4, "%+d", 2);

  NBOX bInsp = {3, 16, 1, 50, "Inspiration", NULL, NULL, 0};
  namedBox(home[1], bInsp);
  NBOX bPerc = {3, 16, 1, 66, "Passive", "Perception", NULL, 0};
  namedBox(home[1], bPerc);
  NBOX bProf = {3, 16, 4, 50, "Proficiency", "Bonus", bonus, 0};
  namedBox(home[1], bProf);
}

static int calcSkillMod(int score)
{
  return score/2-5;
}
