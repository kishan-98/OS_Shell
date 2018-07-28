#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>

// Execution Layer
#include "executer.h"
#include "global_variable.h"
#include "parser.h"
#include "tokenizer.h"

// Commands
#include "bg_command.h"
#include "cd_command.h"
#include "echo_command.h"
#include "exit_command.h"
#include "getenv_command.h"
#include "setenv_command.h"
#include "unsetenv_command.h"
#include "help_command.h"
#include "ls_command.h"
#include "pwd_command.h"
#include "is_background.h"
#include "is_piping.h"
#include "piping.h"
#include "redirection.h"
#include "jobs_command.h"
#include "kjob_command.h"
#include "nightswatch_command.h"
#include "overkill_command.h"
#include "pinfo_command.h"

const char* DELIMITERS = " \t\n\r\a";
const char* COMMAND_DELIMITER = ";";
const char* PIPING_DELIMITER = "|";
const char* REDIRECTION_DELIMITER = "<>";

void init_shell(void);

int main();
