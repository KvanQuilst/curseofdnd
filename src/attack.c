/*
 * Curse of DND - nCurses DND Character Sheet
 * attack.c
 */

#include "attack.h"

WINDOW *attack = NULL;

void initAttack()
{
  const int ATTACK_T = 0;
  const int ATTACK_L = 76;
  const int ATTACK_R = 17;
  const int ATTACK_C = 50;
  attack = newwin(ATTACK_R, ATTACK_C, ATTACK_T, ATTACK_L);
  wborder(attack, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
      ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

  mvwaddch(attack, 1, 49, ACS_BTEE);
  wattron(attack, COLOR_PAIR(5));
  mvwaddch(attack, 2, 49, 'A');
  mvwaddch(attack, 3, 49, 't');
  mvwaddch(attack, 4, 49, 't');
  mvwaddch(attack, 5, 49, 'a');
  mvwaddch(attack, 6, 49, 'c');
  mvwaddch(attack, 7, 49, 'k');
  wattroff(attack, COLOR_PAIR(5));
  mvwaddch(attack, 8, 49, ACS_TTEE);

  wrefresh(attack);
}
