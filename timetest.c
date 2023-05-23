#include <stdlib.h>
#include <stdio.h>

int main()
{
  int i = 0;
  for (i = 0; i < 100; i++)
    {
      long t = time((long) NULL);
      printf("%d\n", t);
      sleep(1);
    }
}

  
