#include <stdlib.h>
#include <stdio.h>


//contains no leaks

int main(int argc, char **argv)

{

    void *p1, *p2, *p3, *p4;
    void *p0;


    p0 = malloc(1);
    free(p0);

    p1 = malloc(5);

    p2 = malloc(1);

    free(p1);



    p1 = malloc(134);

    //free(p2);

    //free(p1); 

    printf("Hello World\n");

 }
