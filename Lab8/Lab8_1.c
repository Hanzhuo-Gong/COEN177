/*
Name: Hanzhuo Gong
Date: 11/19/20
Title: Lab 8: Memory Management
Description: This program will generate 10 random numbers from 1 - 1000
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h> 

/*
int maxLength = 10;
int capNumber = 1000;
int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer [sizeof(int)];
    int i;
    fp = fopen("testInput.txt", "w");
    for (i=0; i<maxLength; i++){
        sprintf(buffer, "%d\n", rand()%capNumber);
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
} */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateRandomNumber (int min, int max){
    int randonNumber = max - min + 1;
    return rand() % randonNumber + min;
}

int main(){
    FILE *fp;
    int i;
    fp = fopen("testInput.txt","w");

    int maxLength = 10;
    int minNumber = 1;
    int maxNumber = 1000;
    srand(time(0));
    for (i = 0; i < maxLength; i++){
        int tempRandomNumber = generateRandomNumber(minNumber,maxNumber);
        fprintf(fp,"%d \n",tempRandomNumber);
    }
    fclose(fp);
    
}

