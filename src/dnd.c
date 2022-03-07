/*
 * Curse of DND - nCurses DND Character Sheet
 * dnd.c
 */
#include <locale.h>

#include "attack.h"
#include "include.h"
#include "logo.h"
#include "health.h"
#include "skills.h"


/* Prototypes */ 
static void init(void);
static void initColor(void);

const char *name;
const char *race;
const char *background;
const char *alignment;
const char *pclass;
int level;
int expr;

short sStr;
short sDex;
short sCon;
short sInt;
short sWis;
short sCha;

short speed;

int main(int argc, char **argv)
{
  setlocale(LC_ALL, "");
  //int row, col, ch;

  name = "Gnommy Depp";
  race = "Mark of the Shadow Elf";
  background = "Actor";
  alignment = "Chaotic Good";
  pclass = "Rogue";
  level = 1;
  expr = 100;

  sStr = 12;
  sDex = 17;
  sCon = 13;
  sInt = 15;
  sWis = 20;
  sCha = 19;

  speed = 30;

  /* Prepare ncurses */
  init();
  initLogo();
  initSkills();
  initHealth();
  initAttack();
  doupdate();
  //getmaxyx(stdscr, row, col);

  /*while ((ch = getch()) != 'q') {

  }*/

  if (skills != NULL)
    wgetch(skills);

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
  //refresh();
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

void makeBox(WINDOW *win, int nlines, int ncols, 
    int begin_y, int begin_x)
{
  mvwvline(win, begin_y+1, begin_x, ACS_VLINE, nlines-2);
  mvwvline(win, begin_y+1, begin_x+ncols-1, ACS_VLINE, nlines-2);
  mvwhline(win, begin_y, begin_x+1, ACS_HLINE, ncols-2);
  mvwhline(win, begin_y+nlines-1, begin_x+1, ACS_HLINE, ncols-2);
  mvwaddch(win, begin_y, begin_x, ACS_ULCORNER);
  mvwaddch(win, begin_y, begin_x+ncols-1, ACS_URCORNER);
  mvwaddch(win, begin_y+nlines-1, begin_x, ACS_LLCORNER);
  mvwaddch(win, begin_y+nlines-1, begin_x+ncols-1, ACS_LRCORNER);

  wrefresh(win);
}

void namedBox(WINDOW *win, NBOX b)
{
  wattron(win, b.color);
  makeBox(win, b.l, b.c, b.y, b.x);
  wattroff(win, b.color);

  if (b.l1)
    mvwaddnstr(win, b.y, b.x+2, b.l1, b.c-4);
  if (b.l2)
    mvwaddnstr(win, b.y+b.l-1, b.x+b.c-2-strnlen(b.l2, b.c-4), b.l2, b.c-4);
  if (b.content) {
    int midy = b.y + (b.l/2);
    int midx = b.x + (b.c/2) - strnlen(b.content, b.c-4)/2;
    mvwaddnstr(win, midy, midx, b.content, b.c-4);
  }
}
