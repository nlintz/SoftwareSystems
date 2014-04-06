/* Hello world program for glib

Copyright 2014 Nathan Lintz

*/
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Unit test to verify that glist insert is working
    
    *list: list to be tested
*/
void unitTest(GList *list)
{
	assert(g_list_first(list)->data == "Nathan!");
	assert(g_list_next(g_list_first(list))->data == "Mikey!");
	assert(g_list_next(g_list_next(
        g_list_first(list)))->data == "Hello World!");
}

/* Creates a list and appends three values to it, then prints the appended
    values in order

*/
int main(){
	GList* list = NULL;
    list = g_list_append(list, "Nathan!");
    if (list == NULL)
    {
        fprintf(stderr, "%s\n", "append failed");
        exit(1);
    }
    list = g_list_append(list, "Mikey!");
    if (list == NULL)
    {
        fprintf(stderr, "%s\n", "append failed");
        exit(1);
    }
    list = g_list_append(list, "Hello World!");
    if (list == NULL)
    {
        fprintf(stderr, "%s\n", "append failed");
        exit(1);
    }
    
    GList* currentList = NULL;
    currentList = g_list_first(list);
    if (currentList == NULL)
    {
        fprintf(stderr, "%s\n", "g_list_first failed");
        exit(1);
    }
    int i=0;
    while (currentList)
    {
    	printf("Item %d: %s\n", i++, currentList->data);
    	currentList = g_list_next(currentList);
    }

    unitTest(list);

	return 0;
}