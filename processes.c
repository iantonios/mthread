// CSC425 -- Fall 2009
// Process creation 

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
   printf("Current process ID: %d\n", getpid());
   int r = fork();
   if (r == 0)
   {
      printf("I am the child process with PID %d, and ", getpid());
      printf("my parent's PID is %d.\n", getppid());
      printf("Child: Dozing off for 5 seconds.\n");
      sleep(5);
      exit(0);
   }
   else
   {
      printf("Parent: Waiting for the child to exit.\n");
      wait(NULL);
      printf("Parent: Done.\n");
   }

   // A chain of 5 processes 
   printf("\n\nChain structure: \n");
   int i;
   for (i = 0; i < 5; i++)
   {
      if ((r = fork()) == 0)
      {
         printf("My PID is %d and my parent's is %d.\n", getpid(), getppid());
         sleep(1);
      }
      else
         break;
   }
   wait(NULL);
   
   // make sure that all processes except the last one in the chain terminate
   if (r != 0)
      exit(0);
   
   
   // A fan of 5 processes sharing the same parent
   printf("\n\nFan structure: \n");
   for (i = 0; i < 5; i++)
   {
      if (fork() == 0)
      {
         printf("My PID is %d and my parent's is %d.\n", getpid(), getppid());
         exit(0);
      }
      sleep(1);
   }
   
   int pid;
   for (;;)
   {
      pid = wait(NULL);
      if (pid == -1)
         break;
   }
}



   