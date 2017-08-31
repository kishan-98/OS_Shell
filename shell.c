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
int exit_command(char **command);

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
    "exit"
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
    &exit_command
};

//No of commands which we are implementing
int count_commands = sizeof(builtin_commands)/sizeof(char*);

//Initializing the various directory path
char* shell_directory;// = (char*)malloc(BUFFER_SIZE*sizeof(char));
char* current_directory;// = (char*)malloc(BUFFER_SIZE*sizeof(char));
char* previous_directory;// = (char*)malloc(BUFFER_SIZE*sizeof(char));

//Initializing the shell
void init_shell(void)
{
  char **lines;
	char **args;
	int status = 1;
    int background = 0;
	char *user;
	char *host;
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
				args = tokenize(lines[i] , DELIMITERS);
                //background = is_background(args);
                status = execute(args);
			}
            free(lines);
    		free(args);
		}
	} while (status);
}

int main(int argc, char **argv)
{
	init_shell();
	return EXIT_SUCCESS;
}
