#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int i;
    FILE *dosya =fopen(strcat(argv[5],".txt"),"a");
    fprintf(dosya,"now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, 			 
    tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fclose(dosya);
    return 0;
}
