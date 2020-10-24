/*
# Name: Hanzhuo Gong
# Date: 10/22/20 
# Title: Lab5 - ynchronization using semaphores, lock, and condition variables.
# Description: This program solve the problem between producer and customer using semaphore

*/


// Thread Sychronization

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>

#define NTHREADS 10
pthread_t threads[NTHREADS];
sem_t *mutex;
sem_t *empty; 
sem_t *full; 

int buffer[10];
int in;
int out;

void* producer (void* arg) { 
 do {
    sem_wait(empty); 
    sem_wait(mutex); //entry section

    int index = (rand()%10); //generate a random index to the buffer
    buffer[in] = index;
    printf("Produced item: buffer[%d]:  %d\n", buffer[in], in); //critical section 
    in = (in+1)%10; //Increment to the next buffer

    sem_post(mutex);
    sem_post(full); //exit section

 } while(1);

  return (NULL);
}


void* consumer (void* arg) { 
 do {
    sem_wait(full); 
    sem_wait(mutex); //entry section
  
    printf("\t Consumed item: buffer[%d] : %d\n", buffer[out], out); //critical section 
    out = (out+1)%10;
    sleep(1); 

    sem_post(mutex); 
    sem_post(empty); //exit section
  
 } while(1);

  return (NULL);
} 

void semUnlink(int sigtype){   
    sem_unlink("mutex");
    sem_unlink("empty");    
    sem_unlink("full");    
    printf("\nDone with terminating.\n");   

    exit(0);
}

int main() { 

    //for ctrl+c
    signal(SIGINT,semUnlink);

    pthread_t producer_thread[10];									
    pthread_t consumer_thread[10];

    //initialize mutex, empty, full
    mutex = sem_open("mutex", O_CREAT, 0644, 1);
    empty = sem_open("empty", O_CREAT, 0644, 10);
    full = sem_open("full", O_CREAT, 0644, 0);

    //the label of each producer & consumer
    int a[10] = {0,1,2,3,4,5,6,7,8,9};

    //create 10 threads for producer and consumer
    for(int i = 0; i < 10; i++) {
            pthread_create(&producer_thread[i], NULL, producer, (void *)&a[i]);
    }

    for(int i = 0; i < 10; i++) {
        pthread_create(&consumer_thread[i], NULL, consumer, (void *)&a[i]);
    }

    //Wait for producer and consumer to finish
    for(int i = 0; i < 10; i++) {
        pthread_join(producer_thread[i], NULL);
    }

    for(int i = 0; i < 10; i++) {
        pthread_join(consumer_thread[i], NULL);
    }

    //unlink mutex, empty, full. since this is in a do while function, code below shouldn't run.
    sem_unlink("mutex");
    sem_unlink("empty");    
    sem_unlink("full");    
 
    printf("Main thread done.\n");

    return 0;
} 


