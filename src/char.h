/*
 * Curse of DND - nCurses DND Character Sheet
 * char.h
 */
#pragma once

/* Definitions */
enum ability_type {
  Str, Dex, Con, Int, Wis, Cha 
};

enum skill_type {
  acrobatics, animalHandling, arcana, atheletics, deception, history,
  insight, intimidation, investigation, medicine, nature, perception,
  performance, persuasion, religion, slightOfHand, stealth, survival
};

/* skills abilities correspond index correspond to skill_type index */
extern enum ability_type skill_abil[];

/* Player Details */
extern char *name;
extern char *race;
extern char *background;
extern char *alignment;
extern char *charClass;
extern char *playerName;
extern int level;
extern int xp;

/* Skills */
extern short ability[6];
extern short abilityMod[6];
extern short throwProf[6];
extern short skill[18];
extern short skillProf[18];
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
