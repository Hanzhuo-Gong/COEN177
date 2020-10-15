/*
# Name: Hanzhuo Gong
# Date: 10/8/2020
# Title: Pthreads and inter-process Communication 
# Description: Lab is practing using pipe and Pthreads and inter-process Communication.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 
#include <sys/types.h> 
#include <sys/ipc.h>

// main
int main(int argc,char *argv[]){
  int  fds[2];
   char buff[60];
   int count;
   int i;
   pipe(fds);   

  if (fork()==0){
      printf("\nProducer1 on the upstream end of the pipe -> %d arguments \n",argc);
      close(fds[0]);
      dup2(fds[1],1);
      execlp("ls", "ls", 0);
      exit(0);
  }

  else if(fork()==0){
      printf("\nProducer2 on the upstream end of the pipe\n");
      close(fds[0]);
      for(i=0;i<3;i++){
        write(fds[1],"Hi from Producer\n", strlen("Hi from Producer\n"));
      }
      exit(0);
  }

  else if(fork()==0){
      printf("\nReader on the downstream end of the pipe \n");
      close(fds[1]);
      while((count=read(fds[0],buff,60))>0){
          for(i=0;i<count;i++){
              write(1,buff+i,1);
              write(1," ",1);	
            }
        printf("\n");
        }
  }
  else{     
   	close(fds[0]);
    close(fds[1]);
    wait(0);
    wait(0);
  }
  return 0;
}
