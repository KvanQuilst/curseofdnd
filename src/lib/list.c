/* 
 * list.c
 * 
 * General list library
 */

#include <stddef.h>

#include "list.h"

void list_append(list list, list_node n)
{
  while(*list != 0)
    *list = (*list)->next;
  *list = n;
  n->next = NULL;
}
