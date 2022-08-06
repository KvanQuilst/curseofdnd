/*
 * Curse of DND - nCurses DND Character Sheet
 * char.h
 */
#pragma once

/* Definitions */
#define NUM_ABILITY 6
#define NUM_SKILLS 18

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
extern short level;
extern int xp;

/* Skills */
extern short ability[NUM_ABILITY];
extern short abilityMod[NUM_ABILITY];
extern short saveProf[NUM_ABILITY];
extern short skill[NUM_SKILLS];
extern short skillProf[NUM_SKILLS];
extern short inspiration;
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

/* Stats */
extern short maxHP;
extern short currHP;
extern short tempHP;
extern short armor;
extern short initiative;
extern short speed;
extern short hitDie;
extern short deathSave;
