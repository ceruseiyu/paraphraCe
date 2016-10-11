#ifndef PARAPHRACE_DICTIONARY
#define PARAPHRACE_DICTIONARY
#include "ntarray.h"

typedef struct itemtype {
	struct itemtype* next;
	char* data;
	int weight;
} DictItem;

void initDict();

DictItem* createDict(char* d, int w);

int addToDict(DictItem** dict, char* d, int w);

void deleteDict(DictItem** d);

int getDictWeight(DictItem* d);

char* pickRandWord(DictItem* d);

int calcWeight(int w);

DictItem* buildDict(char** words, NTArray* keys);

#endif
