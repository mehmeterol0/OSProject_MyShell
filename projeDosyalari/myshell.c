#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
  

int input(char *str);

int bosmu(char *str);

int execArgs(char **args);

void ayir(char *str, char **cevirici, char *sinirlayici);

int cmd(char **args, char **komutListesi);

void execCommand(char **args, char **komutListesi, int index);

void temizle(void);

void yeniSatir(char *str);

int parameterError(char *cmd, char **args);

int kontrol(char **args);

int main()
{
    char girilenDeger[1000] = {'\0'};
    char *ceviriciArgs[100] = {NULL};
    char *processes[100] = {NULL};
    char *komutlar[8] = {"writef","bash","execx", "cat","ls", "clear", "exit", NULL}; 

    int i;
    while (1)
    {
        if (input(girilenDeger))
            continue;

        ayir(girilenDeger, processes, "|"); 
        i = 0;

        while (processes[i] != NULL)
        {
            ayir(processes[i], ceviriciArgs, " "); 
            if (cmd(ceviriciArgs, komutlar))
            {
                printf("yanlis bir komut girildi\n");
            }
            i++;
        }
    }
    return 0;
}

int bosmu(char *str)
{
    while (*str != '\0')
    {
        if (*str != ' ')
        {
            return 0;
        }
        str++;
    }
    return 1;
}

int input(char *str)
{
    printf("\nmyshell>>");
    fgets(str, 1000, stdin);
    yeniSatir(str);
    if (!bosmu(str))
    {
        return 0;
    }

    return -1;
}

int execArgs(char **args)
{
    pid_t pid = fork();
    int i,j;
    int result = 0;
    int iArgs= atoi(args[2]);
    int argBoyut = (sizeof(args) / sizeof(int));
    if (pid == 0)
    {
    
    //(strcmp("execx", args[0]) == 0)
        if (strcmp("execx", args[0]) == 0)
        {
          if((strcmp("-t", args[1]) == 0)){
          	if(args[3] !=NULL || args[5] != NULL ){
           //pdf'e gore bir programın calistirilmasi icin en az 4 parametreye ihtiyac var.		
	   //dogru bir sekilde girildiginde argBoyutumun 2 oldugunu gordum. yazdırma icinde 4'dur.
			    for(j=0; j<iArgs; j++){
			    	pid = fork();
			    	if(!pid){
					i = execv("execx",args);
				}
			    }
		 }
          }
	  else{ 
		printf("eksik parametre/yanlis parametre girildi %d\n",argBoyut);
	        exit(0);
          }
        }
        if(strcmp("cat", args[0]) == 0){
	    i = execv("/bin/cat", args);
        }
        if(strcmp("ls", args[0]) == 0){
            i = execv("/bin/ls",args);
        }
        if (strcmp("bash", args[0]) == 0)
        {
            execv("/bin/sh", args);
        }
        else
        {
            i = execv(args[0], args);
        }
        if (i < 0)
        {
            printf("yanlis bir komut girildi\n");
            exit(0);
        }
    }
    else
    {
        wait(&i);
        result = WEXITSTATUS(i);

    }

    return result;
}

int cmd(char **args, char **komutListesi)
{
    int i = 0;
    int isFound = 0;

    while (komutListesi[i] != NULL)
    {
        if (strcmp(args[0], komutListesi[i]) == 0)
        {
            isFound = 1;
            break;
        }
        i++;
    }

    if (isFound)
    {
        if (!parameterError(args[0], args))
        {
            execCommand(args, komutListesi, i);
        }
        else
        {
            return -1;
        }
    }

    return isFound ? 0 : -1;
}

void execCommand(char **args, char **komutListesi, int index)
{

    if (strcmp("exit", komutListesi[index]) == 0)
    {
        exit(0);
    }
    else if (strcmp("clear", komutListesi[index]) == 0)
    {
        temizle(); 
    }
    else 
    {
        execArgs(args);
    }
}

void ayir(char *str, char **cevirici, char *sinirlayici)
{
    int i = 0;
    while ((cevirici[i] = strsep(&str, sinirlayici)) != NULL)
    {
        if (bosmu(cevirici[i]))
        {
            continue;
        }
        i++;
    }
}

void yeniSatir(char *str)
{
    while (*str != '\0')
    {
        if (*str == '\n')
        {
            *str = '\0';
            break;
        }
        str++;
    }
}

void temizle()
{
    printf("\033[H\033[J");
}
int kontrol(char **args)
{
    int i = 0;
    while (args[i] != NULL) 
    {
        i++;
    }

    if (i < 3) 
    {
        return -1; 
    }



    return 0;
}

int parameterError(char *cmd, char **args)
{
    if (strcmp("execx", cmd) == 0)
    {
        if (kontrol(args))
        {
            return -1;
        }
    }
    return 0;
}


