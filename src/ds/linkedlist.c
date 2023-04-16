#include <ds/linkedlist.h>

static heap_t * _heap = NULL;

static inline list_node_t * get_prev_node(list_t * list, list_node_t * node)
{
    list_node_t * prev = list->first;
    while (prev)
    {
        if(prev->next == node)
        {
            return prev;
        }
    }
    return NULL;
}

list_t * new_list(heap_t * heap)
{
    if(!heap)
        return NULL;

    _heap = heap;

    list_t * list = kmalloc(heap, sizeof(list_t));
    
    list->first = list->last = list->size = NULL;

    return list;
}

void destroy_list(list_t * list)
{
    if(list->size)
    {
        empty_list(list,true);
    }

    kfree(_heap, list);
}

list_node_t * insert_head(list_t * list, void * data)
{
    if(!list || !data)
    {
        return NULL;
    }

    list_node_t * node = kmalloc(_heap, sizeof(list_node_t));
    if(!node)
        return NULL;

    list_node_t * next = list->first;

    if(next == NULL)
    {
        list->last = node;
    }

    node->next = next;
    node->data = data;

    list->first = node;
    list->size++;

    return node;
}

list_node_t * insert_tail(list_t * list, void * data)
{
    if(!list || !data)
    {
        return NULL;
    }

    list_node_t * node = kmalloc(_heap, sizeof(list_node_t));
    if(!node)
        return NULL;

    node->data = data;
    node->next = NULL;

    list_node_t * prev = list->last;
    if(prev != NULL)
    {
        prev->next = node;
    }
    else
    {
        list->first = node;
    }


    list->last = node;
    list->size++;

    return node;
}

void * remove_node(list_t * list, list_node_t * node)
{
    if(!list || !node)
        return NULL;

    list_node_t * prev = get_prev_node(list, node);
    if(!prev)
        return NULL;

    prev->next = node->next;
    void * data = node->data;
    
    kfree(_heap, node);
    list->size--;

    return data;
}

list_node_t * get_node(list_t * list, size_t item)
{
    if(!list || item>=list->size)
        return NULL;

    list_node_t * node = list->first;

    for(size_t i = 0; i != item; i++)
    {
        if(!node)
            return NULL;
        if(item == i)
        {
            return node;
        }
        node = node->next;
    }
}

void * remove_node_index(list_t * list, size_t item)
{
    list_node_t * node = get_node(list, item);
    return remove_node(list, node);
}

void * get_item(list_t * list, size_t item)
{
    list_node_t * node = get_node(list, item);
    return node->data;
}

void empty_list(list_t * list, bool clean_data)
{
    if(!list)
        return;

    list_node_t * node = list->first;
    
    while(node)
    {
        if(clean_data)
            kfree(_heap, node->data);
        kfree(_heap, node);
        node = node->next;
    }

    list->size = 0;
}

list_node_t * get_node_match_value(list_t * list, void * data, size_t size);
list_node_t * get_node_match_address(list_t * list, void * data);