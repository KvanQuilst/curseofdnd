/*
 * Curse of DND - nCurses DND Character Sheet
 * home_curse.h
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
 *
 * returns: 0 on success, -1 on error
 */
int destroyHome(void);
