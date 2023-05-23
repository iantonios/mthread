#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  const char* exitstring = "exit";
  char* z;
  z = malloc(sizeof(char)*100);
  fgets(z,100,stdin);
  
  const char* compstring = z;
  printf("%d\n", strlen(z));
  z[strlen(z)-1] = '\0';
  printf("%s %d\n", z, strlen(z));
  printf("%s %d\n", exitstring, strlen(exitstring));
 
  if(strlen(compstring) == strlen(exitstring))
    {
    if(strncmp(compstring,exitstring,strlen(exitstring)) == 0)
      printf("Here");
    }
}
