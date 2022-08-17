/*
 * Curse of DND - nCurses DND Character Sheet
 * spell.c
 */

#include "common.h"
#include "draw.h"
#include "statemachine.h"

TabWindow *spell;
PANEL *spellPan;

static int initSpell(void)
{
  const char *tabNames[] = {
    "All", "1", "2", "3", "4", "5", "6", "7", "8", "9"
  };

  spell = initTabWindow(sizeof(tabNames)/sizeof(char*), tabNames);
  if (spell == NULL)
    return -1;

  spellPan = new_panel(spell->win);
  if (spellPan == NULL) {
    log_print("[ERROR] failed to create window <spell>!");
    destroyTabWindow(spell);
    return -1;
  }

  return 0;
}

int drawSpell(void)
{
  if (stdscr == NULL) {
    log_print("[ERROR] stdscr is NULL; can't write to screen!");
    return -1;
  }

  if (panel_hidden(spellPan))
    show_panel(spellPan);

  /* Initialize the window if it hasn't been, */
  /* check if initialization completed        */
  if (spell == NULL && initSpell()) return -1;

  update_panels();

  return 0;
}

void destroySpell(void)
{
  if (spell != NULL)
    destroyTabWindow(spell);
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
    
    /* Return to Menu */
    case 'q':
      hide_panel(spellPan);
      s = s_menu;
      break;
  }

  return s;
}
