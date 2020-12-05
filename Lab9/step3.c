/*
Name: Hanzhuo Gong
Date: 12/1/20
Title: Lab 9: File Performance Measurement
Description: This program will read files and find out the time. The user will determine the size of buffer
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
	FILE *fp = fopen(argv[1], "rb");

    char buffer[atoi(argv[2])];

	while (fread(buffer, atoi(argv[2]), 1, fp) == 1){};

	fclose(fp);

	return 0;
}
