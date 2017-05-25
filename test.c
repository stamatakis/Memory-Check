#include <stdlib.h>
#include <stdio.h>



//contains 1 leak
int main(int argc, char **argv)
{
	void *p1;
      
      //printf("in the test\n");
 
       
        p1 = malloc(1365);
       // printf("in test %p", p1); 
	//free(p1);
      //  printf("%p", p1);
return 0;
}
