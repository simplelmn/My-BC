#include "../include/my_bc.h"
#include "../include/my_stack.h"
#include <stdlib.h>

int priority(char c){
    if(c == '+' || c == '-') return 1;
    else if(c == '*' || c == '/' || c == '%') return 2;
    return -1;
}

string_array *infix_to_postfix(string_array *container){
    int i, j;
    int count = 0;
    stack_list *stack = new_stack(container->size);

    if(!stack) return NULL;

    for(i = 0, j = -1; i < container->size; i++){
        if(is_number(container->array[i][0])){
            container->array[++j] = container->array[i];
            count++;
        }else if(container->array[i][0] == '('){
            push(stack, container->array[i]);
        }else if(container->array[i][0] == ')'){
            while(!is_empty(stack) && peek(stack)[0] != '('){
                container->array[++j] = pop(stack);
                count++;
            }
            pop(stack);
        }else{
            while(!is_empty(stack) && priority(container->array[i][0]) <= priority(peek(stack)[0])){
                container->array[++j] = pop(stack);
                count++;
            }
            push(stack, container->array[i]);
        }
    }

    while(!is_empty(stack)){
        container->array[++j] = pop(stack);
        count++;
    }

    container->size = count;
    return container;
}

int my_calculate(char c, int x, int y){
    if(c == '-') return x - y;
    if(c == '+') return x + y;
    if(c == '*') return x * y;
    if(c == '/') return x / y;
    return x % y;
}

int my_answer(string_array *container){
    integer_stack *stack = new_integer_stack(container->size);
    for(int i = 0; i < container->size; i++){
        if(is_number(container->array[i][0])){
            push_int(stack, my_atoi(container->array[i]));
        }else{
            int x = 0, y = 0;
            if(!is_int_empty(stack)){
                x = pop_int(stack);
            }
            if(!is_int_empty(stack)){
                y =  pop_int(stack);
            }
            int res = my_calculate(container->array[i][0], y, x);
            push_int(stack, res);
        }
    }
    return pop_int(stack);
}

string_array *my_add_zero(string_array *container){
    int count = 0;
    int flag = 0;
    for(int i = 0; i < container->size; i++){
        if(container->array[i][0] == '('){
            if(is_number(container->array[i + 1][0])){
                flag++;
            }
            count++;
        }
    }

    char **temp = (char**)malloc((container->size + count + flag) * sizeof(char*));
    for(int i = 0; i < container->size + count; i++)
        temp[i] = (char*)malloc(100 * sizeof(char));
    
    int j = 0;
    for(int i = 0; i < container->size; i++){
        if(container->array[i][0] == '('){
            temp[j++] = container->array[i];
            temp[j++] = "0";
            if(is_number(container->array[i + 1][0])){
                temp[j++] = "+";
            }
        }else{
            temp[j++] = container->array[i];
        }
    }

    string_array *res = (string_array*)malloc(sizeof(string_array));
    res->size = container->size + count + flag;
    res->array = temp;

    return res;
}

int first_ind_pm(string_array *container){
    int x = 0;
    for(int i = 0; i < container->size - 1; i++){
        if(container->array[i][0] == '+' && container->array[i + 1][0] == '-'){
            x = i;
            break;
        }else if(container->array[i][0] == '-' && container->array[i + 1][0] == '+'){
            x = i;
            break;
        }
    }
    return x;
}

int last_ind_pm(string_array *container){
    int x = 0, y = 0;
    for(int i = 0; i < container->size - 1; i++){
        if(container->array[i][0] == '+' && container->array[i + 1][0] == '-'){
            x = i;
            y = i + 1;
        }else if(container->array[i][0] == '-' && container->array[i + 1][0] == '+'){
            x = i;
            y = i + 1;
        }
    }
    if(x > y) return x;
    else return y;
}

int count_minus(string_array *container){
    int count = 0;
    for(int i = 0; i < container->size - 1; i++){
        if(container->array[i][0] == '-' && container->array[i + 1][0] == '+'){
            count++;
        }else if(container->array[i][0] == '+' && container->array[i + 1][0] == '-'){
            count++;
            i++;
        }
    }
    return count;
}

string_array *repeat_plus_minus(string_array *container){
    char **temp = (char**)malloc(container->size * sizeof(char*));
    for(int i = 0; i < container->size; i++)
        temp[i] = (char*)malloc(100 * sizeof(char));
    int j = 0;
    int count = count_minus(container);
    int first = first_ind_pm(container);
    int last = last_ind_pm(container);
    if(first == 0 && last == 0){
        for(int i = 0; i < container->size; i++){
            temp[j++] = container->array[i];
        }
    }else{
        if(count % 2 == 1){
            for(int i = 0; i < first; i++){
                temp[j++] = container->array[i];
            }
            temp[j++] = "-";
            temp[j++] = "1";
            temp[j++] = "*";
            for(int i = last + 1; i < container->size; i++){
                temp[j++] = container->array[i];
            }
        }else{
            for(int i = 0; i < first; i++){
                temp[j++] = container->array[i];
            }
            temp[j++] = "+";
            for(int i = last + 1; i < container->size; i++){
                temp[j++] = container->array[i];
            }
        }
    }
    string_array *res = (string_array*)malloc(sizeof(string_array));
    res->size = j;
    res->array = temp;
    return res;
}

bool error_chars(char a, char b){
    return  (a == '+' && b == '/') ||
            (a == '/' && b == '+') ||
            (a == '+' && b == '*') ||
            (a == '*' && b == '+') ||
            (a == '-' && b == '/') ||
            (a == '/' && b == '-') ||
            (a == '*' && b == '/') ||
            (a == '/' && b == '*') ||
            (a == '-' && b == '-') ||
            (a == '+' && b == '+') ||
            (a == '*' && b == '*') ||
            (a == '/' && b == '/') ||
            (a == '%' && b == '%') ||
            (a == '%' && b == '+') ||
            (a == '+' && b == '%') ||
            (a == '%' && b == '-') ||
            (a == '-' && b == '%') ||
            (a == '%' && b == '*') ||
            (a == '*' && b == '%') ||
            (a == '%' && b == '/') ||
            (a == '/' && b == '%') ||
            (a == '(' && b == ')') ||
            (a == ')' && b == '(');
}

int my_error(char *string){
    for(int i = 0; string[i]; i++){
        if(error_chars(string[i], string[i + 1])){
            return 2;
        }
        if(!is_mychar(string[i]) && !is_number(string[i]) && string[i] != ' '){
            return 2;
        }
        if(string[i] == '/' && string[i + 1] == '0'){
            return 1;
        }
        if(is_number(string[i]) && string[i + 1] == '('){
            return 2;
        }
    }
    return 0;
}