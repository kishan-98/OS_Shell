#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <inttypes.h>
#include "global_variable.h"

float get_time(char* args);

char* get_interrupt_details(char* line);
char* get_dirty_size(char* line);

int nightswatch_null();
int nightswatch_interrupt();
int nightswatch_dirty();

//These must be synced with the function below
/*char (*builtin_nightswatch_commands[]);

//These must be synced with the function above
int (*execute_nightswatch_command[])();*/

const int nightswatch_command(char **command);
