/*
 * Curse of DND - nCurses DND Character Sheet
 * spell.c
 */

#include "common.h"
#include "draw.h"
#include "statemachine.h"

#define SPELL_H 20
#define SPELL_W 80

WINDOW *spell;

static int initSpell(void)
{
  spell = newwin(SPELL_H, SPELL_W, rowSize/2 - SPELL_H/2, colSize/2 - SPELL_W/2);
  if (spell == NULL) {
    log_print("[ERROR] failed to create new window \"spell\"!");
    return -1;
  }

  wborder(spell, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, 
      ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

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
