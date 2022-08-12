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

#define jABILITY "ability"
#define jSKILLPROF "skillProficiency"
#define jSAVEPROF "saveProficiency"
#define jINSPIRATION "inspiration"

#define jMAXHP "maxHp"
#define jCURRHP "currHp"
#define jTEMPHP "tempHp"
#define jAC "ac"
#define jINIT "initiative"
#define jSPEED "speed"
#define jHITDIE "hitDie"
#define jDEATHSAVE "deathSaves"

struct character c;

static void calculateChar(void)
{
  int i;

  /* Calculate Proficiency */
  c.proficiency = (c.level-1)/4 + 2;

  /* Calculate Abiltiy Modifiers */
  for (i = 0; i < NUM_ABILITY; i++) {
    c.abilityMod[i] = c.ability[i]/2-5;
  }

  /* Calculate Saving Throws */
  for (i = 0; i < NUM_ABILITY; i++)
    c.saveThrow[i] = c.abilityMod[i] + c.proficiency * c.saveProf[i];

  /* Calculate Skill Scores */
  for (i = 0; i < NUM_SKILLS; i++)
    c.skill[i] = c.abilityMod[skill_abil[i]] + c.proficiency * c.skillProf[i];

  c.passWisdom = 10 + c.proficiency + c.abilityMod[Wis];
}

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
  *var = malloc((len + 1) * sizeof(char));
  if (*var == NULL)
    return -1;

  (*var)[len] = 0;
  strncpy(*var, tmp, len);

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

/* Get a boolean from an object; store as 1 or 0 */
static int getBoolField(json_object *object, const char *fieldName, int *var)
{
  json_object *field;
  
  if (object == NULL || !json_object_is_type(object, json_type_object))
    return -1;

  field = json_object_object_get(object, fieldName);
  if (field == NULL || !json_object_is_type(field, json_type_boolean)) 
    return -1;

  *var = json_object_get_boolean(field);

  return 0;
}

/* Get an array from an object */
static int getIntArrayField(json_object *object, const char *fieldName, 
    int (*var)[], int maxSize)
{
  json_object *field;
  json_object *num;
  size_t size, i;

  if (object == NULL || !json_object_is_type(object, json_type_object))
    return -1;

  field = json_object_object_get(object, fieldName);
  if (field == NULL || !json_object_is_type(field, json_type_array))
    return -1;

  size = json_object_array_length(field);
  for (i = 0; i < size && i < maxSize; i++) {
    num = json_object_array_get_idx(field, i);
    if (num == NULL || !json_object_is_type(num, json_type_int))
      return -1;

    (*var)[i] = json_object_get_int(num);
  }

  return 0;
}

int load(char *path)
{
  json_object *character;
  json_object *object;

  /* Get the character save */
  character = json_object_from_file(path);
  if (character == NULL) {
    log_print("[ERROR] Character name doesn't exist!");  
    return -1;
  }

  /*
   * Get CharacterInfo Object
   */

  object = json_object_object_get(character, "characterInfo");
  if (object == NULL) {
    log_print("[ERROR] CharacterInfo corrupt in save file!");
    return -1;
  }

  /* Character Name */
  if (getShortStringField(object, jNAME, &c.name) < 0) {
    log_print("[ERROR] Failed to get character name!");
    return -1;
  }

  /* Player Name */
  if (getShortStringField(object, jPLAYERNAME, &c.playerName) < 0) {
    log_print("[ERROR] Failed to get player name!");
    return -1;
  }

  /* Race */
  if (getShortStringField(object, jRACE, &c.race) < 0) {
    log_print("[ERROR] Failed to get character race!");
    return -1;
  }

  /* Class */
  if (getShortStringField(object, jCLASS, &c.charClass) < 0) {
    log_print("[ERROR] Failed to get character class!");
    return -1;
  }

  /* Background */
  if (getShortStringField(object, jBACKGROUND, &c.background) < 0) {
    log_print("[ERROR] Failed to get character background!");
    return -1;
  }

  /* Alignment */
  if (getShortStringField(object, jALIGNMENT, &c.alignment) < 0) {
    log_print("[ERROR] Failed to get character alignment!");
    return -1;
  }

  /* Level */
  if (getIntField(object, jLEVEL, (int *) &c.level) < 0) {
    log_print("[ERROR] Failed to get character level!");
    return -1;
  }
/* Experience */ if (getIntField(object, jXP, &c.xp) < 0) {
    log_print("[ERROR] Failed to get chracter experience!");
    return -1;
  }

  /*
   * Skills
   */

  object = json_object_object_get(character, "skills");
  if (object == NULL) {
    log_print("[ERROR] Skills corrupt in save file!");
    return -1;
  }

  /* Ability */
  if (getIntArrayField(object, jABILITY, &c.ability, NUM_ABILITY) < 0) {
    log_print("[ERROR] Failed to get ability scores!");
    return -1;
  }

  /* Skills Proficiency */
  if (getIntArrayField(object, jSKILLPROF, &c.skillProf, NUM_SKILLS) < 0) {
    log_print("[ERROR] Failed to get skill proficiencies!");
    return -1;
  }

  /* Save Proficiecny */
  if (getIntArrayField(object, jSAVEPROF, &c.saveProf, NUM_ABILITY) < 0) {
    log_print("[ERROR] Failed to get saving throw proficiencies!");
    return -1;
  }

  /* Inspiration */
  if (getBoolField(object, jINSPIRATION, &c.inspiration) < 0) {
    log_print("[ERROR] Failed to get inspiration!");
    return -1;
  }


  /* Stats */

  object = json_object_object_get(character, "stats");
  if (object == NULL) {
    log_print("[ERROR] Status corrupt in save file!");
    return -1;
  }

  /* Max HP */
  if (getIntField(object, jMAXHP, (int *) &c.maxHP) < 0) {
    log_print("[ERROR] Failed to get max HP!");
    return -1;
  }

  /* Current HP */
  if (getIntField(object, jCURRHP, (int *) &c.currHP) < 0) {
    log_print("[ERROR] Failed to get current HP!");
    return -1;
  }

  /* Temporary HP */
  if (getIntField(object, jTEMPHP, (int *) &c.tempHP) < 0) {
    log_print("[ERROR] Failed to get temporary HP!");
    return -1;
  }

  /* AC */
  if (getIntField(object, jAC, (int *) &c.armor) < 0) {
    log_print("[ERROR] Failed to get armor class!");
    return -1;
  }

  /* Initiative */
  if (getIntField(object, jINIT, (int *) &c.initiative) < 0) {
    log_print("[ERROR] Failed to get initiative!");
    return -1;
  }

  /* Speed */
  if (getIntField(object, jSPEED, (int *) &c.speed) < 0) {
    log_print("[ERROR] Failed to get the speed!");
    return -1;
  }

  /* Hit Die */
  if (getIntField(object, jHITDIE, (int *) &c.hitDie) < 0) {
    log_print("[ERROR] Failed to get hit die!");
    return -1;
  }

  /* Death Saves */
  if (getIntField(object, jDEATHSAVE, (int *) &c.deathSave) < 0) {
    log_print("[ERROR] Failed to get death save status!");
    return -1;
  }

  calculateChar();
  
  log_print("Character sheet <%s> successfully loaded!", c.name);
  return 0;
}

int save()
{

  return 0;
}
