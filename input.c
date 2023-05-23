#include <stdio.h>
#include <string.h>

int main()
{
  char* str1 = malloc(sizeof(char)* 20);
  printf("Enter something: ");
  //fgets(str1, 19, stdin);
  gets(str1);
  printf("what you entered has %d characters.\n", strlen(str1));
  //str1[strlen(str1)-1] = '\0';

  char* str2 = malloc(sizeof(char)* 20);
  printf("Enter something else: ");
  gets(str2);
  printf("what you entered has %d characters.\n", strlen(str2));
  //fgets(str2, 19, stdin);
  //str2[strlen(str2)-1] = '\0';
  printf("what you entered: %s, %s\n", str1, str2);
}
