/*
Name: Hanzhuo Gong
Date: 12/1/20
Title: Lab 9: File Performance Measurement
Description: This program will read files and find out the time.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[]){
    char buffer[10000]; 
    FILE *fp;
    fp = fopen(argv[1], "rb"); 
    while (fread(buffer, sizeof(buffer), 1, fp)){
    }

    fclose(fp);
    
	return 0;
}