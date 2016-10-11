#include "dictionary.h"
#include "ntarray.h"
#include "macro.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

void initDict() {
	srand(time(NULL));
}

DictItem* createDict(char* d, int w) {
	DictItem* dict = malloc(sizeof(DictItem));
	CHECK(dict != NULL, NULL);

	dict->data = malloc(strlen(d));
	if(dict->data == NULL) {
		free(dict);
		return NULL;
	}
	strcpy(dict->data, d);

	dict->weight = w;
	dict->next = NULL;

	return dict;
}

int addToDict(DictItem** dict, char* d, int w) {
	DictItem* item = createDict(d, w);
	CHECK(item != NULL, -1);

	if(*dict == NULL) {
		*dict = item;
		return 1;
	}

	if((*dict)->next != NULL) {
		item->next = (*dict)->next;
	}

	(*dict)->next = item;
	return 1;
}

void deleteDict(DictItem** d) {
	CHECKVOID(*d != NULL);

	if((*d)->next == NULL) {
		free(*d);
		return;
	}
	DictItem* cur;

	cur = *d;
	while(cur != NULL) {
		DictItem* save = cur;
		cur = cur->next;
		free(save);
	}
	*d = NULL;
}

int getDictWeight(DictItem* d) {
	CHECK(d != NULL, -1);

	DictItem* cur = d->next;
	int count = d->weight;
	while(cur != NULL) {
		count = count + cur->weight;
		cur = cur->next;
	}
	return count;
}

char* pickRandWord(DictItem* d) {
	CHECK(d != NULL, NULL);

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
			printf("%d%s\n",ran,cur->data);
			return cur->data;
		}
		cur = cur->next;
	}
	printf("%d%s\n",ran,cur->data);
	return cur->data;
}

int calcWeight(int w) {
	return w * 2;
}

DictItem* buildDict(char** words, NTArray* keys) {
	int keyLen = ntLen(keys->data);
	CHECK(keyLen > 0, NULL);

	int wordLen = ntLen(words);
	CHECK(wordLen > 0, NULL);

	DictItem* dict = NULL;
	int i;
	int j;
	int weight;
	for(i = 0; i < wordLen; i++) {
		if(strcmp(words[i], keys->data[0]) == 0) {
			weight = 1;
			j = 1;
			while(j < keyLen && j <= i) {
				if(strcmp(words[i - j], keys->data[j]) == 0) {
					weight = calcWeight(weight);
				} else {
					break;
				}
				j++;
			}
			CHECK(addToDict(&dict, words[i], weight)!= -1, NULL);
		}
	}

	return dict;
}
