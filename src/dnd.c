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

/* Prototypes */ 
static void init(void);
static void initColor(void);

char *APP_NAME;

short sStr;
short sDex;
short sCon;
short sInt;
short sWis;
short sCha;

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

  sStr = 12;
  sDex = 17;
  sCon = 13;
  sInt = 15;
  sWis = 20;
  sCha = 19;

  /* Prepare ncurses */
  if (initCurses() < 0)
    exit(1);

  getmaxyx(stdscr, row, col);

  if (row < 55 || col < 86)
    sizeError(row, col);

  drawHome();
  /*initHome();
  loadHome();*/
  doupdate();
  if (col < 102)
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

static void init()
{
  initscr();
  curs_set(0);
  initColor();
  keypad(stdscr, TRUE);
  cbreak();
  noecho();
  nonl();
  wnoutrefresh(stdscr);
}

static void initColor() {
  start_color();
  use_default_colors();
  init_pair(1, COLOR_RED, -1);
  init_pair(2, COLOR_GREEN, -1);
  init_pair(3, COLOR_YELLOW, -1);
  init_pair(4, COLOR_CYAN, -1);
  init_pair(5, COLOR_BLUE, -1);
  init_pair(6, COLOR_MAGENTA, -1);
}
