
/*Michael Stamatakis
10-3-14
CPSC 3220
project 1 */

#define _GNU_SOURCE
#include <sys/ptrace.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <linux/stat.h>
#include <fcntl.h>


#define FIFO_FILE "MYTRANSFER"

int main(int argc, char *argv[]){

  //FILE *fp;
  char *args[] = {argv[1], NULL};

  //char *envp[] = {"LD_PRELOAD=./memory_shim.so", NULL};
  int num, total = 0, count = 0, i = 1;
  int fd;
  //mode_t mode = S_IFIFO;
  putenv("LD_PRELOAD=./memory_shim.so");
   
  /*while(envp[i] != NULL){
      i++;
  }
  char *environ[i+1];
  environ[i] = "LD_PRELOAD=./memory_shim.so";
  environ[i+1] = NULL;
*/
   //umask(0);
   
      
       
   pid_t pID = fork();
  //This code executed by the child
  
  if (pID == 0) //child working
  {
    //Run the process in a different environment(enable shim library)
    if((execv(args[0], args)) == -1)
      printf("ahhhhhhhh\n");
  }
  //Open the fILe to retrieve the data from the shim
  else{
        umask(0);
       mknod(FIFO_FILE, S_IFIFO|0666, 0);
       fd = open(FIFO_FILE, O_RDONLY);
        while(read(fd, &num, sizeof(int))){
        fprintf(stderr, "LEAK\t%d\n", num);
        count++;
        total += num;
     }
  fprintf(stderr, "TOTAL\t%d\t%d\n", count, total);
}
  
  
return 0;

}
