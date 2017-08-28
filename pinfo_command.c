#include "pinfo_command.h"

int pinfo_command(char **command)
{
    if(command == NULL)
    {
        //Not any command
        fprintf(stderr , "%s\n", "command: expected command");
        return 1;
    }
    else if(command[1] == NULL)
    {
        //Go to root directory
        fprintf(stderr , "%s\n", "command: expected argument to \"pinfo\"");
        return 1;
    }
    char* process_exe = (char*)malloc(BUFFER_SIZE*sizeof(char));
    char* process_status = (char*)malloc(BUFFER_SIZE*sizeof(char));
    char* process_info = (char*)malloc(BUFFER_SIZE*sizeof(char));
    strcpy(process_exe , "/proc/");
    strcat(process_exe , command[1]);
    strcpy(process_status , process_exe);
    strcat(process_exe , "/exe");
    strcat(process_status , "/status");
    readlink(process_exe , process_info , BUFFER_SIZE - 1);
    fprintf(stdout, "\n%s\n\n", process_info);
    FILE* fp = fopen(process_status , "r");
    if(!fp)
    {
        //Error in opening file
        fprintf(stdout, "%s\n", "Error in opening file");
        return 1;
    }
    //fprintf(stdout, "%s\n", "File opened");
    int curr_line = 0 , lines = 17 , curr_target = 0, target_lines[4] = {2,5,13,17};//target_lines is for reading targetted lines
    size_t buffer_size = BUFFER_SIZE;
    while(curr_line < lines)
    {
        curr_line++;
        //fprintf(stdout, "%s\n", "About to getline");
        if(getline(&process_exe , &buffer_size , fp) == -1)
        {
            perror("Error in reading");
            break;
        }
        if(curr_line == target_lines[curr_target])
        {
            //Pring this line
            curr_target++;
            fprintf(stdout, "%s\n", process_exe);
        }
    }
    free(process_exe);
    free(process_status);
    fclose(fp);
    return 1;
}
