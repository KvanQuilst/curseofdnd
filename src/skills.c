/*
 * Curse of DND - nCurses DND Character Sheet
 * skills.c
 */

#include "skills.h"

WINDOW *skills = NULL;

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

  skills = newwin(SKILLS_B-SKILLS_T, SKILLS_R-SKILLS_L, SKILLS_T, SKILLS_L);
  wborder(skills,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,
      ACS_LTEE,ACS_URCORNER,ACS_LTEE,ACS_LRCORNER);

  /* Skill modifiers */
  /* Strength */
  NBOX bStr = {3, 16, 1, 1, "Strength", "+2", "15", COLOR_PAIR(4)};
  namedBox(skills, bStr);

  /* Dexterity */
  NBOX bDex = {3, 16, 1, 17, "Dexterity", "+5", "18", COLOR_PAIR(1)};
  namedBox(skills, bDex);

  /* Constitution */
  NBOX bCon = {3, 16, 1, 33, "Constitution", "+4", "17", COLOR_PAIR(5)};
  namedBox(skills, bCon);

  /* Intelligence */
  NBOX bInt = {3, 16, 4, 1, "Intelligence", "+2", "16", COLOR_PAIR(3)};
  namedBox(skills, bInt);

  /* Wisdom */
  NBOX bWis = {3, 16, 4, 17, "Wisdom", "+1", "21", COLOR_PAIR(6)};
  namedBox(skills, bWis);

  /* Charisma */
  NBOX bCha = {3, 16, 4, 33, "Charisma", "-1", "09", COLOR_PAIR(2)};
  namedBox(skills, bCha);
  
  /*if (SKILLS_L == 0) {
    mvwaddch(skills, 13, 0, ACS_LTEE);
    mvwaddch(skills, 33, 0, ACS_LTEE);
  }*/


  wrefresh(skills);
}
