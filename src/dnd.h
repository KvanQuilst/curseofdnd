/*
 * Curse of DND - nCurses DND Character Sheet
 * dnd.h
 */
#pragma once

#define LOGO_L 0
#define LOGO_R 73
#define LOGO_T 0
#define LOGO_B 12

typedef struct _NBOX NBOX;
struct _NBOX{
  int l, c;
  int y, x;
  char *l1, *l2, *content;
  short color;
};

void makeBox(WINDOW *win, int nlines, int ncols,
    int begin_y, int begin_x);

void namedBox(WINDOW *win, NBOX box);