/*
 * load.c
 *
 * Load and save handler to and from JSON save files
 */

#include <json-c/json.h>
#include<stdio.h>
#include<string.h>

#include "common.h"
#include "char.h"
#include "load.h"

#define jNAME "name"
#define jPLAYERNAME "playerName"
#define jRACE "race"
#define jCLASS "class"
#define jBACKGROUND "background"
#define jALIGNMENT "alignment"
#define jLEVEL "level"
#define jXP "xp"

char *name;
char *playerName;
char *race;
char *charClass;
char *background;
char *alignment;
int level, xp;

/* Get a string field from an object */
static int getShortStringField(json_object *object, const char *fieldName, char **var)
{
  json_object *field;
  const char *tmp;
  size_t len;

  if (object == NULL || !json_object_is_type(object, json_type_object))
    return -1;

  field = json_object_object_get(object, fieldName);
  if (field == NULL || !json_object_is_type(field, json_type_string))
    return -1;

  tmp = json_object_get_string(field);
  if (tmp == NULL)
    return -1;

  len = strnlen(tmp, MAX_SHORT_LEN);
  *var = malloc(len * sizeof(char) + (len == MAX_SHORT_LEN));
  if (*var == NULL)
    return -1;

  strncpy(*var, tmp, len + (len == MAX_SHORT_LEN));

  return 0;
}

/* Get an int from an object */
static int getIntField(json_object *object, const char *fieldName, int *var)
{
  json_object *field;
   
  if (object == NULL || !json_object_is_type(object, json_type_object))
    return -1;

  field = json_object_object_get(object, fieldName);
  if (field == NULL || !json_object_is_type(field, json_type_int))
    return -1;

  *var = json_object_get_int(field);

  return 0;
}

int load(char *path)
{
  json_object *character;
  json_object *object;
  json_object *field;
  const char *tmp;
  size_t len;

  /* Get the character save */
  character = json_object_from_file(path);
  if (character == NULL) {
    log_print("Character name doesn't exist!");  
    return -1;
  }

  /*
   * Get CharacterInfo Object
   */

  object = json_object_object_get(character, "characterInfo");
  if (object == NULL) {
    log_print("CharacterInfo corrupt in save file!");
    return -1;
  }

  /* Character Name */
  if (getShortStringField(object, jNAME, &name) < 0) {
    log_print("Failed to get character name!");
    return -1;
  }

  /* Player Name */
  if (getShortStringField(object, jPLAYERNAME, &playerName) < 0) {
    log_print("Failed to get player name!");
    return -1;
  }

  /* Race */
  if (getShortStringField(object, jRACE, &race) < 0) {
    log_print("Failed to get character race!");
    return -1;
  }

  /* Class */
  if (getShortStringField(object, jCLASS, &charClass) < 0) {
    log_print("Failed to get character class!");
    return -1;
  }

  /* Background */
  if (getShortStringField(object, jBACKGROUND, &background) < 0) {
    log_print("Failed to get character background!");
    return -1;
  }

  /* Alignment */
  if (getShortStringField(object, jALIGNMENT, &alignment) < 0) {
    log_print("Failed to get character alignment!");
    return -1;
  }

  /* Level */
  if (getIntField(object, jLEVEL, &level) < 0) {
    log_print("Failed to get character level!");
    return -1;
  }

  /* Experience */
  if (getIntField(object, jXP, &xp) < 0) {
    log_print("Failed to get chracter experience!");
    return -1;
  }
  
  log_print("Character sheet <%s> successfully loaded!", name);
  return 0;
}

int save()
{

}
