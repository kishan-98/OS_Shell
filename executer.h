#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_variable.h"

const int TOKEN_SIZE;
const int BUFFER_SIZE;
const char* DELIMITERS;

//List of commands
int cd_command(char **args);
int help_command(char **args);
int exit_command(char **args);

//If function is not present, then call syscall
int lsh_launch(char **args);

int count_commands();

int execute(char** command);
