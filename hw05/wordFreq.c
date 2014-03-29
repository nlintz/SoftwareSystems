#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <fcntl.h>
#include <string.h>

//TODO: Add Error Handling, comments, manage memory, header file

typedef struct{
	int value;
} Value;

Value *newValue()
{
	Value *value = malloc(sizeof(Value));
	value->value = 1;
	return value;
}

void freeValue(Value *value)
{
	free(value);
}

typedef struct{
	char *word;
	int frequency;
} WordFrequency;

WordFrequency *newWordFrequency(char *word, int frequency)
{
	WordFrequency *wordFrequency = malloc(sizeof(WordFrequency));
	wordFrequency->word = strdup(word);
	wordFrequency->frequency = frequency;
	return wordFrequency;
}

void freeWordFrequency(WordFrequency *wordFrequency)
{
	free(wordFrequency->word);
	free(wordFrequency);
}

void printWordFrequency(WordFrequency *wordFrequency)
{
	printf("Word: %s  Frequency: %d\n", wordFrequency->word, wordFrequency->frequency);
}

void toLower(char* word)
{
	int i;
	for (i=0; i<strlen(word); i++)
	{
		word[i] = g_ascii_tolower(word[i]);
	}
}

void stripPunctuation(char **word)
{

	GError *err = NULL;
	GMatchInfo *matchInfo;
	GRegex *regex;

	regex = g_regex_new ("([a-z]*)", 0, 0, &err);   
	g_regex_match (regex, *word, 0, &matchInfo);
 
	gchar *result = g_match_info_fetch (matchInfo, 0);

	*word = result;

	g_regex_unref(regex);
}

int isWord(char *word)
{
	int i;
	for(i=0; i<strlen(word); i++)
	{
		if (!g_ascii_isalpha(word[i]))
		{
			return 0;
		}
	}
	return 1;
}

void addWordToHistogram(GHashTable *hist, char *line)
{
	char *word = line;

	toLower(word);
	stripPunctuation(&word);
	if (!isWord(word))
	{
		return;
	}
	if (g_hash_table_lookup(hist, word))
	{
		Value *val = (Value*)g_hash_table_lookup(hist, word);
		Value *new_val = newValue();
		new_val->value = val->value + 1;
		g_hash_table_replace(hist, word, new_val);
		freeValue(val);
	}
	else
	{
		Value *count = newValue();
		g_hash_table_insert(hist, word, count);
	}
}

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

GList *getWordFreqs(GHashTable *hist)
{
	GList *keys = g_hash_table_get_keys(hist);
	GList *wordFreqs = NULL;

	for(; keys!=NULL; keys=keys->next)
	{
		Value *val = g_hash_table_lookup(hist, keys->data);
		WordFrequency *wordFrequency = newWordFrequency(keys->data, val->value);
		wordFreqs = g_list_append(wordFreqs, wordFrequency);
	}	
	g_list_free(keys);
	return wordFreqs;
}

gint compareFrequency(gconstpointer a, gconstpointer b)
{
	WordFrequency *wordFreq1 = (WordFrequency *)a;
	WordFrequency *wordFreq2 = (WordFrequency *)b;
	return (wordFreq1->frequency - wordFreq2->frequency);
}

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

int main()
{
	printSortedHistogram(getHistogramFromFile("CurlytopsAtSunsetBeach.txt"));
	return 0;
}