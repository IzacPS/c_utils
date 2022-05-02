#ifndef CUTILS_CARRAY_H
#define CUTILS_CARRAY_H
#include "array_utils.h"



#define carray_foreach(array)\
    for(void *it = array;\
     it < (void*)(array + carray_size(array));\
      it = (uint8_t *)it + sizeof(array[0]))

#define carray_foreach_indexed(array) \
    for(struct {void *value; uint32_t index; } it = {array, 0};\
        it.value < (void*)(array + carray_size(array));\
        it.value = (uint8_t *)it.value + sizeof(array[0]), it.index++)


#define carray_foreach_step(array, step) \
    for(void * it = array;\
     it < (void*)(array + carray_size(array));\
      it = (uint8_t *)it + sizeof(array[0]) * step)

#define carray_foreach_step_indexed(array, step) \
    for(struct {void *value; uint32_t index; } it = {array, 0};\
     it.value < (void*)(array + carray_size(array));\
      it.value = (uint8_t *)it.value + sizeof(array[0]) * step, it.index += step)

#define carray_foreach_reverse(array)\
    for(void * it = (array + carray_size(array) - 1);\
     it > (void*)array;\
      it = (uint8_t *)it - sizeof(array[0]))

#define carray_foreach_reverse_indexed(array)\
    for(struct {void *value; uint32_t index; } it = {(array + carray_size(array) - 1), carray_size(array) - 1};\
        it.value > (void*)array;\
        it.value = (uint8_t *)it.value - sizeof(array[0]), it.index--)


#define carray_foreach_reverse_step(array, step)\
    for(void * it = (array + carray_size(array) - 1);\
     it > (void*)array;\
      it = (uint8_t *)it - sizeof(array[0]) * step)

#define carray_foreach_reverse_step_indexed(array, step)\
    for(struct {void *value; uint32_t index; } it = {(array + carray_size(array) - 1), carray_size(array) - 1};\
     it.value > (void*)array;\
      it.value = (uint8_t *)it.value - sizeof(array[0]) * step, it.index -= step)


#endif //CUTILS_CARRAY_H

