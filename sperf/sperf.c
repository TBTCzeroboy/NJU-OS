#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *exec_envp[] = { "PATH=/bin", NULL, };
  char *exec_argv[4];
  exec_argv[0]="strace",exec_argv[1]="-tt";
  exec_argv[2]="ls";
  exec_argv[3]=NULL;
  int pipefd[2];
  if(pipe(pipefd)==-1){
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  pid_t pid=fork();
  if(pid<0){
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if(pid==0){
    close(pipefd[0]);
    dup2(pipefd[1],STDERR_FILENO);
    close(STDERR_FILENO);
    execve("/bin/strace",     exec_argv, exec_envp);
  }
  else{
    close(pipefd[1]);
    char buf=0;
    while(read(pipefd[0],&buf,1)>0){
      printf("fuck\n");
      printf("%c",buf);
    }
    return 0;
  } 
  perror(argv[0]);
  exit(EXIT_FAILURE);
}

  //execve("strace",          exec_argv, exec_envp);
  //execve("/bin/strace",     exec_argv, exec_envp);