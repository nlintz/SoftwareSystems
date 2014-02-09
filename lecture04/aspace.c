/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int global;

void swag(){
	int i;
	printf("Address of a local variable is %p\n", &i);
}

int main ()
{
    int local = 5;
    void *p = malloc(128);
    int swoopArray[3];
    swoopArray[0] = 1;
    int *array = malloc(10*sizeof(int));

   	void *p2 = malloc(25);
   	void *p3 = malloc(25);

    printf ("Address of main is %p\n", main);
    printf ("Address of global is %p\n", &global);
    swag();
    printf ("Address of local is %p\n", &local);
    printf ("Address of p is %p\n", p);
    printf ("Address of p2 is %p\n", p2);
    printf ("Address of p3 is %p\n", p3);
    printf ("Address of array is %p\n", array);
    
    return 0;
}

// Order lowest - highest
// main = code segment 
// globals
// stack

// heap is somewhere?