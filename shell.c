#include "shell.h"

int TOKEN_SIZE = 64;
int BUFFER_SIZE = 1024;

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
	//status = execute(args);

	free(line);
	free(args);
} while (status == 0);
}

int main(int argc, char **argv)
{
	init_shell();
	return EXIT_SUCCESS;
}
