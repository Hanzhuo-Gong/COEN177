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
#include <sys/wait.h>
#include <pthread.h>

int main (int argc, char *argv[]) {
    pid_t  pid1, pid2, pid3, pid4;

    printf("Before forking.%d \n", getpid ());

    pid1 = fork();
    pid2 = fork();

    if(!pid1){ 
        pid3 = fork(); 
    }

    if(!pid1 && !pid2 && pid3){ 
        pid4 = fork(); 
    }

    printf("new process with Child: %d, and Parent: %d \n", getpid(), getppid());

    wait(NULL);
    return 0;
    
    
}
