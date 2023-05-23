// The program initializes a character string and creates as many
// threads as there are characters in the string.  Each thread is 
// assigned a character, which it displays.

#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

struct data_t
{
    char s;
};

void *print_char(void *thread_arg)
{
    struct data_t *data;
    data = (struct data_t *) thread_arg;

    printf("%c\n", data->s);
    pthread_exit(NULL);
}

int main()
{
    int rc, i;
    void* status;
    char output[] = "Hello World";
    pthread_t threads[strlen(output)];
    struct data_t data[strlen(output)];

    for (i = 0; i < strlen(output); i++)
    {
        data[i].s = output[i];
        rc = pthread_create(&threads[i], NULL, print_char, (void *) &data[i]);
        if (rc)
        {
            printf("BAD\n");
        }
    }

    for (i = 0; i < strlen(output); i++)
    {
        rc = pthread_join(threads[i], &status);
    }
}
