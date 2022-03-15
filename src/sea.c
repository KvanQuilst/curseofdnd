/*
 * Curse of DND - nCurses DND Character Sheet
 * sea.c
 */

#include "sea.h"

WINDOW *sbg;
WINDOW *sea[3]; /* 0: Attack | 1: Spells | 2: Equipment */
PANEL *pSea[3];

const int tri_r = 36;
const int tri_c = 76;

void initSeaTri(void)
{
  int row, col, l, offset;
  getmaxyx(stdscr, row, col);
  l = col / 3;
  offset = col % 3;

  sbg = newwin(row, col, 0, 0);
  sea[0] = newwin(row, l, 5, 0);
  sea[1] = newwin(row, l+offset, 5, l);
  sea[2] = newwin(row, l, 5, col-l);

  NBOX nAtt = {row-6, l, 0, 0, "Attacks", NULL, NULL, COLOR_PAIR(1)}; 
  namedBox(sea[0], nAtt);

  NBOX nSpell = {row-6, l+offset, 0, 0, "Spells", NULL, NULL, COLOR_PAIR(5)};
  namedBox(sea[1], nSpell);

  NBOX nEquip = {row-6, l, 0, 0, "Equipment", NULL, NULL, COLOR_PAIR(2)};
  namedBox(sea[2], nEquip);

  pSea[0] = new_panel(sea[0]);
  pSea[1] = new_panel(sea[1]);
  pSea[2] = new_panel(sea[2]);
  set_panel_userptr(pSea[0], pSea[1]);
  set_panel_userptr(pSea[1], pSea[2]);
  set_panel_userptr(pSea[2], pSea[0]);
}

void initSeaTabs(void)
{
  int row, col;
  getmaxyx(stdscr, row, col);
  sbg = newwin(tri_r, tri_c, row/2-tri_r/2+2, col/2-tri_c/2);
  sea[0] = newwin(tri_r-2, tri_c, row/2-tri_r/2+4, col/2-tri_c/2);
  sea[1] = newwin(tri_r-2, tri_c, row/2-tri_r/2+4, col/2-tri_c/2);
  sea[2] = newwin(tri_r-2, tri_c, row/2-tri_r/2+4, col/2-tri_c/2);

  /* Tabs */
  wattron(sbg, COLOR_PAIR(1));
  mvwaddch(sbg, 1, 0, ACS_VLINE);
  mvwaddch(sbg, 1, 12, ACS_VLINE);
  mvwhline(sbg, 0, 1, ACS_HLINE, 11);
  mvwprintw(sbg, 1, 2, "Attacks");

  wattron(sbg, COLOR_PAIR(4));
  mvwaddch(sbg, 1, 13, ACS_VLINE);
  mvwaddch(sbg, 1, 25, ACS_VLINE);
  mvwhline(sbg, 0, 14, ACS_HLINE, 11);
  mvwprintw(sbg, 1, 15, "Spells");

  wattron(sbg, COLOR_PAIR(2));
  mvwaddch(sbg, 1, 26, ACS_VLINE);
  mvwaddch(sbg, 1, 38, ACS_VLINE);
  mvwhline(sbg, 0, 27, ACS_HLINE, 11);
  mvwprintw(sbg, 1, 28, "Equipment");
  wattroff(sbg, COLOR_PAIR(2));

  mvwhline(sbg, 1, 39, ACS_HLINE, tri_c-39);
  mvwaddch(sbg, 1, tri_c-1, ACS_URCORNER);
  //mvwaddch(sbg, 1, tri_c-1, ACS_VLINE);

  /* Attacks */
  wattron(sea[0], COLOR_PAIR(1));
  makeBox(sea[0], tri_r-2, tri_c, 0, 0);
  mvwaddch(sea[0], 0, 0, ACS_VLINE);
  mvwhline(sea[0], 0, 1, ' ', 11);
  mvwaddch(sea[0], 0, 12, ACS_LLCORNER);
  wattroff(sea[0], COLOR_PAIR(1));

  /* Spells */
  wattron(sea[1], COLOR_PAIR(4));
  makeBox(sea[1], tri_r-2, tri_c, 0, 0);
  mvwaddch(sea[1], 0, 13, ACS_LRCORNER); 
  mvwhline(sea[1], 0, 14, ' ', 11);
  mvwaddch(sea[1], 0, 25, ACS_LLCORNER);
  wattroff(sea[1], COLOR_PAIR(4));

  /* Equipment */
  wattron(sea[2], COLOR_PAIR(2));
  makeBox(sea[2], tri_r-2, tri_c, 0, 0);
  mvwaddch(sea[2], 0, 26, ACS_LRCORNER);
  mvwhline(sea[2], 0, 27, ' ', 11);
  mvwaddch(sea[2], 0, 38, ACS_LLCORNER);
  wattroff(sea[2], COLOR_PAIR(2));

  pSea[0] = new_panel(sea[0]);
  pSea[1] = new_panel(sea[1]);
  pSea[2] = new_panel(sea[2]);
  set_panel_userptr(pSea[0], pSea[1]);
  set_panel_userptr(pSea[1], pSea[2]);
  set_panel_userptr(pSea[2], pSea[0]);
}

void loadSea(void)
{
  touchwin(sbg);
  wnoutrefresh(sbg);
  for (int i = 0; i < 3; i++) {
    touchwin(sea[i]);
    wnoutrefresh(sea[i]); 
  }
  update_panels();
}
