/* 
 * list.h
 * 
 * General list library
 */
#pragma once

typedef struct list_node_t *list_node;

struct list_node_t {
  struct list_node_t *next;
};

typedef list_node *list;

/* Prototypes */
void list_appends(list *list, list_node *n);
