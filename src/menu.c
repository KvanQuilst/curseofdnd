/*
 * Curse of DND - nCurses DND Character Sheet
 * menu.c
 */

#include "common.h"
#include "draw.h"
#include "statemachine.h"

#define MENU_W 24

WINDOW *menu;

static int initMenu()
{
  menu = newwin(rowSize, MENU_W, 0, colSize-MENU_W);
  if (menu == NULL) {
    log_print("[ERROR] failed to create window <menu>!");
    return -1;
  }

  mvwvline(menu, 0, 0, ACS_VLINE, rowSize);
  mvwprintw(menu, 2, 2, "1. Equipment");
  mvwprintw(menu, 4, 2, "2. Spell Casting");
  mvwprintw(menu, 6, 2, "3. Features and Traits");
  mvwprintw(menu, 8, 2, "4. Character Info");
  mvwprintw(menu, 10, 2, "5. Help");

  return 0;
}

int drawMenu(void)
{
  if (stdscr == NULL) {
    log_print("[ERROR] stdscr is NULL; can't write to screen!");
    return -1;
  }

  /* Initialize the window if it hasn't been, */
  /* check if initialization completed        */
  if (menu == NULL && initMenu()) return -1;

  touchwin(menu);
  wnoutrefresh(menu);

  return 0;
}

void destroyMenu(void)
{
  if (menu != NULL)
    delwin(menu);
}

enum state menuStateMachine(void)
{
  int ch;
  enum state s = s_menu;

  if (drawMenu() < 0) { 
    fprintf(stderr, "Error while drawing window!\n");
    return s_quit;
  }
  doupdate();

  ch = getch();
  
  switch (ch) {
          
    /* Close Menu */
    case 'q':
    case 'e':
      s = s_sheet;
      break;

    /* Spell Casting */
    case '2':
      s = s_spell;
      break;

    /* Quit to home menu */
    case ctrl('q'):
      s = s_home;
      break;
  }

  return s;
}
