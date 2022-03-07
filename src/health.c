/*
 * Curse of DND - nCurses DND Character Sheet
 * health.c
 */

#include "health.h"

WINDOW *health = NULL;

void initHealth() {
  
  const int HEALTH_L = 1;
  const int HEALTH_T = 39;
  const int HEALTH_R = 13; 
  const int HEALTH_C = 48;

  char spd[4] = {0};

  health = newwin(HEALTH_R, HEALTH_C, HEALTH_T, HEALTH_L);
  wborder(health,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,
      ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
  mvwaddch(health, 1, HEALTH_C-1, ACS_BTEE);
  wattron(health, COLOR_PAIR(5));
  mvwaddch(health, 2, HEALTH_C-1, 'V');
  mvwaddch(health, 3, HEALTH_C-1, 'i');
  mvwaddch(health, 4, HEALTH_C-1, 't');
  mvwaddch(health, 5, HEALTH_C-1, 'a');
  mvwaddch(health, 6, HEALTH_C-1, 'l');
  mvwaddch(health, 7, HEALTH_C-1, 'i');
  mvwaddch(health, 8, HEALTH_C-1, 't');
  mvwaddch(health, 9, HEALTH_C-1, 'y');
  wattroff(health, COLOR_PAIR(5));
  mvwaddch(health, 10, HEALTH_C-1, ACS_TTEE);

  NBOX bArmor = {3, 15, 1, 1, "Armor", "Class", NULL};
  namedBox(health, bArmor);

  NBOX bInit = {3, 15, 1, 16, "Initiative", NULL, NULL};
  namedBox(health, bInit);

  snprintf(spd, 4, "%03d", speed);
  NBOX bSpeed = {3, 15, 1, 31, "Speed", NULL, spd};
  namedBox(health, bSpeed);

  NBOX bMax = {3, 45, 5, 1, "Hit Point Maximum: ", "Temporary", NULL};
  namedBox(health, bMax);
  mvwaddstr(health, 7, 3, "Current");
  mvwaddch(health, 6, 22, ACS_VLINE);
  mvwaddch(health, 7, 22, ACS_BTEE);

  NBOX bHit = {3, 22, 9, 1, "Hit Dice: ", NULL, NULL};
  namedBox(health, bHit);

  NBOX bDeath = {3, 22, 9, 23, "Death Saves", "Fail", "o  o  o    o  o  o"};
  namedBox(health, bDeath);
  mvwaddstr(health, 11, 25, "Success");

  wnoutrefresh(health);
}
