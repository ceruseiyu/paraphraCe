#include "dictionary.h"
#include "ntarray.h"
#include "paraphrace.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
  char** test = fileToArray("maine.txt");
  char** key = {"test", "test2", NULL};
  DictItem dict = buildDict(test, key);
}

/*char* markovPick(Dictionary* dict);

int main(int argc, char* argv[]) {
	srand(time(NULL));
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
			strcpy(newWord, markovPick(searchDict));
			char* oldText;
			oldText = text;
			text = malloc(strlen(newWord)+strlen(oldText)+2);
			strcpy(text, oldText);
			strcat(text, " ");
			strcat(text, newWord);
			//I'll fix that eventually
			//free(oldText);
		}
		printf("%s\n",text);
		return 0;
	}
	printf("Incorrect number of arguments!\n");
	return 0;
}

char* markovPick(Dictionary* dict) {
	int length = dictLength(dict);
	int choice = rand() % length;

	DictItem* cur = dict->start;
	int i;

	for(i = 0; i < choice; i++) {
		cur = cur->next;
	}
	return cur->data;
}
*/
