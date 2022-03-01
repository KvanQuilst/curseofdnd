/*
 * Curse of DND - nCurses DND Character Sheet
 * dnd.c
 */
#include <locale.h>
#include <ncurses.h>
#include <string.h>

#include "char.h"
#include "health.h"
#include "skills.h"

#include "dnd.h"

/* Prototypes */ static void init(void);
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
  initSkills();
  initHealth();
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
  initscr();
  curs_set(0);
  initColor();
  keypad(stdscr, TRUE);
  cbreak();
  noecho();
  border(ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,
      ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);

  /* Logo Box */
  mvhline(LOGO_B, LOGO_L+1, ACS_HLINE, LOGO_R-1);
  mvvline(LOGO_L+1, LOGO_R, ACS_VLINE, LOGO_B-1);
  mvaddch(LOGO_B, LOGO_L, ACS_LTEE);
  mvaddch(LOGO_T, LOGO_R, ACS_TTEE);
  mvaddch(LOGO_B, LOGO_R, ACS_LRCORNER);

  /* Logo */
  attron(COLOR_PAIR(2));
  for (int i = 0; i < 5; i++)
    mvprintw(i+1, 1, "%s", dnd[i]);
  attron(COLOR_PAIR(6));
  for (int i = 5; i < 10; i++)
    mvprintw(i+1, 1, "%s", dnd[i]);
  attroff(COLOR_PAIR(6));

  /* Details */
  makeBox(stdscr, 5, 68, 12, 3);
  mvaddch(12, 3, ACS_TTEE);
  mvaddch(12, 70, ACS_TTEE);
  mvprintw(12, 5, "Name");
  mvaddch(12, 25, ACS_RTEE);
  mvprintw(12, 26, "|        Race        |");
  mvaddch(12, 48, ACS_LTEE);
  mvprintw(12, 60, "Alignment");
  mvprintw(16, 59, "Experience");
  mvaddch(16, 25, ACS_RTEE);
  mvprintw(16, 26, "|       Class        |");
  mvaddch(16, 48, ACS_LTEE);
  mvprintw(16, 5, "Background");

  attron(A_BOLD | COLOR_PAIR(5));
  mvprintw(13, 5, "%s", name);
  mvprintw(13, 69-strlen(alignment), "%s", alignment);
  mvprintw(13, 3+(71-3)/2-(strlen(race)/2), "%s", race);
  mvprintw(15, 5, "%s", background);
  mvprintw(15, 3+(71-3)/2-((strlen(pclass)+5)/2), "%s:  %02d", pclass, level);
  mvprintw(15, 65, "%4d", expr);
  attroff(A_BOLD | COLOR_PAIR(5));

  refresh();
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
