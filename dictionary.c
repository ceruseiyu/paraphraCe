#include "dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Dictionary* createDict() {
	Dictionary *dict = malloc(sizeof(Dictionary));

	if(dict == NULL ) {
		return NULL;
	}

	return dict;
}

void addToDict(Dictionary* dict, char key[], char data[]) {
	DictItem* item = malloc(sizeof(DictItem));

	if(item == NULL) {
		return;DICTIONARY_DEFINED
	}

	strcpy(item->key, key);
	strcpy(item->data, data);

	if(dict->start != NULL) {
		item->next = dict->start;
	}

	dict->start = item;
}

int dictLength(Dictionary* dict) {
	int count;
	DictItem* cur;

	if(dict == NULL) {
		return -1;
	}

	if(dict->start == NULL) {
		return 0;
	}

	cur = dict->start;
	count = 1;
	while(cur->next != NULL) {
		count++;
		cur = cur->next;
	}

	return count;
}

void deleteDict(Dictionary* dict) {
	int len = dictLength(dict);
	DictItem* cur;

	if(len == -1) {
		return;
	}

	if(len == 0) {
		free(dict);
		return;
	}

	cur = dict->start;
	while(cur->next != NULL) {
		DictItem* save = cur;
		cur = cur->next;
		free(save);
	}

	free(dict);
}

Dictionary* getFromDict(Dictionary* dict, char key[]) {
	if(dict == NULL) {
		return NULL;
	}

	Dictionary* newDict = createDict();
	if(newDict == NULL) {
		return NULL;
	}

	DictItem* cur = dict->start;
	while(cur->next != NULL) {
		if(strcmp(cur->key, key) == 0) {
			addToDict(newDict, cur->key, cur->data);
		}
		cur = cur->next;
	}
	return newDict;
}

void addFileToDict(Dictionary* dict, char file[]) {
	FILE *fileptr;
	fileptr = fopen(file, "r");
	if(fileptr == NULL) {
		return;
	}

	char check;
	char curWord[50], lastWord[50];
	int count = 0;
	while((check = fgetc(fileptr)) != EOF) {
		if(count >= 49) {
			break;
		}

		if(check == '\n'||check == ' ') {
			curWord[count] = '\0';
			printf("%s\n",curWord);
			count = 0;
			if(lastWord[0] != (char)0) {
				addToDict(dict, lastWord, curWord);
			}
			strcpy(lastWord, curWord);
		} else{
			//printf("%s\n",curWord);
			curWord[count] = check;
			count++;
		}
	}
}

Dictionary* fileToDict(char file[]) {
	Dictionary* dict = createDict();
  if(dict == NULL) {
		return NULL;
	}
	addFileToDict(dict, file);
	return dict;
}
