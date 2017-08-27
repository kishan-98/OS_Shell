#include "help_command.h"

int help_command(char **command)
{
    int id;
    fprintf(stdout , "%s\n", "Welcome to shell!");
    fprintf(stdout , "%s\n", "To use shell type anyone of the below commands with appropriate arguments and hit enter");
    fprintf(stdout , "%s\n", "These are built in commands");
    for(id = 0; id < count_commands; id++)
    {
        fprintf(stdout, "%s\n", builtin_commands[id]);
    }
    fprintf(stdout , "%s\n", "For advanced functions refer to man command");
    return 1;
}
