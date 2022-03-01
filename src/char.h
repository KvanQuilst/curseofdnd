/*
 * Curse of DND - nCurses DND Character Sheet
 * char.h
 */
#pragma once

/* Player Details */
extern const char *name;
extern const char *race;
extern const char *background;
extern const char *alignment;
extern const char *pclass;
extern int level;
extern int expr;

/* Skills */
extern short sStr;
extern short sDex;
extern short sCon;
extern short sInt;
extern short sWis;
extern short sCha;

extern short mStr;
extern short mDex;
extern short mCon;
extern short mInt;
extern short mWis;
extern short mCha;

/* Vitality */
extern short armor;
extern short initiative;
extern short speed;
extern char *hitDice;
