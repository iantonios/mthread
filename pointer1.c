// CSC425 -- Fall 2007
// Review of C

#include <stdio.h>

struct car
{
  char* make;
  int year;
};

// printing an array using array indexing first then using
// pointer arithmetic
void printArray(int *array)
{
  int i;
  
  for (i = 0; i < 5; i++)
    printf("Array[%d] is: %d\n", i, array[i]);

  printf("\nArray values using pointer arithmetic:\n");
  for (i = 0; i < 5; i++)
    printf("Array[%d] is: %d\n", i, *(array+i));
}

// passing by value 
void f1(int a)
{
  a = -100;
}

// passing the address of a variable to emulate pass by reference
void f2(int* p)
{
  *p = -100;
}

// the pointer is passed by value, so this assignment will not be
// reflected after the method returns.  Newly allocated integer
// will no longer be accessible, thus causing a memory leak
void ptrFun1(int* ptr)
{
  ptr = malloc(sizeof(int));
}

// to change the value of the pointer (i.e. to emulate it being
// passed by reference, a second level of indirection is needed
void ptrFun2(int**ptr)
{
  *ptr = malloc(sizeof(int));
}

// A 2D array as a double pointer
void initTable(int** table)
{
  int i, j;

  for (i = 0; i < 5; i++)
    for (j = 0; j < 10; j++)
      table[i][j] = i*j;
}

void printTable(int** table)
{
  int i, j;

  for (i = 0; i < 5; i++)
    {

      for (j = 0; j < 10; j++)
	printf("%d  ", table[i][j]);
      printf("\n");
    }
}


int main()
{
  
  // a pointer to an integer
  int* p1;
  p1 = malloc(sizeof(int));
  *p1 = 10;

  // a pointer to a double
  double* p2;
  p2 = malloc(sizeof(double));
  *p2 = 14.55;

  // pointer value is the memory address
  printf("p1's value is: %d\n", p1);
  // the next memory address should correspond to 
  // an offset equaling the size of an integer
  // shouldn't that cause a segmentation fault?
  printf("The next address: %d\n", p1+1);
  printf("p1 is pointing to: %d\n", *p1);

  printf("p2's value is: %d\n", p2);
  // notice how the address change is by 8 bytes instead
  printf("The next address: %d\n", p2+1);
  printf("Dereferenced pointer: %f\n\n", *p2);

  // allocating memory for an array of 5 integers
  int* array;
  array = malloc(sizeof(int)*5);
  printArray(array);


  int x = 100;
  f1(x);
  printf("\nIn main, after f1, x is: %d\n", x);
  f2(&x);
  printf("in main, after f2, x is: %d\n\n", x);


  int* p3;
  int a = 25;
  p3 = malloc(sizeof(int));
  *p3 = 10;
  printf("In main (before ptrFun1): p3 is %d\n", p3);
  ptrFun1(p3);
  printf("In main: (after ptrFun1): p3 is %d\n\n", p3);

  printf("In main (before ptrFun2): p3 is %d\n", p3);
  ptrFun2(&p3);
  printf("In main (after ptrFun2): p3 is %d\n\n", p3);

  // a structure variable declaration
  struct car c;
  // memory needs to be allocated for the string
  // fields of a structure pointer accessed using a period
  c.make = malloc(sizeof(char) * 10);
  strcpy(c.make, "VW");
  c.year = 2003;
  printf("Car info: %s, %d\n\n", c.make, c.year);

  // a pointer to a structure
  struct car* c2;
  // memory for the fields needs to be allocated before
  // they can be referenced
  c2 = malloc(sizeof(struct car));
  // now memory for the character string needs to be allocated.
  // fields of a pointer to a structure are accessed with an arrow
  c2->make = malloc(sizeof(char) *10);
  strcpy(c2->make, "Ford");
  c2->year = 2005;
  printf("Car info: %s, %d\n\n", c2->make, c2->year);


  // a 2D array as a double pointer
  int** table;
  int i;
  // first allocate memory for the columns -- an array of 
  // 10 integer pointers
  table = malloc(sizeof(int*) * 10);
  // for each column pointer, allocate an array of 5 integers
  for (i = 0; i < 10; i++)
    table[i] = malloc(sizeof(int) * 5);

  // well.. do the obvious
  initTable(table);
  printTable(table);

  // a couple of useful ways to interface with UNIX
  printf("\n\nOutput of ls: \n");
  system("ls");
  printf("\nValue of PATH environment variable:\n");
  printf("%s", getenv("PATH"));
}
