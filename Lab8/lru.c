/*
Name: Hanzhuo Gong
Date: 11/19/20
Title: Lab 8: Memory Management
Description: This program will find out the total page fault using least recently used algorithm
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int pageno;
    int index;
} ref_page;

int main (int argc, char *argv[]){
    int C_SIZE = atoi (argv[1]);// Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; //Cache that holes the input from test file
    
    int i, j, k, position;
    int totalFaults = 0; //track of the total page faults
    int least_recent = -1; //index to hold recently used pages
    int totalRequest = -1;
    
    for (i = 0; i < C_SIZE; i++) { //intialize cache array
      cache[i].pageno = -1;
      cache[i].index = 100;
    }
    
    while (fgets (pageCache, 100, stdin)){
        int page_num = atoi (pageCache);//stores data read as int
        totalRequest++;

        for (i = 0; i < C_SIZE; i++){
            position = 0;
            least_recent = cache[i].index;
            if (page_num == cache[i].pageno){
                for (j = 0; j < C_SIZE; j++){
                    if (cache[j].index < cache[i].index){
                        cache[j].index++;
		    }
		}
		cache[i].index = 0;
                printf("Page %d have a page fault.\n", page_num);
                break;
            }
            if (i == C_SIZE - 1){ //if it is the last then page not in cache
                for (k = 0; k < C_SIZE; k++){
                    cache[k].index++;
		}
		for (j = 0; j < C_SIZE; j++){
                    if (least_recent < cache[j].index){
                        least_recent = cache[j].index;
                        position = j;
		    }
		}
		
		cache[position].pageno = page_num; //insert new page into the least recently used position in the cache
		cache[position].index = 0; //sets that index to the most recent
		totalFaults++;
                
                printf ("Page %d have a page fault.\n", page_num);
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