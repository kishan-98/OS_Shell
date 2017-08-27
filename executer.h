#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include "global_variable.h"

const int TOKEN_SIZE;
const int BUFFER_SIZE;
const char* DELIMITERS;

//If function is not present, then call syscall
int launch_system_command(char **args);

int execute(char** command);
