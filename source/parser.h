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
	FLOAT64,
	FUNC,
	I64,
	NUMBER,
	UNIT
	};

struct node
	{
	enum type type;
	void *val;
	dynarray_node children;
	};

struct node *parser_parse(char *source);

#endif
