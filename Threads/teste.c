#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ORDER 12;
int m = ORDER;
int n = ORDER;

int A [12][12];    
int B [12][12];
int C [12][12];



typedef struct 
{
    int start;
    int end;
}Limit;

typedef struct 
{
    Limit limit;
}LimitThread;


LimitThread thread1;
LimitThread thread2;
LimitThread thread3;
LimitThread thread4;

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

void matrixSumWithThreads( struct limitThread thread){        
    
    for (int i = 0; i < thread.start; i++)
    {
        for (int j = 0; j < thread.end; j++)
        {
            C[i][j] = (A[i][j] + B[i][j]);                 
        }                
    }    
    
}

int main(void)
{   
    thread1.limit.start = 1;
    thread1.limit.start = 1;
    thread1.limit.end = 3;
    thread2.limit.start = 4;
    thread2.limit.end = 6;
    thread3.limit.start = 7;
    thread3.limit.end = 9;
    thread4.limit.start = 10;
    thread4.limit.end = 12;

    // PREENCHIMENTO
    matrixFill(A);    
    matrixFill(B);
    
    // EXIBIÇÃO
    printf("Matriz A:\n");
    displayMatrix(A);
    printf("Matriz B:\n");
    displayMatrix(B);

    // SOMA SEM THREADS    
    matrixSum(A,B,C);
    
    // SOMA COM THREADS
    releaseMatrix(C);    

    //Limits[0] = 1;
    //Limits[1] = 3;
      
    pthread_t threads[4];
    
    pthread_create(&threads[0], NULL, matrixSumWithThreads, &thread1.limit);
    pthread_create(&threads[1], NULL, matrixSumWithThreads, &thread2.limit);
    pthread_create(&threads[2], NULL, matrixSumWithThreads, &thread3.limit);
    pthread_create(&threads[3], NULL, matrixSumWithThreads, &thread4.limit);    

    
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);
    
    printf("Matriz C:\n");
    displayMatrix(C);

    pthread_exit(NULL);
}