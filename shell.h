#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>

#define DELIMITERS " \t\n\r\a"
#define COMMAND_DELIM ";"

void init_shell(void);

char** tokenize(char* line);
void print_info1(char** lines , int count_lines);
void print_info(char* line);
char* parse();

int main();