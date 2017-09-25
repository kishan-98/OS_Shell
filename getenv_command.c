#include "getenv_command.h"

int getenv_command(char **command)
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
    char* temp_env = getenv(command[1]);
    if(!temp_env)
    {
        perror("Error: environment variable get failure");
    }
    else
    {
        fprintf(stdout, "%s\n", temp_env);
    }
    return 1;
}
