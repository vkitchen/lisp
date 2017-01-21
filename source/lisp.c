/*
		LISP.C
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#include <stdio.h>
#include <stdlib.h>
#include "eval.h"
#include "linenoise.h"
#include "parser.h"

int main()
	{
	char *line;
	struct node *ast;
	while ((line = linenoise("> ")) != NULL)
		{
		ast = parser_parse(line);
		eval(ast);
		puts("");
		free(line);
		}
	return 0;
	}
