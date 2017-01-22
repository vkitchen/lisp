/*
		BUILTIN.C
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

static long i64_of_string(char *str)
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

static char *string_of_i64(long val)
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

char *builtin_add(int len, char **partials)
	{
	long result = 0;
	int i;

	for (i = 0; i < len; i++)
		result += i64_of_string(partials[i]);

	return string_of_i64(result);
	}

char *builtin_subtract(int len, char **partials)
	{
	long result = i64_of_string(partials[0]);
	int i;

	for (i = 1; i < len; i++)
		result -= i64_of_string(partials[i]);

	return string_of_i64(result);
	}
