#include "kjob_command.h"

int get_number(char* args)
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
        else{
            //Invalid character
            return -100;
        }
    }
    return number;
}

int kjob_command(char **command)
{
    if(command[1] && command[2])
    {
        pid_t pid;
        int sig;
        long temp = get_number(command[1]);

        pid = (pid_t)temp;
        sig = get_number(command[2]);
        if(sig == -100 || temp == -100)
        {
            fprintf(stderr , "%s\n", "command: expected command");
            return 1;
        }
        int res = kill(pid,sig);
        printf("Process %lu terminated\n", pid);
    }
    else
    {
        fprintf(stderr , "%s\n", "command: expected command");
    }
    return 1;
}
