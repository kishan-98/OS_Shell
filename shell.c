#include "shell.h"

int TOKEN_SIZE = 64;
int BUFFER_SIZE = 1024;

int help_command(char **command);
int cd_command(char **command);
int ls_command(char **command);
int pwd_command(char **command);
int echo_command(char **command);
int pinfo_command(char **command);
int nightswatch_command(char **command);
int getenv_command(char **command);
int setenv_command(char **command);
int unsetenv_command(char **command);
int jobs_command(char **command);
int overkill_command(char **command);
int kjob_command(char **command);
int bg_command(char **command);
int exit_command(char **command);
int pipelining(char **command, int count_pipes);

//These must be synced with the function below
char (*builtin_commands[]) = {
    "help",
    "cd",
    "ls",
    "pwd",
    "echo",
    "pinfo",
    "nightswatch",
    "nw",
    "getenv",
    "setenv",
    "unsetenv",
    "jobs",
    "overkill",
    "kjob",
    "bg",
    "exit",
    "quit",
    NULL
};

//These must be synced with the function above
int (*execute_command[])(char **) = {
    &help_command,
    &cd_command,
    &ls_command,
	&pwd_command,
	&echo_command,
    &pinfo_command,
    &nightswatch_command,
    &nightswatch_command,
    &getenv_command,
    &setenv_command,
    &unsetenv_command,
    &jobs_command,
    &overkill_command,
    &kjob_command,
    &bg_command,
    &exit_command,
    &exit_command
};

//No of commands which we are implementing
int count_commands = sizeof(builtin_commands)/sizeof(char*);

//Initializing the various directory path
char* shell_directory;// = (char*)malloc(BUFFER_SIZE*sizeof(char));
char* current_directory;// = (char*)malloc(BUFFER_SIZE*sizeof(char));
char* previous_directory;// = (char*)malloc(BUFFER_SIZE*sizeof(char));

char *user;
char *host;

void print_shell(){
	fprintf(stdout , "%s@%s : %s > " , user , host , current_directory);
}

void ctrlc() {
    signal(SIGINT, ctrlc);
    printf("\n");
    print_shell();
    fflush(stdout);
}

// void ctrld() {
//     signal(SIGTSTP,ctrld);
//     printf("\n");
//     print_shell();
//     fflush(stdout);
// }

//Initializing the shell
void init_shell(void)
{
    char **lines;
    char **temp_lines;
	char **args;
	int status = 1;
    int background = 0;
	register struct passwd *pw;
	register uid_t uid;
	register struct hostent *host_obj;

	user = malloc(sizeof(char)*BUFFER_SIZE);
	host = malloc(sizeof(char)*BUFFER_SIZE);

	// Getting the Username of the process
	uid = geteuid();
	pw = getpwuid(uid);
	user = pw -> pw_name;

	// Getting the Hostname of the process
	host[BUFFER_SIZE-1] = '\0';
	gethostname(host, BUFFER_SIZE-1);

	shell_directory = (char*)malloc(BUFFER_SIZE*sizeof(char));
	current_directory = (char*)malloc(BUFFER_SIZE*sizeof(char));
	previous_directory = (char*)malloc(BUFFER_SIZE*sizeof(char));
	getcwd(shell_directory , BUFFER_SIZE - 1);
	//strcpy(current_directory , shell_directory);
	current_directory[0] = '~';
	current_directory[1] = '\0';
	strcpy(previous_directory , current_directory);

	fprintf(stdout , "%s %s\n", "Shell directory is" , shell_directory);

	do
	{
		fprintf(stdout , "%s@%s : %s > " , user , host , current_directory);
		lines = parse();
		if(lines)
		{
			int i;
			for(i = 0; lines[i]; i++)
			{
                int count_pipes;
                if(count_pipes = is_piping(lines[i]))
                {
                    //fprintf(stdout, "***%s\n", lines[i]);
                    args = tokenize(lines[i], DELIMITERS);
                    //fprintf(stdout, "***%s\n", lines[i]);
                    //pipelining(args, count_pipes);
                    pipeHandler(args);
                }
                else
                {
                    //fprintf(stdout, "###%s\n", lines[i]);
                    args = tokenize(lines[i] , DELIMITERS);
                    //background = is_background(args);
                    status = execute(args);
                    free(args);
                }
			}
            free(lines);
		}
	} while (status);
}

int main(int argc, char **argv)
{
    signal(SIGINT, ctrlc);
    //signal(SIGTSTP,ctrld);
	init_shell();
	return EXIT_SUCCESS;
}
