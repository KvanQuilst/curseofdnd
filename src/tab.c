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

  if (numTabs > 10) {
    log_print("[ERROR] failed to create new tab window: too many tabs!");
    return NULL;
  }

  tabSize = (TAB_W-1) / numTabs;
  if (tabSize < 4) {
    log_print("[ERROR] failed to create new tab window: tab size too small!");
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
  tab->currTab = 0;

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
    if (tabSize*(i+1) == TAB_W-1)
      mvwaddch(tab->win, 2, TAB_W-1, numTabs == 1 ? ACS_VLINE : ACS_RTEE);
    else if (i > 0)
      mvwaddch(tab->win, 2, tabSize*(i+1), ACS_BTEE);
  }

  return tab;
}

void destroyTabWindow(TabWindow *tab)
{
  if (tab != NULL) {
    delwin(tab->win);
    free(tab);
  }
}

int changeTabWindow(TabWindow *tab, int tabIdx)
{
  if (tab == NULL) {
    log_print("[ERROR] changeTabWindow: tab is NULL!");
    return -1;
  }

  if (tabIdx == tab->currTab)
    return 0;
  if (tabIdx >= tab->numTabs) {
    log_print("[ERROR] changeTabWindow: the tab index (%d) provided \
        is larger than the number of tabs (%d)!",
        tabIdx, tab->numTabs);
    return -1;
  }

  /* Previous Tab Cover */
  //if (tab->currTab == tab->numTabs-1 && tab->tabSize*(tab->numTabs-1) == TAB_W-1) {}*/

    /* Left */
  if (tab->currTab == 0)
    mvwaddch(tab->win, 2, 0, ACS_LTEE);
  else
    mvwaddch(tab->win, 2, tab->tabSize*tab->currTab, ACS_BTEE);

  mvwaddch(tab->win, 2, tab->tabSize*(tab->currTab+1), ACS_BTEE);
  mvwhline(tab->win, 2, tab->tabSize*tab->currTab+1, ACS_HLINE, tab->tabSize-1);


  /* New Tab Uncover */

  tab->currTab = tabIdx;

    /* Left */
  if (tabIdx == 0)
    mvwaddch(tab->win, 2, 0, ACS_VLINE);
  else
    mvwaddch(tab->win, 2, tab->tabSize*tabIdx, ACS_LRCORNER);

  mvwaddch(tab->win, 2, tab->tabSize*(tabIdx+1), ACS_LLCORNER);
  mvwhline(tab->win, 2, tab->tabSize*tabIdx+1, ' ', tab->tabSize-1);

  return 0;
}
