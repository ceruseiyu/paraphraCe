#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define DEFAULT_LENGTH 50;

char* markovPick(Dictionary* dict);

int main(int argc, char* argv[]) {
	if(argc > 1 && argc < 4) {
		Dictionary* dict = fileToDict(argv[1]);
		if (dict == NULL) {
			printf("Dictionary read failure!\n");
			return 0;
		}

		int length;

		if(argc == 2) {
			length = DEFAULT_LENGTH;
		} else if(argc == 3) {
			length = atoi(argv[2]);

			if(length < 1) {
				printf("Minimum number of words allowed is 1!\n");
				return 0;
			}
		}

		int i;
		Dictionary* searchDict;
		char newWord[50];
		char* text = "";
		for(i = 0; i < length; i++) {
			if(i == 0) {
				searchDict = dict;
			} else{
				searchDict = getFromDict(dict, newWord);
				if(dictLength(searchDict) < 1) {
					searchDict = dict;
				}
			}
			char* newWord = markovPick(searchDict);
			char* oldText = text;
			text = malloc(strlen(newWord)+strlen(oldText)+2);
			strcpy(text, oldText);
			strcat(text, " ");
			strcat(text, newWord);
			free(oldText);
		}

		return 0;
	}
	printf("Incorrect number of arguments!\n");
	return 0;

	//Old dictionary test code
	/*Dictionary *dict = createDict();
	addToDict(dict, "key1", "data");
	addToDict(dict, "key2", "data");
	addToDict(dict, "key3", "This one has potatoes");
	Dictionary *second_dict = getFromDict(dict, "key3");
	printf("%s\n", second_dict->start->data);
	deleteDict(dict);
	deleteDict(second_dict);

	Dictionary *third_dict = fileToDict("read.txt");
	printf("%s\n", third_dict->start->next->data);
	Dictionary *search_dict = getFromDict(third_dict, "into");
	printf("%s\n", search_dict->start->data);
	deleteDict(third_dict);
	printf("Segfault nearby!\n");
	deleteDict(search_dict);
	printf("No errors\n");*/
}

char* markovPick(Dictionary* dict) {
	srand(time(NULL));
	int length = dictLength(dict);
	int choice = rand() % length;

	DictItem* cur = dict->start;
	int i;

	for(i = 0; i < choice; i++) {
		cur = cur->next;
	}
	return cur->data;
}
