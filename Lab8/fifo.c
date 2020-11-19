/*
Name: Hanzhuo Gong
Date: 11/19/20
Title: Lab 8: Memory Management
Description: This program will find out the total pages error using FIFO
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct {
    int pageno;
} ref_page;


int main (int argc, char *argv[]) {
    int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file
    
    int i;
    int totalFaults = 0; // keeps track of the total page faults
    int placeInArray = 0;
    int totalRequest = -1;
    
    for (i = 0; i < C_SIZE; i++){//initialise cache array
        cache[i].pageno = -1;
    }
    
    while (fgets (pageCache, 100, stdin))  {
        int page_num = atoi (pageCache); // stores number read from file as an int
        totalRequest++;

        for (i = 0; i < C_SIZE; i++) {
            if (cache[i].pageno == page_num) {// page is cached, go to the next one
                break;
	    }
	    if (i == C_SIZE - 1) { //if iterator reaches last entry, don't cache the page
                printf ("Page: %d has a page fault\n", page_num);
                cache[placeInArray].pageno = page_num;
                totalFaults++;
                
                placeInArray++; //Need to keep the value within the cacheSize
                if (placeInArray == C_SIZE) {
                    placeInArray = 0;
		        }
	    }
	}
    }
    totalFaults--;
    printf ("Total Page Faults: %d\n", totalFaults);
    printf ("Total Request: %d\n", totalRequest);
    int hitNumber = totalRequest - totalFaults;
    printf("Hit Number is: %d\n", hitNumber);
    float hitRate = hitNumber / ((double)totalRequest);
    printf("hit rate is: %.5f\n", hitRate);
    return 0;
}
