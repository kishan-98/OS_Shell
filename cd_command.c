#include "cd_command.h"

int cd_command(char **command)
{
    if(command[0] == NULL)
    {
        fprintf(stderr , "%s\n", "command: expected argument to \"cd\"");
    }
    else if(chdir(command[1]) != 0)
    {
        perror("command");
    }
    return 1;
}
