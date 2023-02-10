#ifndef MY_BC_H
#define MY_BC_H
#include "../include/my_string.h"
#include <stdbool.h>

int priority(char c);
string_array *infix_to_postfix(string_array *container);
int my_calculate(char c, int x, int y);
int my_answer(string_array *container);
string_array *my_add_zero(string_array *container);
int first_ind_pm(string_array *container);
int last_ind_pm(string_array *container);
int count_minus(string_array *container);
string_array *repeat_plus_minus(string_array *container);
bool error_chars(char a, char b);
int my_error(char *string);

#endif