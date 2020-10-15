/*
# Name: Hanzhuo Gong
# Date: 10/15/20
# Title: Lab4 Developing multithread appplications
# Description: multiply matrices using multi-threading
*/


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

//Set up the size of N,M,L
#define N 3
#define M 3
#define L 3
#define Length 3 

//Set up the matrix and thread length
double matrixA[N][M];
double matrixB[M][L];
double matrixC[N][L];
pthread_t threads[Length];


//Matrices multiplication, will be calling by the pthread_create
void* matrices_multi(void* arg) {
    int i = (int)arg;
    for (int j = 0; j < L; j++){
        double temp = 0;
        for (int k = 0; k < M; k++){
            temp += matrixA[i][k] * matrixB[k][j];
        }
    matrixC[i][j] = temp;
    }

}

//Create multithreadsing to do the multiplication
void multithread_multi() {
    for (int i = 0; i < Length; i++){
        pthread_create(&threads[i], NULL, matrices_multi, i);
        printf("Hello thread from %d: \n", i);
    }
    for (int i = 0; i < Length; i++){
        pthread_join(threads[i], NULL);
        printf("Thread %d returned \n", i);
    }    
}

//Print the matrices out
void print_matrices(){
    printf ("-------------Matrix A--------------- \n");
    for (int i = 0; i < Length; i++){
        for (int j = 0; j < Length; j++){
            printf("%f \t ", matrixA[i][j]);
        }
        printf("\n");
    }
    
    printf ("-------------Matrix B--------------- \n");
    for (int i = 0; i < Length; i++){
        for (int j = 0; j < Length; j++){
            printf("%f \t ", matrixB[i][j]);
        }
        printf("\n");
    }
    
    
    printf ("-------------Matrix C--------------- \n");
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%f \t ", matrixC[i][j]);
        }
        printf("\n");
    }
    
}


int main() {
    srand(time(NULL));

    //Set up random number from 1 - 10 into the matrix A & B
    for (int i = 0; i < Length; i++) {
        for (int j = 0; j < Length; j++) {
            matrixA[i][j] = rand() % 10;
        }
    }

	for (int i = 0; i < Length; i++) {
		for (int j = 0; j < Length; j++) {
			matrixB[i][j] = rand() % 10;
        }
    }

    multithread_multi();
    print_matrices();

}
