#include "executer.h"

void print_info2(char** lines){
    int curr_count = 0;
    for(; lines[curr_count]; curr_count++){
        fprintf(stdout , "%s\n" , lines[curr_count]);
    }
    return;
}

int counter_command(char** lines)
{
    int curr_count = 0;
    for(; lines[curr_count]; curr_count++){
    }
    return curr_count;
}

void handler(int sig, siginfo_t *siginfo, void *context)
{
  int status;
  pid_t pid;
  pid = waitpid(-1, &status, WNOHANG);
  if(pid>0)
    printf("pid %d exited with status %d\n", pid, WEXITSTATUS(status));
}

void fileIO(char * args[], char* inputFile, char* outputFile, int option){

	int err = -1;

    pid_t pid;

	int fileDescriptor; // between 0 and 19, describing the output or input file

	if((pid=fork())==-1){
		printf("Child process could not be created\n");
		return;
	}
	if(pid==0){
		// Option 0: output redirection
        if (option == 1){
			// We open file for read only (it's STDIN)
			fileDescriptor = open(inputFile, O_RDONLY, 0600);
			// We replace de standard input with the appropriate file
			dup2(fileDescriptor, STDIN_FILENO);
			close(fileDescriptor);
		}
		else if (option == 2){
			// We open (create) the file truncating it at 0, for write only
			fileDescriptor = open(outputFile, O_CREAT | O_TRUNC | O_WRONLY, 0600);
			// We replace de standard output with the appropriate file
			dup2(fileDescriptor, STDOUT_FILENO);
			close(fileDescriptor);
		// Option 1: input and output redirection
		}
        else if (option == 4){
			fileDescriptor = open(outputFile, O_CREAT | O_APPEND, 0600);
			dup2(fileDescriptor, STDOUT_FILENO);
			close(fileDescriptor);
		}
        else if (option == 3){
			// We open file for read only (it's STDIN)
			fileDescriptor = open(inputFile, O_RDONLY, 0600);
			// We replace de standard input with the appropriate file
			dup2(fileDescriptor, STDIN_FILENO);
			close(fileDescriptor);
			// Same as before for the output file
			fileDescriptor = open(outputFile, O_CREAT | O_TRUNC | O_WRONLY, 0600);
			dup2(fileDescriptor, STDOUT_FILENO);
			close(fileDescriptor);
		}
        else if (option == 5){
			// We open file for read only (it's STDIN)
			fileDescriptor = open(inputFile, O_RDONLY, 0600);
			// We replace de standard input with the appropriate file
			dup2(fileDescriptor, STDIN_FILENO);
			close(fileDescriptor);
			// Same as before for the output file
			fileDescriptor = open(outputFile, O_CREAT | O_APPEND, 0600);
			dup2(fileDescriptor, STDOUT_FILENO);
			close(fileDescriptor);
		}

		//setenv("parent",getcwd(currentDirectory, 1024),1);

		if (execvp(args[0],args)==err){
			printf("err");
			kill(getpid(),SIGTERM);
		}
	}
	waitpid(pid,NULL,0);
}

//Function to launch system command which we did not implement without syscall
int launch_system_command(char **command , int background)
{
    //fprintf(stdout, "%s %d:%s\n", "Inside launch_system_command and background is" , background , command[0]);
    pid_t pid, wpid;
    int status;

    pid = fork();

    if(background)
    {
        struct sigaction act;
        act.sa_sigaction = &handler;
        sigaction(SIGCHLD,&act,NULL);
    }

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
        //Parent process without background
        do
        {
          wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    else{
        // Parent process with background
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

    //fprintf(stdout, "%s\n", "Debugger");
    //print_info2(command);

    char **temp_command;
    int n = counter_command(command) + 2;
    temp_command = (char**)malloc((n)*sizeof(char*));
    int i;
    for(i = 0; i < n; i++)
    {
        temp_command[i] = (char*)malloc(BUFFER_SIZE*sizeof(char));
    }

    int standardIn, standardOut;
    int fd_read;
    int fd_write;

    standardIn = dup(STDIN_FILENO);
    standardOut = dup(STDOUT_FILENO);

    int j = 0, k = 0;
    int input_redirection = 0, output_redirection = 0, append_redirection = 0;
    while(command[j])
    {
        if(!strcmp(command[j], "<"))
        {
            //there is redirection
            input_redirection = 1;
            break;
        }
        j++;
    }

    while(command[k])
    {
        if(!strcmp(command[k], ">"))
        {
            //there is redirection
            output_redirection = 1;
            break;
        }
        if(!strcmp(command[k], ">>"))
        {
            append_redirection = 1;
            break;
        }
        k++;
    }

    if(input_redirection && !command[j+1])
    {
        perror("No input argument provided");
        return 1;
    }

    if((output_redirection || append_redirection) && !command[k+1])
    {
        perror("No output argument provided");
        return 1;
    }

    int option = 0;
    option = input_redirection + 2*output_redirection + 4*append_redirection;

    if(option)
    {
        fileIO(command, (input_redirection ? command[j+1] : NULL), ((output_redirection || append_redirection) ? command[k+1] : NULL), option);
        return 1;
    }

    //Check if command is implemented by this shell
    int id;
    for(id = 0; builtin_commands[id]; id++)
    {
        if(strcmp(command[0] , builtin_commands[id]) == 0)
        {
            return (*execute_command[id])(command);
        }
    }

    return launch_system_command(command, is_background(command));
}

int execute_pipe(char** command, int read_fd, int write_fd){
    if(!command || !command[0])
    {
        return 1;
    }

    //Check if command is implemented by this shell
    int id;
    for(id = 0; builtin_commands[id]; id++)
    {
        if(strcmp(command[0] , builtin_commands[id]) == 0)
        {
            return (*execute_command[id])(command);
        }
    }

    //Command not found; Get it done by system
    return launch_system_command(command , is_background(command));
}
