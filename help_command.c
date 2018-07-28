#include "help_command.h"

const int help_command(char **command)
{
    if(command == NULL)
    {
        //Not any command
        fprintf(stderr , "%s\n", "command: expected command");
        return 1;
    }
    //Provides help for this shell
    int id;
    fprintf(stdout , "%s\n", "Welcome to shell!");
    fprintf(stdout , "%s\n", "To use shell type anyone of the below commands with appropriate arguments and hit enter");
    fprintf(stdout , "%s\n", "These are built in commands");
    for(id = 0; builtin_commands[id]; id++)
    {
        fprintf(stdout, "%s : %s\n", builtin_commands[id], builtin_commands_help[id]);
    }
    fprintf(stdout , "%s\n", "For advanced functions refer to man command");
    return 1;
}
