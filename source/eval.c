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

static char *eval_builtin(struct node *n)
	{
	int length;
	char **partials;
	char *result;
	int i;

	length = dynarray_node_size(n->children);
	partials = memory_alloc(length * sizeof(*partials));

	for (i = 0; i < length; i++)
		partials[i] = eval(dynarray_node_get(n->children, i));

	if (strcmp("+", n->val) == 0)
		result = builtin_add(length, partials);
	else if (strcmp("-", n->val) == 0)
		result = builtin_subtract(length, partials);

	free(partials);
	return result;
	}

char *eval(struct node *n)
	{
	if (n == NULL)
		{
		fprintf(stderr, "eval: No input to evaluate\n");
		exit(1);
		}
	if (n->type == NUMBER)
		return n->val;
	return eval_builtin(n);
	}
