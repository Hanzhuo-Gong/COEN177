/*
# Name: Hanzhuo Gong
# Date: 10/1/2020
# Title: Lab2 Programming in C and use of Systems Calls
# Description: This week lab includes processing and multithreading and system calls fork(), exit(), wait(), and exec()
*/

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
#include <pthread.h>


void *childThread (void* timeDelay){
    int t =* ((int*)timeDelay);
    //child process
    for(int i=0; i<100; i++){
        printf("Child Thread %d\n", i);
        usleep(t);
    }
}

/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    pthread_t parentThread;
    int t = atoi(argv[1]); // n microseconds to input from keyboard for delay
    int* timeDelay = &t;
    
    //thread, attribute, function, arugment
    if (pthread_create(&parentThread, NULL, childThread, (void*) timeDelay) != 0) {
        printf("Not able to print the thread, program exited");
        exit(1);
    }

    //parent process
    for (int i=0;i<100;i++) {
        printf("\t \t \t Parent Thread %d \n",i);
        usleep(t);
    }

    pthread_join(parentThread, (void *) timeDelay);
    
    return 0;
}
