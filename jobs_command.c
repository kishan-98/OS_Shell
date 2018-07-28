#include "jobs_command.h"

int check_if_number (char *str)
{
  int i;
  for (i=0; str[i] != '\0'; i++)
  {
    if (!isdigit (str[i]))
    {
      return 0;
    }
  }
  return 1;
}

const int jobs_command(char **command)
{
    DIR *dirp;
    FILE *fp;
    struct dirent *entry;
    char path[MAX_BUF], read_buf[MAX_BUF],temp_buf[MAX_BUF];
    char uid_int_str[INT_SIZE_BUF]={0},*line;
    char *check_ppid;
    char *user;//*command;
    size_t len=0;
    dirp = opendir ("/proc/");
    if (dirp == NULL)
    {
         perror ("Fail");
         exit(0);
    }

    int PARENT = getpid();
    printf("PARENT: %d\n",PARENT);

    while ((entry = readdir (dirp)) != NULL)
    {
        if (check_if_number (entry->d_name))
        {
            //printf("IN %s \n",entry->d_name);
            strcpy(path,"/proc/");
            strcat(path,entry->d_name);
            strcat(path,"/stat");
            fp=fopen(path,"r");
            //printf("OPEN  %d %s \n",fp,entry->d_name);
            getline(&line,&len,fp);
            //printf("READ %s \n",entry->d_name);
            //printf("> %s \n",entry->d_name);
            char comm[10],state;
            unsigned int flags;
            int pid,ppid,pgrp,session,tty_nr,tpgid;
            unsigned long minflt,cminflt,majflt,cmajflt,utime,stime;
            unsigned long long starttime;
            long cutime,cstime,priority,nice,num_threads,itreavalue;
            sscanf(line,"%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld  %ld %llu",&pid,comm,&state,&ppid,&pgrp,&session,&tty_nr,&tpgid,&flags,&minflt,&cminflt,&majflt,&cmajflt,&utime,&stime,&cutime,&cstime,&priority,&nice,&num_threads,&itreavalue,&starttime);
            //sscanf(line,"%d %s %c %d %d %d %d",&pid,comm,&state,&ppid,&pgrp,&session,&tty_nr);

            // Get the name of the process
            strcpy (path, "/proc/");
            strcat (path, entry->d_name);
            strcat (path, "/comm");

        	fp = fopen (path, "r");
        	if (fp != NULL)
        	{
        	fscanf (fp, "%s", read_buf);
            fclose(fp);
            }
            //printf("@@@ %s \n",entry->d_name);
            //printf("id: %d\n",ppid);
            if (ppid == PARENT)
                fprintf(stdout,"%s %c %s\n",entry->d_name,state,read_buf);
        }
    }
    closedir (dirp);
    return 1;
}
