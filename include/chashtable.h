#ifndef CUTILS_CHASHTABLE_H
#define CUTILS_CHASHTABLE_H
#include <stdint.h>

typedef struct chash_table chash_table_st;
typedef struct chash_table_iterator chash_table_iterator_st;

typedef uint32_t (*chash_table_comp_pfn)(void *, void *, uint64_t);

#define CTABLE_KEY(key, key_size) (ctable_key_st){&(key), key_size}

#define chash_table_init(ht, value_type, size) \
    _chash_table_init(&(ht), sizeof(value_type), size)
void _chash_table_init(chash_table_st **ht, uint32_t value_type_size, uint32_t size);

#define chash_table_add(ht, key, key_size, value) _chash_table_add(&(ht), key, key_size, &(value))
void _chash_table_add(chash_table_st **ht, void *key, uint32_t key_size, void *value);

void *chash_table_get(chash_table_st *ht, void *key, uint32_t key_size);

void chash_table_remove(chash_table_st *ht, void *key, uint32_t key_size);

void chash_table_set_comp_key_func(chash_table_st *ht, chash_table_comp_pfn comp_key_func);

//chash_table_iterator_st chash_table_get_iterator(chash_table_st *ht);

//void chash_table_iterator_init(chash_table_iterator_st * iter);

//#define chhash_table_iter_start(ht, iter) _chash_table_iter_start(ht, )
//void _chash_table_iter_start(chash_table_st *ht);

//void chash_table_iter_end(chash_table_st *ht);
//uint32_t chash_table_iter_next(chash_table_st *ht, void * current);

#define chash_table_foreach(ht)\
    for(struct {chash_table_iter_data package; chash_table_iter next} iter = {}; chash_table_iter_next(ht, &iter); )

#define chash_table_finish(ht) _chash_table_finish(&(ht))
void _chash_table_finish(chash_table_st **ht);

#endif //CUTILS_CHASHTABLE_H