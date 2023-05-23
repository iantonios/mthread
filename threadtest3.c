#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void* print(void *arg)
{
    int* data;
    data = (int *) arg;

    printf("%d\n", *data);
    pthread_exit(NULL);
}

int main()
{
    int i;
    pthread_t threads[5];

    for (i = 0; i < 5; i++)
        pthread_create(&threads[i], NULL, print, &i);
        

    for (i = 0; i < 5; i++)
        pthread_join(threads[i], NULL);
}
