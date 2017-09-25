#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_variable.h"

const int TOKEN_SIZE;
const int BUFFER_SIZE;
const char* DELIMITERS;

void print_info(char* line);
char** parse();
