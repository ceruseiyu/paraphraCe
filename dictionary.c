#include "dictionary.h"
#include <stdlib.h>

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
		return;
	}

	item->key = key;
	item->data = data;

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
	int i;
	DictItem* cur;

	if(len == -1) {
		return;
	}

	if(len == 0) {
		free(dict);
		return;
	}

	cur = dict->start;
	for(i = 0; i < len; i++) {
		DictItem* save = cur;
		if(cur->next == NULL) {
			free(cur);
			break;
		} 
		cur = cur->next;
		free(save);
	}

	free(dict);
}
