#include "cstring.h"
#include <string.h>
#include <stdlib.h>


cstring_st cstring_new(const char* str)
{
    return (cstring_st){.data = _strdup(str), .size = strlen(str)};
}

cstring_st cstring_new_from_buffer(const char* buf, uint32_t size)
{
    cstring_st newstr = (cstring_st){.size = size};
    newstr.data = calloc(1, size);
    memcpy(newstr.data, buf, size);
    return newstr;
}

void cstring_delete(cstring_st str)
{
    free(str.data);
    str.size = 0;
    str.data = NULL;
}

uint32_t cstring_size(cstring_st str)
{
    return str.size;
}

void cstring_to_lowercase(cstring_st str)
{
    _strlwr_s(str.data, str.size + 1);
}

void cstring_to_uppercase(cstring_st str)
{
    _strupr_s(str.data, str.size + 1);
}

void _cstring_add(cstring_st *str, const char* add)
{
    uint32_t add_size = strlen(add);
    str->data = realloc(str->data, str->size + add_size + 1);
    memcpy(str->data + str->size, add, add_size + 1);
    str->size += add_size;
}

const char* cstring_raw(cstring_st str)
{
    return str.data;
}

char *cstring_find_char(cstring_st str, const char c)
{
    return strchr(str.data, c);
}

uint32_t cstring_find_char_pos(cstring_st str, const char c)
{
    return (uint32_t)(cstring_find_char(str, c) - str.data);
}

char *cstring_find_last_char(cstring_st str, const char c)
{
    return strrchr(str.data, c);
}

uint32_t cstring_find_last_char_pos(cstring_st str, const char c)
{
    return (uint32_t)(cstring_find_last_char(str, c) - str.data);
}

char *cstring_find_str(cstring_st str, const char *s)
{
    return strstr(str.data, s);
}

uint32_t cstring_find_str_pos(cstring_st str, const char *s)
{
    char *pos = cstring_find_str(str, s);
    if(!pos) return -1;
    return (uint32_t)(pos - str.data);
}

char *cstring_find_last_str(cstring_st str, const char *s)
{   
    char *last = NULL;
    char *current = NULL;
    char *start = str.data;
    while((current = strstr(start, s))) 
    {
        last = current;
        start = current + 1;
    }
    return last;
}

uint32_t cstring_find_last_str_pos(cstring_st str, const char *s)
{
    char *pos = cstring_find_last_str(str, s);
    if(!pos) return -1;
    return (uint32_t)(pos - str.data);
}

//clist_st *cstring_find_all_str(cstring_st str, const char *s);

//TODO: check if theres diferente implementations for strcmp
//because the documentation doesnt say if the return is on the range
//of -1 to 1
cstring_comp_result_et cstring_are_equal(cstring_st str1, cstring_st str2)
{
    return (cstring_comp_result_et)strcmp(str1.data, str2.data);
}

cstring_st cstring_get_copy(cstring_st str)
{
    return cstring_new_from_buffer(str.data, str.size + 1);
}

cstring_st cstring_get_ref(cstring_st str)
{
    return (cstring_st){ .data = str.data, .size = str.size };
}

char *cstring_iter_start(cstring_st str)
{
    return str.data;
}

char* cstring_iter_end(cstring_st str)
{
    return &str.data[str.size - 1];
}

