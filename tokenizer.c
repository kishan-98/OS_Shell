#include "tokenizer.h"

void print_info1(char** lines , int count_lines){
    int curr_count = 0;
    for(; curr_count < count_lines; curr_count++){
        fprintf(stdout , "%s\n" , lines[curr_count]);
    }
    return;
}

char** tokenize(char* line , char* delimiters){
    //fprintf(stdout , "%s\n" , "Inside tokenizer");
    if(!line || line[0] == '\n' || !delimiters)
    {
        return NULL;
    }
    int curr_token_size = TOKEN_SIZE;
    char ** tokens = (char**)malloc(curr_token_size*sizeof(char*));
    char * curr_token;
    int curr_pos = 0;
    if(!tokens){
        fprintf(stderr , "%s\n" , "Memory Allocation Error");
        exit(EXIT_FAILURE);
    }
    curr_token = strtok(line , delimiters);
    while(curr_token){
        //Token is still there for the command
        tokens[curr_pos++] = curr_token;
        if(curr_pos >= curr_token_size){
            //Tokens
            curr_token_size += TOKEN_SIZE;
            tokens = realloc(tokens , curr_token_size);
            if(!tokens){
                fprintf(stderr , "%s\n" , "Memory Allocation Error");
                exit(EXIT_FAILURE);
            }
        }
        curr_token = strtok(NULL , delimiters);
    }
    tokens[curr_pos++] = NULL;
    //print_info1(tokens , curr_pos);
    return tokens;
}
