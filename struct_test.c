// Program reads in up to 5 car records from stdin and 
// stores them in an array of pointers to Car structures.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 5

typedef struct CarInfo
{
  char* make;
  int year;
} Car;

// function prototype 
void printRecords(Car** cars, int count);

int main()
{
  // double pointer to Car struct
  Car** cars;
  
  // count of Car records read in
  int recordCount = 0;
  
  // holders for data entered by user
  char input[80];
  
  // create array of 10 pointers to Car structs
  cars = malloc(MAX_RECORDS * sizeof(Car*));
  
  printf("Enter car make followed by year (Ctrl-D to exit): ");
  fgets(input, 80, stdin);
  
  while (!feof(stdin) && recordCount < MAX_RECORDS)
  { 
    // extract make and year from user input
    char* mk = strtok(input, " ");
    char* yr = strtok(NULL, " ");
    
    // allocate memory for struct and then make field
    cars[recordCount] = malloc(sizeof(Car));
    cars[recordCount]->make = malloc(sizeof(mk) + 1);
    
    // copy values to Car struct
    strcpy(cars[recordCount]->make, mk);
    cars[recordCount]->year = atoi(yr);
    recordCount++;
    
    // ask for the next record
    if (recordCount < MAX_RECORDS)
    {
      printf("Enter car make followed by year (Ctrl-D to exit): ");
      fgets(input, 80, stdin);
    }
  }
  
  printRecords(cars, recordCount);
  
  // deallocate memory
  int i;
  for (i = 0; i < recordCount; i++)
  {
    // deallocate field then the struct
    free(cars[i]->make);
    free(cars[i]);
  }
  // deallocate array
  free(cars);
  
  return EXIT_SUCCESS;
}
    
  

void printRecords(Car** cars, int count)
{
  int i;
  
  printf("\n\n      Make     Year\n");
  for (i = 0; i < count; i++)
    printf("%10s %8d\n", cars[i]->make, cars[i]->year);
  
}