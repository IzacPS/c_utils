#include "chashtable.h"
#include <stdlib.h>
#include <string.h>
#include "array_utils.h"

#include <stdio.h>

#include "fnv.h"
// #include "murmur3.h"
// #define XXH_STATIC_LINKING_ONLY   /* access advanced declarations */
// #define XXH_IMPLEMENTATION   /* access definitions */
// #include "xxhash.h"

static uint32_t ctable_size_primes[] ={
    11,17,37,67,127,257,521,1031,2053,
    4099,8209,16411,32771,65537,131101,
    262147,524309,1048583,2097169};

//TODO:ajust the alignment
struct ctable_bucket
{
    uint64_t    hash;
    void        *key;
    uint32_t    key_size;
    uint32_t    is_in_use;
    char        data[];
};

struct chash_table_iterator_data
{
    void *key;
    void *value;
    uint32_t key_size;
    uint32_t value_size;
};

struct chash_table_iterator
{
    struct ctable_bucket *current;
    struct chash_table_iterator_data data;
};

static inline uint32_t __comp_key(void *a, void *b, uint64_t size)
{
    return !memcpy(a, b, size);
}

struct chash_table
{
    uint64_t                size;

    struct ctable_bucket    *__temp_bucket;
    struct ctable_bucket    *__insert_bucket;
    chash_table_comp_pfn                comp_key_func;
    uint32_t                *allocated_size;
    uint32_t                value_type_size;
    char                    buckets[];
};

static inline uint64_t __cbucket_size(chash_table_st *ht)
{
    return (ht)->value_type_size + sizeof(struct ctable_bucket);
}
static inline struct ctable_bucket *__cbucket_at(chash_table_st *ht, uint32_t idx)
{
    return (struct ctable_bucket*)((ht)->buckets + idx * __cbucket_size(ht));
}

void _chash_table_init(chash_table_st **ht, uint32_t value_type_size, uint32_t size)
{
    uint32_t *new_size;
    uint32_t i = 0;

    do
    {
        new_size = &ctable_size_primes[i];
    }while(ctable_size_primes[i++] <= size);

    *ht = calloc(1, sizeof(struct chash_table) + ((sizeof(struct ctable_bucket) + value_type_size) * (*new_size)));
    (*ht)->allocated_size = new_size;
    (*ht)->value_type_size = value_type_size;
    (*ht)->comp_key_func = __comp_key;

    (*ht)->__temp_bucket = calloc(1, (*ht)->value_type_size + sizeof(struct ctable_bucket));
    (*ht)->__insert_bucket = calloc(1, (*ht)->value_type_size + sizeof(struct ctable_bucket));
}


void chash_table_set_comp_key_func(chash_table_st *ht, chash_table_comp_pfn comp_key_func)
{
    ht->comp_key_func = comp_key_func;
}

static void _chash_table_reallocate(chash_table_st ** ht)
{
    uint64_t old_bucket_size = *(*ht)->allocated_size;
    ++(*ht)->allocated_size;
    chash_table_st *old_ht = *ht;

    *ht = calloc(1, sizeof(struct chash_table) + (__cbucket_size(old_ht) * (*(old_ht)->allocated_size)));
    
    (*ht)->value_type_size = old_ht->value_type_size;
    (*ht)->allocated_size = old_ht->allocated_size;
    (*ht)->__temp_bucket = old_ht->__temp_bucket;
    (*ht)->__insert_bucket = old_ht->__insert_bucket;

    for(uint64_t i = 0; i < old_bucket_size; i++)
    {
        struct ctable_bucket *bucket = __cbucket_at(old_ht, i);
        
        if(!bucket->is_in_use) continue;

        _chash_table_add(ht, bucket->key, bucket->key_size, bucket->data);
    }
    free(old_ht);
}

static inline uint32_t get_probe_distance(int32_t initial_probe_index, int32_t current_probe_index, uint64_t size)
{
    if(initial_probe_index <= current_probe_index)
        return current_probe_index - initial_probe_index;
    return current_probe_index + (size - initial_probe_index);
}

void _chash_table_add(chash_table_st **ht, void *key, uint32_t key_size, void *value)
{
    float factor = *(*ht)->allocated_size * 0.8f;
    if((*ht)->size >= factor)
        _chash_table_reallocate(ht);

    uint64_t hash = fnv_64a_buf(key, key_size, FNV1A_64_INIT);
    //uint64_t hash = XXH64(key.data, key.size, 0);

    uint64_t initial_probe_bucket = hash % (*(*ht)->allocated_size);
    
    uint64_t current_entry_dib = 0;
    uint64_t entry_to_insert_dib = 0;
    
    (*ht)->__insert_bucket->hash = hash;
    (*ht)->__insert_bucket->key = calloc(1, key_size);
    (*ht)->__insert_bucket->key_size = key_size;
    (*ht)->__insert_bucket->is_in_use = 1;
    memcpy((*ht)->__insert_bucket->key, key, key_size);
    memcpy((*ht)->__insert_bucket->data, value, (*ht)->value_type_size);

    uint64_t current_index = initial_probe_bucket;
    for(uint64_t i = 0; i < *(*ht)->allocated_size; i++)
    {
        current_index = (current_index + i) % (*(*ht)->allocated_size);
        struct ctable_bucket *bucket = __cbucket_at(*ht, current_index);
        if(!bucket->is_in_use)
        {
            memcpy(bucket, (*ht)->__insert_bucket, (*ht)->value_type_size + sizeof(struct ctable_bucket));
            break;
        }
        else
        {
            current_entry_dib = get_probe_distance(bucket->hash % *(*ht)->allocated_size, current_index, *(*ht)->allocated_size);
            if(entry_to_insert_dib > current_entry_dib)
            {
                memcpy((*ht)->__temp_bucket, bucket, (*ht)->value_type_size + sizeof(struct ctable_bucket));
                
                memcpy(bucket, (*ht)->__insert_bucket, (*ht)->value_type_size + sizeof(struct ctable_bucket));

                memcpy((*ht)->__insert_bucket, (*ht)->__temp_bucket, (*ht)->value_type_size + sizeof(struct ctable_bucket));
                
                entry_to_insert_dib = current_entry_dib;
            }
        }
        entry_to_insert_dib++;
    }
    (*ht)->size++;
}

void *chash_table_get(chash_table_st *ht, void *key, uint32_t key_size)
{
    uint64_t hash = fnv_64a_buf(key, key_size, FNV1A_64_INIT);
    //uint64_t hash = XXH64(key.data, key.size, 0);

    uint64_t initial_probe_bucket = hash % (*ht->allocated_size);
    uint64_t current_entry_dib = 0;
    
    for(uint64_t i = 0; i < *ht->allocated_size; i++)
    {
        uint64_t current_index = (initial_probe_bucket + i) % (*ht->allocated_size);
        struct ctable_bucket *bucket = __cbucket_at(ht, current_index);

        current_entry_dib = get_probe_distance(bucket->hash % *(ht)->allocated_size, current_index, *(ht)->allocated_size);
        
        if(!bucket->is_in_use || i > current_entry_dib)
            return NULL;

        if(ht->comp_key_func(bucket->key, key, key_size))
            return bucket->data;
    }
    return NULL;
}

// static inline void *chash_table_iter_start(chash_table_st *ht)
// {
//     struct ctable_bucket * bucket = __cbucket_at(ht, 0);
//     uint64_t max_iter = (bucket->hash % *ht->allocated_size);
//     while(!bucket->is_in_use && max_iter < *ht->allocated_size)
//         bucket = __cbucket_at(ht, ++max_iter);
//     return (max_iter > *ht->allocated_size) ? NULL : bucket;
// }

// chash_table_iterator_st chash_table_get_iterator(chash_table_st *ht)
// {
//     struct ctable_bucket *bucket = chash_table_iter_start(ht);
//     if(!bucket) return (chash_table_iterator_st){0, 0, 0, 0, 0};
//     (chash_table_iterator_st){
//         .current = bucket,
//         .data = (struct chash_table_iterator_data){
//             .key = bucket->key,
//             .value = bucket->data,
//             .key_size = bucket->key_size,
//             .value_size = ht->value_type_size
//         }
//     };
// }

// void *chash_table_iter_end(chash_table_st *ht)
// {
//     uint32_t last_bucket = *ht->allocated_size - 1;
//     struct ctable_bucket * bucket = __cbucket_at(ht, last_bucket);
//     while(!bucket->is_in_use && last_bucket >= 0)
//         bucket = __cbucket_at(ht, --last_bucket);
    
//     return (last_bucket < 0) ? NULL : bucket;
// }

// void *chash_table_iter_next(chash_table_st *ht, void * current, struct chash_table_iterator_data *data)
// {
//     struct ctable_bucket * bucket = current;
//     uint64_t max_iter = (bucket->hash % *ht->allocated_size);
//     while(!bucket->is_in_use && max_iter < *ht->allocated_size)
//         bucket = __cbucket_at(ht, ++max_iter);
    
//     data->key = bucket->key;
//     data->value = bucket->data;
//     data->key_size = bucket->key_size;
//     data->value_size = ht->value_type_size;
// }

void chash_table_remove(chash_table_st *ht, void *key, uint32_t key_size)
{
    uint64_t hash = fnv_64a_buf(key, key_size, FNV1A_64_INIT);
    //uint64_t hash = XXH64(key.data, key.size, 0);

    uint64_t initial_probe_bucket = hash % (*ht->allocated_size);
    
    uint64_t current_index = 0;
    uint64_t current_entry_dib = 0;

    for(uint64_t i = 0; i < *ht->allocated_size; i++)
    {
        struct ctable_bucket *bucket = __cbucket_at(ht, current_index);
        current_index = (initial_probe_bucket + i) % (*ht->allocated_size);

        current_entry_dib = get_probe_distance(bucket->hash % *(ht)->allocated_size, initial_probe_bucket, *(ht)->allocated_size);

        if(!bucket->is_in_use || i > current_entry_dib) break;

        if(ht->comp_key_func(bucket->key, key, key_size))
        {
            //TODO: clear bucket data field?
            uint64_t index_previous = 0;
            uint64_t index_swap = 0;
            struct ctable_bucket *bucket_index_swap;
            struct ctable_bucket *bucket_index_previous;
            for(uint64_t i = 1; i < *ht->allocated_size; i++)
            {
                index_previous = (current_index + i - 1) % (*ht->allocated_size);
                index_swap = (current_index + i) % (*ht->allocated_size);
                bucket_index_swap = __cbucket_at(ht, index_swap);
                bucket_index_previous = __cbucket_at(ht, index_previous);
                if(!bucket_index_swap->is_in_use)
                {
                    bucket_index_previous->is_in_use = 0;
                    break;
                }
                uint64_t distance = get_probe_distance(bucket_index_swap->hash % *(ht)->allocated_size, current_index, *(ht)->allocated_size);

                if(distance == 0)
                {
                    bucket_index_previous->is_in_use = 0;
                    break;
                }
                memcpy(bucket_index_previous, bucket_index_swap, sizeof(struct ctable_bucket) + ht->value_type_size);
            }
            break;
        }
    }
    ht->size--;
}

void _chash_table_finish(chash_table_st **ht)
{
    // printf("colisions = %d\n", colisions);
    // for(int i = 0; i < *(*ht)->allocated_size; i++)
    // {
    //     struct ctable_bucket *bucket = __cbucket_at(*ht, i);
        
    //     if(!bucket->is_in_use) continue;

    //     uint64_t *data = (uint64_t *)bucket->data;
    //     printf("pos = %lld | probe = %d\n",
    //         bucket->hash % (*(*ht)->allocated_size), bucket->probe_size);
    // }

    free((*ht)->__temp_bucket);
    free((*ht)->__insert_bucket);
    free(*ht);
}
