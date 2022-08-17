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

  win = newwin(TAB_H, TAB_W, rowSize/2 - TAB_H/2, (colSize-MENU_W)/2 - TAB_W/2);
  if (win == NULL) {
    log_print("[ERROR] failed to create new window \"win\"!");
    return NULL;
  }

  wborder(win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, 
      ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

  return win;
}
