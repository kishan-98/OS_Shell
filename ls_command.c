#include "ls_command.h"

int ls_null(char* fp)
{
    // Implements only ls
    if (fp[0] == '~')
    {
        char* temp = (char*)malloc(2*BUFFER_SIZE*sizeof(char));
        strcpy(temp,shell_directory);
        strcat(temp, &fp[1]);
        strcpy(fp, temp);
        free(temp);
    }
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    char buf[512];
    mydir = opendir(fp);
    if(!mydir)
    {
        perror("command");
        return 1;
    }
    struct passwd *pwd;
    struct group *grp;
    struct tm *tm;
    char datestring[256];

    while((myfile = readdir(mydir)) != NULL)
    {
        stat(buf, &mystat);
        char* temp_name = myfile->d_name;
        if(temp_name[0]!='.')
            fprintf(stdout, "%s\n", temp_name);
    }
    closedir(mydir);
    return 1;
}

int ls_l(char* fp)
{
    // Implements ls -l
    if (fp[0] == '~')
    {
        char* temp = (char*)malloc(2*BUFFER_SIZE*sizeof(char));
        strcpy(temp,shell_directory);
        strcat(temp, &fp[1]);
        strcpy(fp, temp);
        free(temp);
    }
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    char buf[512];
    mydir = opendir(fp);
    if(!mydir)
    {
        perror("command");
        return 1;
    }
    struct passwd *pwd;
    struct group *grp;
    struct tm *tm;
    char datestring[256];

    while((myfile = readdir(mydir)) != NULL)
    {
        stat(myfile->d_name, &mystat);
        char* temp_name = myfile->d_name;
        if(temp_name[0]!='.')
        {
            printf((S_ISDIR(mystat.st_mode))  ? "d" : "-");
            printf((mystat.st_mode & S_IRUSR) ? "r" : "-");
            printf((mystat.st_mode & S_IWUSR) ? "w" : "-");
            printf((mystat.st_mode & S_IXUSR) ? "x" : "-");
            printf((mystat.st_mode & S_IRGRP) ? "r" : "-");
            printf((mystat.st_mode & S_IWGRP) ? "w" : "-");
            printf((mystat.st_mode & S_IXGRP) ? "x" : "-");
            printf((mystat.st_mode & S_IROTH) ? "r" : "-");
            printf((mystat.st_mode & S_IWOTH) ? "w" : "-");
            printf((mystat.st_mode & S_IXOTH) ? "x" : "-");

            /* Print out owner's name if it is found using getpwuid(). */
            if ((pwd = getpwuid(mystat.st_uid)) != NULL)
                printf(" %-8.8s", pwd->pw_name);
            else
                printf(" %-8d", mystat.st_uid);

            /* Print out group name if it is found using getgrgid(). */
            if ((grp = getgrgid(mystat.st_gid)) != NULL)
                printf("%-8.8s", grp->gr_name);
            else
                printf("%-8d", mystat.st_gid);

            /* Print size of file. */
            printf(" %9jd", (intmax_t)mystat.st_size);
            tm = localtime(&mystat.st_mtime);

            /* Get localized date string. */
            strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
            printf(" %s", datestring);
            printf(KGRN " %s\n" RESET,myfile->d_name);
        }
    }
    closedir(mydir);
    return 1;
}

int ls_a(char* fp)
{
    // Implements ls -la
    if (fp[0] == '~')
    {
        char* temp = (char*)malloc(2*BUFFER_SIZE*sizeof(char));
        strcpy(temp,shell_directory);
        strcat(temp, &fp[1]);
        strcpy(fp, temp);
        free(temp);
    }
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    char buf[512];
    mydir = opendir(fp);
    if(!mydir)
    {
        perror("command");
        return 1;
    }
    struct passwd *pwd;
    struct group *grp;
    struct tm *tm;
    char datestring[256];

    while((myfile = readdir(mydir)) != NULL)
    {
        stat(buf, &mystat);
        fprintf(stdout, "%s\n", myfile->d_name);
    }
    closedir(mydir);
    return 1;
}

int ls_la(char* fp)
{
    // Implements ls -la or ls -al
    if (fp[0] == '~')
    {
        char* temp = (char*)malloc(2*BUFFER_SIZE*sizeof(char));
        strcpy(temp,shell_directory);
        strcat(temp, &fp[1]);
        strcpy(fp, temp);
        free(temp);
    }
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    char buf[512];
    mydir = opendir(fp);
    if(!mydir)
    {
        perror("command");
        return 1;
    }
    struct passwd *pwd;
    struct group *grp;
    struct tm *tm;
    char datestring[256];

    while((myfile = readdir(mydir)) != NULL)
    {
        stat(myfile->d_name, &mystat);
        char* temp_name = myfile->d_name;
        printf((S_ISDIR(mystat.st_mode))  ? "d" : "-");
        printf((mystat.st_mode & S_IRUSR) ? "r" : "-");
        printf((mystat.st_mode & S_IWUSR) ? "w" : "-");
        printf((mystat.st_mode & S_IXUSR) ? "x" : "-");
        printf((mystat.st_mode & S_IRGRP) ? "r" : "-");
        printf((mystat.st_mode & S_IWGRP) ? "w" : "-");
        printf((mystat.st_mode & S_IXGRP) ? "x" : "-");
        printf((mystat.st_mode & S_IROTH) ? "r" : "-");
        printf((mystat.st_mode & S_IWOTH) ? "w" : "-");
        printf((mystat.st_mode & S_IXOTH) ? "x" : "-");

        /* Print out owner's name if it is found using getpwuid(). */
        if ((pwd = getpwuid(mystat.st_uid)) != NULL)
            printf(" %-8.8s", pwd->pw_name);
        else
            printf(" %-8d", mystat.st_uid);

        /* Print out group name if it is found using getgrgid(). */
        if ((grp = getgrgid(mystat.st_gid)) != NULL)
            printf("%-8.8s", grp->gr_name);
        else
            printf("%-8d", mystat.st_gid);

        /* Print size of file. */
        printf(" %9jd", (intmax_t)mystat.st_size);
        tm = localtime(&mystat.st_mtime);

        /* Get localized date string. */
        strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
        printf(" %s", datestring);
        printf(KGRN " %s\n" RESET,myfile->d_name);
    }
    closedir(mydir);
    return 1;
}

const int ls_command(char **command)
{
    //printf("%s\n", command[1]);
    if(command == NULL)
    {
        //Not any command
        fprintf(stderr , "%s\n", "command: expected command");
        return 1;
    }

    int i = 0;
    int flag_ls_l = 0, flag_ls_a = 0;
    char* path = (char*)malloc(BUFFER_SIZE*sizeof(char));
    path[0] = '.';
    path[1] = '\0';
    for(i = 1; command[i]; i++)
    {
        if(command[i][0]=='-'){
            int j;
            for(j = 1; command[i][j] != '\0'; j++)
            {
                if(command[i][j] == 'l')
                {
                    flag_ls_l = 1;
                }
                else if(command[i][j] == 'a')
                {
                    flag_ls_a = 1;
                }
            }
        }
        else{
            strcpy(path , command[i]);
        }
    }

    if(flag_ls_l)
    {
        if(flag_ls_a)
        {
            return ls_la(path);
        }
        return ls_l(path);
    }
    else if(flag_ls_a)
    {
        return ls_a(path);
    }
    return ls_null(path);

    return 1;
}
