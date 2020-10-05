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

int main(int argc, char *argv[]) {
    pid_t  pid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\n Before forking.\n");
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    } 

    else if(pid == 0){

        for (i=0;i<100;i++) {
            printf("Child process %d\n",i);
            usleep(n);
        }
        execlp("/bin/ls", "ls", NULL);
    }

    else {
        wait (NULL);
        printf("Child Complete\n");
        // Parent process
        for (i=0;i<100;i++) {
            printf("\t \t \t Parent Process %d \n",i);
            usleep(n);
        }
        exit(0);
    }
    return 0;
}