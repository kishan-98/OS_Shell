#include "shell.h"

const int TOKEN_SIZE = 64;
const int BUFFER_SIZE = 1024;

const int help_command(char **command);
const int cd_command(char **command);
const int ls_command(char **command);
const int pwd_command(char **command);
const int echo_command(char **command);
const int pinfo_command(char **command);
const int nightswatch_command(char **command);
const int getenv_command(char **command);
const int setenv_command(char **command);
const int unsetenv_command(char **command);
const int jobs_command(char **command);
const int overkill_command(char **command);
const int kjob_command(char **command);
const int bg_command(char **command);
const int exit_command(char **command);
int pipelining(char **command, int count_pipes);

//These must be synced with the function below
const char (*builtin_commands[]) = {
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

const char (*builtin_commands_help[]) = {
    "Displays all the commands",
    "Changes directory",
    "List all files",
    "Displays current directory",
    "Print the following string",
    "Process info",
    "Ticks the given command",
    "Ticks the given command",
    "Gets the environmental variable of the current shell",
    "Sets the environmental variable of the current shell",
    "Unsets the environmental variable of the current shell",
    "jobs",
    "overkill",
    "kjob",
    "Background current command",
    "Exit the current shell",
    "Quit the current shell",
    NULL
};

//These must be synced with the function above
const int (*execute_command[])(char **) = {
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
const char* shell_directory;// = (char*)malloc(BUFFER_SIZE*sizeof(char));
char* current_directory;// = (char*)malloc(BUFFER_SIZE*sizeof(char));
char* previous_directory;// = (char*)malloc(BUFFER_SIZE*sizeof(char));
char* temp_directory;// = (char*)malloc(BUFFER_SIZE*sizeof(char));

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
	getcwd(temp_directory , BUFFER_SIZE - 1);
    shell_directory = temp_directory;
	//strcpy(current_directory , shell_directory);
	current_directory[0] = '~';
	current_directory[1] = '\0';
	strcpy(previous_directory , current_directory);

	fprintf(stdout , "%s %s\n", "Shell directory is" , shell_directory);
    fprintf(stdout, "%sinit completed%s\n", "\x1B[34m", "\x1B[0m");
	do
	{
		fprintf(stdout , "%s@%s : %s > " , user , host , current_directory);
		lines = parse();
        fprintf(stdout, "%sparsing completed%s\n", "\x1B[31m", "\x1B[0m");
        // fprintf(stdout, "%s%lu%s\n", "\x1B[32m", sizeof(lines)/sizeof(lines[0]), "\x1B[0m");
        // fprintf(stdout, "%s%lu%s\n", "\x1B[32m", sizeof(lines[0])/sizeof(lines[0][0]), "\x1B[0m");
		if(lines)
		{
			int i;
			for(i = 0; lines[i]; i++)
			{
                // fprintf(stdout, "%s%d%s\n", "\x1B[34m", i, "\x1B[0m");
                // fprintf(stdout, "%s%s%s\n", "\x1B[34m", lines[i], "\x1B[0m");
                int count_pipes;
                if((count_pipes = is_piping(lines[i])))
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
                    // fprintf(stdout, "%stokenize completed%s\n", "\x1B[32m", "\x1B[0m");
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
