#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <fcntl.h>

const char* DELIMITERS = " \t\n\r\a";
const char* COMMAND_DELIMITER = ";";
const char* PIPING_DELIMITER = "|";
const char* REDIRECTION_DELIMITER = "<>";

void init_shell(void);

int main();
