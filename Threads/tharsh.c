#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ORDER 12;
int m = ORDER;
int n = ORDER;

int A [12][12];    
int B [12][12];
int C [12][12];

struct limitThread
{
   int start;
   int end;
};

struct limitThread thread1;
struct limitThread thread2;
struct limitThread thread3;
struct limitThread thread4;


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

void matrixSumWithThreads(struct limitThread thread){        
     printf("thread.Start: %d\n", thread.start);
    printf("thread.End: %d\n", thread.end);
    for (int i = thread.start; i < thread.end; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = (A[i][j] + B[i][j]);                 
              
        }  
        //printf("\n");                  
    }    
    //printf("\n");  
}

int main(void)
{   
    thread1.start = 1;
    thread1.end = 3;
    thread2.start = 4;
    thread2.end = 6;
    thread3.start = 7;
    thread3.end = 9;
    thread4.start = 10;
    thread4.end = 12;

    printf("thread1.limit[1]:%d\n", thread1);
    printf("thread1.limit[1]:%d\n", thread2);
    printf("thread3.limit[1]:%d\n", thread3);
    printf("thread4.limit[1]:%d\n", thread4);
    

    // PREENCHIMENTO
    matrixFill(A);    
    matrixFill(B);
    
    // EXIBIÇÃO
    printf("Matriz A:\n");
    displayMatrix(A);
    printf("Matriz B:\n");
    displayMatrix(B);

    // SOMA SEM THREADS    
    //matrixSum(A,B,C);
    
    // SOMA COM THREADS
    //releaseMatrix(C);    

    //Limits[0] = 1;
    //Limits[1] = 3;
      
    pthread_t threads[4];
    
    pthread_create(&threads[0], NULL, matrixSumWithThreads, &thread1);
    pthread_create(&threads[1], NULL, matrixSumWithThreads, &thread2);
    pthread_create(&threads[2], NULL, matrixSumWithThreads, &thread3);
    pthread_create(&threads[3], NULL, matrixSumWithThreads, &thread4);     

    
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);
    
    printf("Matriz C:\n");
    displayMatrix(C);

    pthread_exit(NULL);
}