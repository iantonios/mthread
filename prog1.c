#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>

void printx(char*);
char* f(char*);
void print(double**);


// generate a random string of user specified length
int main(int argc, char* argv[])
{
  int array[3][4] = {{1, 2, 3,4}, {1, 2, 3,4}, {1, 2, 3,4}};

  int i, j;
  for (i = 0; i < 3; i++)
    {
      for (j = 0; j < 4; j++)
	printf("%d ", array[i][j]);
      printf("\n");
    }
  /*
  process* p = malloc(sizeof(process));
  p->processID = 222;
  p->owner = malloc(100);
  strcpy(p->owner, "ritchie");
  printf("process id: %d, owner: %s.\n", p->processID, p->owner);
  */

/*
  if (argc != 2)
    {
      printf("Usage: %s n, string_size.\n", argv[0]);
      exit(1);
    }

  int length = atoi(argv[1]);
  char* s = malloc(length+1);
  int i;
  srand(time(NULL));
  for (i = 0; i < length; i++)
    s[i] = (char) ('a' + rand()%26);
  s[length] = '\0';
  printf("%s\n", s);
 
  char* s = malloc(15);
  fgets(s, 5, stdin);
  printf("%s\n", s);
 */ 


  /*
  double** table;
  table = (double**) malloc(sizeof(double*)*5);
  int i;
  for (i = 0; i < 5; i++)
      table[i] = malloc((i+1)*sizeof(double));
  
  int row, col;
  for (row = 0; row < 5; row++)
    for (col = 0; col <= row; col++)
      table[row][col] = 10.3;

 
  for (i = 0; i < 5; i++)
    free(table[i]);

  free(table);
  //print(table);
  //printf("\n%d", RAND_MAX);
  

  char* s = malloc(100);
  printf("Enter some words: ");
  gets(s);
  char* tok = strtok(s, " ");
  printf("Tokens are: \n");
  while (tok != NULL)
    {
      printf("%s\n", tok);
      tok = strtok(NULL, " ");      
    }
  
    printf("%s", argv[0]);*/

}

void print(double** table)
{
  int row, col;
  for (row = 0; row < 5; row++)
    {
      for (col = 0; col <= row; col++)
	printf("%f ", table[row][col]);
      printf("\n");
    }

}

char* f(char* s)
{
  s = "hello";
  return s;
}


void printx(char* s)
{
  //  s[3] = 'x';
  printf("%s",s);
}
