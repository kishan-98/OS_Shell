#ifndef GLOBAL_VARIABLE
#define GLOBAL_VARIABLE

extern const int BUFFER_SIZE;
extern const int TOKEN_SIZE;
extern const char* DELIMITERS;
extern const char (*builtin_commands[]);
extern const int (*execute_command[])(char **);
extern const int count_commands;

#endif
