#include "cstack.h"
#include <stdlib.h>

struct cstack
{
    uint64_t size;
    uint64_t allocated_size;
    //custom allocator here
    uint32_t type_size;
    char data[];
};

void _cstack_init(cstack_st **s, uint32_t type_size)
{
    *s = calloc(1, sizeof(struct cstack) + type_size * 8);
    (*s)->allocated_size = 8;
    (*s)->type_size = type_size;
}

static inline _cstack_reallocate(cstack_st **s, uint64_t size)
{
    *s = realloc(*s, sizeof(struct cstack) + (*s)->type_size * size);
    (*s)->allocated_size = size;
}

void _cstack_push(cstack_st **s, void *value)
{
    if((*s)->size == (*s)->allocated_size)
        _cstack_reallocate(s, (*s)->allocated_size * (*s)->allocated_size);

    void *position_to_add = (*s)->data + (*s)->type_size * (*s)->size;
    memcpy(position_to_add, value, (*s)->type_size);
    (*s)->size++;
} 

void *_cstack_pop(cstack_st * s)
{
    if(s->size == 0) return NULL;
    s->size--;
    return s->data + s->type_size * s->size;
}

void *_cstack_peek(cstack_st *s)
{
    if(s->size == 0) return NULL;
    return s->data + s->type_size * (s->size - 1);
}

uint64_t cstack_size(cstack_st *s)
{
    return s->size;
}

void _cstack_finish(cstack_st **s)
{
    free(*s);
}