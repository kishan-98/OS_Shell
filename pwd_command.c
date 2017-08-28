#include "pwd_command.h"

int pwd_command(char **command)
{
    if(command == NULL)
    {
        //Not any command
        fprintf(stderr , "%s\n", "command: expected command");
        return 1;
    }
    if(current_directory[0] == '~'){
        fprintf(stdout , "%s\n", shell_directory);
    }
    else{
        fprintf(stdout , "%s\n", current_directory);
    }
    return 1;
}
