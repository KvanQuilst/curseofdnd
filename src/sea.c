/*
 * Curse of DND - nCurses DND Character Sheet
 * sea.c
 */

#include "sea.h"

WINDOW *sea[3]; /* 0: Attack | 1: Spells | 2: Equipment */

void loadSeaTri(void)
{
  int row, col;
  getmaxyx(stdscr, row, col);
}

void loadSeaTabs(void)
{
  int row, col;
  getmaxyx(stdscr, row, col);
  sea[0] = newwin(row, col, 2, 0);
  sea[1] = newwin(row, col, 2, 0);
  sea[2] = newwin(row, col, 2, 0);

  /* Tabs */
  attron(COLOR_PAIR(1));
  mvaddch(1, 0, ACS_VLINE);
  mvaddch(1, 12, ACS_VLINE);
  mvhline(0, 1, ACS_HLINE, 11);
  mvprintw(1, 3, "Attacks");

  attron(COLOR_PAIR(4));
  mvaddch(1, 13, ACS_VLINE);
  mvaddch(1, 25, ACS_VLINE);
  mvhline(0, 14, ACS_HLINE, 11);
  mvprintw(1, 15, "Spells");

  attron(COLOR_PAIR(2));
  mvaddch(1, 26, ACS_VLINE);
  mvaddch(1, 38, ACS_VLINE);
  mvhline(0, 27, ACS_HLINE, 11);
  mvprintw(1, 28, "Equipment");
  wnoutrefresh(stdscr);

  /* Equipment */
  makeBox(sea[2], row-3, col, 0, 0);
  mvwaddch(sea[2], 0, 26, ACS_LRCORNER);
  mvwhline(sea[2], 0, 27, ' ', 11);
  mvwaddch(sea[2], 0, 28, ACS_LLCORNER);
  wattroff(sea[2], COLOR_PAIR(2));
  wnoutrefresh(sea[2]);

  /* Spells */
  wattron(sea[1], COLOR_PAIR(4));
  makeBox(sea[1], row-3, col, 0, 0);
  mvwaddch(sea[1], 0, 13, ACS_LRCORNER); 
  mvwhline(sea[1], 0, 14, ' ', 11);
  mvwaddch(sea[1], 0, 25, ACS_LLCORNER);
  wattroff(sea[1], COLOR_PAIR(4));
  wnoutrefresh(sea[1]);

  /* Attacks */
  wattron(sea[0], COLOR_PAIR(1));
  makeBox(sea[0], row-3, col, 0, 0);
  mvwaddch(sea[0], 0, 0, ACS_VLINE);
  mvwhline(sea[0], 0, 1, ' ', 11);
  mvwaddch(sea[0], 0, 12, ACS_LLCORNER);
  wattroff(sea[0], COLOR_PAIR(1));
  wnoutrefresh(sea[0]);
}
