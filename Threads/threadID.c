#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * printThreadsID(void *threadId){
    printf("Eu sou a Thread com TID %lu, e %lu.\n", pthread_self(), gettid());    
}

int main(void)
{
    int num_threads;
    printf("Digite o número de Threads desejadas: ");
    scanf("%d", &num_threads);

    pthread_t threads[num_threads];
    int t;
    for (t = 0; t < num_threads; t++)
    {
        pthread_create(&threads[t], NULL, printThreadsID, NULL);   
    }

    for (t = 0; t < num_threads; t++)
    {
        pthread_join(threads[t], NULL);
    }
    pthread_exit(NULL);
}