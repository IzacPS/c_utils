#ifndef CUTILS_CSTACK_H
#define CUTILS_CSTACK_H
#include <stdint.h>

typedef struct cstack cstack_st;

#define cstack_init(s, type) _cstack_init(&(s), sizeof(type))
void _cstack_init(cstack_st **s, uint32_t type_size);

#define cstack_push(s, value) _cstack_push(&(s), &(value))
void _cstack_push(cstack_st **s, void *value); 

#define cstack_pop(s) _cstack_pop((s))
void *_cstack_pop(cstack_st * s);

#define cstack_peek(s) _cstack_peek(s)
void *_cstack_peek(cstack_st *s);

uint64_t cstack_size(cstack_st *s);

#define cstack_finish(s) _cstack_finish(&(s))
void _cstack_finish(cstack_st **s);

#endif //CUTILS_STACK_H