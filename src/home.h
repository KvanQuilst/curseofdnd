/*
 * Curse of DND - nCurses DND Character Sheet
 * home.h
 */
#pragma once

/*
 * Initializes the home view if it has not been created yet
 * Brings forward the home home view on stdscr
 *
 * returns: 0 on success, -1 on error
 */
int drawHome(void);

/*
 * Destroys the home view if it has been created
 */
void destroyHome(void);
