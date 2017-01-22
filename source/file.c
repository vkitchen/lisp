/*
		FILE.C
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#include <stdio.h>
#include "file.h"
#include "memory.h"

char *read_entire_file(char *file)
	{
	FILE *f = fopen(file, "rb");
	/* open failed */
	if (f == NULL)
		return NULL;

	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  //same as rewind(f);

	char *buffer = memory_alloc(fsize + 1);
	fread(buffer, fsize, 1, f);
	fclose(f);

	buffer[fsize] = 0;

	return buffer;
	}
