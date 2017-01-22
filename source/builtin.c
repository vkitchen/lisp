/*
		BUILTIN.C
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "builtin.h"
#include "memory.h"
#include "parser.h"

long i64_of_string(char *str)
	{
	long val;
	char *endptr;

	errno = 0;	/* To distinguish success/failure after call */
	val = strtol(str, &endptr, 10);

	/* Check for various possible errors */

	if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || (errno != 0 && val == 0))
		{
		perror("strtol");
		exit(1);
		}

	if (endptr == str)
		{
		fprintf(stderr, "i64_of_string: No digits were found\n");
		exit(1);
		}

	return val;
	}

char *string_of_i64(long val)
	{
	char *result = memory_alloc(sizeof(char) * 21); /* max 19 places for i64, + sign, + terminator */
	int n = snprintf(result, 21, "%ld", val);
	if (n < 0 || result[n] != '\0')
		{
		fprintf(stderr, "string_of_i64: Conversion failed\n");
		exit(1);
		}
 	return result;
	}

double float64_of_string(char *str)
	{
	double val;
	char *endptr;

	errno = 0;	/* To distinguish success/failure after call */
	val = strtod(str, &endptr);

	/* Check for various possible errors */

	if ((errno == ERANGE && (val == HUGE_VAL || val == -HUGE_VAL)) || (errno != 0 && val == 0))
		{
		perror("strtol");
		exit(1);
		}

	if (endptr == str)
		{
		fprintf(stderr, "float64_of_string: No digits were found\n");
		exit(1);
		}

	return val;
	}

struct node *builtin_add(int len, struct node **partials)
	{
	long result = 0;
	double resultF = 0;
	int i;
	struct node *n = memory_alloc(sizeof(*n));
	int resultIsFloat = 0;

	for (i = 0; i < len; i++)
		if (partials[i]->type == FLOAT64)
			resultIsFloat = 1;

	if (!resultIsFloat)
		{
		for (i = 0; i < len; i++)
			{
			if (partials[i]->type == I64)
				result += *(long *)partials[i]->val;
			else if (partials[i]->type == NUMBER)
				result += i64_of_string(partials[i]->val);
			}
		n->type = NUMBER;
		n->val = string_of_i64(result);
		n->children = NULL;
		}
	else
		{
		for (i = 0; i < len; i++)
			{
			if (partials[i]->type == I64)
				resultF += *(double *)partials[i]->val;
			else if (partials[i]->type == FLOAT64)
				resultF += *(double *)partials[i]->val;
			else if (partials[i]->type == NUMBER)
				resultF += (double)i64_of_string(partials[i]->val);
			}
		n->type = FLOAT64;
		n->val = memory_alloc(sizeof(double));
		*(double *)n->val = resultF;
		n->children = NULL;
		}

	return n;
	}

struct node *builtin_subtract(int len, struct node **partials)
	{
	long result = 0;
	double resultF = 0;
	int i;
	struct node *n = memory_alloc(sizeof(*n));
	int resultIsFloat = 0;

	for (i = 0; i < len; i++)
		if (partials[i]->type == FLOAT64)
			resultIsFloat = 1;

	if (!resultIsFloat)
		{
		if (partials[0]->type == I64)
			result = *(long *)partials[0]->val;
		else if (partials[0]->type == NUMBER)
			result = i64_of_string(partials[0]->val);

		for (i = 1; i < len; i++)
			{
			if (partials[i]->type == I64)
				result -= *(long *)partials[i]->val;
			else if (partials[i]->type == NUMBER)
				result -= i64_of_string(partials[i]->val);
			}
		n->type = NUMBER;
		n->val = string_of_i64(result);
		n->children = NULL;
		}
	else
		{
		if (partials[0]->type == I64)
			resultF = *(double *)partials[0]->val;
		else if (partials[0]->type == FLOAT64)
			resultF = *(double *)partials[0]->val;
		else if (partials[0]->type == NUMBER)
			resultF = (double)i64_of_string(partials[0]->val);

		for (i = 1; i < len; i++)
			{
			if (partials[i]->type == I64)
				resultF -= *(double *)partials[i]->val;
			else if (partials[i]->type == FLOAT64)
				resultF -= *(double *)partials[i]->val;
			else if (partials[i]->type == NUMBER)
				resultF -= (double)i64_of_string(partials[i]->val);
			}
		n->type = FLOAT64;
		n->val = memory_alloc(sizeof(double));
		*(double *)n->val = resultF;
		n->children = NULL;
		}

	return n;
	}

struct node *builtin_multiply(int len, struct node **partials)
	{
	long result = 0;
	double resultF = 0;
	int i;
	struct node *n = memory_alloc(sizeof(*n));
	int resultIsFloat = 0;

	for (i = 0; i < len; i++)
		if (partials[i]->type == FLOAT64)
			resultIsFloat = 1;

	if (!resultIsFloat)
		{
		if (partials[0]->type == I64)
			result = *(long *)partials[0]->val;
		else if (partials[0]->type == NUMBER)
			result = i64_of_string(partials[0]->val);

		for (i = 1; i < len; i++)
			{
			if (partials[i]->type == I64)
				result *= *(long *)partials[i]->val;
			else if (partials[i]->type == NUMBER)
				result *= i64_of_string(partials[i]->val);
			}
		n->type = NUMBER;
		n->val = string_of_i64(result);
		n->children = NULL;
		}
	else
		{
		if (partials[0]->type == I64)
			resultF = *(double *)partials[0]->val;
		else if (partials[0]->type == FLOAT64)
			resultF = *(double *)partials[0]->val;
		else if (partials[0]->type == NUMBER)
			resultF = (double)i64_of_string(partials[0]->val);

		for (i = 1; i < len; i++)
			{
			if (partials[i]->type == I64)
				resultF *= *(double *)partials[i]->val;
			else if (partials[i]->type == FLOAT64)
				resultF *= *(double *)partials[i]->val;
			else if (partials[i]->type == NUMBER)
				resultF *= (double)i64_of_string(partials[i]->val);
			}
		n->type = FLOAT64;
		n->val = memory_alloc(sizeof(double));
		*(double *)n->val = resultF;
		n->children = NULL;
		}

	return n;
	}

struct node *builtin_divide(int len, struct node **partials)
	{
	double resultF = 0;
	int i;
	struct node *n = memory_alloc(sizeof(*n));

	if (partials[0]->type == I64)
		resultF = *(double *)partials[0]->val;
	else if (partials[0]->type == FLOAT64)
		resultF = *(double *)partials[0]->val;
	else if (partials[0]->type == NUMBER)
		resultF = (double)i64_of_string(partials[0]->val);

	for (i = 1; i < len; i++)
		{
		if (partials[i]->type == I64)
			resultF /= *(double *)partials[i]->val;
		else if (partials[i]->type == FLOAT64)
			resultF /= *(double *)partials[i]->val;
		else if (partials[i]->type == NUMBER)
			resultF /= (double)i64_of_string(partials[i]->val);
		}
	n->type = FLOAT64;
	n->val = memory_alloc(sizeof(double));
	*(double *)n->val = resultF;
	n->children = NULL;

	return n;
	}
