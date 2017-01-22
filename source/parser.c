/*
		PARSER.C
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "builtin.h"
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
	/* token is considered numeric if digit or decimal point

			432
			432.5
	*/
	if (isdigit(p->source[p->pos]) || (isdigit(p->source[p->pos - 1]) && p->source[p->pos] == '.'))
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
	enum token t;
	struct node *n = memory_alloc(sizeof(*n));
	char *number;
	size_t start = p->pos;

	while ((t = tokenizer_peek(p)) == NUMERIC)
		p->pos++;

	number = strndup(&p->source[start], p->pos - start);
	/* hasn't been typed yet */
	if (strstr(number, ".") == NULL)
		{
		n->type = NUMBER;
		n->val = number;
		n->children = NULL;
		}
	/* contains a decimal point, ie float64 */
	else
		{
		n->type = FLOAT64;
		n->val = memory_alloc(sizeof(double));
		*(double *)n->val = float64_of_string(number);
		n->children = NULL;
		}

	/* printf("debug %s number: %s\n", number, &p->source[p->pos]); */

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
