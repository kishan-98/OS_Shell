#include "shell.h"

int TOKEN_SIZE = 64;
int BUFFER_SIZE = 1024;

void init_shell(void)
{
	char *line;
	char **args;
	int status;

	do 
	{
	printf("> ");
	line = parse();
	args = tokenize(line);
	//status = lsh_execute(args);

	free(line);
	free(args);
	} while (status);
}

int main(int argc, char **argv)
{
	init_shell();
	return EXIT_SUCCESS;
}

