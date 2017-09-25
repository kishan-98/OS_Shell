#include "is_piping.h"

int is_piping(char *command)
{
    // fprintf(stdout, "%s\n", "Inside is_piping");
    // fprintf(stdout, "%s\n", command);
    if(!command)
    {
        //There is nothing so no chance of piping process
        return 0;
    }
    int i;
    int count_pipes = 0;
    for(i = 0; command[i] != '\0'; i++)
    {
        //fprintf(stdout, "%d\n", i);
        if(command[i] == '|')
        {
            //There is pipe; Incrementing counter by one
            count_pipes++;
        }
    }
    return count_pipes;
}
