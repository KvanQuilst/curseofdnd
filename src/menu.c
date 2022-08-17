/*
 * Curse of DND - nCurses DND Character Sheet
 * menu.c
 */

#include "common.h"
#include "draw.h"
#include "menu.h"
#include "statemachine.h"

WINDOW *menu;
PANEL *menuPan;

const char *select[] = {
  "1. Equipment",
  "2. Spell Casting",
  "3. Features and Traits",
  "4. Character Info",
  "5. Help"
};

static void highlight(int line)
{
  wattr_on(menu, COLOR_PAIR(CYAN) | A_UNDERLINE, NULL);
  mvwprintw(menu, line*2, 2, "%s", select[line-1]);
  wattr_off(menu, COLOR_PAIR(CYAN) | A_UNDERLINE, NULL);
}

static void drawSelect(void) 
{
  int i;

  for (i = 0; i < 5; i++) {
    mvwprintw(menu, 2+i*2, 2, "%s", select[i]);
  }
}

static int initMenu()
{
  menu = newwin(rowSize, MENU_W, 0, colSize-MENU_W);
  if (menu == NULL) {
    log_print("[ERROR] failed to create window <menu>!");
    return -1;
  }

  menuPan = new_panel(menu);
  if (menuPan == NULL) {
    log_print("[ERROR] failed to create window <menu>!");
    delwin(menu);
    return -1;
  }

  mvwvline(menu, 0, 0, ACS_VLINE, rowSize);

  return 0;
}

int drawMenu(void)
{
  if (stdscr == NULL) {
    log_print("[ERROR] stdscr is NULL; can't write to screen!");
    return -1;
  }

  if (panel_hidden(menuPan))
    show_panel(menuPan);

  /* Initialize the window if it hasn't been, */
  /* check if initialization completed        */
  if (menu == NULL && initMenu()) return -1;
  drawSelect();

  update_panels();

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
      hide_panel(menuPan);
      s = s_sheet;
      break;

    /* Spell Casting */
    case '2':
      highlight(2);
      s = s_spell;
      break;
  }

  return s;
}
