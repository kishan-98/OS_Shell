#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "global_variable.h"
#include "is_background.h"

int execute_system_command(char ** args, int background);
//If function is not present, then call syscall
int launch_system_command(char **command , int background);

int execute(char** command);
