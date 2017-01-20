/*
		MEMORY.H
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#ifndef MEMORY_H_
#define MEMORY_H_

#include <stdlib.h>

void *memory_alloc(size_t size);
void *memory_realloc(void *ptr, size_t size);

#endif
