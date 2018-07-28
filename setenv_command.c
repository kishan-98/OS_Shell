#include "setenv_command.h"

const int setenv_command(char **command)
{
    if(command == NULL)
    {
        //Not any command
        fprintf(stderr , "%s\n", "command: expected command");
        return 1;
    }
    if(!strcmp(command[1], "NULL") || (command[1] && command[2] && command[3]))
    {
        //Either no argument is passed or more than 2 arguments is passed
        perror("Error: Unexpected command input/s");
    }
    if(!command[2])
    {
        char* temp = "\0";
        //1 is for overwriting if there is no environment variable
        if(setenv(command[1], temp, 1))
        {
            perror("Error: environment variable set failure");
        }
        return 1;
    }
    else
    {
        //1 is for overwriting if there is no environment variable
        if(setenv(command[1], command[2], 1))
        {
            perror("Error: environment variable set failure");
        }
        return 1;
    }
    return 1;
}
