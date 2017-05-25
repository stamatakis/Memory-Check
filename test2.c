#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


	typedef struct rec
	{
    		int i;
    		float PI;
    		char A;
	}RECORD;

	
//contains 1 leak
int main(int argc, char **argv)
{
	/*void *p1, *p2, *p3, *p4;
      fprintf(stderr, "in the test\n");
 
      
	p1 = malloc(1345);
	p2 = malloc(2);
	free(p1);

	p1 = malloc(134);
	free(p2);

	p3 = malloc(1);
	p4 = malloc(981);
	//free(p4);
	free(p3);*/

    		RECORD *ptr_one;

    		ptr_one = (RECORD *) malloc (sizeof(RECORD));

    		(*ptr_one).i = 10;
    		(*ptr_one).PI = 3.14;
    		(*ptr_one).A = 'a';

    		printf("First value: %d\n",(*ptr_one).i);
    		printf("Second value: %f\n", (*ptr_one).PI);
    		printf("Third value: %c\n", (*ptr_one).A);

    		//free(ptr_one);

return 0;
}
