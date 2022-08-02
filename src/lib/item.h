/*
 * item.h
 */
#pragma once

#define MAX_SHORT_LEN 64
#define MAX_LONG_LEN 1024

/* Generic Item */
typedef struct item_st *item_t;

struct item_st {
  struct item_st *next;
  char *name;
  char *desc;
};

/* Equipment Item */
typedef struct item_equip_st *item_equip_t;

struct item_equip_st {
  struct item_equip_st *next;
  char *name;       /* SHORT */
  char *desc;       /* LONG */
  unsigned count;
};

/* Spell Item */
typedef struct item_spell_st *item_spell_t;

struct item_spell_st {
  struct item_spell_st *next;
  char *name;       /* SHORT */
  char *desc;       /* LONG */
  char *school;     /* SHORT */
  char *materials;  /* LONG */
  char *range;      /* SHORT */
  char *duration;   /* SHORT */
};

/* Prototypes */

/* Returns NULL for error */
item_equip_t item_newEquipment(char *name, char *desc, unsigned count);

/* Returns NULL for error */
item_spell_t item_newSpell(char *name, char *desc, char *school,
                            char *materials, char *range, char *duration);
