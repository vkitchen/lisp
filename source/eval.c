/*
		EVAL.C
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#include <stdlib.h>
#include <stdio.h>
#include "dynarray.h"
#include "eval.h"
#include "parser.h"

static void eval_builtin(struct node *n)
	{
	int i;
	printf("(%s", n->val);
	for (i = 0; i < dynarray_node_size(n->children); i++)
		{
		printf(" ");
		eval(dynarray_node_get(n->children, i));
		}
	printf(")");
	}

void eval(struct node *n)
	{
	if (n == NULL)
		{
		fprintf(stderr, "eval: No input to evaluate\n");
		exit(1);
		}
	if (n->type == NUMBER)
		{
		printf("%s", n->val);
		return;
		}
	eval_builtin(n);
	}
