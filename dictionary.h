#ifndef DICTIONARY_DEFINED
#define DICTIONARY_DEFINED

typedef struct itemtype {
	struct itemtype* next;
	char key[50];
	char data[50];
} DictItem;

typedef struct dicttype {
	DictItem* start;
} Dictionary;

Dictionary* createDict(void);
void deleteDict(Dictionary* dict);

void addToDict(Dictionary* dict, char key[], char data[]);

int dictLength(Dictionary* dict);

Dictionary* getFromDict(Dictionary* dict, char key[]);

Dictionary* fileToDict(char file[]);
void addFileToDict(Dictionary* dict, char file[]);

#endif
