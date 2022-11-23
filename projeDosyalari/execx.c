#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

pid_t call(int argc, char* argv[]) {
  int i;
  int result = 0;
  pid_t pid = fork();
  if (pid == 0) {
    char* envp[] = { NULL };
    execve(argv[0], argv, envp);
    perror("Could not execve");
    exit(1);
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
