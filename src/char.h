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

extern char *abilityString[NUM_ABILITY];

enum skill_type {
  acrobatics, animalHandling, arcana, atheletics, deception, history,
  insight, intimidation, investigation, medicine, nature, perception,
  performance, persuasion, religion, slightOfHand, stealth, survival
};

/* skills abilities correspond index correspond to skill_type index */
extern enum ability_type skill_abil[];

/* Player Details */
extern struct character {
  char *name;
  char *race;
  char *background;
  char *alignment;
  char *charClass;
  char *playerName;
  short level;
  int xp;

  /* Skills */
  int ability[NUM_ABILITY];
  int abilityMod[NUM_ABILITY];
  int saveThrow[NUM_ABILITY];
  int saveProf[NUM_ABILITY];
  int skill[NUM_SKILLS];
  int skillProf[NUM_SKILLS];
  int inspiration;
  int proficiency;
  int passWisdom;

  /* Stats */
  short maxHP;
  short currHP;
  short tempHP;
  short armor;
  short initiative;
  short speed;
  short hitDie;
  short deathSave;

  /* Spell Casting */
  char *castingAbil;
  short spellSave;
  short spellAttack;
} c;
