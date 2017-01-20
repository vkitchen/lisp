/*
		LISP.C
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#include <stdio.h>
#include <stdlib.h>
#include "linenoise.h"
#include "parser.h"

int main()
	{
	char *line;
	while ((line = linenoise("> ")) != NULL)
		{
		printf("You wrote: %s\n", line);
		parser_parse(line);
		free(line);
		}
	return 0;
	}
