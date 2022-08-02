/*
 * item.c
 *
 * Item struct for equipment, spells, etc. and the general
 * function to interact with items
 */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"

/* Create Generic Item */
static int item_newItem(item_t item, char *name, char *desc)
{
  size_t len;
  
  len = strnlen(name, MAX_SHORT_LEN);
  if (len <= 0)
    return -1;

  item->next = NULL;
  item->name = strncpy((char *) malloc(len), name, MAX_SHORT_LEN);

  len = strnlen(desc, MAX_LONG_LEN);
  item->desc = strncpy((char *) malloc(len), desc, MAX_LONG_LEN);

  return 0;
}

/* Create an Equipment Item */
item_equip_t item_newEquipment(char *name, char *desc, unsigned count)
{
  item_equip_t item;

  if (name == NULL || desc == NULL)
    return NULL;

  item = malloc(sizeof(item_equip_t));
  if (item_newItem((item_t) item, name, desc) < 0)
    return NULL;

  item->count = count;

  return item;
}

/* Create a Spell Item */
item_spell_t item_newSpell(char *name, char *desc, char *school,
                          char *materials, char *range, char *duration)
{
  item_spell_t item;
  size_t len;

  if (name == NULL || desc == NULL)
    return NULL;

  item = malloc(sizeof(item_spell_t));
  if (item_newItem((item_t) item, name, desc) < 0)
    return NULL;

  len = strnlen(school, MAX_SHORT_LEN);
  item->school = strncpy((char *) malloc(len), school, len);

  len = strnlen(materials, MAX_LONG_LEN);
  item->materials = strncpy((char *) malloc(len), materials, len);

  len = strnlen(range, MAX_SHORT_LEN);
  item->range = strncpy((char *) malloc(len), range, len);

  len = strnlen(duration, MAX_SHORT_LEN);
  item->duration = strncpy((char *) malloc(len), duration, len);

  return item;
}
