/*
 * Curse of DND - nCurses DND Character Sheet
 * sea.c
 */

#include "sea.h"

WINDOW *sea[3]; /* 0: Attack | 1: Spells | 2: Equipment */

void loadSeaTri(void)
{
  int row, col;
  getmaxyx(stdsrc, row, col);
}

void loadSeaTabs(void)
{
  int row, col;
  getmaxyx(stdscr, row, col);
  sea[0] = newwin(row, col, 0, 0);
  sea[1] = newwin(row, col, 0, 0);
  sea[2] = newwin(row, col, 0, 0);
  

  /* Equipment */
  wattron(sea[2], COLOR_PAIR(2));
  makeBox(sea[2], row-3, col, 2, 0);
  mvwhline(sea[2], 0, 29, ACS_HLINE, 12);
  mvwaddch(sea[2], 1, 42, ACS_VLINE);
  mvwaddch(sea[2], 2, 42, ACS_BTEE);
  mvwprintw(sea[2], 1, 29, "Equipment");
  wattroff(sea[2], COLOR_PAIR(2));
  wnoutrefresh(sea[2]);

  /* Spells */
  wattron(sea[1], COLOR_PAIR(4));
  makeBox(sea[1], row-3, col, 2, 0);
  mvwhline(sea[1], 0, 14, ACS_HLINE, 12);
  mvwaddch(sea[1], 1, 27, ACS_VLINE);
  mvwaddch(sea[1], 2, 27, ACS_BTEE);
  mvwprintw(sea[1], 1, 15, "Spells");
  wattroff(sea[1], COLOR_PAIR(4));
  wnoutrefresh(sea[1]);

  /* Attacks */
  wattron(sea[0], COLOR_PAIR(1));
  makeBox(sea[0], row-3, col, 2, 0);
  mvwaddch(sea[0], 1, 0, ACS_VLINE);
  mvwhline(sea[0], 0, 1, ACS_HLINE, 12);
  mvwhline(sea[0], 2, 1, ' ', 12);
  mvwaddch(sea[0], 1, 13, ACS_VLINE);
  mvwaddch(sea[0], 2, 0, ACS_VLINE);
  mvwaddch(sea[0], 2, 13, ACS_LLCORNER);
  mvwprintw(sea[0], 1, 2, "Attacks");
  wattroff(sea[0], COLOR_PAIR(1));


  wnoutrefresh(sea[0]);
}
