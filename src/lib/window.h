/*
 * window.h
 */
#pragma once

#include <ncurses.h>

enum {
  home, menu, list
} window_type;

typedef struct window_t *window;
struct window_t {
  window_type type;
  WINDOW *w;
  WINDOW *parent;
  void (*destroy)();
};
