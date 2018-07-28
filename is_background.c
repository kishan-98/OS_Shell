#include "is_background.h"

int is_background(char **command)
{
    if(!command || !command[0])
    {
        //There is nothing so no chance of background process
        return 0;
    }
    int len = strlen(command[0]);
    if(command[0][len - 1] == '&')
    {
        //There is & right adjacent to the command name
        command[0][len - 1] = '\0';
        //strncpy(command[0] , command[0] , len-1);
        return 1;
    }
    //There could be & anywhere
    int i;
    for(i = 1; command[i]; i++)
    {
        if(!strcmp(command[i] , "&") || !strcmp(command[i] , "bg"))
        {
            //This command is background process
            command[i] = "\0";
            return 1;
        }
    }
    //& was not found
    return 0;
}
