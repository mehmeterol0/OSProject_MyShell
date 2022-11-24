#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t call(int argc, char* argv[]) {
  int i,j;
  int result = 0;
  pid_t pid = fork();
  if (pid == 0) {
  
    execv("writef", argv);

  }else
  { 
    return pid;
  }
}

int main(int *argv[]) {

  pid_t pid = call(NULL,NULL);
  printf("New process got pid: %d\n", pid);
  return 0;
}


/*
int main(char **argv[])
{
    int i,j;
    int pid = fork();
    int result;
    int iArgs= atoi(argv[2]);
    if (pid == 0)
    {
    	for(j=0; j<10; j++){
            	pid = fork();
            	if(!pid){
			execv("writef",argv);
		}
        }

    }
    else
    {
        wait(&i); 
        result = WEXITSTATUS(i); 
    }

    return result; 
}
*/
