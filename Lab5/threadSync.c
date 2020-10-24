/*
# Name: Hanzhuo Gong
# Date: 10/22/20 
# Title: Lab5 - ynchronization using semaphores, lock, and condition variables.
# Description: This program will just run and observe the result

*/

/*
//Observation: threads may not entering in order, like thread 2 can enter before thread 1. 
Thread may enter into critical section before the display to show the previous threads return.
Multiple threads can be return at one time, and multiple threads may display to enter the critical section

ThreadSync.c often return the threads after another threads enter the critical section, while threadHello.c will
return threads at the same time.
*/

// Thread Sychronization

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 

#define NTHREADS 10
pthread_t threads[NTHREADS];
sem_t *mutex; 

void* go(void* arg) { 
  sem_wait(mutex); //entry section
  printf("Thread %d Entered Critical Section..\n", (int)arg); //critical section 
   sleep(1); 
  sem_post(mutex); //exit section 
  return (NULL);
} 

int main() { 
mutex = sem_open("mutex", O_CREAT, 0644, 1);
static int i;
for (i = 0; i < NTHREADS; i++)  
   pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
for (i = 0; i < NTHREADS; i++) {
   pthread_join(threads[i],NULL);
   printf("\t\t\tThread %d returned \n", i);
   }
printf("Main thread done.\n");
sem_unlink("mutex"); 
return 0; 
} 
