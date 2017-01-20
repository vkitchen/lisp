/*
		MEMORY.C
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#include <stdlib.h>
#include <stdio.h>

void *memory_alloc(size_t size)
	{
	void *p = malloc(size);
	if (p == NULL)
		{
		fprintf(stderr, "memory_alloc: Failed to allocate %zd bytes memory", size);
		exit(1);
		}
	return p;
	}

void *memory_realloc(void *ptr, size_t size)
	{
	void *p = memory_realloc(ptr, size);
	if (p == NULL)
		{
		fprintf(stderr, "memory_realloc: Failed to allocate %zd bytes memory", size);
		exit(1);
		}
	return p;
	}
