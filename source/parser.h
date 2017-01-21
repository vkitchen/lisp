/*
		PARSER.H
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#ifndef PARSER_H_
#define PARSER_H_

#include "dynarray.h"

enum type
	{
	FUNC,
	NUMBER
	};

struct node
	{
	enum type type;
	char *val;
	dynarray_node children;
	};

struct node *parser_parse(char *source);

#endif
