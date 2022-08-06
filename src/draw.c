/*
 * Curse of DND - nCurses DND Character Sheet
 * draw.c
 */

#include "common.h"
#include "draw.h"

int rowSize, colSize;

int initCurses(void)
{
  initscr();
  if (stdscr == NULL) {
    log_print("[ERROR]: stdscr could not be initialized!");
    return -1;
  }

  /* General Settings */
  curs_set(0);
  keypad(stdscr, TRUE);
  cbreak();
  noecho();
  nonl();
  wnoutrefresh(stdscr);

  /* Colors */
  start_color();
  use_default_colors();
  init_pair(1, COLOR_RED, -1);
  init_pair(2, COLOR_GREEN, -1);
  init_pair(3, COLOR_YELLOW, -1);
  init_pair(4, COLOR_CYAN, -1);
  init_pair(5, COLOR_BLUE, -1);
  init_pair(6, COLOR_MAGENTA, -1);

  getmaxyx(stdscr, rowSize, colSize);

  return 0;
}

int makeBox(WINDOW *win, int nlines, int ncols, 
    int begin_y, int begin_x)
{
  if (stdscr == NULL) {
    log_print("[ERROR]: stdscr is NULL; can't write to the screen!");
    return -1;
  }

  if (win == NULL) {
    log_print("[ERROR]: makeBox(): win is NULL; can't write to window!");
    return -1;
  }

  mvwvline(win, begin_y+1, begin_x, ACS_VLINE, nlines-2);
  mvwvline(win, begin_y+1, begin_x+ncols-1, ACS_VLINE, nlines-2);
  mvwhline(win, begin_y, begin_x+1, ACS_HLINE, ncols-2);
  mvwhline(win, begin_y+nlines-1, begin_x+1, ACS_HLINE, ncols-2);
  mvwaddch(win, begin_y, begin_x, ACS_ULCORNER);
  mvwaddch(win, begin_y, begin_x+ncols-1, ACS_URCORNER);
  mvwaddch(win, begin_y+nlines-1, begin_x, ACS_LLCORNER);
  mvwaddch(win, begin_y+nlines-1, begin_x+ncols-1, ACS_LRCORNER);

  return 0;
}

int namedBox(WINDOW *win, NBOX b)
{
  if (stdscr == NULL) {
    log_print("[ERROR]: stdscr is NULL; can't write to the screen!");
    return -1;
  }

  if (win == NULL) {
    log_print("[ERROR]: makeBox(): win is NULL; can't write to window!");
    return -1;
  }

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

  return 0;
}
