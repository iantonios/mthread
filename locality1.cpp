#include <ctime>
#include <iostream>

using namespace std;

int main()
{
  const int SIZE = 100000;
  const int REPS = 1000;
  double array[SIZE];
  int randIndex = 0;

  srand((long) time(NULL));
  
  clock_t start = clock();
  for (int j = 0; j < REPS; j++)
    {
      for (int i = 0; i < SIZE; i++)
	{
	  randIndex = (randIndex + (int) ((double) rand() / RAND_MAX * SIZE)) % SIZE;
	  array[i] = randIndex;
	}
    }
  clock_t end = clock();
  double seq = (double)(end - start); // / CLK_TCK;
  cout << "Time to generate indices randomly and access array sequentially: " << seq << endl;

  start = clock();
  for (int j = 0; j < REPS; j++)
    {
      for (int i = 0; i < SIZE; i++)
	{
	  randIndex = (randIndex + (int) ((double) rand() / RAND_MAX * SIZE)) % SIZE;
	}
    }
  end = clock();
  double nomem = (double) (end - start); // / CLK_TCK; 
  cout << "Time to generate indices randomly without array references: " << nomem << endl;

  start = clock();
  for (int j = 0; j < REPS; j++)
    {
      for (int i = 0; i < SIZE; i++)
	{
	  randIndex = (randIndex + (int) ((double) rand() / RAND_MAX * SIZE)) % SIZE;
	  array[randIndex] = randIndex;
	}
    }
  end = clock();
  double random = (double) (end - start) ;// / CLK_TCK;
  cout << "Time to generate indices randomly and access array randomly: " << random << endl;

  double seqmem = seq - nomem;
  double randmem = random - nomem;

  double pct = (randmem - seqmem) / seqmem * 100; 

  cout << "Sequential vs. random percentage faster: " << pct;
  return 0;
}
