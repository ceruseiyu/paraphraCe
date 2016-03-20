#ifndef DICTIONARY_DEFINED
#define DICTIONARY_DEFINED

typedef struct itemtype {
	struct itemtype* next;
	char *key;
	char *data;
} DictItem;

typedef struct dicttype {
	DictItem* start;
} Dictionary;

Dictionary* createDict(void);
void addToDict(Dictionary* dict, char key[], char data[]);
int dictLength(Dictionary* dict);
void deleteDict(Dictionary* dict);

#endif