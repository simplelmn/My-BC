#include <stdio.h>
#include "include/my_bc.h"
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(argc == 2){
        if(my_error(argv[1]) == 1){
            perror("divide by zero");
            exit(EXIT_FAILURE);
        }else if(my_error(argv[1]) == 2){
            perror("parse error");
            exit(EXIT_FAILURE);
        }else{
            string_array *temp = my_tokenize(argv[1]);
            temp = my_add_zero(temp);
            temp = repeat_plus_minus(temp);
            temp = infix_to_postfix(temp);
            printf("%d\n", my_answer(temp));
        }
    }else if(argc == 1){
        perror("you should enter mathematical operation");
        exit(EXIT_FAILURE);
    }
    return 0;
}