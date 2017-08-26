#include"tokenizer.h"

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
    return tokens;
}
