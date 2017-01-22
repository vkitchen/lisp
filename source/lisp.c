/*
		LISP.C
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#include <stdio.h>
#include <stdlib.h>
#include "eval.h"
#include "file.h"
#include "linenoise.h"
#include "parser.h"

void exec_file(char *file)
	{
	char *buffer = read_entire_file(file);
	if (buffer == NULL)
		{
		printf("file \"%s\" not found\n", file);
		exit(1);
		}

	struct node *ast;
	struct node *result;
	ast = parser_parse(buffer);
	result = eval(ast);
	}

void repl()
	{
	char *line;
	struct node *ast;
	struct node *result;
	while ((line = linenoise("> ")) != NULL)
		{
		ast = parser_parse(line);
		result = eval(ast);
		if (result->type == NUMBER)
			printf("%s\n", result->val);
		else if (result->type == I64)
			printf("%ld\n", *(long *)result->val);
		else if (result->type == FLOAT64)
			printf("%f\n", *(double *)result->val);
		else if (result->type == FUNC)
			printf("function: %s\n", result->val);
		else
			printf("main: unkown result from eval\n");
		free(line);
		}
	}

int main(int argc, char **argv)
	{
	if (argc == 1)
		repl();
	else
		exec_file(argv[1]);

	return 0;
	}
