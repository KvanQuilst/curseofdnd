/*
 * Curse of DND - nCurses DND Character Sheet
 * dnd.c
 */

#include <stdlib.h>

#include "common.h"
#include "draw.h"
#include "load.h"
#include "statemachine.h"

char *APP_NAME;

int main(int argc, char **argv)
{
  enum state s = s_home;

  APP_NAME = argv[0];

  log_init();
  log_print("Curse of DND is starting...");

  if (load("../saves/gnommy_depp") < 0) {
    exit(1);
  }

  /* Prepare ncurses */
  if (initCurses() < 0) exit(1);

  while (s != s_quit) {
    switch(s) {

      case s_home:
        s = homeStateMachine();
        break;

      case s_sheet:
        s = sheetStateMachine();
        break;

      case s_menu:
        s = menuStateMachine();
        break;

      case s_spell:
        s = spellStateMachine();
        break;

      case s_quit:
        break;
    }
  }

  endwin();
  return 0;
}
