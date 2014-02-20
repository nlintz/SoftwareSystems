/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

char *tracks[] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};

/* Returns a heap-allocated string that contains the strings 
   from the given array, joined up with no spaces between.
*/
char *strjoin(char *array[], int n)
{
    // TODO: fill this in
    int length = 0;
    int j = 0;
    
    for (int i=0; i<n; i++)
    {
        length = length + strlen(tracks[i]);
    }

    char *buffer = malloc(sizeof(char)*(length + 1));
    buffer[0] = '\0';

    for (int i=0; i<n; i++)
    {
        strcpy(buffer+j, tracks[i]);
        int len = strlen(tracks[i]);
        j = j+len;
    }

    return buffer;
}


int main (int argc, char *argv[])
{
    char *s = strjoin(tracks, 5);
    printf("%s\n", s);
    return 0;
}
