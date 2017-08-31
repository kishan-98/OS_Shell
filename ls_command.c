#include "ls_command.h"


int ls_null(char* fp)
{
    // Implements only ls
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    char buf[512];
    mydir = opendir(fp);
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
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    char buf[512];
    mydir = opendir(fp);
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
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    char buf[512];
    mydir = opendir(fp);
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
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    char buf[512];
    mydir = opendir(fp);
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

int ls_command(char **command)
{
    //printf("%s\n", command[1]);
    if(command[1] == NULL)
    {
        return ls_null(".");
    }
    else if(command[1])
    {
        if(command[2] == NULL && command[1][0] == '-')
        {
            if(!strcmp(command[1],"-l"))
            {
                return ls_l(".");
            }
            else if(!strcmp(command[1],"-a"))
            {
                return ls_a(".");
            }
            else if(!strcmp(command[1],"-la") || !strcmp(command[1],"-al"))
            {
                return ls_la(".");
            }
        }
        else if(command[2] != NULL && command[1][0] != '-')
        {
            if(!strcmp(command[2],"-l"))
            {
                return ls_l(command[1]);
            }
            else if(!strcmp(command[2],"-a"))
            {
                return ls_a(command[1]);
            }
            else if(!strcmp(command[2],"-la") || !strcmp(command[2],"-al"))
            {
                return ls_la(command[1]);
            }
        }
        else if(command[1][0] != '-' && command[2] == NULL)
        {
            return ls_null(command[1]);
        }
        else
        {
            perror("command");
            return(EXIT_FAILURE);
        }
    }

    return 1;
}
