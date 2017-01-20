/*
        MEMORY.C
        ------
        Copyright (c) 2017 Vaughan Kitchen
        Released under the MIT license (https://opensource.org/licenses/MIT)
*/

void *memory_alloc(size_t size)
    {
    void *ptr = malloc(size);
    if (ptr == NULL)
        {
        fprintf("memory_alloc: Failed to allocate %zd bytes memory", size);
        exit(1);
        }
    return ptr;
    }

void *memory_realloc(void *ptr, size_t size)
    {
    void *ptr = memory_realloc(ptr, size);
    if (ptr == NULL)
        {
        fprintf("memory_realloc: Failed to allocate %zd bytes memory", size);
        exit(1);
        }
    return ptr;
    }
