/*
Name: Hanzhuo Gong
Date: 12/1/20
Title: Lab 9: File Performance Measurement
Description: User will determine which files to read, the size of buffer, and number of pthread (number of copy).
The program will return the time.
*/

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

char fileName[20]; //max length of the file
int bufferSize;

void *threadFunction(void *arg) {
    FILE *fp;
    FILE *fo;
    char outputFile[20]; //output max length of the file
    char buffer[bufferSize];

    sprintf(outputFile, "step5_%d.txt", (int)arg);
    
    fp = fopen(fileName, "r");
    fo = fopen(outputFile, "w");

    while(fread(buffer, sizeof(char), 1, fp) > 0) {;
        fwrite(buffer, sizeof(char), 1, fo);
    }
    fclose(fp);
    fclose(fo);
    
    return NULL;
}

int main (int argc, char *argv[]){

    bufferSize = atoi(argv[2]);  //buffersize
    int NTHREADS = atoi(argv[3]);  //number of thread

    pthread_t threads[NTHREADS];
    strcpy(fileName, argv[1]); //file name
    
    int i;
    for (i = 0; i < NTHREADS; i++)  {
        pthread_create(&threads[i], NULL, threadFunction, (void *)(size_t)i);
	}
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i],NULL);
    }

    return 0;
}
