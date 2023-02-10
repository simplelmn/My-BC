#ifndef MY_STACK_H
#define MY_STACK_H
#include <stdbool.h>

typedef struct Stack_list{
    int max_size;
    int top;
    char **array;
}stack_list;

typedef struct Integer_stack{
    int max_size;
    int top;
    int *array;
}integer_stack;

stack_list *new_stack(int max_size);
integer_stack *new_integer_stack(int max_size);
bool is_empty(stack_list *stack);
bool is_int_empty(integer_stack *stack);
bool is_full(stack_list *stack);
bool is_int_full(integer_stack *stack);
void push(stack_list *stack, char *string);
void push_int(integer_stack *stack, int num);
char *peek(stack_list *stack);
char *pop(stack_list *stack);
int pop_int(integer_stack *stack);

#endif