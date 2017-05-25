/*Michael Stamatakis
10-3-14
CPSC 3220
project 1 */


#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/reg.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ptrace.h>
#include <fcntl.h>

#define FIFO_FILE "MYTRANSFER"


//void __attribute__((constructor)) init(void);
//void __attribute__((destructor)) cleanup(void);
void begin (void) __attribute__((constructor));
void end (void) __attribute__((destructor));

void (*original_free)(void *ptr) = NULL;
void *(*original_malloc)(size_t size) = NULL;
void *(*original_printf)(const char *format, ...) = NULL;
 
struct node
{
    int leaksize;
    void *addrptr;
    struct node *next;
 };
 
struct node *start; 

//Destructor
void end(void)
{  
   int fd;
   struct node *temp = start; 
   int num;
  //mode_t mode = S_IFIFO;

   //fflush(NULL);
   //umask(0);
   //mknod(FIFO_FILE, S_IFIFO|0666, 0);
  fd = open(FIFO_FILE, O_WRONLY);

   temp = temp->next;
   while(temp->next != NULL){

      num = temp->leaksize;  
      write(fd, &num, sizeof(int));
      //fflush(NULL);
      temp = temp->next;
   }
      num = temp->leaksize;  
      write(fd, &num, sizeof(int));
  
  
}
//Initialize the original functions to make use of them
void begin(void)
{
   if(original_malloc == NULL)
   {
      original_malloc = dlsym(RTLD_NEXT, "malloc");
   }
   if(original_free == NULL)
   {
      original_free = dlsym(RTLD_NEXT, "free");
   }
   if(original_printf == NULL){
      original_printf = dlsym(RTLD_NEXT, "printf");
   }

   start = original_malloc(sizeof(struct node));
   start->next = NULL;
}
//This malloc function will keep track of the allocated memory
//as well as actually allocating it.
int printf(const char *format, ...){

return 0;

}

void *malloc(size_t size)
{ 
   
   void *ptr = original_malloc(size);
   struct node *temp = start;
   struct node *temp2;
   
   if(temp->next == NULL)
   {}  
   else
   {
      while(temp->next != NULL)
      temp = temp->next;
   }
   temp2 = original_malloc(sizeof(struct node));
   temp2->leaksize = (int)size;
   temp2->next = NULL;
   temp2->addrptr = ptr;
   temp->next = temp2; 
  
   return ptr;
}
//This function will keep track of the freed memory as well as free in it.   
void free(void *ptr)
{
  struct node *temp = start;
  struct node *temp2 = NULL;
  struct node *to_delete = NULL;

  while (temp->addrptr != ptr)
  {  
    temp2 = temp;   
    temp = temp->next;
    
  }
  to_delete = temp;
  temp2->next = to_delete->next;
  original_free(to_delete);

   original_free(ptr);
   
}




