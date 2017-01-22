/*
		EVAL.C
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builtin.h"
#include "dynarray.h"
#include "eval.h"
#include "memory.h"
#include "parser.h"

static struct node *eval_builtin(struct node *n)
	{
	int length;
	struct node **partials;
	struct node *result;
	int i;

	length = dynarray_node_size(n->children);
	partials = memory_alloc(length * sizeof(*partials));

	for (i = 0; i < length; i++)
		partials[i] = eval(dynarray_node_get(n->children, i));

	if (strcmp("+", n->val) == 0)
		result = builtin_add(length, partials);
	else if (strcmp("-", n->val) == 0)
		result = builtin_subtract(length, partials);
	else if (strcmp("*", n->val) == 0)
		result = builtin_multiply(length, partials);
	else if (strcmp("/", n->val) == 0)
		result = builtin_divide(length, partials);
	else if (strcmp("print", n->val) == 0)
		result = builtin_print(length, partials);

	free(partials);
	return result;
	}

struct node *eval(struct node *n)
	{
	if (n == NULL)
		{
		fprintf(stderr, "eval: No input to evaluate\n");
		exit(1);
		}
	if (n->type == NUMBER)
		return n;
	if (n->type == I64)
		return n;
	if (n->type == FLOAT64)
		return n;
	if (n->type == UNIT)
		return n;
	if (n->type == FUNC)
		return eval_builtin(n);
	fprintf(stderr, "eval: node type unknown\n");
	}
