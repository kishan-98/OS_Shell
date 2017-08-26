#include"parsing.h"

char* parse(){
    int curr_buffer_size = BUFFER_SIZE;
    int curr_pos = 0;
    char* command = (char*)malloc(curr_buffer_size*sizeof(char));
    if(!command){
        fprintf(stderr , "%s\n" , "Memory Allocation Error");
        exit(EXIT_FAILURE);
    }
    while(true){
        char c = getch();
        if(c == '\n' || c == EOF){
            command[curr_pos++] = '\0';
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
