#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <inttypes.h>
#include "global_variable.h"
#define KGRN  "\x1B[32m"
#define RESET   "\x1b[0m"

const int ls_command(char **command);
int ls_null(char* fp);
int ls_l(char* fp);
int ls_a(char* fp);
int ls_la(char* fp);
