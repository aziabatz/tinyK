#ifndef TK_LIST_H
#define TK_LIST_H

#include <types.h>
#include <stddef.h>
#include <stdbool.h>
#include <mem/heap/heap.h>

struct linkedlist_node
{
    void * data;
    struct linkedlist_node *next;
};

typedef struct linkedlist_node list_node_t;

struct linkedlist
{
    list_node_t * first;
    list_node_t * last;
    size_t size;
};

typedef struct linkedlist list_t;

list_node_t * insert_head(list_t * list, void * data);
list_node_t * insert_tail(list_t * list, void * data);
void * remove_node(list_t * list, list_node_t * node);
void * remove_node_index(list_t * list, size_t item);

list_node_t * get_node_match_value(list_t * list, void * data, size_t size);
list_node_t * get_node_match_address(list_t * list, void * data);
void empty_list(list_t * list, bool clean_data);

list_t * new_list(heap_t * heap);
void destroy_list(list_t * list);

#endif