#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char *argv[]) {

  int pid; //forklama icin gerekli olan degiskenim
  int iArgs= atoi(argv[2]); //gelen 2. parametre benim programin kac kere calisacagini gosterir.
  int j;
  int argBoyut = strlen(argv); //gelen arg boyu tutar.
  int parametreKontrol = 0;

  
  if(argv[3] != NULL){ //sadece programı istedigi kadar calıstırır.
     if(argBoyut == 6){ //sadece ilgili program calismasi icin gereken parametre 4 yerinde olmalidir.
	  	for(j=0; j<iArgs; j++){ //iArgs benim kac kere calisacagini tutuyordu.
	  		  pid = fork();//her bir calismada bir fork islemi gerceklesmektedir.
	  		  if(pid == 0){
	  		          if(parametreKontrol==0){
				  printf("New process got pid: %d - ppid : %d \n", getpid(), getppid());
				  //getpid ile pid, getppid ile ppid degerleri cekilir.
				  execv (argv[3],argv); //gelen argumana gore ilgili program argumanlariyla gonderilir.
				  }
			  }
		  }
	  }
     else{
     	printf("Yanlis Parametre, argBoyut : %d",argBoyut);//yanlis parametre kontrolu
     	exit(0);
     }

  }
  else{
  	    	printf("yanlis parametre girildi. 2 %d\n",argBoyut);//yanlis parametre kontrolu
		exit(0);
  }


  pid = wait(NULL); //bunu yazmassam bash,ls,cat calismamaktadir.
  return 0;
}



