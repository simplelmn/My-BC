#ifndef MY_STRING_H
#define MY_STRING_H
#include <stdbool.h>

#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY

typedef struct s_string_array{
    int size;
    char **array;
}string_array;

#endif

bool is_mychar(char c);
bool is_number(char c);
void count_mychar(char *string, int *count);
void count_num(char *string, int *count);
string_array *my_tokenize(char *string);
int my_atoi(char *string);

#endif