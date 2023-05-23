#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
  int pid;

  printf("Parent process's PID: %d\n", getpid());
  pid = fork();

  if (pid == 0)
    {
      printf("I am the child process, and my PID is: %d\n", getpid());
      printf("My parent's PID is: %d\n", getppid());
      sleep(20);
      exit(10);
    }
  int retval;
  int status;
  retval = wait(&status);
  if (retval != pid)
    fprintf(stderr, "wait interrupted by signal.\n");
  else  
    printf("Thread %d done executing with exit code %u\n", retval, status);
}
