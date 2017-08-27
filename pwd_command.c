#include "pwd_command.h"

int pwd_command(char **command)
{
    if(command == NULL)
    {
        //Not any command
        fprintf(stderr , "%s\n", "command: expected command");
    }
    fprintf(stdout , "%s\n", current_directory);
    return 1;
}
