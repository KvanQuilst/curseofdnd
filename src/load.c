/*
 * load.c
 *
 * Load and save handler to and from JSON save files
 */

#include <json-c/json.h>
#include<stdio.h>
#include<string.h>

#include "char.h"
#include "load.h"

int load(char *charName)
{
  json_object *character;
  json_object *object;
  json_object *field;
  char *path;

  /* Append the player name to the path */
  sprintf(path, "../saves/%s.json", charName);

  /* Get the character save */
  character = json_object_from_file(path);
  if (character == NULL) {
    //fprintf(stderr, "%s\n", json_util_get_last_err());
    fprintf(stderr, "%s: no character name provided\n", "APP_NAME");  
    return -1;
  }


  /* Get CharacterInfo Object */
  object = json_object_object_get(character, "characterInfo");
  if (object == NULL) {
    fprintf(stderr, "%s: characterInfo corrupt in save file\n", "APP_NAME");
    return -1;
  }

  /* Character Name */
  field = json_object_object_get(object, "name");
  if (field == NULL) {
    fprintf(stderr, "%s: character name corrupt in save file\n", "APP_NAME");
    return -1;
  }
  name = json_object_get_string(field);
  
  return 0;
}

int save()
{

}
