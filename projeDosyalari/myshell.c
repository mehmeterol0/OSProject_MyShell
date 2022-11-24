#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


#define MAX_CAHARACTER 1000 
#define MAX_LIST 100        
#define CMD_SIZE 6          

int input(char *str);

int bosmu(char *str);

int execArgs(char **args);

void ayir(char *str, char **parsed, char *delim);

int cmdHandler(char **args, char **cmdList);

void execCommand(char **args, char **cmdList, int index);

void temizle(void);

void yeniSatir(char *str);

int parameterError(char *cmd, char **args);

int kontrol(char **args);

int main()
{
    char girilenDeger[MAX_CAHARACTER] = {'\0'};
    char *parsedArgs[MAX_LIST] = {NULL};
    char *processes[MAX_LIST] = {NULL};
    char *komutlar[CMD_SIZE] = {"writef","bash","execx", "cat", "clear", "exit", NULL}; 

    int i;
    while (1)
    {
        if (input(girilenDeger))
            continue;

        ayir(girilenDeger, processes, "|"); 
        i = 0;

        while (processes[i] != NULL)
        {
            ayir(processes[i], parsedArgs, " "); 
            if (cmdHandler(parsedArgs, komutlar))
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
    int kontrol = 0;
    int iArgs= atoi(args[2]);
    if (pid == 0)
    {
        if (strcmp("execx", args[0]) == 0)
        {
            for(j=0; j<iArgs; j++){
            	pid = fork();
            	if(!pid){
	        	i = execv("execx",args);
	        }
            }
        }
        if (strcmp("bash", args[0]) == 0)
        {
            i = execv("/bin/sh", args);
        }
	if (strcmp("writef", args [3]) == 0){
	    i = execv("writef",args);
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

int cmdHandler(char **args, char **cmdList)
{
    int i = 0;
    int isFound = 0;

    while (cmdList[i] != NULL)
    {
        if (strcmp(args[0], cmdList[i]) == 0)
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
            execCommand(args, cmdList, i);
        }
        else
        {
            return -1;
        }
    }

    return isFound ? 0 : -1;
}

void execCommand(char **args, char **cmdList, int index)
{

    if (strcmp("exit", cmdList[index]) == 0)
    {
        exit(0);
    }
    else if (strcmp("clear", cmdList[index]) == 0)
    {
        temizle(); 
    }
    else 
    {
        execArgs(args);
    }
}

void ayir(char *str, char **parsed, char *delim)
{
    int i = 0;
    while ((parsed[i] = strsep(&str, delim)) != NULL)
    {
        if (bosmu(parsed[i]))
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


