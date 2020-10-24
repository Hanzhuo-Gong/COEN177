/*
# Name: Hanzhuo Gong
# Date: 10/22/20 
# Title: Lab5 - ynchronization using semaphores, lock, and condition variables.
# Description: This program solve the problem between producer and customer using condition variable

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
pthread_mutex_t mutex;
pthread_cond_t empty;
pthread_cond_t full;

int buffer[10];
int buffer_item_counter;
int maxSize = 10;
int in;
int out;

void* producer(void* arg) { 
 do {
    pthread_mutex_lock(&mutex); //entry section
  
    while (buffer_item_counter >= maxSize){
        pthread_cond_wait(&empty, &mutex);
    }
  
    int index = (rand()%10);
    buffer[in] = index;
    printf("Produced item: buffer[%d]:  %d\n", buffer[in], in); //critical section
    in = (in+1)%10; //Increment to the next buffer
    buffer_item_counter++; //Increment the coutner
    
    pthread_cond_signal(&full);
    pthread_mutex_unlock(&mutex);
  
 } while(1);

  return (NULL);
} 

void* consumer(void* arg) { 
 do {
    pthread_mutex_lock(&mutex); //entry section

    while (buffer_item_counter == 0) {
        pthread_cond_wait(&full, &mutex);
    }
    printf("\t Consumed item: buffer[%d] : %d\n", buffer[out], out); //critical section
    buffer_item_counter--;
    sleep(1); 
    out = (out+1)%10;
  
    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mutex);
  
 } while(1);
  
  return (NULL);
}

void condDestroyer(int sigtype){   
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);  
    printf("\nDone with terminating.\n");   

    exit(0);
}

int main() { 
    buffer_item_counter = 0;

    //for ctrl+c
    signal(SIGINT,condDestroyer);

    pthread_t producer_thread[10];									
    pthread_t consumer_thread[10];
    
    //initialize mutex, empty, full
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&full, NULL);
 
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
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);
    printf("Main thread done.\n");
    return 0; 
} 



