#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char command[100];
int main(int argc, char *argv[]) {
  char *exec_argv[] = { "strace", "ls", NULL, };
  char *exec_envp[] = { "PATH=/bin", NULL, };
  int a[argc];
  a[0]=1;
  printf("%d\n",a[0]);
  execve("strace",          exec_argv, exec_envp);
  execve("/bin/strace",     exec_argv, exec_envp);
  execve("/usr/bin/strace", exec_argv, exec_envp);
  perror(argv[0]);
  exit(EXIT_FAILURE);
}