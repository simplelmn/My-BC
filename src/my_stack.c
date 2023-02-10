#include "../include/my_stack.h"
#include <stdio.h>
#include <stdlib.h>

stack_list *new_stack(int max_size){
    stack_list *stack = (stack_list*)malloc(sizeof(stack_list));
    stack->max_size = max_size;
    stack->top = -1;
    stack->array = (char**)malloc(max_size * sizeof(char*));
    for(int i = 0; i < max_size; i++)
        stack->array[i] = (char*)malloc(100 * sizeof(char));
    return stack;
}

integer_stack *new_integer_stack(int max_size){
    integer_stack *stack = (integer_stack*)malloc(sizeof(integer_stack));
    stack->max_size = max_size;
    stack->top = -1;
    stack->array = (int*)malloc(max_size * sizeof(int));
    return stack;
}

bool is_empty(stack_list *stack){
    return stack->top == -1;
}

bool is_int_empty(integer_stack *stack){
    return stack->top == -1;
}

bool is_full(stack_list *stack){
    return stack->top == stack->max_size - 1;
}

bool is_int_full(integer_stack *stack){
    return stack->top == stack->max_size - 1;
}

void push(stack_list *stack, char *string){
    if(is_full(stack)){
        printf("Overflowe\n");
        return;
    }
    stack->array[++stack->top] = string;
}

void push_int(integer_stack *stack, int num){
    if(is_int_full(stack)){
        printf("Overflowe\n");
        return;
    }
    stack->array[++stack->top] = num;
}

char *peek(stack_list *stack){
    if(!is_empty(stack))
        return stack->array[stack->top];
    else
        exit(EXIT_FAILURE);
}

char *pop(stack_list *stack){
    if(is_empty(stack)){
        printf("Underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->array[stack->top--];
}

int pop_int(integer_stack *stack){
     if(is_int_empty(stack)){
        printf("Underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->array[stack->top--];
}