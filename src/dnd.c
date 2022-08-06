/*
 * Curse of DND - nCurses DND Character Sheet
 * dnd.c
 */
#include <locale.h>
#include <stdlib.h>

#include "common.h"
#include "draw.h"
#include "include.h"
//#include "home.h"
#include "home_curse.h"
#include "sea.h"
#include "load.h"

#define ctrl(x) ((x) & 0x1f)

char *APP_NAME;

void sizeError(int row, int col)
{
  endwin();
  printf("Your window is too small!\n");
  exit(0);
}

int main(int argc, char **argv)
{
  setlocale(LC_ALL, "");
  int row, col;
  int ch; 
  short running = 1, update = 0;
  
  APP_NAME = argv[0];

  log_init();
  log_print("Curse of DND is starting...");

  enum {s_home, s_equip, s_detail};
  int state = s_home;

  if (load("../saves/gnommy_depp") < 0) {
    exit(1);
  }

  /* Prepare ncurses */
  if (initCurses() < 0)
    exit(1);

  if (rowSize < 55 || colSize < 86)
    sizeError(rowSize, colSize);

  drawHome();
  doupdate();
  if (colSize < 102)
    initSeaTabs();
  else
    initSeaTri();

  while (running) {
    ch = getch();

    /* Grab Input */
    switch (ch) {

      /* u : level up */
      case 'u':
        break;

      /* e : equipment attacks spells */
      case 'e':
        update = 1;
        state = state != s_home ? s_home : s_equip;
        break;

      /* l : load */
      case 'l':
        break;

      /* s : save */
      case 's':
        break;

      /* q : quit */
      case 'q':
        running = 0;
        break;

    }

    switch (state) {
      case s_home:
        if (update) drawHome();
        break;
        
      case s_equip:
        if (update) loadSea();
        break;
    }
    doupdate();
  }

  endwin();
  return 0;
}
