/*
 * Curse of DND - nCurses DND Character Sheet
 * sheet.h
 */
#pragma once

/* 
 * Initializes the main sheet view if it has not been created yet
 * Brings forward the main sheet view on stdscr
 *
 * returns: 0 on success, -1 on error
 */
int drawSheet(void);

/*
 * Destroys the main sheet view if it has been created
 */
void destroySheet(void);

/* Update Element Functions */
/* NOTE: To update for a level up, destroy and redraw the sheet */
int updateHealth(void);
int updateTempHealth(void);
int updateDeathSave(void);
int updateInspiration(void);
int updateExperience(void);

/*
 * Position Definitions
 * *_L : 0-indexed Line (y value)
 * *_C : 0-indexed Colomn (x value)
 */

/* Character Box */
/* NOTE: The character box is always as wide as the screen */
#define CHARBOX_L 0
#define CHARBOX_C 0

/* Inspiration */
#define INSP_L 9
#define INSP_C 0

/* Proficiency */
#define PROF_L 9
#define PROF_C 25

/* Passwive Wisdom */
#define PASSWIS_L 9
#define PASSWIS_C 52

/* Strength */
#define STR_L 12
#define STR_C 0

/* Dexterity */
#define DEX_L 15
#define DEX_C 0

/* Constitution */
#define CON_L 18
#define CON_C 0

/* Intelligence */
#define INT_L 21
#define INT_C 0

/* Wisdom */
#define WIS_L 24
#define WIS_C 0

/* Charisma */
#define CHA_L 27
#define CHA_C 0

/* Saving Throws */
#define SAVE_L 12
#define SAVE_C 19

/* Skills */
#define SKILL_L 18
#define SKILL_C 19

/* Health */
#define HEALTH_L 9
#define HEALTH_C 78

/* Battle Stats */
#define BATTLE_L 12
#define BATTLE_C 78

/* Hit Die */
#define HITDIE_L 15
#define HITDIE_C 78

/* Death Save */
#define DEATH_L 15
#define DEATH_C 90

/* Spell Casting */
#define SPLCST_L 19
#define SPLCST_C 81

/* Spell Save */
#define SPLSAV_L 23
#define SPLSAV_C 81

/* Spell Attack */
#define SPLATK_L 27
#define SPLATK_C 81
