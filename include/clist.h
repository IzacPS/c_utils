#ifndef CUTILS_CLIST_H
#define CUTILS_CLIST_H
#include <stdint.h>

//Has to be a pointer
typedef struct clist clist_st; 
typedef uint32_t (*clist_comp_pfn)(const void *, const void *, uint32_t);

//default comparation callback for clist_remove
typedef uint32_t (* has_same_memory_content_pfn)(const void *, const void *, uint64_t);

#define clist_init(list, type) _clist_init(&(list), sizeof(type))
void _clist_init(clist_st **list, uint32_t type_size);

uint64_t clist_size(clist_st *list);

#define clist_add(list, value) _clist_add(&(list), &(value))
void _clist_add(clist_st **list, void *value);

#define clist_add_at(list, index, value) _clist_add_at((list), index, &(value))
void _clist_add_at(clist_st *list, uint32_t index, void *value);

void clist_remove_at(clist_st *list, uint32_t index);

#define clist_remove(list, value, cmp_pfn) _clist_remove((list), &(value))
void _clist_remove(clist_st *list, void *value);

#define clist_finish(list) _clist_finish(&(list))
void _clist_finish(clist_st **list);

void clist_clear(clist_st *list);

void *clist_iter_start(clist_st *list);

void *clist_iter_end(clist_st *list);

void *clist_iter_at(clist_st *list, uint32_t index);

void *clist_iter_next(clist_st *list, void * current, uint32_t add);

void *clist_iter_prev(clist_st *list, void *current, int32_t sub);

void clist_set_comp_func(clist_st *list, clist_comp_pfn comp);

void clist_sort(clist_st *list, int (*compar)(const void *, const void*));
//This get item functionality doesnt check if the index is out of bounds.
//this is to avoid checking with ifs. One solution would be to use mod.
//to guarantee that the index is on the bounds of the list size.
//Observe that this only return a reference.
void * clist_get(clist_st *list, uint32_t index);

//the index inside the loop is a void type.
#define clist_foreach(list) \
    for(void *it = clist_iter_start(list);\
        it <= clist_iter_end(list);\
        it = clist_iter_next(list, it, 1))

#define clist_foreach_indexed(list) \
    for(struct {void *value; uint32_t index; } it = { clist_iter_start(list), 0};\
        it.value <= clist_iter_end(list);\
        it.value = clist_iter_next(list, it.value, 1), it.index++)

#define clist_foreach_step(list, step) \
    for(void *it = clist_iter_start(list);\
        it <= clist_iter_end(list);\
        it = clist_iter_next(list, it, step))

#define clist_foreach_step_indexed(list, step) \
    for(struct {void *value; uint32_t index; } it = { clist_iter_start(list), 0};\
        it.value <= clist_iter_end(list);\
        it.value = clist_iter_next(list, it.value, step), it.index += step)

#define clist_foreach_reverse(list) \
    for(void *it = clist_iter_end(list);\
        it > clist_iter_start(list);\
        it = clist_iter_prev(list, it, 1))

#define clist_foreach_reverse_indexed(list) \
    for(struct {void *value; uint32_t index; } it = { clist_iter_start(list), clist_size(list) - 1};\
        it.value > clist_iter_start(list);\
        it.value = clist_iter_prev(list, it.value, 1), it.index--)

#define clist_foreach_reverse_step(list, step) \
    for(void *it = clist_iter_end(list);\
        it > clist_iter_start(list);\
        it = clist_iter_prev(list, it, step))

#define clist_foreach_reverse_step_indexed(list, step) \
    for(struct {void *value; uint32_t index; } it = { clist_iter_start(list), clist_size(list) - 1};\
        it.value > clist_iter_start(list);\
        it.value = clist_iter_prev(list, it.value, step), it.index -= step)

#endif //CUTILS_CLIST_H