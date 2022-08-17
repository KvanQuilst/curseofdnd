/*
 * Curse of DND - nCurses DND Character Sheet
 * tab.c
 */

#include "common.h"
#include "draw.h"
#include "menu.h"

#define TAB_H 24
#define TAB_W 84

WINDOW *initTabWindow(int numTabs, const char *tabNames[])
{
  WINDOW *win;
  int tabSize, maxName;
  int i;

  tabSize = (TAB_W-1) / numTabs;
  if (tabSize < 4) {
    log_print("[ERROR] failed to create new tab window: tab size too small!\n");
    return NULL;
  }
  maxName = tabSize - 3;

  win = newwin(TAB_H, TAB_W, rowSize/2 - TAB_H/2, (colSize-MENU_W)/2 - TAB_W/2);
  if (win == NULL) {
    log_print("[ERROR] failed to create new window \"win\"!");
    return NULL;
  }

  mvwvline(win, 1, 0, ACS_VLINE, TAB_H-2);
  mvwvline(win, 3, TAB_W-1, ACS_VLINE, TAB_H-3);
  mvwaddch(win, 2, TAB_W-1, ACS_URCORNER);
  mvwhline(win, TAB_H-1, 1, ACS_HLINE, TAB_W-2);
  mvwaddch(win, TAB_H-1, 0, ACS_LLCORNER);
  mvwaddch(win, TAB_H-1, TAB_W-1, ACS_LRCORNER);
  mvwhline(win, 2, tabSize+1, ACS_HLINE, TAB_W-tabSize-2);
  mvwaddch(win, 2, tabSize, ACS_LLCORNER);

  for (i = 0; i < numTabs; i++) {
    mvwprintw(win, 1, 2+i*tabSize, "%.*s", maxName, tabNames[i]);
    mvwhline(win, 0, 1+i*tabSize, ACS_HLINE, tabSize-1);
    mvwaddch(win, 1, tabSize*(i+1), ACS_VLINE);
    if (tabSize*i == TAB_W-1)
      mvwaddch(win, 2, tabSize*(i+1), ACS_RTEE);
    else if (i > 0)
      mvwaddch(win, 2, tabSize*(i+1), ACS_BTEE);
  }

  return win;
}
