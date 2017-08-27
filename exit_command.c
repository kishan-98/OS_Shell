#include "exit_command.h"

int exit_command(char **command)
{
    if(command == NULL)
    {
        //Not any command
        fprintf(stderr , "%s\n", "command: expected command");
    }
    //Returns 0 so that the shell stops
    return 0;
}
