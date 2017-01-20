/*
		DYNARRAY.H
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#ifndef DYNARRAY_H_
#define DYNARRAY_H_

typedef struct dynarray_noderec *dynarray_node;
/* forward declare as we're only storing pointers */
struct node;

dynarray_node dynarray_node_new();
void dynarray_node_push(dynarray_node da, struct node *value);
struct node *dynarray_node_pop(dynarray_node da);
struct node *dynarray_node_get(dynarray_node da, size_t pos);
size_t dynarray_node_capacity(dynarray_node da);
size_t dynarray_node_size(dynarray_node da);
void dynarray_node_free(dynarray_node da);

#endif
