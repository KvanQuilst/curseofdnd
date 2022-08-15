/*
 * Curse of DND - nCurses DND Character Sheet
 * dnd.c
 */
#include <locale.h>
#include <stdlib.h>

#include "common.h"
#include "draw.h"
#include "include.h"
#include "home.h"
#include "load.h"
#include "menu.h"
#include "sheet.h"

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
  int ch;
  short running = 1, update = 0;
  
  enum state {s_home, s_sheet, s_menu};
  enum state s = s_home;

  APP_NAME = argv[0];

  log_init();
  log_print("Curse of DND is starting...");

  if (load("../saves/gnommy_depp") < 0) {
    exit(1);
  }

  /* Prepare ncurses */
  if (initCurses() < 0)
    exit(1);

  if (rowSize < 30 || colSize < 102)
    sizeError(rowSize, colSize);

  /*drawMenu();
  drawSheet();*/
  drawHome();
  doupdate();

  while (running) {
    ch = getch();

    //log_print("'%c' pressed!", ch);

    /* Global Commands */
    switch(ch) {
      
    }

    /* State Specific Commands */
    switch(s) {

      /* Home */
      case s_home:
        switch (ch) {
         
          /* Load sheet view */
          case '2':
            update = 1;
            s = s_sheet;
            break;

          /* Quit */
          case ctrl('q'):
            running = 0;
            break;

        }
        break;

      /* Main Sheet */
      case s_sheet:
        switch (ch) {

          /* Open Menu */
          case 'e':
            update = 1;
            s = s_menu;
            break;

          /* Quit to home menu */
          case ctrl('q'):
            update = 1;
            s = s_home;
            break;

        }
        break;

      /* Menu */
      case s_menu:
        switch (ch) {
          
          /* Close Menu */
          case 'q':
          case 'e':
            update = 1;
            s = s_sheet;
            break;

          /* Quit to home menu */
          case ctrl('q'):
            update = 1;
            s = s_home;
            break;

        }
        break;
    }

    switch (s) {
      case s_home:
        //log_print("[INFO] State: Home");
        if (update) drawHome();
        break;
        
      case s_sheet:
        //log_print("[INFO] State: Sheet");
        if (update) drawSheet();
        break;

      case s_menu:
        //log_print("[INFO] State: Menu");
        if (update) drawMenu();
        break;
    }
    doupdate();
  }

  endwin();
  return 0;
}
