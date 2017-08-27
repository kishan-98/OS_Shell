#include "parser.h"

void print_info(char* line){
    fprintf(stdout , "%s\n" , line);
    return;
}

char* parse(){
    //fprintf(stdout , "%s\n" , "Inside parser");
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
            //Line is over; Stop parsing further
            command[curr_pos++] = '\0';
            //print_info(command);
            return command;
        }
        else{
            //Line is still to be parsed
            command[curr_pos++] = c;
        }
        if(curr_pos >= curr_buffer_size){
            //Line seems to be more than expected size; realloc the memory
            curr_buffer_size += BUFFER_SIZE;
            command = realloc(command , curr_buffer_size);
            if(!command){
                fprintf(stderr , "%s\n" , "Memory Allocation Error");
                exit(EXIT_FAILURE);
            }
        }
    }
}
