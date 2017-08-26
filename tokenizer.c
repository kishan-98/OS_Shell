#include"tokenizer.h"

void print_info(char** lines , int count_lines){
    int curr_count = 0;
    for(; curr_count < count_lines; curr_count++){
        fprintf(stdout , "%s\n" , lines[curr_count]);
    }
    return;
}

char** tokenize(char* line){
    int curr_token_size = TOKEN_SIZE;
    char ** tokens = (char**)malloc(curr_token_size*sizeof(char*));
    char * curr_token;
    int curr_pos = 0;
    if(!tokens){
        fprintf(stderr , "%s\n" , "Memory Allocation Error");
        exit(EXIT_FAILURE);
    }
    curr_token = strtok(line , DELIMITERS);
    while(curr_token){
        tokens[curr_pos++] = curr_token;
        if(curr_pos >= curr_token_size){
            curr_token_size += TOKEN_SIZE;
            curr_token = realloc(curr_token , curr_token_size);
            if(!curr_token){
                fprintf(stderr , "%s\n" , "Memory Allocation Error");
                exit(EXIT_FAILURE);
            }
        }
        curr_token = strtok(line , DELIMITERS);
    }
    tokens[curr_pos++] = NULL;
    print_info(tokens , curr_pos);
    return tokens;
}
