#include "executer.h"

int cd_command(char **args);
int help_command(char **args);
int exit_command(char **args);

char (*builtin_commands[])(char **) = {
   &cd_command,
   &help_command,
   &exit_command
}

int count_commands()
{
    return sizeof(builtin_commands)/sizeof(char*);
}

int launch_command(char **command)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(command[0], command) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  }
  else if (pid < 0)
  {
    // Error forking
    perror("lsh");
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
    for(id = 0; id < count_commands; id++)
    {
        if(strcmp(command[0] , builtin_commands[id]) == 0)
        {
            return (*builtin_commands[id])(command);
        }
    }

    //Command not found; Get the syscall
    return launch_command(command)
}
