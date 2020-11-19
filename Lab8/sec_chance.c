/*
Name: Hanzhuo Gong
Date: 11/19/20
Title: Lab 8: Memory Management
Description: This program will find out the total page faults using the 2nd chance
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct{
    int pageno;
    int index;
} ref_page;

int main (int argc, char *argv[]){
    int C_SIZE = atoi (argv[1]); //Size of Cache passed by user
    ref_page cache[C_SIZE];	//Cache that holes the input from test file

    int n;
    int notfound = 0;
    int totalFaults = 0;
    int totalRequest = -1;
    
    for (n = 0; n < C_SIZE; n++){ //initialize cache array
        cache[n].pageno = -1;
        cache[n].index = 0;
    }
    
    char cache2[1000];  //secondary cache to store input from the text
    int k = 0; //track entry in the cache and replace
    
    while (fgets (cache2, 100, stdin))  {
        int page_num = atoi (cache2);
        int i;
        totalRequest++;
        
        for (i = 0; i < C_SIZE; i++) {
            if (page_num == cache[i].pageno){
                cache[i].index = 1;
                notfound = 0;
                break;
	    }
	    if (i == C_SIZE - 1) {//if i reach the last entry without any matching, go to the next loop
                notfound = 1;
	    }
	}
    
	if (notfound == 1) {
            int j;
            for (j = k; j < C_SIZE; j++) {
                if (cache[j].index == 1){ //if reference is 1, set to 0 and skip it
                    cache[j].index = 0;
                    k++;
                    if (k == C_SIZE){ //to wrap around if the last entry gets a second chance
                        k = 0;
                        j = -1;
		    }
                }else{
                    cache[j].pageno = page_num;	//inserts new page into the cache
                    cache[j].index = 0;
                    totalFaults++;
                    printf ("Page %d have a page fault.\n", page_num);//display the error
                    k++;
                    if (k == C_SIZE){ //wraps around
                        k = 0;
		    }
		    break;
		}
	    }
	}
    }
    totalFaults--;
    printf ("Total Page Faults: %d \n", totalFaults);
    printf ("Total Request: %d\n", totalRequest);
    int hitNumber = totalRequest - totalFaults;
    printf("Hit Number is: %d\n", hitNumber);
    float hitRate = hitNumber / ((double)totalRequest);
    printf("hit rate is: %.5f\n", hitRate);
    return 0;
}