#include "cd_command.h"

int cd_command(char **command)
{
    if(command == NULL)
    {
        //Not any command
        fprintf(stderr , "%s\n", "command: expected command");
    }
    if(command[1] == NULL)
    {
        //There is no argument provided to the command
        fprintf(stderr , "%s\n", "command: expected argument to \"cd\"");
    }
    else if(chdir(command[1]) != 0)
    {
        //Error in changing directory
        perror("command");
    }
    return 1;
}
