/* Histogram generator for words in a piece of text

Copyright 2014 Nathan Lintz

*/
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <fcntl.h>
#include <string.h>

/* struct representing a word's frequency

   used for the hashtable since hashtables need a pointer
   , not just an integer
*/
typedef struct{
	int value;
} Value;

/* Constructor for Value struct

	returns a pointer to a Value struct
*/
Value *newValue()
{
	Value *value = malloc(sizeof(Value));
	if (value == NULL) {
		fprintf(stderr, "%s\n", "malloc failed");
		exit(1);
	}
	value->value = 1;
	return value;
}

/* Free method for a Value struct
	
	*value: pointer to Value struct to free
*/
void freeValue(Value *value)
{
	free(value);
}

/* struct representing a word and its freqeuncy in the text
	used to store the histogram in an array

*/
typedef struct{
	char *word;
	int frequency;
} WordFrequency;

/* Constructor for WordFrequency struct

	*word: pointer to a string
	frequency: integer for the frequency of the word

	returns a pointer to a WordFrequency struct
*/
WordFrequency *newWordFrequency(char *word, int frequency)
{
	WordFrequency *wordFrequency = malloc(sizeof(WordFrequency));
	if (wordFrequency == NULL) {
		fprintf(stderr, "%s\n", "malloc failed");
		exit(1);
	}
	wordFrequency->word = strdup(word);
	wordFrequency->frequency = frequency;
	return wordFrequency;
}

/* Free method for a WordFrequency struct
	
	*wordFrequency: pointer to WordFrequency struct to free
*/
void freeWordFrequency(WordFrequency *wordFrequency)
{
	free(wordFrequency->word);
	free(wordFrequency);
}

/* prints the fields of a WordFrequency struct

	*wordFrequency: WordFrequency struct to print

*/
void printWordFrequency(WordFrequency *wordFrequency)
{
	printf("Word: %s  Frequency: %d\n", wordFrequency->word, 
		wordFrequency->frequency);
}

/* converts a word to lower case
	used so that histogram won't count upper and lower case words as 
		different strings

	*word: pointer to string that will be converted to lower case
*/
void toLower(char* word)
{
	int i;
	for (i=0; i<strlen(word); i++)
	{
		word[i] = g_ascii_tolower(word[i]);
	}
}

/* strips the punctuation off of a word

	**word: pointer to a string pointer for the word that will be
		stripped
*/
void stripPunctuation(char **word)
{

	GError *err = NULL;
	GMatchInfo *matchInfo;
	GRegex *regex;

	regex = g_regex_new ("(^[a-z]*'*[a-z]*)", 0, 0, &err);
	if (err) {
		fprintf (stderr, "Regex failed: %s\n", err->message);
		exit(1);
	}
	g_regex_match (regex, *word, 0, &matchInfo);

	gchar *result = g_match_info_fetch (matchInfo, 0);
	if (result == NULL)
	{
		fprintf (stderr, "Regex failed: %s\n", err->message);
		exit(1);
	}

	*word = result;

	g_regex_unref(regex);
}

/* Checks if a word is actually a word (e.g. **** will return 0 
	characters and shouldn't be counted as a word)

	returns 0 if it is a word, returns 1 otherwise
*/
int isWord(char *word)
{
	if (strlen(word) == 0)
	{
		return 0;
	}
	return 1;
}

/* Adds a word to a histogram and increments its count

	*hist: GHashTable for the histogram
	*line: word you want to add the the histogram

*/
void addWordToHistogram(GHashTable *hist, char *line)
{
	char *word = line;
	toLower(word);
	stripPunctuation(&word);
	if (!isWord(word))
	{
		return;
	}

	// If the word exists in the hashtable, increment its count
	if (g_hash_table_lookup(hist, word))
	{
		Value *val = (Value*)g_hash_table_lookup(hist, word);
		Value *new_val = newValue();
		new_val->value = val->value + 1;
		g_hash_table_replace(hist, word, new_val);
		freeValue(val);
	}

	// Otherwise, insert the word with a count of 1
	else
	{
		Value *count = newValue();
		g_hash_table_insert(hist, word, count);
	}
}

/* Converts  a file into a histogram of word frequency

	*fileName: string of the filename that should be converted
		into a histogram

	returns a GHashTable pointer of the word frequency histogram
*/
GHashTable* getHistogramFromFile(char *fileName) 
{
	GHashTable *hist = g_hash_table_new(g_str_hash, g_str_equal);
	FILE *file = fopen(fileName, "r");
	char word[80];

	while(fscanf(file, "%s", word) == 1)
	{
		addWordToHistogram(hist, word);
	}
	fclose(file);
	return hist;
}

/* builds a list of WordFrequency structs for
	all word-frequency pairs in the histogram

	*hist: histogram that will be converted into an array

	returns a GList object holding WordFrequency structs for the given
		histogram
*/
GList *getWordFreqs(GHashTable *hist)
{
	GList *keys = g_hash_table_get_keys(hist);
	GList *wordFreqs = NULL;

	for(; keys!=NULL; keys=keys->next)
	{
		Value *val = g_hash_table_lookup(hist, keys->data);
		WordFrequency *wordFrequency = newWordFrequency(keys->data, 
			val->value);
		wordFreqs = g_list_append(wordFreqs, wordFrequency);
	}	
	g_list_free(keys);
	return wordFreqs;
}

/* comparator function for the g_list_sort function
	sorts the histogram by frequency

*/
gint compareFrequency(gconstpointer a, gconstpointer b)
{
	WordFrequency *wordFreq1 = (WordFrequency *)a;
	WordFrequency *wordFreq2 = (WordFrequency *)b;
	return (wordFreq1->frequency - wordFreq2->frequency);
}

/* prints all the words and their associated frequency in 
	a histgram

	*hist: GHashTable of the histogram

*/
void printHistogram(GHashTable *hist)
{
	GList *keys = g_hash_table_get_keys(hist);
	for(; keys!=NULL; keys=keys->next)
	{
		Value *val = g_hash_table_lookup(hist, keys->data);
		printf("Word: %s  Frequency: %d\n", keys->data, val->value);
	}
	g_list_free(keys);
}

/* prints all the words and their associated frequency in 
	a histgram in order of frequeny

	*hist: GHashTable of the histogram

*/
void printSortedHistogram(GHashTable *hist)
{
	GList *wordFreqs = getWordFreqs(hist);
	wordFreqs = g_list_sort(wordFreqs, compareFrequency);
	while(wordFreqs)
	{
		WordFrequency *wf = wordFreqs->data;
		printWordFrequency(wf);
		wordFreqs = g_list_next(wordFreqs);
	}
	g_list_free(wordFreqs);
}

/* prints a sorted histogram of the words in CurlytopsAtSunsetBeach

*/
int main()
{
	printSortedHistogram(getHistogramFromFile("CurlytopsAtSunsetBeach.txt"));
	return 0;
}