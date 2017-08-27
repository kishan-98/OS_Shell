#include "executer.h"

//Function to launch system command which we did not implement without syscall
int launch_system_command(char **command)
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

//Execute the given command after inputterd throught parser and argumented by tokenizer
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
            return (*execute_command[id])(command);
        }
    }

    //Command not found; Get it done by system
    return launch_system_command(command);
}
