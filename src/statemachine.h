/*
 * Curse of DND - nCurses DND Character Sheet
 * statemachine.h
 */
#pragma once

enum state {s_quit, s_home, s_sheet, s_menu, s_spell};

/*
 * State Machine for Home View
 *
 * returns: the current state of the machine
 */
enum state homeStateMachine(void);

/*
 * State Machine for Sheet View
 *
 * returns: the current state of the machine
 */
enum state sheetStateMachine(void);

/*
 * State Machine for Menu View
 *
 * returns: the current state of the machine
 */
enum state menuStateMachine(void);

/*
 * State Machine for Spell View
 *
 * returns: the current state of the machine
 */
enum state spellStateMachine(void);
