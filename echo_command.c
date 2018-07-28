#include "echo_command.h"

const int echo_command(char **command)
{
    if(command == NULL)
    {
        //Not any command
        fprintf(stderr , "%s\n", "command: expected command");
        return 1;
    }
    int i;
    for(i = 1; command[i]; i++)
    {
        //Print the next delimiter separated arguments
        fprintf(stdout, "%s ", command[i]);
    }
    fprintf(stdout, "%s", "\n");
    return 1;
}
