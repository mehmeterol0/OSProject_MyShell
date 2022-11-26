#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/*
pid_t call(int argc, char *argv[]) {
  int i,j;
  int result = 0;
  pid_t pid = fork();
  if (pid == 0) {
  
    //execv("writef", argv);
    execv (argv[3],argv);

  }else
  { 
    return pid;
  }
}

*/

int main(int argc, char *argv[]) {

  //pid_t pid = call(argc,argv);
  //pid_t pid;
  printf("New process got pid: %d - ppid : %d\n", getpid(), getppid());
  int i,j;
  int result = 0;
  //pid = fork();
  int argBoyut = (sizeof(argv) / sizeof(int));
  //if (pid == 0) {
    //execv("writef", argv);
    if(strcmp("-f", argv[4]) == 0){
    	if(argBoyut == 2){
    		execv (argv[3],argv);
    	}
    }

  //}

  return 0;
}



