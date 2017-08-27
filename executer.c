#include "executer.h"

int cd_command(char **args);
int help_command(char **args);
int exit_command(char **args);

char (*builtin_commands[]) = {
   "cd",
   "help",
   "exit"
};

int (*execute_command[])(char **) = {
    &cd_command,
    &help_command,
    &exit_command
};

int count_commands()
{
    return sizeof(builtin_commands)/sizeof(char*);
}

int cd_command(char **args)
{
    if(args[0] == NULL)
    {
        fprintf(stderr , "%s\n", "command: expected argument to \"cd\"");
    }
    else if(chdir(args[1]) != 0)
    {
        perror("command");
    }
    return 1;
}

int help_command(char **args)
{
    int id;
    fprintf(stdout , "%s\n", "Welcome to shell!");
    fprintf(stdout , "%s\n", "To use shell type anyone of the below commands with appropriate arguments and hit enter");
    fprintf(stdout , "%s\n", "These are built in commands");
    for(id = 0; id < count_commands(); id++)
    {
        fprintf(stdout, "%s\n", builtin_commands[id]);
    }
    fprintf(stdout , "%s\n", "For advanced functions refer to man command");
    return 1;
}

int exit_command(char **args){
    return 0;
}

int launch_command(char **command)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(command[0], command) == -1) {
      perror("command");
    }
    exit(EXIT_FAILURE);
  }
  else if (pid < 0)
  {
    // Error forking
    perror("command");
  }
  else
  {
    // Parent process
    do
    {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int execute(char** command){
    if(command[0] == NULL)
    {
        return 1;
    }

    //Check if command is implemented by this shell
    int id;
    for(id = 0; id < count_commands(); id++)
    {
        if(strcmp(command[0] , builtin_commands[id]) == 0)
        {
            return (*execute_command[id])(command);
        }
    }

    //Command not found; Get the syscall
    return launch_command(command);
}
