/*
		BUILTIN.H
		------
		Copyright (c) 2017 Vaughan Kitchen
		Released under the MIT license (https://opensource.org/licenses/MIT)
*/

#ifndef BUILTIN_H_
#define BUILTIN_H_

long i64_of_string(char *str);
char *string_of_i64(long val);
double float64_of_string(char *str);
struct node *builtin_add(int len, struct node **partials);
struct node *builtin_subtract(int len, struct node **partials);
struct node *builtin_multiply(int len, struct node **partials);
struct node *builtin_divide(int len, struct node **partials);

#endif
