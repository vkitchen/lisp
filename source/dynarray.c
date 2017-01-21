/*
		DYNARRAY.C
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#include <stdio.h>
#include <stdlib.h>
#include "dynarray.h"
#include "memory.h"

struct dynarray_noderec
	{
	size_t capacity;
	size_t size;
	struct node **items;
	};

dynarray_node dynarray_node_new()
	{
	dynarray_node da = memory_alloc(sizeof(*da));
	da->capacity = 2;
	da->size = 0;
	da->items = memory_alloc(da->capacity * sizeof(*da->items));
	return da;
	}

void dynarray_node_push(dynarray_node da, struct node *value)
	{
	if (da->capacity == da->size)
		{
		da->capacity *= 2;
		da->items = memory_realloc(da->items, da->capacity * sizeof(*da->items));
		}
	da->items[da->size++] = value;
	}

struct node *dynarray_node_pop(dynarray_node da)
	{
	if (da->size == 0)
		{
		fprintf(stderr, "dynarray_node_pop: No more items left to pop\n");
		exit(1);
		}
	return da->items[--da->size];
	}

struct node *dynarray_node_get(dynarray_node da, size_t pos)
	{
	if (!(0 <= pos && pos < da->size))
		{
		fprintf(stderr, "dynarray_node_get: can not get index %zd from dynamic array of length %zd\n", pos, da->size);
		exit(1);
		}
	return da->items[pos];
	}

size_t dynarray_node_capacity(dynarray_node da)
	{
	return da->capacity;
	}

size_t dynarray_node_size(dynarray_node da)
	{
	return da->size;
	}

void dynarray_node_free(dynarray_node da)
	{
	free(da->items);
	free(da);
	}
