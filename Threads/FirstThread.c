#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10

int vetor[SIZE];

void * function(void *arg){
    int *value = (int *)(arg);
    int i;
    if( *value == 1){
        printf("\nThread 1 executando...\n");
        for(i = 0; i < SIZE/2; i++){
            vetor[i] = 1;
            printf("T1 : Vetor[%d] = 1\n", i);            
        
            for (int i = 0; i < SIZE; i++)
            {
                printf("%d", vetor[i]);
                
            }
            printf("\n");
        }
    }
    else{
        printf("\nThread 2 executando...\n");
        for(i = SIZE; i >= SIZE/2; i--){
            vetor[i] = 2;
            printf("T2 : Vetor[%d] = 2\n", i);         
            for (int i = 0; i < SIZE; i++)
            {
                printf("%d", vetor[i]);
                
            }
            printf("\n");           
        }
        
    }
};

int main(){
    pthread_t thread1, thread2;
    int argument1 = 1;
    int argument2 = 2;
    
    pthread_create(&thread1, NULL, function, (void *)(&argument1));
    pthread_create(&thread2, NULL, function, (void *)(&argument2));

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    /*
    printf("\n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d", vetor[i]);
        
    }
    printf("\n");*/

    exit(0);
}
