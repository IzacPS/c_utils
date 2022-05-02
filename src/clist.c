#include "clist.h"
#include <stdlib.h>
#include <string.h>

struct clist
{
    uint64_t size;
    uint64_t allocated_size;
    clist_comp_pfn comp_func;
    uint32_t type_size;
    uint8_t  data[];
};
#define CLIST_INITIAL_SIZE 4

static inline uint32_t has_same_memory_content(const void * a, const void *b, uint32_t type_size)
{
    return memcmp(a, b, type_size) == 0;
}

//Using calloc for now
void _clist_init(clist_st **list, uint32_t type_size)
{
    *list = calloc(1, sizeof(struct clist) + type_size * CLIST_INITIAL_SIZE);
    (*list)->allocated_size = CLIST_INITIAL_SIZE;
    (*list)->type_size = type_size;
    (*list)->comp_func = has_same_memory_content;
}

uint64_t clist_size(clist_st *list)
{
    return list->size;
}

void *clist_iter_start(clist_st *list)
{
    return list->data;
}

void *clist_iter_end(clist_st *list)
{
    return list->data + (list->size - 1) * list->type_size;
}

void *clist_iter_at(clist_st *list, uint32_t index)
{
    return list->data + list->size * index;
}

void *clist_iter_next(clist_st *list, void * current, uint32_t add)
{
    return ((uint8_t *)current) + list->type_size * add;
}

void *clist_iter_prev(clist_st *list, void *current, int32_t sub)
{
    return ((uint8_t *)current) - list->type_size * sub;
}

static void clist_realloc(clist_st **list, uint32_t size)
{
    //*list = calloc(1, sizeof(struct clist) + old_data->type_size * size);
    //memcpy(*list, old_data, sizeof(struct clist) + old_data->size * old_data->type_size);
    *list = realloc(*list, sizeof(struct clist) + (*list)->type_size * size);

    (*list)->allocated_size = size;
}

void _clist_add(clist_st **list, void *value)
{
    if((*list)->size == (*list)->allocated_size)
        clist_realloc(list, (*list)->allocated_size * (*list)->allocated_size);

    memcpy((*list)->data + (*list)->size * (*list)->type_size, 
        value, 
        (*list)->type_size);
    (*list)->size++;
}

void _clist_add_at(clist_st *list, uint32_t index, void *value)
{
//TODO: check for index out of bounds
    memcpy(list->data +  index * list->type_size,
        value, 
        list->type_size);
    list->size++;
}

void clist_remove_at(clist_st *list, uint32_t index)
{
    for(void *value = clist_iter_at(list, index); 
        value <= clist_iter_end(list);
    value = clist_iter_next(list, value, 1))
    {
        memcpy(value, clist_iter_next(list, value, 1), list->type_size);
    }
    list->size--;
}

void * clist_get(clist_st *list, uint32_t index)
{
    return (void *)(list->data + index * list->type_size);
}

void clist_set_comp_func(clist_st *list, clist_comp_pfn comp)
{
    list->comp_func = comp;
}

//TODO: implement this functions with a comparation callback as parameter
void _clist_remove(clist_st *list, void* value)
{
    clist_foreach_indexed(list)
    {
        if(list->comp_func(it.value, value, list->type_size))
        {
            clist_remove_at(list, it.index);
        }
    }
}

void clist_sort(clist_st *list, int (*compar)(const void *, const void*))
{
    qsort(list->data, list->size, list->type_size, compar);
}

void _clist_finish(clist_st **list)
{
    free(*list);
}

void clist_clear(clist_st *list)
{
    list->size = 0;
}
