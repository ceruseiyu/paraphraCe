#include "dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

void initDict() {
	srand(time(NULL));
}

DictItem* createDict(char* d, int w) {
	DictItem* dict = malloc(sizeof(DictItem));
	if(dict == NULL) {
		return NULL;
	}

	dict->data = malloc(strlen(d));
	if(dict->data == NULL) {
		free(dict);
		return NULL;
	}
	strcpy(dict->data, d);

	dict->weight = w;

	return dict;
}

int addToDict(DictItem* dict, char* d, int w) {
	DictItem* item = createDict(d, w);
	if(item == NULL) {
		return -1;
	}

	if(dict == NULL) {
		dict = item;
		return 1;
	}

	if(dict->next != NULL) {
		item->next = dict->next;
	}

	dict->next = item;
	return 1;
}

void deleteDict(DictItem* d) {
	if(d == NULL) {
		return;
	}

	if(d->next == NULL) {
		free(d);
		return;
	}
	DictItem* cur;

	cur = d;
	while(cur != NULL) {
		DictItem* save = cur;
		cur = cur->next;
		free(save);
	}
}

int getDictWeight(DictItem* d) {
	if(d == NULL) {
		return -1;
	}

	DictItem* cur = d->next;
	int count = d->weight;
	while(cur != NULL) {
		count = count + cur->weight;
		cur = cur->next;
	}
	return count;
}

char* pickRandWord(DictItem* d) {
	if(d == NULL) {
		return NULL;
	}

	int weight = getDictWeight(d);
	int ran = rand() % weight;

	if(d->next == NULL) {
		return d->data;
	}

	DictItem* cur = d;
	int curWeight = 0;
	while(cur->next != NULL) {
		curWeight += cur->weight;
		if(curWeight >= ran) {
			return cur->data;
		}
		cur = cur->next;
	}
	return cur->data;
}

int ntLen(char** array) {
	if(array == NULL) {
		return -1;
	}

	int i = 0;
	while(array[i] != NULL) {
		i++;
	}
	return i;
}

int calcWeight(int w) {
	return w * 2;
}

char** fileToArray(char* file) {
	FILE* fileptr = fopen(file, "r");
	if(fileptr == NULL) {
		return NULL;
	}

	char** words = malloc(sizeof(char*));
	if(words == NULL) {
		return NULL;
	}
	int wordCount = 0;

	char* curWord = malloc(1);
	if(curWord == NULL) {
		free(words);
		return NULL;
	}
	int charCount = 0;
	char newChar;

	while((newChar = fgetc(fileptr)) != EOF) {
		if(newChar == ' ' || newChar == '\n') {
			if(charCount > 0) {
				words[wordCount] = curWord;
				wordCount++;
				curWord = realloc(curWord, charCount+1);
				curWord[charCount] = '\0';
				words = realloc(words, sizeof(char*) * (wordCount + 1));
				curWord = malloc(1);
				charCount = 0;
			}
		} else{
			curWord = realloc(curWord, charCount+1);
			if(curWord == NULL) {
				return NULL;
			}
			curWord[charCount] = newChar;
			charCount++;
		}
	}
	fclose(fileptr);

	if(charCount > 1) {
		words[wordCount] = curWord;
		wordCount++;
		words = realloc(words, sizeof(char*) * (wordCount + 1));
	}
	words[wordCount] = NULL; // Terminate array with NULL

	return words;
}

DictItem* buildDict(char** words, char** keys) {
	int keyLen = ntLen(keys);
	if(keyLen < 1) {
		return NULL;
	}

	int wordLen = ntLen(words);
	if(wordLen < 1) {
		return NULL;
	}

	DictItem* dict;

	int i;
	int j;
	int weight;
	for(i = 0; i < wordLen; i++) {
		if(strcmp(words[i], keys[0]) == 0) {
			weight = 1;
			j = 1;
			while(j < keyLen && j <= i) {
				if(strcmp(words[i - j], keys[j]) == 0) {
					weight = calcWeight(weight);
				} else {
					break;
				}
				j++;
			}
			if(addToDict(dict, words[i], weight) == -1) {
				return NULL;
			}
		}
	}

	return dict;
}
