/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5
#define LENGTH_ERROR_MESSAGE 100
char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
    	if (strstr(tracks[i], search_for)) {
    	    printf("Track %i: '%s'\n", i, tracks[i]);
    	}
    }
}

//
// Helpers for find_track_regex
// Compiles the regular expression and checks for errors
int compile_regex(regex_t *compiled_regex, char *pattern)
{
    int status = regcomp(compiled_regex, pattern, 0);
    if (status)
    {
        char error_message[LENGTH_ERROR_MESSAGE];
        regerror(status, compiled_regex, error_message, LENGTH_ERROR_MESSAGE);
        printf (
            "Regex is wrong, enter a correctly formatted" \
                " regular expression:  \n %s\n", error_message);
        exit(1);
    }
    return 0;
}

int match_regex(regex_t *regex, char *text)
{
    int match_status = regexec(regex, text, 0, NULL, 0);
    if (match_status)
    {
        return 0;
    }
    return 1;
}
// Finds all tracks that match the given pattern.
//
// Prints track number and title.
void find_track_regex(char pattern[])
{
    // TODO: fill this in
    regex_t regex;
    int i;
    
    compile_regex(&regex, pattern);

    for (i=0; i<NUM_TRACKS; i++) {
        int match = match_regex(&regex, tracks[i]);
        if (match)
        {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
	    *ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];

    /* take input from the user and search */
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    rstrip(search_for);
    // find_track(search_for);
    find_track_regex(search_for);

    return 0;
}
