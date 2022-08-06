/*
 * Curse of DND - nCurses DND Character Sheet
 * home_curse.c
 */

#include "common.h"
#include "draw.h"

WINDOW *home;

#define LOGO_W 74
#define LOGO_H 13

static int initHome(void)
{
  const char *dndLogo[10] = {
    "     _______  ___   _____    __________  ______________  __    ___     ",
    "    /  ___  \\/  /  /  /  \\  /  /  _____)/ _____/  ___  \\/  \\  /  /_____",
    "   /  /  /  /  /  /  /    \\/  /  /  ___/  __) /  /  /  /    \\/  /  ___/",
    "  /  /__/  /  /__/  /  /\\    /  /__/  /  /___/  /__/  /  /\\    (___  ) ", 
    " /________/\\_______/__/  \\__/\\_______/______/________/__/  \\__/_____/  ",
    "         _______  ______  _______  _______  _______  __    ___         ",
    "        /  ___  \\/  __  \\/  ___  \\/  _____)/  ___  \\/  \\  /  /_____    ",
    "   &   /  /  /  /  /_/  /  /__/  /  /  ___/  /  /  /    \\/  /  ___/    ",
    "      /  /__/  /      _/  ___   /  /__/  /  /__/  /  /\\    (___  )     ",
    "     /________/__/ \\__/__/  /__/\\_______/________/__/  \\__/_____/      "
  }; 
  int x_mid, y_mid;
  int logo_x, logo_y;

  getmaxyx(stdscr, rowSize, colSize); 
  x_mid = colSize/2;
  y_mid = rowSize/2;

  home = newwin(rowSize, colSize, 0, 0);
  if (home == NULL) {
    log_print("[ERROR]: failed to create new window \"home\"!");
    return -1;
  }

  makeBox(home, LOGO_H, LOGO_W + 2*(x_mid%2), y_mid - LOGO_H, x_mid - LOGO_W/2 - (x_mid%2));

  /* Top Half dndLogo[] */
  logo_x = x_mid - (LOGO_W-2)/2;
  logo_y = y_mid - LOGO_H+1;
  wattron(home, COLOR_PAIR(GREEN));
  for (int i = 0; i < 5; i++)
    mvwprintw(home, i+logo_y, logo_x - (colSize%2), "%s", dndLogo[i]);

  /* Bottom Half dndLogo[] */
  wattron(home, COLOR_PAIR(MAGENTA));
  for (int i = 5; i < 10; i++)
    mvwprintw(home, i+logo_y, logo_x + (colSize%2), "%s", dndLogo[i]);
  wattroff(home, COLOR_PAIR(MAGENTA));

  /* Curse of DND */
  mvwprintw(home, y_mid, x_mid-21, "Curse of DnD - nCurses DnD Character Sheet");

  /* New */
  mvwprintw(home, y_mid+3, x_mid-9, "1:  New Character");

  /* Load */
  mvwprintw(home, y_mid+5, x_mid-9, "2:  Load Character");

  /* Help */
  mvwprintw(home, y_mid+7, x_mid-9, "3:  Help");

  return 0;
}

int drawHome(void)
{
  if (stdscr == NULL) {
    log_print("[ERROR] stdscr is NULL; can't write to screen!");
    return -1;
  } 

  /* Initialize the screen if it hasn't been, */
  /* check if initialization completed        */
  if (home == NULL && initHome()) return -1;

  touchwin(home);
  wnoutrefresh(home);

  return 0;
}
