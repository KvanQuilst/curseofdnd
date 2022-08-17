/*
 * Curse of DND - nCurses DND Character Sheet
 * spell.c
 */

#include "common.h"
#include "draw.h"
#include "statemachine.h"

#define SPELL_H 24
#define SPELL_W 84

WINDOW *spell;

static int initSpell(void)
{
  const char *tabNames[] = {
    "All", "1", "2", "3", "4", "5", "6", "7", "8", "9"
  };

  spell = initTabWindow(10, tabNames);
  if (spell == NULL)
    return -1;

  return 0;
}

int drawSpell(void)
{
  if (stdscr == NULL) {
    log_print("[ERROR] stdscr is NULL; can't write to screen!");
    return -1;
  }

  /* Initialize the window if it hasn't been, */
  /* check if initialization completed        */
  //if (spell == NULL && initSpell()) return -1;
  if (spell == NULL) {
    if (initSpell() < 0)
      return -1;
  }

  touchwin(spell);
  wnoutrefresh(spell);

  return 0;
}

void destroySpell(void)
{
  if (spell != NULL)
    delwin(spell);
}

enum state spellStateMachine(void)
{
  int ch;
  enum state s = s_spell;

  if (drawSpell() < 0) { 
    fprintf(stderr, "Error while drawing window!\n");
    return s_quit;
  }
  doupdate();

  ch = getch();

  switch (ch) {
    
    /* Close Frame */
    case 'q':
      s = s_menu;
      break;

  }

  return s;
}
