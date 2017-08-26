#include "parser.h"

void print_info(char* line){
    fprintf(stdout , "%s\n" , line);
    return;
}

char* parse(){
    int curr_buffer_size = BUFFER_SIZE;
    int curr_pos = 0;
    char* command = (char*)malloc(curr_buffer_size*sizeof(char));
    if(!command){
        fprintf(stderr , "%s\n" , "Memory Allocation Error");
        exit(EXIT_FAILURE);
    }
    while(1){
        char c = getchar();
        if(c == '\n' || c == EOF){
            command[curr_pos++] = '\0';
            print_info(command);
            return command;
        }
        else{
            command[curr_pos++] = c;
        }
        if(curr_pos >= curr_buffer_size){
            curr_buffer_size += BUFFER_SIZE;
            command = realloc(command , curr_buffer_size);
            if(!command){
                fprintf(stderr , "%s\n" , "Memory Allocation Error");
                exit(EXIT_FAILURE);
            }
        }
    }
}
