/*
 * Curse of DND - nCurses DND Character Sheet
 * draw.h
 */

#include <ncurses.h>
#include <string.h>

enum color {
  WHITE, RED, GREEN, YELLOW, CYAN, BLUE, MAGENTA, BLACK
};

typedef struct NBOX_st NBOX;
struct NBOX_st {
  int l, c;
  int y, x;
  const char *l1, *l2, *content;
  enum color color;
};

typedef struct TabWindow_st TabWindow;
struct TabWindow_st {
  WINDOW *win;
  int numTabs, tabSize, maxName;
};

/* Globals */
extern int rowSize, colSize;


/* Prototypes */

/*
 * Initialize nCurses with the settings used for Curse of DnD
 * 
 * returns: 0 on success, -1 on error
 */
int initCurses(void);


/* 
 * Make a closed box 
 * 
 * @win: WINDOW to draw box to
 * @nlines: height of box (number of lines)
 * @ncols: width of box (number of columns)
 * @begin_y: y position of box relative to win
 * @begin_x: x position of box relative to win
 * returns: 0 on success, -1 on error
 */
int makeBox(WINDOW *win, int nlines, int ncols,
    int begin_y, int begin_x);

/*
 * Create a named box of the following form:
 *  <Name>---------
 * | <Content>     |
 *  -----<Subtitle>
 *
 * @win: WINDOW to draw box to
 * @box: NBOX struct which describes the properties of the box
 * returns: 0 on success, -1 on error
 */
int namedBox(WINDOW *win, NBOX box);

/* 
 * Tab Windows
 */


/*
 * Initialize a generic tabbed window
 *
 * @numTabs: The number of tabs across the top of the window. This number
             should correspond to number of tabNames
 * @tabNames: The name of each tab across the top
 * returns: An intialized window with a generic tab structure drawn to it
 */
TabWindow *initTabWindow(int numTabs, const char *tabNames[]);

/*
 * Destroy a TabWindow
 *
 * @tab: the TabWindow to be destroyed
 */
void destroyTabWindow(TabWindow *tab);
