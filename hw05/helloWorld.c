#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void unitTest(GList *list)
{
	assert(g_list_first(list)->data == "Nathan!");
	assert(g_list_next(g_list_first(list))->data == "Mikey!");
	assert(g_list_next(g_list_next(g_list_first(list)))->data == "Hello World!");
}

int main(){ //TODO - Add error checking
	GList* list = NULL;
    list = g_list_append(list, "Nathan!");
    list = g_list_append(list, "Mikey!");
    list = g_list_append(list, "Hello World!");
    
    GList* currentList = NULL;
    currentList = g_list_first(list);
    int i=0;
    while (currentList)
    {
    	printf("Item %d: %s\n", i++, currentList->data);
    	currentList = g_list_next(currentList);
    }

    unitTest(list);

	return 0;
}