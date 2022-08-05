/*
 * Curse of DND - nCurses DND Character Sheet
 * char.h
 */
#pragma once

//TODO combine max/short constants -> common.h?
#define MAX_SHORT_LEN 64

/* Player Details */
extern char *name;
extern char *race;
extern char *background;
extern char *alignment;
extern char *pclass;
extern char *pname;
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
