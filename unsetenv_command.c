#include "unsetenv_command.h"

int unsetenv_command(char **command)
{
    if(command == NULL)
    {
        //Not any command
        fprintf(stderr , "%s\n", "command: expected command");
        return 1;
    }
    if(command[1] == "NULL" || (command[1] && command[2]))
    {
        //Either no argument is passed or more than 1 arguments is passed
        perror("Error: Unexpected command input/s");
    }
    if(unsetenv(command[1]))
    {
        perror("Error: environment variable unset failure");
    }
    return 1;
}
