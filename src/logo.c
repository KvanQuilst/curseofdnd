/*
 * Curse of DND - nCurses DND Character Sheet
 * logo.c
 */

#include "logo.h"

WINDOW *logo = NULL;

void initLogo(void)
{
  const int LOGO_T = 0;
  const int LOGO_L = 1;
  const int LOGO_R = 17;
  const int LOGO_C = 74;
  const char *dnd[10] = {
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

  logo = newwin(LOGO_R, LOGO_C, LOGO_T, LOGO_L);
  wborder(logo, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
      ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

  /* Logo */
  wattron(logo, COLOR_PAIR(2));
  for (int i = 0; i < 5; i++)
    mvwprintw(logo, i+1, 1, "%s", dnd[i]);
  wattron(logo, COLOR_PAIR(6));
  for (int i = 5; i < 10; i++)
    mvwprintw(logo, i+1, 1, "%s", dnd[i]);
  wattroff(logo, COLOR_PAIR(6));

  /* Details */
  makeBox(logo, 5, 74, 12, 0);
  mvwaddch(logo, 12, 0, ACS_LTEE);
  mvwaddch(logo, 12, 73, ACS_RTEE);
  mvwprintw(logo, 12, 2, "Name");
  mvwaddch(logo, 12, 25, ACS_RTEE);
  mvwprintw(logo, 12, 26, "|        Race        |");
  mvwaddch(logo, 12, 48, ACS_LTEE);
  mvwprintw(logo, 12, 63, "Alignment");
  mvwprintw(logo, 16, 62, "Experience");
  mvwaddch(logo, 16, 25, ACS_RTEE);
  mvwprintw(logo, 16, 26, "|       Class        |");
  mvwaddch(logo, 16, 48, ACS_LTEE);
  mvwprintw(logo, 16, 2, "Background");

  wattron(logo, A_BOLD | COLOR_PAIR(5));
  mvwprintw(logo, 13, 2, "%s", name);
  mvwprintw(logo, 13, 72-strlen(alignment), "%s", alignment);
  mvwprintw(logo, 13, 3+(71-3)/2-(strlen(race)/2), "%s", race);
  mvwprintw(logo, 15, 2, "%s", background);
  mvwprintw(logo, 15, 3+(71-3)/2-((strlen(pclass)+5)/2), "%s:  %02d", pclass, level);
  mvwprintw(logo, 15, 68, "%4d", expr);
  wattroff(logo, A_BOLD | COLOR_PAIR(5));

  wnoutrefresh(logo);
}
