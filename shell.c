#include "shell.h"

int TOKEN_SIZE = 64;
int BUFFER_SIZE = 1024;

int help_command(char **command);
int cd_command(char **command);
int pwd_command(char **command);
int exit_command(char **command);

//These must be synced with the function below
char (*builtin_commands[]) = {
    "help",
    "cd",
    "pwd",
    "exit"
};

//These must be synced with the function above
int (*execute_command[])(char **) = {
    &help_command,
    &cd_command,
	&pwd_command,
    &exit_command
};

int count_commands = sizeof(builtin_commands)/sizeof(char*);

void init_shell(void)
{
	char *line;
	char **args;
	int status = 0;

	do
	{
		printf("> ");
		line = parse();
		args = tokenize(line);
		status = execute(args);

		free(line);
		free(args);
	} while (status);
}

int main(int argc, char **argv)
{
	init_shell();
	fprintf(stdout, "%s\n", "GoodBye!");
	fprintf(stdout, "%s\n", "Have a nice day.");
	return EXIT_SUCCESS;
}
