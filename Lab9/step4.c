/*
Name: Hanzhuo Gong
Date: 12/1/20
Title: Lab 9: File Performance Measurement
Description: This program will read files and write the data to a output file call step4.txt, also display the time
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
	FILE *fp = fopen(argv[1], "rb");
	FILE *fo = fopen("step4.txt", "wb"); //output of the file

	char buffer[atoi(argv[2])];

	while (fread(buffer, atoi(argv[2]), 1, fp)){
		fwrite(buffer, atoi(argv[2]), 1, fo);	
	};

	fclose(fp);
	fclose(fo);

	return 0;
}