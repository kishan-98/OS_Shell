#include "executer.h"

//Function to launch system command which we did not implement without syscall
int launch_system_command(char **command , int background)
{
    //fprintf(stdout, "%s %d:%s\n", "Inside launch_system_command and background is" , background , command[0]);
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        // Child process
        /*if(background){
            setpgid(0 , 0);
        }*/
        if (execvp(command[0], command) == -1)
        {
          perror("command");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        // Error forking
        perror("command");
    }
    else if(!background)
    {
        //Parent process with background
        do
        {
          wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    else{
        // Parent process without background
        fprintf(stdout, "%s %s %d %s\n", command[0] , "process with process id" , pid , "started");
    }
    return 1;
}

//Execute the given command after inputterd throught parser and argumented by tokenizer
int execute(char** command){
    if(!command || !command[0])
    {
        return 1;
    }

    //Check if command is implemented by this shell
    int id;
    for(id = 0; id < count_commands; id++)
    {
        if(strcmp(command[0] , builtin_commands[id]) == 0)
        {
            return (*execute_command[id])(command);
        }
    }

    //Command not found; Get it done by system
    return launch_system_command(command , is_background(command));
}
