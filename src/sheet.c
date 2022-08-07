/*
 * Curse of DND - nCurses DND Character Sheet
 * home.c
 */

#include "common.h"
#include "draw.h"

WINDOW *sheet;

static int initSheet(void)
{
  sheet = newwin(rowSize, colSize, 0, 0);
}

int drawSheet(void)
{
  if (stdscr == NULL) {
    log_print("[ERROR] stdscr is NULL; can't write to screen!");
    return -1;
  }

  /* Initialize the window if it hasn't been, */
  /* check if initialization completed        */
  if (sheet == NULL && initSheet()) return -1;

  touchwin(sheet);
  wnoutrefresh(sheet);

  return 0;
}

void destroySheet(void)
{
  if (sheet != NULL)
    delwin(sheet);
}
