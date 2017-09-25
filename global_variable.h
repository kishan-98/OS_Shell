#ifndef GLOBAL_VARIABLE
#define GLOBAL_VARIABLE

extern const int BUFFER_SIZE;
extern const int TOKEN_SIZE;
extern const char* DELIMITERS;
extern const char* COMMAND_DELIMITER;
extern const char* PIPING_DELIMITER;
extern const char* REDIRECTION_DELIMITER;
extern const char (*builtin_commands[]);
extern const int (*execute_command[])(char **);
//Absolute path of current directory
extern const char* shell_directory;
extern char* current_directory;
extern char* previous_directory;

#endif
