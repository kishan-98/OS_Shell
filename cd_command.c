#include "cd_command.h"

int cd_command(char **command)
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
        //fprintf(stderr , "%s\n", "command: expected argument to \"cd\"");
        command[1] = (char*)malloc(2*sizeof(char));
        command[1][0] = '~';
        command[1][1] = '\0';
        return cd_command(command);
    }
    else if(command[1][0] == '~'){
        if(chdir(shell_directory) != 0)
        {
            perror("command");
            return 1;
        }
        else
        {
            strcpy(previous_directory , current_directory);
            strcpy(current_directory , command[1]);
            return 1;
        }
    }
    else if(command[1][0] == '-')
    {
        //Go to previous working directory
        strcpy(command[1] , previous_directory);
        return cd_command(command);
    }
    else if(chdir(command[1]) != 0)
    {
        //Error in changing directory
        perror("command");
        return 1;
    }
    else
    {
        strcpy(previous_directory , current_directory);
        strcpy(current_directory , command[1]);
        return 1;
    }
    return 1;
}
