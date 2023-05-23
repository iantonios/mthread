// display the contents of a file with line numbers

#include <stdio.h>

int main(int argc, char* argv[])
{
  if (argc !=2)
    {
      printf("usage: %s filename", argv[0]);
      exit(1);
    }

  // open the file for reading. fopen returns a pointer 
  FILE* fp = fopen(argv[1], "r");

  // create the string that will be input
  char line[81];
  int linenum = 1;

  while (!feof(fp))
    {
      // read up to 80 characters from file and store in string 'line' 
      fgets(line, 80, fp);

      // print line number and line contents
      printf("%d. %s", linenum++, line);
    }
  fclose(fp);

}

