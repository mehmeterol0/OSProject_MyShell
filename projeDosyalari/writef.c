#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int pid,ppid;
    pid = getpid(); //pid degerini tutan degisken
    ppid = getppid(); //ppid degerini tutan degisken
    FILE *dosya =fopen(strcat(argv[5],".txt"),"a"); //dosyamiz gelen arguman ismine gore .txt dosyasi olusturur.
    fprintf(dosya,"now: %d-%02d-%02d %02d:%02d:%02d - pid : %d - ppid : %d\n", tm.tm_year + 1900, tm.tm_mon + 1, 			 
    tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,pid,ppid);
    //istenildigi sekilde once system zamani, sonra pid, en sonda ppid degerleri tek satirda yazilmaktadir.
    fclose(dosya); //dosyayi her seferinde mutlaka kapatmamiz gerekmektedir. 
    //acik bir dosya icersine asla yazi yazilamaz.
    return 0;
}
