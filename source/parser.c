/*
		PARSER.C
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#include "memory.h"

struct parser
	{
	char *source;
	int pos;
	};

static void parser_new(char *source)
	{
	struct parser *p = memory_alloc(sizeof(*p));
	p->source = source;
	p->pos = 0;
	}

void parser_parse(char *source)
	{
	}
