#ifndef CUTILS_CSTRING_H
#define CUTILS_CSTRING_H
#include <stdint.h>

struct cstring
{
    char        *data;
    uint32_t    size;
};
typedef struct cstring cstring_st;
typedef struct cwstring cwstring_st;

typedef enum cstring_comp_result
{
    CSTRING_SMALLER = -1,
    CSTRING_EQUALS = 0,
    CSTRING_BIGGER = 1
}cstring_comp_result_et;

cstring_st cstring_new(const char* str);
cstring_st cstring_new_from_buffer(const char* buf, uint32_t size);

void cstring_delete(cstring_st str);

uint32_t cstring_size(cstring_st str);

void cstring_to_lowercase(cstring_st str);

void cstring_to_uppercase(cstring_st str);

#define cstring_add(str, add) _cstring_add(&(str), add)
void _cstring_add(cstring_st *str, const char* add);

const char* cstring_raw(cstring_st str);

char *cstring_find_char(cstring_st str, const char c);
uint32_t cstring_find_char_pos(cstring_st str, const char c);
char *cstring_find_last_char(cstring_st str, const char c);
uint32_t cstring_find_last_char_pos(cstring_st str, const char c);

char *cstring_find_str(cstring_st str, const char *s);
uint32_t cstring_find_str_pos(cstring_st str, const char *s);
char *cstring_find_last_str(cstring_st str, const char *s);
uint32_t cstring_find_last_str_pos(cstring_st str, const char *s);

//clist_st *cstring_find_all_str(cstring_st str, const char *s);


cstring_comp_result_et cstring_are_equal(cstring_st str1, cstring_st str2);

cstring_st cstring_get_copy(cstring_st str);

cstring_st cstring_get_ref(cstring_st str);

char *cstring_iter_start(cstring_st str);
char* cstring_iter_end(cstring_st str);

#define cstring_foreach(str) for(char *it = cstring_iter_start(str); it <= cstring_iter_end(str); it++)
// cstring_st cstring_ref(const char* str);
// cstring_st cstring_ref_from_buffer(const char* buf, uint32_t size);


#endif //CUTILS_CSTRING_H