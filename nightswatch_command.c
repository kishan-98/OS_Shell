#include "nightswatch_command.h"

float DEFAULT_TIME = 2;

float get_time(char* args)
{
    //Convert string to integer if valid otherwise return 0
    int i;
    float time = 0;
    float mult_fact = 10 , error_fact = 1;
    int flag = 0;
    for(i = 0; args[i] != '\0'; i++)
    {
        if(0 <= (args[i]-'0') && (args[i]-'0') < 10)
        {
            time = mult_fact*time + (error_fact)*(args[i]-'0');
            if(flag)
            {
                //Inside decimans
                error_fact /= 10;
            }
        }
        else if(args[i] == '.'){
            mult_fact = 1;
            error_fact /= 10;
            flag = 1;
        }
        else{
            //Invalid character
            return 0;
        }
    }
    return time >= 0.1 ? time : 0;
}

char* get_dirty_size(char* line)
{
    //Get the dirty file size
    int i = 0;
    while(line[i++] != ' ');
    while(line[i++] == ' ');
    char* dirty_size = (char*)malloc(BUFFER_SIZE*sizeof(char));
    int curr_pos = 0;
    while(line[i] != '\0')
    {
        dirty_size[curr_pos++] = line[i++];
    }
    return dirty_size;
}

char* get_interrupt_details(char* line)
{
    //Get the dirty file size
    char* pos = strstr(line , "i8042");
    int i = (int)(pos - line);
    while(line[--i] != ' ');
    char* interrupt_details = (char*)malloc(BUFFER_SIZE*sizeof(char));
    strncpy(interrupt_details , line , ++i);
    interrupt_details[i - 1] = '\n';
    return interrupt_details;
}

int nightswatch_null()
{
    //No command to be "nightswatched"
    perror("command : enter command to be nightswatched");
    return 1;
}

int nightswatch_interrupt()
{
    char* file_path = (char*)malloc(BUFFER_SIZE*sizeof(char));
    char* file_data = (char*)malloc(BUFFER_SIZE*sizeof(char));
    int status = 0;
    size_t buffer_size = BUFFER_SIZE;
    if(!file_path)
    {
        //Error in memory allocation
        perror("Memory allocation error");
        free(file_path);
        free(file_data);
        return 1;
    }
    strcpy(file_path , "/proc/interrupts");
    FILE* fp = fopen(file_path , "r");
    if(!fp)
    {
        //Error in opening file
        perror("Error in opening file");
        free(file_path);
        free(file_data);
        return 1;
    }
    status = getline(&file_data , &buffer_size , fp);
    fprintf(stdout, "%s", file_data);
    status = 0;
    fclose(fp);
    while(1)
    {
        int c;
        static struct termios oldt, newt;

        /*tcgetattr gets the parameters of the current terminal
        STDIN_FILENO will tell tcgetattr that it should write the settings
        of stdin to oldt*/
        tcgetattr( STDIN_FILENO, &oldt);
        /*now the settings will be copied*/
        newt = oldt;

        /*ICANON normally takes care that one line at a time will be processed
        that means it will return if it sees a "\n" or an EOF or an EOL*/
        newt.c_lflag &= ~(ICANON);

        /*Those new settings will be set to STDIN
        TCSANOW tells tcsetattr to change attributes immediately. */
        tcsetattr( STDIN_FILENO, TCSANOW, &newt);

        fd_set rfds;
        struct timeval tv;
        int retval;

        /* Watch stdin (fd 0) to see when it has input. */
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        /* Wait up to DEFAULT_TIME. */
        tv.tv_sec = DEFAULT_TIME;
        tv.tv_usec = 0;

        retval = select(1, &rfds, NULL, NULL, &tv);
        if (retval == -1)
        {
            perror("select()");
        }
        else if (retval)
        {
            char c = getchar();
            if(c == 'q')
            {
                //User input q; que to exit
                //Restore old settings
                tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
                free(file_path);
                free(file_data);
                return 1;
            }
        }
        fp = fopen(file_path , "r");
        if(!fp)
        {
            //Error in opening file
            perror("Error in opening file");
            //Restore old settings
            tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
            free(file_path);
            free(file_data);
            return 1;
        }
        do {
            status = getline(&file_data , &buffer_size , fp);
            //fprintf(stdout, "%s = %d\n", "status" , status);
            if(strstr(file_data , "i8042") && strstr(file_data , " 1:"))
            {
                fprintf(stdout, "%s", get_interrupt_details(file_data));
                break;
            }
        } while(status != -1);
        fclose(fp);
        //Restore old settings
        tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    }
    free(file_path);
    free(file_data);
    return 1;
}

int nightswatch_dirty()
{
    char* file_path = (char*)malloc(BUFFER_SIZE*sizeof(char));
    char* file_data = (char*)malloc(BUFFER_SIZE*sizeof(char));
    int status = 0;
    if(!file_path)
    {
        //Error in memory allocation
        perror("Memory allocation error");
        free(file_path);
        free(file_data);
        return 1;
    }
    strcpy(file_path , "/proc/meminfo");
    while(1)
    {
        int c;
        static struct termios oldt, newt;

        /*tcgetattr gets the parameters of the current terminal
        STDIN_FILENO will tell tcgetattr that it should write the settings
        of stdin to oldt*/
        tcgetattr( STDIN_FILENO, &oldt);
        /*now the settings will be copied*/
        newt = oldt;

        /*ICANON normally takes care that one line at a time will be processed
        that means it will return if it sees a "\n" or an EOF or an EOL*/
        newt.c_lflag &= ~(ICANON);

        /*Those new settings will be set to STDIN
        TCSANOW tells tcsetattr to change attributes immediately. */
        tcsetattr( STDIN_FILENO, TCSANOW, &newt);

        fd_set rfds;
        struct timeval tv;
        int retval;

        /* Watch stdin (fd 0) to see when it has input. */
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        /* Wait up to DEFAULT_TIME. */
        tv.tv_sec = DEFAULT_TIME;
        tv.tv_usec = 0;

        retval = select(1, &rfds, NULL, NULL, &tv);
        if (retval == -1)
        {
            perror("select()");
        }
        else if (retval)
        {
            char c = getchar();
            if(c == 'q')
            {
                //User input q; que to exit
                //Restore old settings
                tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
                free(file_path);
                free(file_data);
                return 1;
            }
        }
        FILE* fp = fopen(file_path , "r");
        if(!fp)
        {
            //Error in opening file
            perror("Error in opening file");
            //Restore old settings
            tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
            free(file_path);
            free(file_data);
            return 1;
        }
        size_t buffer_size = BUFFER_SIZE;
        do {
            status = getline(&file_data , &buffer_size , fp);
            //fprintf(stdout, "%s = %d\n", "status" , status);
            if(strstr(file_data , "Dirty"))
            {
                fprintf(stdout, "%s", get_dirty_size(file_data));
                break;
            }
        } while(status != -1);
        fclose(fp);
        //Restore old settings
        tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    }
    free(file_path);
    free(file_data);
    return 1;
}

//These must be synced with the function below
char (*builtin_nightswatch_commands[]) = {
    "",
    "interrupt",
    "dirty",
    NULL
};

//These must be synced with the function above
int (*execute_nightswatch_command[])() = {
    &nightswatch_null,
    &nightswatch_interrupt,
    &nightswatch_dirty
};

const int nightswatch_command(char **command)
{
    if(command == NULL)
    {
        //Not any command
        fprintf(stderr , "%s\n", "command: expected command");
        return 1;
    }
    int i;
    int nightswatch_id = 0;//Stores the id of nightswatch command to be implemented
    for(i = 1; command[i]; i++)
    {
        //Check for all the argument
        if(!strcmp(command[i] , "-n"))
        {
            //This is flag for setting time
            if(command[i+1])
            {
                //Get the time and set it as default time
                DEFAULT_TIME = get_time(command[i+1]);
                if(!DEFAULT_TIME)
                {
                    fprintf(stdout, "%s\n", "Invalid time input");
                    return 1;
                }
            }
        }
        else
        {
            //Check for the rest of supported commands
            int id;
            for(id = 1; builtin_nightswatch_commands[id]; id++)
            {
                if(!strcmp(command[i] , builtin_nightswatch_commands[id]))
                {
                    //This is command to be 'nightswatched'
                    if(nightswatch_id)
                    {
                        //There are two commands to be "nightswatched"; not possibe
                        /*fprintf(stdout, "%s\n", "Two command cannot be nightswatched together");
                        return 1;*/
                        //Do nothing; implement the first given command
                    }
                    else
                    {
                        //Set this command to be nightswatch_id
                        nightswatch_id = id;
                    }
                }
            }
        }
    }
    //fprintf(stdout, "%s %d\n", "nightswatch_id =",nightswatch_id);
    return (*execute_nightswatch_command[nightswatch_id])();
}
