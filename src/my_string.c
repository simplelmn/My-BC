#include "../include/my_string.h"
#include <stdlib.h>

bool is_mychar(char c){
    return c == '+' || c == '-' ||c == '*' || c == '/' || c == '%' || c == '(' || c == ')';
}

bool is_number(char c){
    return c >= '0' && c <= '9';
}

void count_mychar(char *string, int *count){
    for(int i = 0; string[i]; i++)
        if(is_mychar(string[i]))
            (*count)++;
}

void count_num(char *string, int *count){
    int flag = 0;
    if(is_number(string[0])) flag = 1;

    for(int i = 0; string[i]; i++){
        if(is_number(string[i])){
            if(flag == 1)
                (*count)++;
            flag = 0;
        }else{
            flag = 1;
        }
    }
}

string_array *my_tokenize(char *string){
    string_array *res = (string_array*)malloc(sizeof(string_array));
    int cnt_char = 0, cnt_num = 0;
    count_mychar(string, &cnt_char);
    count_num(string, &cnt_num);
    char **container = (char**)malloc((cnt_char + cnt_num) * sizeof(char*));
    for(int i = 0; i < cnt_char + cnt_num; i++)
        container[i] = (char*)malloc(100 * sizeof(char));
    
    int ii = 0, jj = 0, flag = 2;
    for(int i = 0; string[i]; i++){
        if(is_number(string[i])){
           if(flag == 1) {
               ii++;
               flag = 0;
            }
            container[ii][jj++] = string[i];
        }else{
            jj = 0;
            if(string[i] != ' ')
                ii++;

            if(is_mychar(string[0]) && flag == 2)
                ii = 0;
            if(string[i] != ' ')
                container[ii][jj] = string[i];

            flag = 1;
        }
    }

    res->size = cnt_char + cnt_num;
    res->array = container;

    return res;
}

int my_atoi(char *string){
    int ans = 0;
    for(int i = 0; string[i]; i++)
        ans = ans * 10 + string[i] - '0';
    return ans;
}