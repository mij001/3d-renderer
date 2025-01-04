#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "rerr.h"

typedef struct
{
    size_t element_size;
    size_t base_element_count;
    size_t capacity;
    size_t cursor;
    void *array;
} list_t;

list_t list_create(size_t element_size, size_t base_element_count);
size_t list_length(list_t list);
void destroy_list(list_t list);

// typrcast the void pointer into the ptype we wants
#define get_list_element(type, list, indx) ((type *)((list).array))[(indx)]

#define push_to_list(list, element)                                                                     \
    do                                                                                                  \
    {                                                                                                   \
        if ((list).capacity <= (((list).cursor) + 1) * ((list).element_size))                           \
        {                                                                                               \
            (list).capacity += ((list).base_element_count) * ((list).element_size);                     \
            (list).array = realloc((list).array, ((list).capacity));                                    \
        }                                                                                               \
        memcpy(                                                                                         \
            ((list).array + ((list).cursor) * ((list).element_size)), &(element), (list).element_size); \
        (list).cursor++;                                                                                \
                                                                                                        \
    } while (0);
