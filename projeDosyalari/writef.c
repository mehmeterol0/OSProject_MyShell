#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int pid,ppid;
    pid = getpid();
    ppid = getppid();
    FILE *dosya =fopen(strcat(argv[5],".txt"),"a");
    fprintf(dosya,"now: %d-%02d-%02d %02d:%02d:%02d - pid : %d - ppid : %d\n", tm.tm_year + 1900, tm.tm_mon + 1, 			 
    tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,pid,ppid);
    fclose(dosya);
    return 0;
}
