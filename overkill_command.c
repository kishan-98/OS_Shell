#include "overkill_command.h"

int get_number1(char* args)
{
    //Convert string to integer if valid otherwise return 0
    int i;
    int number = 0;
    int mult_fact = 10 , error_fact = 1;
    int flag = 0;
    for(i = 0; args[i] != '\0'; i++)
    {
        if(0 <= (args[i]-'0') && (args[i]-'0') < 10)
        {
            number = 10*number + (int)(args[i]-'0');
        }
        else
        {
            //Invalid character
            return -100;
        }
    }
    return number;
}

int overkill_command(char **command)
{
    int res = kill(0,9);
    printf("Process %d terminated\n", res);
    return 1;
}
