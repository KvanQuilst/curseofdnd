/*
 * Curse of DND - nCurses DND Character Sheet
 * menu.h
 */
#pragma once

#define MENU_W 24

/*
 * Initializes the menu view if it has not been created yet
 * Brings forward the menu home view on stdscr
 *
 * returns: 0 on success, -1 on error
 */
int drawMenu(void);

/*
 * Destroys the home view if it has been created
 */
void destroyMenu(void);
