#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define BILLION  1000000000.0
#define ORDER 50;

int m = ORDER;
int n = ORDER;

int A [50][50];    
int B [50][50];
int C [50][50];

struct limitThread
{
   int limit[2];
};

struct limitThread thread1;
struct limitThread thread2;
struct limitThread thread3;
struct limitThread thread4;

struct timespec start, end;

void matrixFill(int matrix[m][n]){
    srand(time(NULL));    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = rand() % 10;       
        }        
    }
}

void displayMatrix(int matrix[m][n]){           
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {            
            printf("%d ", matrix[i][j]);            
        }    
        printf("\n");    
    }   
    printf("\n");     
}

void matrixSum(int a[m][n], int b[m][n], int c[m][n]){           
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = (a[i][j] + b[i][j]);                 
        }                
    }    
}

void releaseMatrix( int c[m][n]){   
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {     
            c[i][j] = 0; 
        }                
    }
}

void matrixSumWithThreads( void * args){          
    struct limitThread * thread = (struct limitThread *) args;
    for (int i = thread->limit[0]; i <= thread->limit[1]; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = (A[i][j] + B[i][j]);                               
        }                 
    }         
}

int main(void)
{   
    thread1.limit[0]=0;
    thread1.limit[1]=11;
    thread2.limit[0]=12;
    thread2.limit[1]=24;
    thread3.limit[0]=25;
    thread3.limit[1]=37;
    thread4.limit[0]=38;
    thread4.limit[1]=49;

    // PREENCHIMENTO
    matrixFill(A);    
    matrixFill(B);
    
    // EXIBIÇÃO
    printf("Matriz A:\n");
    displayMatrix(A);
    printf("Matriz B:\n");
    displayMatrix(B);

    // SOMA SEM THREADS
    clock_gettime(CLOCK_REALTIME, &start);    
    //matrixSum(A,B,C);
    clock_gettime(CLOCK_REALTIME, &end);
    double runtime =  (end.tv_nsec - start.tv_nsec) / BILLION;
    
    printf("Matriz C sem threads:\n");
    displayMatrix(C);
    // LIMPANDO A MATRIZ C
    releaseMatrix(C);    

    // SOMA COM THREADS
    pthread_t threads[4];    

    clock_gettime(CLOCK_REALTIME, &start);
    pthread_create(&threads[0], NULL, matrixSumWithThreads,(void *) &thread1);
    pthread_create(&threads[1], NULL, matrixSumWithThreads,(void *) &thread2);
    pthread_create(&threads[2], NULL, matrixSumWithThreads,(void *) &thread3);
    pthread_create(&threads[3], NULL, matrixSumWithThreads,(void *) &thread4);    
    clock_gettime(CLOCK_REALTIME, &end);   
    double runtimeWithThread =  (end.tv_nsec - start.tv_nsec) / BILLION;    

    for (int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
    //EXIBIÇÃO MATRIZ C
    printf("Matriz C com threads:\n");
    displayMatrix(C);

    printf("Tempo de execução sem threads:%f\n", runtime);
    printf("Tempo de execução com threads:%f\n", runtimeWithThread);

    pthread_exit(NULL);
}