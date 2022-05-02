#ifndef CUTILS_CQUEUE_H
#define CUTILS_CQUEUE_H
#include <stdint.h>

typedef struct cqueue cqueue_st;

#define cqueue_init(s, type) _cqueue_init(&(s), sizeof(type))
void _cqueue_init(cqueue_st **s, uint32_t type_size);

#define cqueue_push(s, value) _cqueue_push(&(s), &(value))
void _cqueue_push(cqueue_st **s, void *value); 

#define cqueue_pop(s) _cqueue_pop((s))
void *_cqueue_pop(cqueue_st * s);

#define cqueue_peek(s) _cqueue_peek(s)
void *_cqueue_peek(cqueue_st *s);

uint64_t cqueue_size(cqueue_st *s);

#define cqueue_finish(s) _cqueue_finish(&(s))
void _cqueue_finish(cqueue_st **s);

#endif //CUTILS_CQUEUE_H