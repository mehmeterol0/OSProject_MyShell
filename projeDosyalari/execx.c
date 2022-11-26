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
  int pid;
  int iArgs= atoi(argv[2]);
  int j;
  //pid = fork();
  int argBoyut = ((sizeof(argv)) / (sizeof (int)));
  
  if(strcmp("writef", argv[3]) == 0){ //sadece programı istedigi kadar calıstırır.
  	for(j=0; j<iArgs; j++){
  		  pid = fork();
  		  if(pid == 0){
			  printf("New process got pid: %d - ppid : %d\n", getpid(), getppid());
			  execv (argv[3],argv);
		  }
	  }
	  if(strcmp("-f", argv[4]) == 0){ // alınan parametreye gore dosyaya yazma islemi.
		  for(j=0; j<(iArgs/2)-1; j++){
		  printf("New process got pid: %d - ppid : %d\n", getpid(), getppid());
		  	pid = fork();
		  	if(pid == 0){
			    if(argv[5] != NULL){
			    	execv (argv[3],argv);
			    }
			}
		   }
  	  }
  	  else{
  	    	printf("yanlis parametre girildi. %d\n",argBoyut);
		exit(0);
  	  }
  }
  else{
  	    	printf("yanlis parametre girildi. %d\n",argBoyut);
		exit(0);
  }


  pid = wait(NULL); //bunu yazmassam bash,ls,cat calısmaz.
  return 0;
}



