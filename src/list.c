#include "list.h"

list_t list_create(size_t element_size, size_t base_element_count)
{
    base_element_count = (base_element_count >= 100) ? base_element_count : 100;

    list_t new_list = {.element_size = element_size,
                       .base_element_count = base_element_count,
                       .capacity = base_element_count * element_size,
                       .cursor = 0,
                       .array = NULL};

    new_list.array = malloc(new_list.capacity);

    return new_list;
}

size_t list_length(list_t list)
{
    return list.cursor;
}

void destroy_list(list_t list)
{
    if (list.array != NULL)
    {
        free(list.array);
    }
}
