/*Michael Stamatakis
10-3-14
CPSC 3220
project 1 */

#define _GNU_SOURCE
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <errno.h>
#include <string.h>



typedef struct node{
   long data;
   struct node *next;
   int count;
}node;

int main(int argc, char **argv) {

  int status, i = 0, found = 0;
  long rax;
  node *temp = NULL;
  node *temp2 = NULL;
  node *start = NULL;
  node *one_ahead = NULL;
  FILE *fp = NULL;
  //Allocate node for start of linked list
  start = (node *) malloc(sizeof(node));
  start->next = NULL;
  //Prepare args for exec function
  char *args[] = {argv[1], argv[2], NULL};
  char *newenviron[] = { NULL };
 
      //Parse the arguments separating any args that have multiple commands 
      args[0] = strtok(argv[1], " \0");
      for(i= 1; args[i] != NULL; i++)
         args[i] = strtok(NULL, " \0");
             
     
      
  
    pid_t child = fork();
    if (child == 0) {

        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        //Send the file or command arguments to the newenviron to be processed        
        execvpe(args[0], args, newenviron);

   } else {
       //This option is used to only trace system calls not user calls
       ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);
       while(1) {
          wait(&status);
          if(WIFEXITED(status))
              break;
                      
          found = 0;          

          rax = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * ORIG_RAX, NULL);
      
          ptrace(PTRACE_SYSCALL, child, NULL, NULL);
          //This code increments the count on a sys_call 
          temp = start->next;
           while (temp != NULL) {

             if (temp->data != rax){
                temp = temp->next;
             }   
             else if (temp->data == rax){
                temp->count += 1;
                temp = temp->next;
                found = 1;
             }   
         }
         //This segment adds a unique sys_call to the linked list
         if(found == 0){
           temp = start;
           one_ahead = start;
           one_ahead = one_ahead->next;
           while (temp->next != NULL && one_ahead->data < rax){ 
               temp = temp->next;
               one_ahead = one_ahead->next;
           }         

           temp2 = (struct node *) malloc(sizeof (node));
           temp2->next = one_ahead;
           temp2->data = rax;
           temp2->count = 1;
           temp->next = temp2;
         }
    }
 

}

   //Open file, iterate the list and print the data to the file
   temp = start;
   fp = fopen(argv[2], "w");
   if(fp == NULL)
   {
      printf("error\n");
      exit(0);
   }
   temp = temp->next;
   while(temp != NULL)
   {
      if(temp->count > 1)
         temp->count = temp->count/2;
      fprintf(fp, "%ld  %d \n", temp->data, temp->count);
      temp = temp->next;
   }
   fclose(fp);
   return 0; 
}  
  
  
  
  
  
