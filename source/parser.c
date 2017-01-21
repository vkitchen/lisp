/*
		PARSER.C
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "dynarray.h"
#include "memory.h"
#include "parser.h"

struct parser
	{
	char *source;
	size_t length;
	size_t pos;
	};

static struct node *parse(struct parser *p);

static struct parser *parser_new(char *source)
	{
	struct parser *p = memory_alloc(sizeof(*p));
	p->source = source;
	p->length = strlen(source);
	p->pos = 0;
	return p;
	}

enum token
	{
	ALPHA,
	END,
	LEFT_PARENTH,
	NUMERIC,
	OTHER,
	RIGHT_PARENTH,
	SPACE
	};

static enum token tokenizer_peek(struct parser *p)
	{
	if (p->pos == p->length)
		return END;

	if (isalpha(p->source[p->pos]))
		return ALPHA;
	if (isdigit(p->source[p->pos]))
		return NUMERIC;
	if (p->source[p->pos] == '(')
		return LEFT_PARENTH;
	if (p->source[p->pos] == ')')
		return RIGHT_PARENTH;
	if (isspace(p->source[p->pos]))
		return SPACE;

	return OTHER;
	}

static struct node *parse_func(struct parser *p)
	{
	struct node *n = memory_alloc(sizeof(*n));
	char *name;
	size_t end = p->pos;
	p->pos++;					/* move past '(' */

	while (!isspace(p->source[++end]))
		;
	name = strndup(&p->source[p->pos], end - p->pos);
	p->pos = end;

	n->type = FUNC;
	n->val = name;
	n->children = dynarray_node_new();

	while (tokenizer_peek(p) != RIGHT_PARENTH)
		{
		dynarray_node_push(n->children, parse(p));
		/* printf("debug loop: %s\n", &p->source[p->pos]); */
		}

	p->pos++;					/* move past ')' */

	return n;
	}

static struct node *parse_number(struct parser *p)
	{
	struct node *n = memory_alloc(sizeof(*n));
	char *number;
	size_t end = p->pos;

	while (isdigit(p->source[++end]))
		;
	number = strndup(&p->source[p->pos], end - p->pos);
	p->pos = end;

	/* printf("debug %s number: %s\n", number, &p->source[p->pos]); */

	n->type = NUMBER;
	n->val = number;
	n->children = dynarray_node_new();
	return n;
	}

static struct node *parse(struct parser *p)
	{
	enum token t;

	while (isspace(p->source[p->pos]))
		p->pos++;

	t = tokenizer_peek(p);

	if (t == LEFT_PARENTH)
		return parse_func(p);
	if (t == NUMERIC)
		return parse_number(p);

	/* puts("FAIL!!!"); */
	return NULL;
	}

struct node *parser_parse(char *source)
	{
	struct parser *p;
	struct node *n;

	p = parser_new(source);
	n = parse(p);
	free(p);
	return n;
	}
