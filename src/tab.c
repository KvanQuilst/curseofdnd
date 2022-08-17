/*
 * Curse of DND - nCurses DND Character Sheet
 * tab.c
 */

#include <stdlib.h>

#include "common.h"
#include "draw.h"
#include "menu.h"

#define TAB_H 24
#define TAB_W 84

TabWindow *initTabWindow(int numTabs, const char *tabNames[])
{
  TabWindow *tab;
  int tabSize;
  int i;

  tabSize = (TAB_W-1) / numTabs;
  if (tabSize < 4) {
    log_print("[ERROR] failed to create new tab window: tab size too small!\n");
    return NULL;
  }

  tab = malloc(sizeof(TabWindow));
  if (tab == NULL) {
    log_print("[ERROR] could not allocated memory for window!\n");
    return NULL;
  }

  tab->win = newwin(TAB_H, TAB_W, rowSize/2 - TAB_H/2, (colSize-MENU_W)/2 - TAB_W/2);
  if (tab->win == NULL) {
    log_print("[ERROR] failed to create new window \"win\"!");
    return NULL;
  }
  tab->numTabs = numTabs;
  tab->tabSize = tabSize;
  tab->maxName = tabSize - 3;

  mvwvline(tab->win, 1, 0, ACS_VLINE, TAB_H-2);
  mvwvline(tab->win, 3, TAB_W-1, ACS_VLINE, TAB_H-3);
  mvwaddch(tab->win, 2, TAB_W-1, ACS_URCORNER);
  mvwhline(tab->win, TAB_H-1, 1, ACS_HLINE, TAB_W-2);
  mvwaddch(tab->win, TAB_H-1, 0, ACS_LLCORNER);
  mvwaddch(tab->win, TAB_H-1, TAB_W-1, ACS_LRCORNER);
  mvwhline(tab->win, 2, tabSize+1, ACS_HLINE, TAB_W-tabSize-2);
  mvwaddch(tab->win, 2, tabSize, ACS_LLCORNER);

  for (i = 0; i < numTabs; i++) {
    mvwprintw(tab->win, 1, 2+i*tabSize, "%.*s", tab->maxName, tabNames[i]);
    mvwhline(tab->win, 0, 1+i*tabSize, ACS_HLINE, tabSize-1);
    mvwaddch(tab->win, 1, tabSize*(i+1), ACS_VLINE);
    if (tabSize*i == TAB_W-1)
      mvwaddch(tab->win, 2, tabSize*(i+1), ACS_RTEE);
    else if (i > 0)
      mvwaddch(tab->win, 2, tabSize*(i+1), ACS_BTEE);
  }

  return tab;
}

void destroyTabWindow(TabWindow *tab)
{
  delwin(tab->win);
  free(tab);
}
